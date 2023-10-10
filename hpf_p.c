#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "algos.h"

int comparePriorityHPFP(void * data1, void * data2)
{
  Process * ps1 = (Process *) data1;
	Process * ps2 = (Process *) data2;
	if(ps1->priority < ps2->priority) {
		return -1;
	}else if ((ps1->priority == ps2->priority) &&  (ps1->arrival_time < ps2->arrival_time))
  {
    return -1;
  }
   else {
		return 1;
	}
}

averageStats highest_priority_first_p(Queue *processes){
    int t = 0;
    //Queues for processes
    Queue* q1 = createQueue();
    Queue* q2 = createQueue();
    Queue* q3 = createQueue();
    Queue* q4 = createQueue();
    //linked list for managaing process order in preemeption
    Queue* ll_1 = createQueue();
    Queue* ll_2 = createQueue();
    Queue* ll_3 = createQueue();
    Queue* ll_4 = createQueue();

    Node *process_pointer = processes->front;
	  if(process_pointer == NULL) {
		  fprintf(stderr,"No Process to schedule\n");
	  }

    printf("\nHighest Priority First Preemptive:\n");
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

        if(process_pointer != NULL) {
			Process * new_process = (Process *)(process_pointer->data);
			while(process_pointer !=NULL && new_process->arrival_time <= t) {
                if(new_process->priority == 1) enqueue(q1,new_process);
                if(new_process->priority == 2) enqueue(q2,new_process);
                if(new_process->priority == 3) enqueue(q3,new_process);
                if(new_process->priority == 4) enqueue(q4,new_process);
                sort(q1,comparePriorityHPFP);
                sort(q2,comparePriorityHPFP);
                sort(q3,comparePriorityHPFP);
                sort(q4,comparePriorityHPFP);
				process_pointer = process_pointer->next;
				if(process_pointer!=NULL){
					new_process = (Process *)(process_pointer->data);
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

  			//add current running process to the time chart
  			printf("%c",scheduledProcess->pid);

  			//update current processes stat
  			if(scheduledProcess->startTime == -1) {
  				scheduledProcess->startTime = t;
  			}

  			scheduledProcess->executionTime++;

            //printf("Process name %c", proc->pid);

            if(scheduledProcess->executionTime >= scheduledProcess->runtime) {
                scheduledProcess->endTime = t;
                if(scheduledProcess->priority == 1) enqueue(ll_1, scheduledProcess);
                else if(scheduledProcess->priority == 2) enqueue(ll_2, scheduledProcess);
                else if(scheduledProcess->priority == 3) enqueue(ll_3, scheduledProcess);
                else if(scheduledProcess->priority == 4) enqueue(ll_4, scheduledProcess);
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
    avg.avgThroughput = (avg1.avgThroughput + avg2.avgThroughput + avg3.avgThroughput + avg4.avgThroughput)/4 ;

    printf("The average statistics High Priority First Preemptive considering all priority queues is:\n");
    printf("Average Response Time : %.1f\n",avg.avgResponseTime);
    printf("Average Wait Time : %.1f\n",avg.avgWaitTime);
    printf("Average Turn Around Time :%.1f\n",avg.avgTurnaround);

    return avg;
}