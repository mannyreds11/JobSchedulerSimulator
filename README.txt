CPU Scheduling Simulator

Instructions: 
1. Compile: $ make
2. Run:     $ ./a.out

usage: ./a.out  [options]
options == 
	-a #	interarrival time
	-e  	show event queue
	-h  	show this help
	-j #	select scheduling algorithm [1 ...]
	       1 -- First Come First Served
	       2 -- Round Robin
	       3 -- Shortest Job First 
	       4 -- Longest Job First 
	       5 -- Shortest Job Remaining 
	       6 -- Longest Job Remaining
	-n #	number of iterations
	-p  	do not show parameters
	-q  	show job queue
	-s #	service time
	-t #	ending time
	-v  	show stats each iteration

