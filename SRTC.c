#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "algos.h"

// Function to create a process_stat structure for a process
Process *createProcessStat(Process *proc);

// Comparator function for sorting processes based on remaining time to completion
int compareRemainingTime(void *data1, void *data2);

// Function to print the contents of a queue for testing during shortest remaining time to completion
void print_queue_srtc(Queue *q);

// Implementation of Shortest Remaining Time to Completion (SRTC) preemptive scheduling
averageStats shortest_remaining_time_p(Queue *processes)
{
    int timeQuantum = 0;

    // Create a queue for processes
    Queue *processQueue = createQueue();

    // Create a linked list for managing the order of processes during preemption
    Queue *orderQueue = createQueue();

    // Point to the head of the process list
    Node *processPointer = processes->front;

    // Check if there are processes to schedule
    if (processPointer == NULL)
    {
        fprintf(stderr, "No processes to schedule\n");
    }

    // While the process queue is not empty or the time quantum is less than 100
    Process *scheduledProcess = NULL;
    printf("\n\nShortest Remaining Time To Completion Preemptive:\n");

    while (timeQuantum < 100 || scheduledProcess != NULL)
    {
        // If there is a scheduled process, enqueue it
        if (scheduledProcess != NULL)
        {
            enqueue(processQueue, scheduledProcess);
            scheduledProcess = NULL;
        }

        // Check for incoming new processes and enqueue them in the queue
        if (processPointer != NULL)
        {
            Process *newProcess = (Process *)(processPointer->data);
            while (processPointer != NULL && newProcess->arrival_time <= timeQuantum)
            {
                enqueue(processQueue, createProcessStat(newProcess));
                processPointer = processPointer->next;

                if (processPointer != NULL)
                {
                    newProcess = (Process *)(processPointer->data);
                }
            }

            // Sort all the processes that have arrived based on their remaining time to completion
            sort(processQueue, compareRemainingTime);
        }

        // If there is no scheduled process, check the process queue and schedule one
        if (scheduledProcess == NULL && processQueue->size > 0)
        {
            scheduledProcess = (Process *)dequeue(processQueue);

            // If the process has not started before the time quantum of 100, remove it from the queue
            while (timeQuantum >= 100 && scheduledProcess->startTime == -1)
            {
                scheduledProcess = (Process *)dequeue(processQueue);
            }
        }

        // Execute the scheduled process or print an underscore if none is scheduled
        if (scheduledProcess != NULL)
        {
            Process *currentProcess = scheduledProcess;

            // Add the current running process to the time chart
            printf("%c", currentProcess->pid);

            // Update the current process's statistics
            if (scheduledProcess->startTime == -1)
            {
                scheduledProcess->startTime = timeQuantum;
            }

            scheduledProcess->executionTime++;

            // Check if the process has completed
            if (scheduledProcess->executionTime >= currentProcess->runtime)
            {
                scheduledProcess->endTime = timeQuantum;
                enqueue(orderQueue, scheduledProcess);
                scheduledProcess = NULL;
            }
        }
        else
        {
            printf("_");
        }

        // Increase the time quantum
        timeQuantum++;
    }

    // Print Process Statistics
    return print_policy_stat(orderQueue);
}
