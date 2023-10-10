#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "queue.h"
#include <time.h>

int compare(void *data1, void *data2) {
	Process *p1 = (Process *)data1;
	Process *p2 = (Process *)data2;
	if(p1->arrival_time < p2->arrival_time) {
		return -1;
	} else if(p1->arrival_time == p2->arrival_time){
		return 0;
	} else {
		return 1;
	}
}

Process * createProcess(char pid, int arrival_time, int runtime, int priority) {
    Process * process = (Process *) malloc(sizeof(Process));
	process->pid = pid;
    process->arrival_time = arrival_time;
	process->runtime = runtime;
	process->priority = priority;
    process->startTime = -1;
    process->endTime = -1;
    process->turnaroundTime = 0;
    process->responseTime = 0;
    process->waitTime = 0;
    process->executionTime = 0;
	return process;
}
void resetProcess(Process * process) {
    process->startTime = -1;
    process->endTime = -1;
    process->turnaroundTime = 0;
    process->responseTime = 0;
    process->waitTime = 0;
    process->executionTime = 0;
}
void resetProcesses(Queue * processes) {
	Node* currentProcess = processes->front;
	int processCtr = 0;
	while(processCtr < processes->size) {
		resetProcess(currentProcess->data);
		currentProcess = currentProcess->next;
		processCtr += 1;
	}
}
Queue *generateProcesses(int n) {
	Queue *processList = createQueue();
	char pid = 'A';
	unsigned int priority;
	int arrival_time, run_time;
	time_t t;


   /* Intializes random number generator */

    int seed = time(NULL);
    srand(seed); // guarantee consistency when debugging

	if(processList == NULL) fprintf(stderr,"Unable to create Queue\n");

	while(n--) {
		arrival_time = rand() % 100;
		run_time = (rand() % 10) + 1;
		priority = (rand() % 4)+1;
		Process *p = createProcess(pid,arrival_time,run_time,priority);
		enqueue(processList,p);
		pid++;
	}

	sort(processList,compare);

	Node *ptr = processList->front;
	pid = 'A';
	while(ptr!=NULL) {
		((Process *)ptr->data)->pid = pid;
		if(pid == 'Z') pid = 'a' - 1;
		pid++;
		ptr=ptr->next;
	}

	return processList;
}
