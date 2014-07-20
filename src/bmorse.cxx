// ----------------------------------------------------------------------------
// bmorse.c --  bayesian morse code decoder 
//
// Copyright (C) 2012-2014   Mauri Niininen, AG1LE
//
// This file is part of Bayesian Morse code decoder   
//	  Parts of this is adapted from FLDIGI  cw.cxx 
// 	  Copyright (C) 2006-2010  Dave Freese, W1HKJ
//    Parts of this is adapted from sndfile-spectrogram 
//	  Copyright (C) 2007-2009 Erik de Castro Lopo <erikd@mega-nerd.com>
//
// bmorse is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// bmorse is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with bmorse.  If not, see <http://www.gnu.org/licenses/>.
// ---------------------------------------------------------------------------

#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <sndfile.h>
#include <fftw3.h>
#include "complex.h"
#include "window.h"
#include "bmorse.h"
#include "fftfilt.h"

#define ARRAY_LEN(x)    ((int) (sizeof (x) / sizeof (x [0])))
#define MAX(x,y)                ((x) > (y) ? (x) : (y))
#define MIN(x,y)                ((x) < (y) ? (x) : (y))
#define	MIN_WIDTH	640
#define	MIN_HEIGHT	480
#define	MAX_WIDTH	65536
#define	MAX_HEIGHT	4096
#define TWOPI	2.0*M_PI
#define DEC_RATIO  20
typedef int ftnlen;

/*
{	int print_variables ;  	// FALSE
	int print_symbols; 		// FALSE 
	int print_speed; 		// FALSE 
	int process_textfile;	// FALSE
	int print_text;			// FALSE
	int print_xplot;		// FALSE
	int width; 				// 8192
	int speclen ;			// 32 
	int bfv;				// 0 
	double frequency;		// 600 
	double sample_duration; // 5
	double sample_rate; 	// 4000
	double delta;			// 10.0
	double amplify;			// 0.0
	int fft;				// 0 
	int agc;				// 0 
	int speed;				// 20
	int dec_ratio;			// 20   (4000 Hz/ 20 => 200 Hz ) decimation ratio  samplerate / bayes decoder rate  
*/
PARAMS params = { 
FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 8192, 32, 0, 600, 5, 4000, 10.0, 0.0, 0, 0,20,20};

fftfilt			*FFT_filter; 


double filter(double a, int len)
{
	static double  in[2000];
	static double  out;
	static int	i, pint;
	static int empty = 1;

        if ((len == 0) || (len ==1)) {
                return a;
        }
        if (empty) {
                empty = 0;
                for (i = 0; i < len; i++) {
                        in[i] = a;
                }
                out = a * len;
                pint = 0;
                return a;
        }
        out = out - in[pint] + a;
        in[pint] = a;
        if (++pint >= len) pint = 0;
        return out / len;
}

double decayavg(double average, double input, double weight)
{
	if (weight <= 1.0) return input;
	return input * (1.0 / weight) + average * (1.0 - (1.0 / weight));
}

sf_count_t sfx_mix_mono_read_double (SNDFILE * file, double * data, sf_count_t datalen)
{
	SF_INFO info ;

#if HAVE_SF_GET_INFO
	/*
	**	The function sf_get_info was in a number of 1.0.18 pre-releases but was removed
	**	before 1.0.18 final and replaced with the SFC_GET_CURRENT_SF_INFO command.
	*/
	sf_get_info (file, &info) ;
#else
	sf_command (file, SFC_GET_CURRENT_SF_INFO, &info, sizeof (info)) ;
#endif

	if (info.channels == 1)
		return sf_read_double (file, data, datalen) ;

	static double multi_data [2048] ;
	int k, ch, frames_read ;
	sf_count_t dataout = 0 ;

	while (dataout < datalen)
	{	int this_read ;
		
		this_read = MIN (ARRAY_LEN (multi_data) / info.channels, datalen) ;

		frames_read = sf_readf_double (file, multi_data, this_read) ;
		if (frames_read == 0)
			break ;

		for (k = 0 ; k < frames_read ; k++)
		{	double mix = 0.0 ;

			for (ch = 0 ; ch < info.channels ; ch++)
				mix += multi_data [k * info.channels + ch] ;
			data [dataout + k] = mix / info.channels ;
			} ;

		dataout += this_read ;
		} ;

	return dataout ;
} /* sfx_mix_mono_read_double */


