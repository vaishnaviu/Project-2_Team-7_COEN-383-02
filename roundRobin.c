#include "algos.h"
#include "queue.h"
#include "process.h"
#include <stdio.h>
#include <stdlib.h>

// Function to run Round Robin (RR) scheduling algorithm
averageStats roundRobinPreemptive(Queue *processes, int time_slice) {
    averageStats avg_rr;
    avg_rr = print_policy_stat(processes);  // Use the provided print_policy_stat function

    // Implement Round Robin Scheduling Algorithm with time slice of 1 quantum
    Node *ptr = processes->front;
    int remaining_time[processes->size];
    for (int i = 0; i < processes->size; i++) {
        Process *p = (Process *)ptr->data;
        remaining_time[i] = p->runtime;
        ptr = ptr->next;
    }

    int time = 0;
    int quantum = 1;  // Time slice for Round Robin

    while (1) {
        int done = 1;

        for (int i = 0; i < processes->size; i++) {
            Process *p = (Process *)ptr->data;

            if (remaining_time[i] > 0) {
                done = 0;

                // Process will run for the quantum or its remaining time, whichever is smaller
                int run_time = (remaining_time[i] < quantum) ? remaining_time[i] : quantum;

                // Update process times
                time += run_time;
                remaining_time[i] -= run_time;
                p->endTime = time;

                // Move the pointer to the next process in the queue
                ptr = ptr->next;
            }
        }

        if (done)
            break;
    }

    return avg_rr;
}