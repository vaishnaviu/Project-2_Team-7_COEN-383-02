// roundrobin.c
#include "algos.h"
#include "process.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

averageStats roundRobinPreemptive(Queue *processes, int time_slice) {
    int t = 0;

    // Creation of Process Queue
    Queue *processQueue = (Queue *)createQueue();
    Node *procPtr = processes->front;
    if (processes->front == NULL) {
        fprintf(stderr, "No Process to schedule\n");
    }

    // Keep checking while time quanta is less than 100 or the process queue is empty...
    Process *scheduledProcess = NULL;

    Queue *ll = createQueue();
    printf("\nRound Robin Algorithm:\n");
    Node *cur_node = NULL;
    int cur_run = 0;

    while (t < 100 || processQueue->size > 0) {
        // Check for incoming new process and do enqueue.
        if (procPtr != NULL && t < 100) {
            Process *newProcess = (Process *)(procPtr->data);
            while (procPtr != NULL && newProcess->arrival_time <= t) {
                enqueue(processQueue, newProcess);
                procPtr = procPtr->next;
                if (procPtr != NULL)
                    newProcess = (Process *)(procPtr->data);
            }
        }

        // Check process queue and schedule it if there is no scheduled process now..
        if (cur_node == NULL) {
            cur_run = 0;
            cur_node = processQueue->front;
        } else if (cur_run == time_slice) {
            cur_run = 0;
            cur_node = cur_node->next;
            if (cur_node == NULL) {
                cur_node = processQueue->front;
            }
        }

        if (cur_node != NULL) {
            scheduledProcess = (Process *)cur_node->data;
            Process *proc = scheduledProcess;

            if (t >= 100) {
                if (scheduledProcess->startTime == -1) {
                    // Do not start any new process, remove it from processQueue
                    // free(scheduledProcess);
                    Node *next = cur_node->next;
                    removeNode(processQueue,cur_node->data);
                    cur_node = next;
                    cur_run = 0;
                    continue;
                }
            }

            // Add the currently running process to the time chart
            printf("%c", proc->pid);
            cur_run++;

            // Update the current processes stat
            if (scheduledProcess->startTime == -1) {
                scheduledProcess->startTime = t;
            }
            scheduledProcess->executionTime++;

            if (scheduledProcess->executionTime >= proc->runtime) {
                //start+run
                scheduledProcess->endTime = t;
                enqueue(ll, scheduledProcess);
                Node *next = cur_node->next;
                removeNode(processQueue,cur_node->data);
                cur_node = next;
                cur_run = 0;
            }
        } else {
            printf("_");
        }

        // Keep increasing the time
        t++;
    }

    // Create the average statistics
    return print_policy_stat(ll);

    // Free allocated memory
    // Modify this based on your specific memory allocation
    // Node *currentNode = ll->front;
    // while (currentNode != NULL) {
    //     free(currentNode->data);
    //     Node *temp = currentNode;
    //     currentNode = currentNode->next;
    //     free(temp);
    // }
    // free(ll);

    // return avg;
}
