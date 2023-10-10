#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "algos.h"


int compareRunTime(void *data1, void *data2) {
	Process *ps1 = (Process *)data1;
	Process *ps2 = (Process *)data2;
	if(ps1->runtime < ps2->runtime) 
	{
		return -1;
	} 
	else 
	{
		return 1;
	}
}

// Implementation of shortest remaining time to completion - nonpremptive
averageStats shortest_job_first_np(Queue *processes) {
	int timeQuantum = 0;

	// Create a queue for processes
	Queue *processQueue = (Queue *)createQueue();
	Node *processPointer = processes->front;
	if(processes->front == NULL) {
		fprintf(stderr,"No Process to schedule\n");
	}
	//while process queue is not empty or time quanta is less than 100
	Process * scheduledProcess = NULL;

	Queue *ll = createQueue();
	printf("\nShortest Job First:\n");
	while(timeQuantum<100 || scheduledProcess!=NULL) {
		//check for incoming new process and enqueue it in the queue
		if(processPointer != NULL) {
			Process *newProcess = (Process *)(processPointer->data);
			while(processPointer != NULL && newProcess->arrival_time <= timeQuantum) 
			{
				enqueue(processQueue, newProcess);
				sort(processQueue,compareRunTime);
				processPointer = processPointer->next;
				if(processPointer != NULL)
					newProcess = (Process *)(processPointer->data);
			}
		}

		//if there is no scheduled process, then check process queue and schedule it
		if(scheduledProcess == NULL && processQueue->size > 0) 
		{
			scheduledProcess = (Process *)dequeue(processQueue);
		}

		if(scheduledProcess != NULL) {
			Process *proc = scheduledProcess;

			//add current running process to the time chart
			printf("%c",proc->pid);

			//update current processes stat
			if(scheduledProcess->startTime == -1) {
				scheduledProcess->startTime = timeQuantum;
			}
			scheduledProcess->executionTime++;

			if(scheduledProcess->executionTime >= scheduledProcess->runtime) {
				scheduledProcess->endTime = timeQuantum;
				enqueue(ll,scheduledProcess);
				scheduledProcess = NULL;
			}
		} else {
			printf("_");
		}
		//increase the time
		timeQuantum++;
	}
	printf("\n");

	//Print Process Stat
	return print_policy_stat(ll);
	/*
	printf("\nProcess Name\t| Arrival Time | Run Time | Response Time | Wait Time | Turn Around Time | Priority |\n");
	node * ptr = ll->head;
	float avg_response_time = 0;
	float avg_wait_time = 0;
	float avg_turnaround = 0;
	int process_count = 0;
	while(ptr!=NULL) {
		process_stat *stat = (process_stat *)ptr->data;
		if(stat == NULL) printf("No Stat\n");
		process *proc = (process *)stat->proc;
		if(proc == NULL) printf("No Process\n");
		float arrival_time = proc->arrival_time;
		float run_time = proc->run_time;
		float response_time = stat->start_time - arrival_time;
		float turnaround = stat->end_time - proc->arrival_time + 1;
		float wait_time = turnaround - run_time;
		unsigned char priority = proc->priority;
		avg_response_time += response_time;
		avg_wait_time += wait_time;
		avg_turnaround += turnaround;
		process_count++;
		printf("%16c|%14.1f|%10.1f|%15.1f|%11.1f| %17.1f| %9u|\n",proc->pid,arrival_time, run_time, response_time, wait_time, turnaround, priority);
		ptr = ptr->next;
	}
	avg_response_time = avg_response_time / process_count;
	avg_wait_time = avg_wait_time / process_count;
	avg_turnaround = avg_turnaround / process_count;
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("%16c|%14.1f|%10.1f|%15.1f|%11.1f| %17.1f\n",' ',0.0, 0.0, avg_response_time, avg_wait_time, avg_turnaround);
	//compute overall stat
	//return stat
	*/
}