static void read_mono_audio (SNDFILE * file, sf_count_t filelen, double * data, int datalen, int indx, int total)
{
	sf_count_t start;
	
	memset (data, 0, datalen * sizeof (data [0])) ;
	
		
	start = (indx * filelen) / total - datalen / 2 ;

	if (start >= 0)
		sf_seek (file, start, SEEK_SET) ;
	else
	{	start = -start ;
		sf_seek (file, 0, SEEK_SET) ;
		data += start ;
		datalen -= start ;
		} ;

	sfx_mix_mono_read_double (file, data, datalen) ;

	return ;
} /* read_mono_audio */

double calc_magnitude (const double * freq, int freqlen, double * magnitude)
{
	int k ;
	double max = 0.0 ;

	for (k = 1 ; k < freqlen / 2 ; k++)	{	
		magnitude[k] = sqrt (freq [k] * freq [k] + freq [freqlen - k - 1] * freq [freqlen - k - 1]) ;
		max = MAX (max, magnitude [k]) ;
	} ;
	magnitude [0] = 0.0 ;

	return max ;
} /* calc_magnitude */


#define PEAKS_SIZE 2000

struct PEAKS {
	double 	mx[PEAKS_SIZE];
	double 	mn[PEAKS_SIZE];
	int 	mxpos[PEAKS_SIZE];
	int 	mnpos[PEAKS_SIZE];
	int 	mxcount;
	int		mncount;
	double	delta;
};


//	peak_detect() detects peaks in a vector  *******************************************************************************
//	Finds the local maxima and minima ("peaks") in the vector V.
//  A point is considered a maximum peak if it has the maximal
//  value, and was preceded (to the left) by a value lower by DELTA.

void peak_detect(double *v, int length, struct PEAKS *p)
{

	int i, lookformax; 
	double value, mn,mx;
	int mnpos,mxpos;

	p->mxcount = 0;
	p->mncount = 0;

	  
	if (p->delta <= 0) {
		printf ("%s : line %d :Input argument DELTA must be positive.\n", __FILE__, __LINE__) ;
			exit (1) ;
	}

	mn = 1.0/0.0; 
	mx = -1.0/0.0;
	mnpos = -10000; mxpos = 10000;
	lookformax = 1;
	
	for (i=0; i< length; i++) {
		  value = v[i];
		  if (value > mx) {mx = value; mxpos = i;}
		  if (value < mn) {mn = value; mnpos = i;}
		  
		  if (lookformax){
				if (value < mx-p->delta) {
				  p->mx[p->mxcount] = mx;
				  p->mxpos[p->mxcount] = mxpos;
				  p->mxcount += 1;
				  mn = value; mnpos = i;
				  lookformax = 0;
				};
			} else {
				if (value > mn+p->delta) {
				  p->mn[p->mncount] = mn;
				  p->mnpos[p->mncount] = mnpos;
				  p->mncount += 1;
				  mx = value; mxpos = i;
				  lookformax = 1;
				};
			}
	}
}

void apply_window (double * data, int datalen)
{
	double window [10 * MAX_HEIGHT] ;
	static int window_len = 0 ;
	int k ;

	if (window_len != datalen)
	{
		window_len = datalen ;
		if (datalen > ARRAY_LEN (window))
		{
			printf ("%s : datalen >  MAX_HEIGHT\n", __func__) ;
			exit (1) ;
		} ;

		calc_kaiser_window (window, datalen, 20.0) ;
//		calc_nuttall_window (window, datalen);
	} ;

	for (k = 0 ; k < datalen ; k++)
		data [k] *= window [k] ;

	return ;
} /* apply_window */



void interp_spec (float * mag, int maglen, const double *spec, int speclen)
{
	int k, lastspec = 0 ;

	mag [0] = spec [0] ;

	for (k = 1 ; k < maglen ; k++) {
		double sum = 0.0 ;
		int count = 0 ;

		do	{	
			sum += spec [lastspec] ;
			lastspec ++ ;
			count ++ ;
			}
		while (lastspec <= ceil ((k * speclen) / maglen)) ;

		mag [k] = sum / count ;

	} ;

	return ;
} /* interp_spec */

