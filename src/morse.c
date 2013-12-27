// ----------------------------------------------------------------------------
// morse.c --  morse code decoder 
//
// Copyright (C) 2012-2014
//		     (C) Mauri Niininen, AG1LE
//
// This file is part of Morse.  

// Morse is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Morse is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Morse.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "morse.h"
#include <sndfile.h>
#include <fftw3.h>
#include "window.h"

#define ARRAY_LEN(x)    ((int) (sizeof (x) / sizeof (x [0])))
#define MAX(x,y)                ((x) > (y) ? (x) : (y))
#define MIN(x,y)                ((x) < (y) ? (x) : (y))
#define	MIN_WIDTH	640
#define	MIN_HEIGHT	480
#define	MAX_WIDTH	65536
#define	MAX_HEIGHT	4096

PARAMS params = { FALSE, FALSE, FALSE, FALSE,  16384, 16, 0, 0};



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
	sf_count_t start ;

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

static double calc_magnitude (const double * freq, int freqlen, double * magnitude)
{
	int k ;
	double max = 0.0 ;

	for (k = 1 ; k < freqlen / 2 ; k++)
	{	magnitude [k] = sqrt (freq [k] * freq [k] + freq [freqlen - k - 1] * freq [freqlen - k - 1]) ;
		max = MAX (max, magnitude [k]) ;
		} ;
	magnitude [0] = 0.0 ;

	return max ;
} /* calc_magnitude */


static void apply_window (double * data, int datalen)
{
	static double window [10 * MAX_HEIGHT] ;
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

static void interp_spec (float * mag, int maglen, const double *spec, int speclen)
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
  static integer sample_counter = 0;
  static real rn = .1f;
  static integer retstat, n1, n2, imax, xhat, elmhat;
  static real pmax, zout, spdhat, px;
  static int init = 1; 

	if (params.print_variables && init) { 
		printf("\nretstat\timax\telmhat\txhat\tx\tpx\tpmax\tspdhat\trn\tzout\tp1\tp2\tp3\tp4\tp5\tp6\n");
		init = 0; 
		}

		sample_counter++;
//		if (sample_counter % DECIMATE == 0) { /* 	DECIMATE 4 kHz by 20  down to 200Hz - 5 ms sample time for PROCES */

			noise_(x, &rn, &zout);
			if (zout > 1.0) zout = 1.0; 
			if (zout < 0.0) zout = 0.0;
			
			retstat = proces_(&zout, &rn, &xhat, &px, &elmhat, &spdhat, &imax, &pmax);
			if (params.print_variables) 
				printf("\n%d\t%d\t%d\t%d\t%f\t%f\t%f\t%f\t%f\t%f",(int)retstat,(int)imax,(int)elmhat,(int)xhat,x,px,pmax,spdhat,rn,zout); 

//		}
}


static void
decode_sndfile (SNDFILE *infile, int samplerate, sf_count_t filelen)
{


	static double time_domain [10 * MAX_HEIGHT] ;
	static double freq_domain [10 * MAX_HEIGHT] ;
	static double single_mag_spec [5 * MAX_HEIGHT] ;
	static float mag_spec [MAX_WIDTH][MAX_HEIGHT] ;

	fftw_plan plan ;
	double max_mag = 0.0 ;
	int width = 8192, height= 32, w, speclen ;

	width = params.width; 
	/*
	**	Choose a speclen value that is long enough to represent frequencies down
	**	to 20Hz, and then increase it slightly so it is a multiple of 0x40  (64) so that
	**	FFTW calculations will be quicker.
	*/

	speclen = 16; 	// 16 ok for 4000 Hz test60db.wav @16384 width
	speclen = params.speclen;  //  64  for 48000 Hz capture.wav @4096 w or 2048
	
	params.sample_rate = samplerate; 
	params.sample_duration = 2000.*speclen/samplerate; 
	
	if (2 * speclen > ARRAY_LEN (time_domain))
	{	printf ("%s : 2 * speclen > ARRAY_LEN (time_domain)\n", __func__) ;
		exit (1) ;
		} ;
	printf("\nsamplerate:%d speclen:%d", samplerate, speclen);

	plan = fftw_plan_r2r_1d (2 * speclen, time_domain, freq_domain, FFTW_R2HC, FFTW_MEASURE | FFTW_PRESERVE_INPUT) ;
	if (plan == NULL)
	{	printf ("%s : line %d : create plan failed.\n", __FILE__, __LINE__) ;
		exit (1) ;
		} ;

	for (w = 0 ; w < width ; w++)
	{	double single_max ;

		read_mono_audio (infile, filelen, time_domain, 2 * speclen, w, width) ;

		apply_window (time_domain, 2 * speclen) ;

		fftw_execute (plan) ;

		single_max = calc_magnitude (freq_domain, 2 * speclen, single_mag_spec) ;
		max_mag = MAX (max_mag, single_max) ;
		
		process_data(single_max/max_mag); // decode Morse code here 
		
		interp_spec (mag_spec [w], height, single_mag_spec, speclen) ;
		} ;

	fftw_destroy_plan (plan) ;
	
}

static void
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

	decode_sndfile ( infile, info.samplerate, info.frames) ;

	sf_close (infile);

	return ;
} /* render_sndfile */

void process_textfile(char *filename)
{
	FILE *fp; 
	float x; 
	int res; 
	
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
		process_data((double)x); 
	}	
}


static void usage_exit (const char * argv0)
{
	const char * progname ;

	progname = strrchr (argv0, '/') ;
	progname = (progname == NULL) ? argv0 : progname + 1 ;

	puts ("\nBayesian Morse Decoder program reads sound file and decodes CW to text.") ;

	printf ("\nUsage :\n\n    %s  [options] <sound file> \n\n", progname) ;

	puts (
		"    Options include:\n\n"
		"        -var				Print variables for post-analysis (default off).\n"
		"        -sym				Print symbols before translation (default off). \n"
		"        -txt				Print decoded and translated text (default off).\n"
		"        -txf				Process text file instead of soundfile.\n"
		"        -len	<length>		Window length for FFT [8,16,32,64,128...].\n"
		"        -wid	<width>			Width of buffer to read & process [8192, 16384].\n"


		) ;

	puts (
		"    TXF: 		The text file contains real valued input (1 datapoint per line) to be decoded.\n"
		"    Default: 	The sound file type is determined by the file name extension which should be one\n"
		"    			of 'wav', 'aifc', 'aif', 'aiff', 'au', 'caf' and 'w64'.\n"
		) ;

	exit (0) ;
} /* usage_exit */



 
// MAIN PROGRAM = BAYESIAN MORSE DECODER 
// (c) Mauri Niininen AG1LE 
// 

int main(int argc, char**argv)
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
		if (strcmp (argv [k], "-var") == 0){
			params.print_variables = TRUE;
			continue ;
			}
		if (strcmp (argv [k], "-sym") == 0){
			params.print_symbols = TRUE;
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
		} ;

/* 	INITIALIZE DATA STRUCTURES */
	initl_();
	inputl_();
	
	if(params.process_textfile) 
		process_textfile(argv[k-1]);
	else 
 		process_sndfile(argv[k-1]);
 
		
} /* MAIN__ */





