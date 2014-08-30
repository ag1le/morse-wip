function code=generate_morse(file)
% First step: Generate 100x20 random strings and save to text file
% You can use 
% http://www.random.org/strings/?num=100&len=20&digits=on&upperalpha=on&loweralpha=off&unique=on&format=plain&rnd=new
% or
% http://www.unit-conversion.info/texttools/random-string-generator/


fid = fopen(file,"r");
fid2 = fopen("kaggle.csv","w")
 
Fs = 8000;  % 8 KHz sampling rate 
Tune = 600; % 600 Hz signal 

row = 1;
fprintf(fid2, "Text,ID,file,SNR,Tune,WPM\n");
while (!feof(fid))
	txt = fgetl (fid);
	fname = ["cw" int2str(row) ".wav"];
	SNR = randi([-6,60]);		% SNR between - 6 dB ... + 60 dB
	WPM = randi([12,60]);    	% Speed between 12 ... 60 WPM
	%Tune = randi([300,1200]);	% Null beat between 300 ... 1200 Hz
	x = morse(txt,fname,SNR,Tune,Fs,WPM);
	fprintf(fid2, "%s,%d,%s,%d,%d,%d\n",txt,row,fname,SNR,Tune,WPM);
	printf("%s,row:%d,%s,SNR:%d,Tune:%d,WPM:%d\n",txt,row,fname,SNR,Tune,WPM);
	row = row + 1;
end
fclose(fid); 
fclose(fid2);
