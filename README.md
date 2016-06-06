#Checkbook Program  
  
---  
This program is designed to allow the user to keep track of their bank accounts and transactions.  Pretty simple.  
  
###Building the program:  
  
The program was developed on windows, and as such, the QMake project file will need to be modified slightly for other operating systems you intend to build on.  Build requirements are listed below:  
  
-  QMake (Comes with [Qt](http://www.qt.io/))
-  Compiler that supports C++14
-  [Boost](http://www.boost.org/) libraries
-  [Qt](http://www.qt.io/) libraries
-  Make or, on Windows, NMake
-  [Botan](https://botan.randombit.net/#recommended-algorithms)  
  
To build, simply open up a terminal in the project directory (the same folder the "windows.pro" file is in), and run `qmake && make release` on Linux.  If you're using windows, run `qmake && nmake release`.  The binary will be in build/release.