void process_data(double x)
{
	static int sample_counter = 0;
	static float rn = .1f;
	static int retstat, n1, n2;
	static long int imax, xhat, elmhat;
	static float pmax, zout, spdhat, px;
	static int init = 1,pinit = 1; 
	static double agc_peak = 0.0;
	static morse* mp; 
	char buf [12];
	
	
	if (init) {
		mp = new morse();
		init = 0;
	}

	if (params.amplify != 0.0) 
		x = params.amplify * x; 

	if (params.agc) {

		if (x > agc_peak)
			agc_peak = decayavg(agc_peak, x, 10);
		else
			agc_peak = decayavg(agc_peak, x, 800);
	
		if (agc_peak != 0.0){
			x /= agc_peak;
			x = clamp(x, 0.0, 1.0);
			}
		else
			x = 0.0;
	}

	
	if (params.print_xplot)
		printf("\n%f",x);

	if (params.print_variables && pinit) { //print variable labels first (only once) iu
		printf("\nretstat\timax\telmhat\txhat\tx\tpx\tpmax\tspdhat\trn\tzout\tp1\tp2\tp3\tp4\tp5\tp6\n");
		pinit = 0; 
	}

	mp->noise_(x, &rn, &zout);

	zout = clamp(zout, 0.0, 1.0);
	memset(buf,0,sizeof(buf));

	retstat = mp->proces_(zout, rn, &xhat, &px, &elmhat, &spdhat, &imax, &pmax, buf);
	if (params.print_variables) 
		printf("\n%d\t%d\t%d\t%d\t%f\t%f\t%f\t%f\t%f\t%f",(int)retstat,(int)imax,(int)elmhat,(int)xhat,x,px,pmax,spdhat,rn,zout); 
	if (params.print_speed) 
		printf("\n%f", spdhat);
	if (params.print_text) 
		printf("%s",buf);
	

}

int rx_FFTprocess(const double *buf, int len)
{
	complex  z, *zp;
	int n,i,speclen,Hz;
	static int smpl_ctr = 0;
	static double FFTvalue,FFTphase =0.0; 

/*	fftw_plan plan; 
	double single_max,noise_sum,sig_sum,Nrms,Srms,fbin;
	double time_domain[1024];
	double freq_domain[1024];
	double single_mag_spec[1024];
	struct PEAKS p;

	p.delta = params.delta;
	speclen = 512;

	for (i=0; i< len; i++) 
		time_domain[i] = buf[i];
	
	
	plan = fftw_plan_r2r_1d (2*speclen, time_domain, freq_domain, FFTW_R2HC, FFTW_MEASURE | FFTW_PRESERVE_INPUT) ;
	if (plan == NULL)
	{	printf ("%s : line %d : create plan failed.\n", __FILE__, __LINE__) ;
		exit (1) ;
		} ;
	

//	calculate FFT 
	apply_window (time_domain, 2*speclen) ;
	fftw_execute (plan) ;
	single_max = calc_magnitude (freq_domain, 2*speclen, single_mag_spec) ;

// find peaks in power spectrum  Ps
//			- Fpeak = peak_detect(Ps,delta)
//			- integrate Fpeak over N timeslots  (64 .. 128 ms ? ) 

	peak_detect(single_mag_spec, 2*speclen, &p);

	// print found freq peaks - only once
	if (0 ) {
		for (i=0; i <p.mxcount; i++) {
			Hz = (p.mxpos[i]*(4000/2))/(speclen);
			printf("peak[%d]:%f\tHz:%d\tmaxcount:%d\n",p.mxpos[i],p.mx[i],Hz,p.mxcount);
		}
	}
	//params.frequency = Hz;
/*
		- calculate noise floor level  
			 - noisemax => frequency bins from 1 to first detected peak 
			 - fbin  => freq bin size 
			 - Pxx  => power spectrum  512
				=>   Nrms = sqrt(sum(Pxx(1:noisemax)*fbin)) / sqrt(f(noisemax));
			- update delta & threshold 

	fbin = 4000./1024;
	noise_sum = 0.;
	for (i = 10; i<p.mxpos[0]-10; i++) {
		noise_sum += single_mag_spec[i]; 
	}
//	printf("\n noise_sum:%f bins:%d",noise_sum,p.mxpos[0]-10);
	Nrms = sqrt(noise_sum* fbin)/sqrt(Hz);

	sig_sum = 0.;
	for (i = p.mxpos[0]-5; i< p.mxpos[0]+5; i++) {
		sig_sum += single_mag_spec[i];
	}	
	Srms = sqrt (sig_sum*fbin);
//	printf("\n SNR = %5.2f S:%f ss:%f N:%f  Hz:%d", Srms/Nrms, Srms, sig_sum,Nrms,Hz); 
		- calculate SNR of found Fpeak
			-  integrate Srms = sqrt(sum(Fpeak +/- 10 Hz)*fbin)) 
		 	- SNR = Srms / Nrms 
*/

	while (len-- > 0) {
		// convert CW signal to baseband 	
		z = complex ( *buf * cos(FFTphase), *buf * sin(FFTphase) );
		FFTphase += TWOPI * params.frequency / params.sample_rate;
		if (FFTphase > M_PI)
			FFTphase -= TWOPI;
		else if (FFTphase < M_PI)
			FFTphase += TWOPI;

		buf++;
		
		// run low pass filter 
		n = FFT_filter->run(z, &zp); // n = 0 or filterlen/2
		
		if (!n) continue;

		for (int i = 0; i < n; i++) {



	// update the basic sample counter used for morse timing
				++smpl_ctr;
				if (smpl_ctr % params.dec_ratio) continue; // decimate by DEC_RATIO		

	// demodulate
				FFTvalue = zp[i].mag();
	// run envelope filter 
				FFTvalue = filter(FFTvalue,params.bfv);

				process_data(FFTvalue);

		} // for (i =0; i < n ...

	} //while (len-- > 0)

}



