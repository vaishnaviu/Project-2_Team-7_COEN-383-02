#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "algos.h"

averageStats firstComeFirstServe(Queue *processQueue) {
	int timeQuanta = 0;

	if(processQueue->size == 0) {
		fprintf(stderr,"No Process to schedule\n");
	}
	Node *incoming_proc = processQueue->front;
	//while processQueue is not empty or time quanta is less than 100
	Process * scheduledProcess = NULL;
	Queue *arrivedProcesses = createQueue();
	Queue *finishedProcesses = createQueue();
	printf("\nFirst Come First Serve:\n");
	while(timeQuanta<100 || scheduledProcess!=NULL) {
		//check for incoming new process and enqueue it in the queue
		if(incoming_proc != NULL) {
			Process * newProcess = (Process *)(incoming_proc->data);
			if(newProcess->arrival_time <= timeQuanta) {
				enqueue(arrivedProcesses,newProcess);
				incoming_proc = incoming_proc->next;
			}
		}

		if(scheduledProcess == NULL && arrivedProcesses->size > 0) {
			scheduledProcess = (Process *) dequeue(arrivedProcesses);
		}

		if(scheduledProcess != NULL) {
			//add current running process to the time chart
			printf("%c",scheduledProcess->pid);

			if(scheduledProcess->startTime == -1) {
				scheduledProcess->startTime = timeQuanta;
			}
			scheduledProcess->executionTime++;

			if(scheduledProcess->executionTime > scheduledProcess->runtime) {
				scheduledProcess->endTime = timeQuanta;
				enqueue(finishedProcesses,scheduledProcess);
				scheduledProcess = NULL;
			}
		} 
		timeQuanta++;
	}
	printf("\n");
	return print_policy_stat(finishedProcesses);
}
