#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "algos.h"

averageStats firstComeFirstServe(Queue *processQueue) {
	int t = 0;

	if(processQueue->size == 0) {
		fprintf(stderr,"No Process to schedule\n");
	}
	Node *incoming_proc = processQueue->front;
	//while process queue is not empty or time quanta is less than 100
	Process * scheduledProcess = NULL;
	Queue *arrivedProcesses = createQueue();
	Queue *finishedProcesses = createQueue();
	printf("\nFirst Come First Serve:\n");
	while(t<100 || scheduledProcess!=NULL) {
		//check for incoming new process and enqueue it in the queue
		if(incoming_proc != NULL) {
			Process * new_process = (Process *)(incoming_proc->data);
			if(new_process->arrival_time <= t) {
				enqueue(arrivedProcesses,new_process);
				incoming_proc = incoming_proc->next;
			}
		}

		if(scheduledProcess == NULL && arrivedProcesses->size > 0) {
			scheduledProcess = (Process *) dequeue(arrivedProcesses);
		}

		if(scheduledProcess != NULL) {

			if(scheduledProcess->startTime == -1) {
				scheduledProcess->startTime = t;
			}
			scheduledProcess->executionTime++;

			if(scheduledProcess->executionTime > scheduledProcess->runtime) {
				scheduledProcess->endTime = t;
				enqueue(finishedProcesses,scheduledProcess);
				scheduledProcess = NULL;
			}
		} 
		t++;
	}
	printf("\n");
	return print_policy_stat(finishedProcesses);
}