void decode_sndfile (SNDFILE *infile, SF_INFO info)
{


	double time_domain [10 * MAX_HEIGHT] ;
	double freq_domain [10 * MAX_HEIGHT] ;
	double single_mag_spec [5 * MAX_HEIGHT] ;
//	static float mag_spec [MAX_WIDTH][MAX_HEIGHT] ;
	struct PEAKS p;

	static int once=1;
	
	fftw_plan plan ;
	double x, max_mag = 0.0 ;
	int width = 8192, height= 32, w, speclen ;
 
	int f,sr,sc =0,c,num_items,num,i,j;
	double *buf, *bp;
	int bfv;   // bit filter value 
	
	//  speclen should be multiple of 2^n but also keep time resolution < 5 ms 
	//  for 48Khz sampling rate speclen 64 represents 2.6667 ms sample time??
	//

			
	/* Print some of the info, and figure out how much data to read. */
    f = info.frames;
    sr = info.samplerate;
    params.sample_rate = info.samplerate;
 	params.dec_ratio = info.samplerate / BAYES_RATE; 
    c = info.channels;
    num_items = f*c;

 	

 	// bit filter based on 10 msec rise time of CW waveform or manually set 
 	if (params.bfv !=0)
 		bfv = params.bfv;
 	else
	// bit filter based on 10 msec rise time of CW waveform
		bfv = (int)(sr * .010 / params.dec_ratio); 		
// 		bfv = sr/100;   //  Samplerate / 100 => bfv value required for 10 msec rise time

	speclen = params.speclen; 
	p.delta = params.delta; 	
	//params.sample_duration= (2.0*speclen*1000.0)/((double)16*sr);
    
    if (!params.print_text) {
		printf("# frames=%d\n",f);
		printf("# channels=%d\n",c);
		printf("# samplerate=%d\n",sr);
		printf("# dec_ratio=%d\n",params.dec_ratio);
		printf("# bit filter=%d\n",bfv);
		printf("# num_items=%d\n",num_items);
		printf("# sample_duration=%f\n",params.sample_duration);
		printf("# params.bitfilter=%d\n",params.bfv);
		printf("# speed(WPM):%d\n",params.speed);
		printf("# FFT filter bandwidth %f\n",2.0* params.speed/1.2);
 	}
   
  
	if (params.fft) {
			// speclen = 16; 			// 16 ok for 4000 Hz test60db.wav @16384 width
			 //  64  for 48000 Hz capture.wav @4096 w or 2048
			width = params.width; 

			if (2 * speclen > ARRAY_LEN (time_domain))
			{	printf ("%s : 2 * speclen > ARRAY_LEN (time_domain)\n", __func__) ;
				exit (1) ;
				} ;
		//	fprintf(stderr,"\nsamplerate:%d\nwidth:%d\nspeclen:%d\nsample duration:%f\n", samplerate,width, speclen,params.sample_duration);

			plan = fftw_plan_r2r_1d (2 * speclen, time_domain, freq_domain, FFTW_R2HC, FFTW_MEASURE | FFTW_PRESERVE_INPUT) ;
			if (plan == NULL)
			{	printf ("%s : line %d : create plan failed.\n", __FILE__, __LINE__) ;
				exit (1) ;
				} ;



			for (w = 0 ; w < width ; w++)
			{	double single_max ;

				read_mono_audio (infile, info.frames, time_domain, 2 * speclen, w, width) ;
				apply_window (time_domain, 2 * speclen) ;
				fftw_execute (plan) ;

				single_max = calc_magnitude (freq_domain, 2 * speclen, single_mag_spec) ;			
		
				// print one FFT row - just to check
/*
				if (1) { //was once 
					printf("\nmax:%f", single_max);
					for (int i=0; i< speclen; i++) 
						printf("\n%f",single_mag_spec[i]);
					once=0;
				}	

	
				// detect peaks in the FFT spectrum 
				peak_detect(single_mag_spec, speclen, &p);
*/			
				// print found freq peaks - only once
				if (once ) {
					for (i=0; i <p.mxcount; i++) {
						int Hz = (p.mxpos[i]*(sr/2))/(speclen);
						printf("peak[%d]:%f\tHz:%d\tmaxcount:%d\n",p.mxpos[i],p.mx[i],Hz,p.mxcount);
					}
					once=0;
				}	

	

				max_mag = MAX (max_mag, single_max) ;
				single_max = filter(single_max,bfv); 
			//	process_data(single_max/max_mag); // decode Morse code here 
		
			//	interp_spec (mag_spec [w], height, single_mag_spec, speclen) ;
			} ;

			fftw_destroy_plan (plan) ;

	} else {  // use  FLDIGI CW.CXX  FFT filtering 

			//overlap and add filter length should be a factor of 2
			// low pass implementation
			int FilterFFTLen = 4096;
			FFT_filter = new fftfilt((params.speed)/(1.2 * params.sample_rate), FilterFFTLen);
		  
			/* Allocate space for the data to be read, then read it. */
			buf = (double *) malloc((num_items+512)*sizeof(double));
			if (buf == 0) {
				printf ("%s : line %d :out of memory.\n", __FILE__, __LINE__) ;
				exit (1) ;
			}
			memset(buf,0,(num_items+512)*sizeof(double));
			bp = buf; 

			num = sf_read_double(infile,bp,num_items);
//			printf("Read %d items\n",num);

			for (i = 0; i < num_items; i += 512){
					rx_FFTprocess(bp, 512);
					bp += 512; 
			}
			free(buf); 
	}
	 

	
	
}

