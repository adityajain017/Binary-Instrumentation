CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Input File
 * Running the program
	* Q1, Q2, Q3, Q4
 * Contact Details


INTRODUCTION
------------

Hi!! This is the Assignment #2 submission of course CS622: Advance Computer Architecture by
Group No.: 23 {Aditya Jain (Roll: 20111004), Mahi Agrawal (Roll: 20111029)}
This assignment is coded in C++ 

* Folder contains 4 cpp files, 1 txt file, and 1 folder named "input"
	
	* addrtrace.cpp :- (Q1)Prints the total machine access printed on the terminal and generates the thread  memory trace for the program in the output file "input/thread_memory_trace.txt"

	* distance_calculator.cpp:- (Q2)Generates the cdf (log of distance vs F(d)) details in output file: cdf_q2.csv 
	
	* cache-simulator.cpp :- (Q3)Prints the cache hits and cache miss on the terminal and generates the 
	  cdf (log of distance vs F(d)) details in output file: cdf_q3.csv

	* q4_sharing_profile.cpp :- (Q4)Prints the total number of blocks that are private or if shared then 
	  shared by how many threads on the terminal.

	* README.txt 

	* Folder named "input" :- All generated trace files are stored here. So trace files must be present 
	  in this folder before executing Q2, Q3, and Q4 files.  
	


INPUT FILE
-------------
* prog1.cpp, prog2.cpp, prog3.cpp, prog4.cpp 


RUNNING THE PROGRAM
----------------

Q1 
------
Compile these programs to generate static binaries. Use the following commands.
gcc -O3 -static -pthread prog1.c -o prog1
gcc -O3 -static -pthread prog2.c -o prog2
gcc -O3 -static -pthread prog3.c -o prog3
gcc -O3 -static -pthread prog4.c -o prog4

For generating total machine access details on terminal and generating thread wise memory trace:

-> Compile pintool: $ make obj-intel64/addrtrace.so
-> Launch pin: $ ../../../pin -t obj-intel64/addrtrace.so -- ./prog1 8
* Output : Prints total machine access on terminal and generates : thread_memory_trace.txt


Q2
------
File name: distance_calculator.cpp
Input required:input/thread_memory_trace.txt 
Output: cdf_q2.csv 
Command to execute the file:
	$ g++ distance_calculator.cpp -o distance_calculator
	$ ./distance_calculator

Q3
------
File name: cache-simulator.cpp
Input required:input/thread_memory_trace.txt 
Output: cdf_q3.csv 
Command to execute the file:
	$ g++ cache-simulator.cpp -o cache-simulator
	$ ./cache-simulator 

Q4
------
File name: q4_sharing_profile.cpp
Input required: input/thread_memory_trace.txt 
Output: Printed on the terminal 
Command to execute the file:
	$ g++ q4_sharing_profile.cpp -o q4_sharing_profile
	$ ./q4_sharing_profile (eg: ./q4_sharing_profile) 



CONTACT DETAILS
-----------------

Submitted By: Aditya Jain (Roll: 20111004), Mahi Agrawal (Roll: 20111029)

In case of any querry please contact on following:

Aditya Jain
---------------
* Email:  adityaj20@iitk.ac.in, jainaditya017@outlook.com

Mahi Agrawal
----------------
* Email: maahi20@iitk.ac.in

------------------------------------------------ THANK YOU----------------------------------------------------------- ---------------------------------------------------------------------------------------------------------------------
