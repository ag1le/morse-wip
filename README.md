(C) 2013  AG1LE Mauri Niininen 

This software is a Morse decoder orinally created by Dr. E. L. Bell in 1977.  
The software was manually entered from Fortran program listings and later converted to C++
by AG1LE Mauri Niininen.  

DEPENDENCIES:
- libsndfile1-dev  -- used to open WAV sound files 
- fftw3-dev        -- used for FFT calculation
- tcl              -- used for running cer vs snr testing
- sqlite3          -- used to store test results in SQL database 
- libsqlite3-tcl   -- used by tcl to call sqlite3 

install dependencies by 

sudo apt-get install libsndfile1-dev fftw3-dev
sudo apt-get install tcl
sudo apt-get install sqlite3
sudo apt-get install libsqlite3-tcl

