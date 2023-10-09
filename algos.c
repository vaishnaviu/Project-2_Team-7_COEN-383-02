#include "algos.h"
#include "process.h"
#include <stdio.h>
#include <stdlib.h>

averageStats print_policy_stat(Queue * processes)
{
	averageStats avg;
	//Print Process Stat
	printf("\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("Process Name\t| Arrival Time | Start Time | End Time | Run Time | Response Time | Wait Time | Turnaround Time | Priority |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	Node * ptr = processes->front;
	float avg_response_time = 0;
	float avg_wait_time = 0;
	float avg_turnaround = 0;
	int process_count = 0;
	while(process_count < processes->size) {
		Process *process = (Process *)ptr->data;
		int arrival_time = process->arrival_time;
		int run_time = process->runtime;
		int response_time = process->startTime - arrival_time;
		int turnaround = process->endTime - process->arrival_time;
		int wait_time = turnaround - run_time;
		unsigned int priority = process->priority;
		avg_response_time += response_time;
		avg_wait_time += wait_time;
		avg_turnaround += turnaround;
		process_count++;
		printf("%16c|%14.1d|%12.1d|%10.1d|%10.1d|%15.1d|%11.1d| %17.1d|%10d|\n",process->pid,arrival_time, process->startTime, process->endTime, run_time, response_time, wait_time, turnaround,priority);
		ptr = ptr->next;
	}
	avg.avgThroughput = process_count;
	if(process_count == 0) process_count = 1;
	avg_response_time = avg_response_time / process_count;
	avg_wait_time = avg_wait_time / process_count;
	avg_turnaround = avg_turnaround / process_count;
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("%16s|%14.1f|%12.1f|%10.1f|%10.1f|%15.1f|%11.1f| %17.1f|\n"," Average",0.0, 0.0, 0.0,0.0,avg_response_time, avg_wait_time, avg_turnaround);
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	//compute overall stat
	//return stat
	avg.avgResponseTime = avg_response_time;
	avg.avgWaitTime = avg_wait_time;
	avg.avgTurnaround = avg_turnaround;

	return avg;
}
