#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "algos.h"

// Implementation of highest priority first non preemptive //

averageStats highest_priority_first_np(Queue * processes)
{
  int t = 0;
  //Queues of processes
  Queue * q1 = createQueue();
  Queue * q2 = createQueue();
  Queue * q3 = createQueue();
  Queue * q4 = createQueue();

  Queue * ll_1 = createQueue();
  Queue * ll_2 = createQueue();
  Queue * ll_3 = createQueue();
  Queue * ll_4 = createQueue();
  Node * process_pointer = processes->front;
  if(processes->front == NULL) {
		fprintf(stderr,"No Process to schedule\n");
	}
  printf("\nHighest Priority First Non Preemptive:\n");
  
  Process * scheduled_process = NULL;
  while(t<100 || scheduled_process!=NULL ){//while process queue is not empty or time quanta is less than 100
		if(process_pointer != NULL) {
			Process * new_process = (Process *)(process_pointer->data);
			while(process_pointer !=NULL && new_process->arrival_time <= t) {
        if(new_process->priority == 1) enqueue(q1,new_process);
        if(new_process->priority == 2) enqueue(q2,new_process);
        if(new_process->priority == 3) enqueue(q3,new_process);
        if(new_process->priority == 4) enqueue(q4,new_process);

				process_pointer = process_pointer->next;
				if(process_pointer!=NULL)
        {
					new_process = (Process *)(process_pointer->data);
        }
			}

    }

    //if there is no scheduled process, then check process queue and schedule it //
		if(scheduled_process == NULL) {
      if (q1->size > 0) scheduled_process = (Process *) dequeue(q1);
      else if (q2->size > 0) scheduled_process = (Process *) dequeue(q2);
      else if (q3->size > 0) scheduled_process = (Process *) dequeue(q3);
      else if (q4->size > 0) scheduled_process = (Process *) dequeue(q4);
      if (t>=100 && scheduled_process->startTime == -1){
        scheduled_process = NULL;
        continue;
      }
    }


    if(scheduled_process != NULL) {

  			//add current running process to the time chart
  			printf("%c",scheduled_process->pid);

  			//update current processes stat
  			if(scheduled_process->startTime == -1) {
  				scheduled_process->startTime = t;
  			}

  			scheduled_process->executionTime++;

        if(scheduled_process->executionTime >= scheduled_process->runtime) {
          scheduled_process->endTime = t;
          if(scheduled_process->priority == 1) enqueue(ll_1,scheduled_process);
          else if(scheduled_process->priority == 2) enqueue(ll_2,scheduled_process);
          else if(scheduled_process->priority == 3) enqueue(ll_3,scheduled_process);
          else if(scheduled_process->priority == 4) enqueue(ll_4,scheduled_process);

          scheduled_process = NULL;
        }
      }else {
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

    printf("The average statistics High Priority First Non Preemptive considering all priority queues is:\n");
    printf("Average Response Time : %.1f\n",avg.avgResponseTime);
    printf("Average Wait Time : %.1f\n",avg.avgWaitTime);
    printf("Average Turn Around Time :%.1f\n",avg.avgTurnaround);

    return avg;

}