#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "algos.h"

// Function to create a process_stat structure for a process
Process *create_process_stat(Process *proc);

// Comparator function for sorting processes based on remaining time to completion
int compareRemainingTime(void *data1, void *data2)
{
  Process *ps1 = (Process *) data1;
	Process *ps2 = (Process *) data2;
	if((ps1->runtime - ps1->executionTime)< (ps2->runtime - ps2->executionTime)) {
		return -1;
	} else {
		return 1;
	}
}

// Function to print the contents of a queue for testing during shortest remaining time to completion
void print_queue_srtc(Queue * q)
{
  if (q->front != NULL)
  {
    Node *n = q->front;
    printf("Queue Contains:\n");
    while(n != NULL)
    {
      Process *ps = n->data;
      //Process *p = ps->Process;
      printf("Process Id %c Remaining Time %d\n",ps->pid,(ps->runtime - ps->executionTime));
      n = n->next;
    }
  }
  return;
}

// Implementation of Shortest Remaining Time to Completion (SRTC) preemptive scheduling
average_stats shortest_remaining_time_p(linked_list *processes) {
    int time_quantum = 0;

    // Create a queue for processes
    queue *process_queue = create_queue();
    
    // Create a linked list for managing the order of processes during preemption
    linked_list *order_list = create_linked_list();

    // Point to the head of the process list
    node *process_pointer = processes->head;

    // Check if there are processes to schedule
    if (process_pointer == NULL) {
        fprintf(stderr, "No processes to schedule\n");
    }

    // While the process queue is not empty or the time quantum is less than 100
    process_stat *scheduled_process = NULL;
    printf("\n\nShortest Remaining Time To Completion Preemptive:\n");

    while (time_quantum < 100 || scheduled_process != NULL) {
        // If there is a scheduled process, enqueue it
        if (scheduled_process != NULL) {
            enqueue(process_queue, scheduled_process);
            scheduled_process = NULL;
        }

        // Check for incoming new processes and enqueue them in the queue
        if (process_pointer != NULL) {
            process *new_process = (process *)(process_pointer->data);
            while (process_pointer != NULL && new_process->arrival_time <= time_quantum) {
                enqueue(process_queue, create_process_stat(new_process));
                process_pointer = process_pointer->next;

                if (process_pointer != NULL) {
                    new_process = (process *)(process_pointer->data);
                }
            }

            // Sort all the processes that have arrived based on their remaining time to completion
            sort(process_queue, compare_remaining_time);
        }

        // If there is no scheduled process, check the process queue and schedule one
        if (scheduled_process == NULL && process_queue->size > 0) {
            scheduled_process = (process_stat *)dequeue(process_queue);

            // If the process has not started before the time quantum of 100, remove it from the queue
            while (time_quantum >= 100 && scheduled_process->start_time == -1) {
                scheduled_process = (process_stat *)dequeue(process_queue);
            }
        }

        // Execute the scheduled process or print an underscore if none is scheduled
        if (scheduled_process != NULL) {
            process *current_process = scheduled_process->proc;

            // Add the current running process to the time chart
            printf("%c", current_process->pid);

            // Update the current process's statistics
            if (scheduled_process->start_time == -1) {
                scheduled_process->start_time = time_quantum;
            }

            scheduled_process->run_time++;

            // Check if the process has completed
            if (scheduled_process->run_time >= current_process->run_time) {
                scheduled_process->end_time = time_quantum;
                add_node(order_list, scheduled_process);
                scheduled_process = NULL;
            }
        } else {
            printf("_");
        }

        // Increase the time quantum
        time_quantum++;
    }

    // Print Process Statistics
    return print_policy_stat(order_list);
}
