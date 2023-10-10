#include "algos.h"
#include "process.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

averageStats roundRobinPreemptive(Queue *processes, int time_slice) {
    int t = 0;

    // Create a queue for the processes to be scheduled
    Queue *processQueue = createQueue();

    // Pointer to traverse the list of processes
    Node *processPointer = processes->front;

    if (processes->front == NULL) {
        fprintf(stderr, "No Process to schedule\n");
    }

    // Pointer to the currently scheduled process
    Process *scheduledProcess = NULL;

    // Create a queue to hold the processes in the order of execution
    Queue *ll_queue = createQueue();

    printf("\nRound Robin Algorithm:\n");

    // Pointer to the current node in the processQueue
    Node *currentProcNode = NULL;

    int currentRun = 0;  // Current run within the time slice

    // Continue checking while time is below 100 or the process queue is not empty
    while (t < 100 || processQueue->size > 0) {
        // Check for incoming new processes and enqueue them
        if (processPointer != NULL && t < 100) {
            Process *newProcess = (Process *)(processPointer->data);
            while (processPointer != NULL && newProcess->arrival_time <= t) {
                enqueue(processQueue, newProcess);
                processPointer = processPointer->next;
                if (processPointer != NULL)
                    newProcess = (Process *)(processPointer->data);
            }
        }

        // Check the process queue and schedule a process if required
        if (currentProcNode == NULL) {
            currentRun = 0;
            currentProcNode = processQueue->front;
        } else if (currentRun == time_slice) {
            currentRun = 0;
            currentProcNode = currentProcNode->next;
            Process* process_to_preempt = dequeue(processQueue);
            enqueue(processQueue, process_to_preempt);
            if (currentProcNode == NULL) {
                currentProcNode = processQueue->front;
            }
        }

        if (currentProcNode != NULL) {
            // Get the scheduled process
            scheduledProcess = (Process *)currentProcNode->data;

            if (t >= 100) {
                if (scheduledProcess->startTime == -1) {
                    // Remove process from processQueue without starting a new one
                    Node *next = currentProcNode->next;
                    dequeue(processQueue);
                    currentProcNode = next;
                    currentRun = 0;
                    continue;
                }
            }

            // Record the current running process on the time chart
			printf("%c",scheduledProcess->pid);
            currentRun++;

            // Update current process statistics
            if (scheduledProcess->startTime == -1) {
                scheduledProcess->startTime = t;
            }
            scheduledProcess->executionTime++;

            if (scheduledProcess->executionTime >= scheduledProcess->runtime) {
                // Process execution completed
                scheduledProcess->endTime = t;
                enqueue(ll_queue, scheduledProcess);
                Node *next = currentProcNode->next;
                dequeue(processQueue);
                currentProcNode = next;
                currentRun = 0;
            }
        } else {
            // Print underscore for idle time when no process is scheduled
            printf("_");
        }
        // Move to the next time quanta
        t++;
    }

    // Generate average statistics
    return print_policy_stat(ll_queue);
}