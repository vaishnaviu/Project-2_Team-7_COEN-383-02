#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "algos.h"

void firstComeFirstServe(Queue *processQueue) {
	int t = 0;
    //Create Process Queue
	Node *incoming_proc = processQueue->front;
	if(incoming_proc == NULL) {
		fprintf(stderr,"No Process to schedule\n");
	}
	//while process queue is not empty or time quanta is less than 100
	Process * scheduledProcess = NULL;

	Queue *finishedProcesses = createQueue();
	printf("\nFirst Come First Serve:\n");
	while(t<100 || scheduledProcess!=NULL) {
		//if there is no scheduled process, then check process queue and schedule it
		if(scheduledProcess == NULL && processQueue->size > 0 && t>= ((Process *)(incoming_proc->data))->arrival_time) {
			scheduledProcess = (Process *) dequeue(processQueue);
			incoming_proc = processQueue->front;
		}

		if(scheduledProcess != NULL) {

			//update current processes stat
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
		//increase the time
		t++;
	}
	printf("\n");

}
