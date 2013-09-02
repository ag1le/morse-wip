(C) 2013  AG1LE Mauri Niininen 

This software is a Morse decoder orinally created by Dr. E. L. Bell in 1977.  
The software was manually entered from Fortran program listings and later converted to C++. 

2013-SEP-01  	Initial version. Original Fortran sources compiled with  
			gfortran -g  *.f 
		produces a.out  executable program.  

		Based on initial testing the element state estimation works, but translating letters 
		has still problems. Produces a sequence of letter states but translation to actual 
		characters produces incorrect letters. 

 		Compilation of C-sources produced by f2c is done with following commands:

			gcc -c *.c 
			gcc  *.o -lf2c -lm

		produces a.out executable program. The output of both versions of a.out is in 
			output_c.txt
			output_f.txt 

		These have minor differences - source still unknown. 
