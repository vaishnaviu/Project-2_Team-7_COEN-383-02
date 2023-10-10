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
	
}
