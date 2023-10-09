#ifndef PROCESS_H
#define PROCESS_H
#include "queue.h"

struct process {
    char pid;
    int arrival_time;
    int runtime;
    int priority;
    int startTime;
    int endTime;
    int responseTime;
    int waitTime;
    int turnaroundTime;
    int executionTime;
};

typedef struct process Process;

Process *createProcess(char pid, int arrival_time, int runtime, int priority);
Queue *generateProcesses(int n);

#endif