void
process_sndfile (char * filename)
{
	SNDFILE *infile ;
	SF_INFO info ;

	memset (&info, 0, sizeof (info)) ;

	infile = sf_open (filename, SFM_READ, &info) ;
	if (infile == NULL)
	{	printf ("Error : failed to open sound file '%s' : \n%s\n", filename, sf_strerror (NULL)) ;
		return ;
		} ;
	
	decode_sndfile ( infile, info) ;	

	sf_close (infile);

	return ;
} /* render_sndfile */





void process_textfile(char *filename)
{
	FILE *fp; 
	float x; 
	int res; 
	static int samplecounter =0; 
	
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("\nError : failed to open text file '%s' : \n", filename); 
		return; 
	}
	while (1) { 
 		res = fscanf(fp,"%f",&x); 
		if ( res != 1) { 
			fclose(fp); 
			printf("\n");
			exit(0);
		}
		samplecounter++;
		if ((samplecounter % 20) == 0) {  // assuming that text envelope files have 4000 Hz sampling rate, decimate by 20 to get to 200 Hz (5ms sample time)st
			process_data((double)x); 
		}
	}	
}


void usage_exit (const char * argv0)
{
	const char * progname ;

	progname = strrchr (argv0, '/') ;
	progname = (progname == NULL) ? argv0 : progname + 1 ;

	puts ("\nBayesian Morse Decoder program reads sound file and decodes CW to text.") ;

	printf ("\nUsage :\n\n    %s  [options] <sound file> \n\n", progname) ;

	puts (
		"    Options include:\n\n"
		"        -ver				Print git version tag and exit.\n"		
		"        -var				Print variables for post-analysis (default off).\n"
		"        -sym				Print symbols before translation (default off). \n"
		"        -txt				Print decoded and translated text (default off).\n"
		"        -txf				Process text file instead of soundfile.\n"
		"        -agc				Use Automatic Gain Control (default off).\n"
		"        -bfv	<value>		Bit filter value (default 10 msec).\n"
		"        -frq	<value>		CW signal frequency (default 600 Hz).\n"
		"        -fft   <value>		Enable FFT filtering (default 0 - off)  \n"
		"        -plt				Plot envelope using xplot: ./morse -plt <sndfile> | xplot \n"
		"        -prs				Plot speed (WPM)using xplot: ./morse -plt <sndfile> | xplot \n"		
		"        -spd   <value>		Set default speed in WPM for decoder (default 20 )  \n"
		"        -len	<length>		Window length for FFT [8,16,32,64,128...].\n"
		"        -wid	<width>			Width of buffer to read & process [8192, 16384].\n"
		"        -dur	<duration>		Sample duration in msec [5.0] used in path.c.\n"
		"        -del	<delta>			Peak detection delta [10.0].\n"				


		) ;

	puts (
		"    -txf: 		The text file contains real valued input (1 datapoint per line) to be decoded.\n"
		"    Default: 	The sound file type is determined by the file name extension which should be one\n"
		"    			of 'wav', 'aifc', 'aif', 'aiff', 'au', 'caf' and 'w64'.\n"
		) ;

	exit (0) ;
} /* usage_exit */



 
// MAIN PROGRAM = BAYESIAN MORSE DECODER 
// (c) Mauri Niininen AG1LE 
// 

