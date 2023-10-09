#include <stdio.h>
#include <stdlib.h>
#include "../queue.h"
#include "../process.h"
#include "../algos.h"


averageStats highest_priority_first_p(Queue *processes){
    int t = 0;
    //Queues for processes
    Queue* q1 = createQueue();
    Queue* q2 = createQueue();
    Queue* q3 = createQueue();
    Queue* q4 = createQueue();
    //linked list for managaing process order in preemeption
    Linked_List* ll_1 = createQueue();
    Linked_List* ll_2 = createQueue();
    Linked_List* ll_3 = createQueue();
    Linked_List* ll_4 = createQueue();

    Node *incoming_proc = processes->front;
	if(incoming_proc == NULL) {
		fprintf(stderr,"No Process to schedule\n");
	}
	//while process queue is not empty or time quanta is less than 100
	Process * scheduledProcess = NULL;

    while(t<100 || scheduledProcess!=NULL){

        if(scheduledProcess!=NULL){
            if(scheduledProcess->priority == 1) enqueue(q1,scheduledProcess);
            if(scheduledProcess->priority == 2) enqueue(q2,scheduledProcess);
            if(scheduledProcess->priority == 3) enqueue(q3,scheduledProcess);
            if(scheduledProcess->priority == 4) enqueue(q4,scheduledProcess);

            //enqueue(process_queue,scheduled_process);
            //scheduled_process = NULL;
        }

        if(incoming_proc != NULL) {
			Process * new_process = (Process *)(incoming_proc->data);
			while(incoming_proc !=NULL && new_process->arrival_time <= t) {
                if(new_process->priority == 1) {enqueue(q1,createProcess(new_process->pid, new_process->arrival_time, new_process->runtime, new_process->priority));}
                if(new_process->priority == 2) {enqueue(q2,createProcess(new_process->pid, new_process->arrival_time, new_process->runtime, new_process->priority));}
                if(new_process->priority == 3) {enqueue(q3,createProcess(new_process->pid, new_process->arrival_time, new_process->runtime, new_process->priority));}
                if(new_process->priority == 4) {enqueue(q4,createProcess(new_process->pid, new_process->arrival_time, new_process->runtime, new_process->priority));}
		        sort(q1,compare);
                sort(q2,compare);
                sort(q3,compare);
                sort(q4,compare);
				incoming_proc = incoming_proc->next;
				if(incoming_proc!=NULL){
					new_process = (Process *)(incoming_proc->data);
                }
			}
      // sort all the processes that have arrived based on their remaining running time to completion //
      //sort(process_queue,compare_priority);
        }

        if(scheduledProcess == NULL) {
            if (q1->size > 0) scheduledProcess = (Process *) dequeue(q1);
            else if (q2->size > 0) scheduledProcess = (Process *) dequeue(q2);
            else if (q3->size > 0) scheduledProcess = (Process *) dequeue(q3);
            else if (q4->size > 0) scheduledProcess = (Process *) dequeue(q4);
            // If the process has not started before quanta 100, remove the process from the queue and take the next process in queue for execution //
            /*
            while(t>=100 && scheduled_process->start_time == -1)
            {
              scheduled_process = (process_stat *) dequeue(process_queue);
            }
            */
            if (t>=100 && scheduledProcess->startTime == -1){
            //free(scheduled_process);
            scheduledProcess = NULL;
            continue;
            }
		}

        if(scheduledProcess != NULL) {
  			//Process * proc = scheduledProcess->proc;

  			//add current running process to the time chart
  			printf("%c",scheduledProcess->pid);

  			//update current processes stat
  			if(scheduledProcess->startTime == -1) {
  				scheduledProcess->startTime = t;
  			}

  			scheduledProcess->runtime++;

            //printf("Process name %c", proc->pid);

            if(scheduledProcess->runtime >= scheduledProcess->runtime) {
                scheduledProcess->endTime = t;
                if(scheduledProcess->priority == 1) enqueue(ll_1,scheduledProcess);
                else if(scheduledProcess->priority == 2) enqueue(ll_2,scheduledProcess);
                else if(scheduledProcess->priority == 3) enqueue(ll_3,scheduledProcess);
                else if(scheduledProcess->priority == 4) enqueue(ll_4,scheduledProcess);
                //add_node(ll,scheduled_process);
                scheduledProcess = NULL;
                //free(scheduled_process);
            }
        }
        
        else {
    	    printf("_");
  		}
  		//increase the time
  		t++;
    }

    //Print Process Stat
    averageStats avg1,avg2,avg3,avg4,avg;
    printf("\nFor Priority Queue 1");
    avg1 = print_policy_stat(ll_1);
    printf("\nFor Priority Queue 2");
    avg2 = print_policy_stat(ll_2);
    printf("\nFor Priority Queue 3");
    avg3 = print_policy_stat(ll_3);
    printf("\nFor Priority Queue 4");
    avg4 = print_policy_stat(ll_4);

    avg.avgResponseTime = (avg1.avgResponseTime + avg2.avgResponseTime + avg3.avgResponseTime + avg4.avgResponseTime)/4 ;
    avg.avgWaitTime = (avg1.avgWaitTime + avg2.avgWaitTime + avg3.avgWaitTime + avg4.avgWaitTime)/4 ;
    avg.avgTurnaround = (avg1.avgTurnaround + avg2.avgTurnaround + avg3.avgTurnaround + avg4.avgTurnaround)/4 ;
    avg.avgThroughput = (avg1.avgThroughput + avg2.avgThroughput + avg3.avgThroughput + avg4.avgThroughput) ;

    printf("The average statistics High Priority First Preemptive considering all priority queues is:\n");
    printf("Average Response Time : %.1f\n",avg.avgResponseTime);
    printf("Average Wait Time : %.1f\n",avg.avgWaitTime);
    printf("Average Turn Around Time :%.1f\n",avg.avgTurnaround);

    return avg;
}