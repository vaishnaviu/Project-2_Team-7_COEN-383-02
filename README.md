# Process-Scheduling-Algorithms

This repository contains a C program that simulates various process scheduling algorithms, including:

* First come first served (FCFS) [non-preemptive]
* Shortest job first (SJF) [non-preemptive]
* Shortest remaining time (SRT) [preemptive]
* Round robin (RR) [preemptive]
* Highest priority first (HPF) [non-preemptive]
* Highest priority first (HPF) [preemptive]

#Instructions to Compile and Run

To compile the program, use the following command:

gcc *.c -o main

To run the program, use the following command:

./main

#Simulation Details

* Each algorithm is run for 100 quanta (time slices).
* Simulated processes are generated with random arrival times, expected run times, and priorities.
* The program displays details of each created process, a time chart showing the execution sequence, and calculated statistics for each algorithm run.

For each algorithm run, the following statistics are provided:

* Average Turnaround Time
* Average Waiting Time
* Average Response Time
* Throughput