int main(int argc, const char* argv[])
{
    /* Initialized data */


    int k;

	int s_stop(char *, ftnlen);

    /* Local variables */

    int res; 
	FILE *fp; 

	/* 	PARSE PARAMETERS FROM COMMAND LINE  */
    
    if (argc < 2)
		usage_exit (argv [0]) ;

	for (k = 1 ; k < argc; k++) {
		if (strcmp (argv [k], "-bfv") == 0){
			k++ ;
			params.bfv = atoi (argv [k]) ;
			continue ;
		}
		if (strcmp (argv [k], "-wid") == 0){
			k++ ;
			params.width = atoi (argv [k]) ;
			continue ;
		}
		if (strcmp (argv [k], "-len") == 0) {
			k++ ;
			params.speclen = atoi (argv [k]) ;
			continue ;
		} 
		if (strcmp (argv [k], "-fft") == 0){
			k++ ;
			params.fft = atoi (argv [k]) ;
			continue ;
		}
		if (strcmp (argv [k], "-dur") == 0){
			k++ ;
			params.sample_duration = atof (argv [k]) ;
			continue ;
		}
		if (strcmp (argv [k], "-del") == 0){
			k++ ;
			params.delta = atof (argv [k]) ;
			continue ;
		}
		if (strcmp (argv [k], "-spd") == 0){
			k++ ;
			params.speed = atoi (argv [k]) ;
			continue ;
		}
		if (strcmp (argv [k], "-frq") == 0){
			k++ ;
			params.frequency = atof (argv [k]) ;
			continue ;
		}
		if (strcmp (argv [k], "-amp") == 0){
			k++ ;
			params.amplify = atof (argv [k]) ;
			continue ;
		}
		if (strcmp (argv [k], "-var") == 0){
			params.print_variables = TRUE;
			continue ;
			}
		if (strcmp (argv [k], "-ver") == 0){
			printf("Version: %s\n", GVERSION);
			exit(0);
			}
		if (strcmp (argv [k], "-sym") == 0){
			params.print_symbols = TRUE;
			continue ;
			}
		if (strcmp (argv [k], "-agc") == 0){
			params.agc = TRUE;
			continue ;
			}
		if (strcmp (argv [k], "-txt") == 0){
			params.print_text = TRUE;
			continue ;
			}
		if (strcmp (argv [k], "-txf") == 0){
			params.process_textfile = TRUE;
			continue ;
			}
		if (strcmp (argv [k], "-plt") == 0){
			params.print_xplot = TRUE;
			continue ;
			}
		if (strcmp (argv [k], "-prs") == 0){
			params.print_speed = TRUE;
			continue ;
			}
		} ;

/* 	INITIALIZE DATA STRUCTURES */

	if(params.process_textfile) 
		process_textfile((char *)argv[k-1]);
	else 
 		process_sndfile((char *)argv[k-1]);
 
		
} /* MAIN__ */





