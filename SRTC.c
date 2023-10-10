#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "algos.h"

// Comparator function for sorting processes based on remaining time to completion
int compareRemainingTime(void *data1, void *data2)
{
    Process *ps1 = (Process *)data1;
    Process *ps2 = (Process *)data2;
    if ((ps1->runtime - ps1->executionTime) < (ps2->runtime - ps2->executionTime))
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

// Function to print the contents of a queue for testing during shortest remaining time to completion
void print_queue_srtc(Queue *q)
{
    if (q->front != NULL)
    {
        Node *n = q->front;
        printf("Queue Contains:\n");
        while (n != NULL)
        {
            Process *ps = n->data;
            printf("Process Id %c Remaining Time %d\n", ps->pid, (ps->runtime - ps->executionTime));
            n = n->next;
        }
    }
    return;
}

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
    if (processes->front == NULL)
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
                enqueue(processQueue, newProcess);
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
            //add current running process to the time chart
  			printf("%c",scheduledProcess->pid);
            // Update the current process's statistics
            if (scheduledProcess->startTime == -1)
            {
                scheduledProcess->startTime = timeQuantum;
            }

            scheduledProcess->executionTime++;

            // Check if the process has completed
            if (scheduledProcess->executionTime >= scheduledProcess->runtime)
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
