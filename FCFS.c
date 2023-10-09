#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "algos.h"

void firstComeFirstServe(Queue *processQueue) {
	int t = 0;
	Node *incoming_proc = processQueue->front;
	if(processQueue->size == 0) {
		fprintf(stderr,"No Process to schedule\n");
	}

	Process * scheduledProcess = NULL;
	Queue *arrivedProcesses = createQueue();
	Queue *finishedProcesses = createQueue();
	printf("\nFirst Come First Serve:\n");
	while(t<100 || scheduledProcess!=NULL) {

		if(processQueue->size > 0 && ((Process*)incoming_proc->data)->arrival_time <= t) {
			Process * new_process = (Process*) dequeue(processQueue);
			enqueue(arrivedProcesses,new_process);
			incoming_proc = processQueue->front;
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
                printf("%c: startTime = %d endTime=%d\n", scheduledProcess->pid, scheduledProcess->startTime, scheduledProcess->endTime);
				scheduledProcess = NULL;
			}
		} 
		t++;
	}
	printf("\n");

}
