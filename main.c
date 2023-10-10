#include <stdio.h>
#include "process.h"
#include "queue.h"
#include "algos.h"

int main(int argc,char **argv) {
	int counter = 0;
	//Run 5 times
	averageStats avg_fcfs[6],avg_sjf[6],avg_srf[6],avg_rr[6],avg_hpfp[6],avg_hpfnp[6],final[6];

	while (counter<5){
		//Generate Processes
		printf("*****************************************************************************************************************************\n");
		printf("Round %d\n",counter+1);
		printf("*****************************************************************************************************************************\n");

		Queue * processList = generateProcesses(52);
		Node * ptr = processList->front;
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("Process ID | Arrival Time | Run Time | Priority |\n");
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		while(ptr != NULL) {
			Process *p = (Process *)ptr->data;
			printf("%10c | %12.1d | %8.1d| %8d |\n",p->pid,p->arrival_time,p->runtime,p->priority);
			ptr = ptr->next;
		}
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("Total Number of Processes : %d\n",processList->size);
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");

		//Run FCFS
		avg_fcfs[counter] = firstComeFirstServe(processList);
		resetProcesses(processList);
		//Run SJF
		// avg_sjf[counter] = shortest_job_first_np(processList);
		// resetProcesses(processList);
		// //Run SRF
		avg_srf[counter] = shortest_remaining_time_p(processList);
		resetProcesses(processList);
		// //Run RR
		avg_rr[counter] = roundRobinPreemptive(processList,5);
		resetProcesses(processList);
		// //Run HPF P
		avg_hpfp[counter] = highest_priority_first_p(processList);
		resetProcesses(processList);
		//Run HPF NP
		avg_hpfnp[counter] = highest_priority_first_np(processList);
		resetProcesses(processList);
		//Run HPF P Aging
		//Run HPF NP Aging
		counter++;
	}
	// Initialiazing to 0 //
	for (int i = 0; i<6 ; i++)
	{
			final[i].avgResponseTime = 0;
			final[i].avgWaitTime = 0;
			final[i].avgTurnaround = 0;
			final[i].avgThroughput = 0;
	}

	// adding average values received from all the rounds //
	for (int i = 0; i<5 ; i++)
	{
			final[0].avgResponseTime += avg_fcfs[i].avgResponseTime;
			final[1].avgResponseTime += avg_sjf[i].avgResponseTime;
			final[2].avgResponseTime += avg_srf[i].avgResponseTime;
			final[3].avgResponseTime += avg_rr[i].avgResponseTime;
			final[4].avgResponseTime += avg_hpfp[i].avgResponseTime;
			final[5].avgResponseTime += avg_hpfnp[i].avgResponseTime;

			final[0].avgWaitTime += avg_fcfs[i].avgWaitTime;
			final[1].avgWaitTime += avg_sjf[i].avgWaitTime;
			final[2].avgWaitTime += avg_srf[i].avgWaitTime;
			final[3].avgWaitTime += avg_rr[i].avgWaitTime;
			final[4].avgWaitTime += avg_hpfp[i].avgWaitTime;
			final[5].avgWaitTime += avg_hpfnp[i].avgWaitTime;

			final[0].avgTurnaround += avg_fcfs[i].avgTurnaround;
			final[1].avgTurnaround += avg_sjf[i].avgTurnaround;
			final[2].avgTurnaround += avg_srf[i].avgTurnaround;
			final[3].avgTurnaround += avg_rr[i].avgTurnaround;
			final[4].avgTurnaround += avg_hpfp[i].avgTurnaround;
			final[5].avgTurnaround += avg_hpfnp[i].avgTurnaround;

			final[0].avgThroughput += avg_fcfs[i].avgThroughput;
			final[1].avgThroughput += avg_sjf[i].avgThroughput;
			final[2].avgThroughput += avg_srf[i].avgThroughput;
			final[3].avgThroughput += avg_rr[i].avgThroughput;
			final[4].avgThroughput += avg_hpfp[i].avgThroughput;
			final[5].avgThroughput += avg_hpfnp[i].avgThroughput;
	}

	// calulating average values for all the algorithms //
	for (int i = 0; i<6 ; i++)
	{
			final[i].avgResponseTime /= 5;
			final[i].avgWaitTime /= 5;
			final[i].avgTurnaround /= 5;
			final[i].avgThroughput /= 5;
	}

	//printing final statistics output //
	printf("*****************************************************************************************************************************\n");
	printf("*****************************************************************************************************************************\n");
	printf("\nThe average of the 5 runs of all algorithms is as follows:\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("First Come First Serve:\n");
	printf("Average Response Time : %.1f\n",final[0].avgResponseTime);
	printf("Average Wait Time : %.1f\n",final[0].avgWaitTime);
	printf("Average Turn Around Time :%.1f\n",final[0].avgTurnaround);
	printf("Average throughput :%.1f\n",final[0].avgThroughput);
	// printf("-----------------------------------------------------------------------------------------------------------------------------\n");
// 	printf("Shortest Job First Non Preemptive:\n");
// 	printf("Average Response Time : %.1f\n",final[1].avgResponseTime);
// 	printf("Average Wait Time : %.1f\n",final[1].avgWaitTime);
// 	printf("Average Turn Around Time :%.1f\n",final[1].avgTurnaround);
// 	printf("Average throughput :%.1f\n",final[1].avgThroughput);
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("Shortest Remaining Time First Preemptive:\n");
	printf("Average Response Time : %.1f\n",final[2].avgResponseTime);
	printf("Average Wait Time : %.1f\n",final[2].avgWaitTime);
	printf("Average Turn Around Time :%.1f\n",final[2].avgTurnaround);
	printf("Average throughput :%.1f\n",final[2].avgThroughput);
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("Round Robin Preemptive:\n");
	printf("Average Response Time : %.1f\n",final[3].avgResponseTime);
	printf("Average Wait Time : %.1f\n",final[3].avgWaitTime);
	printf("Average Turn Around Time :%.1f\n",final[3].avgTurnaround);
	printf("Average throughput :%.1f\n",final[3].avgThroughput);
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("Highest Priority First Preemptive:\n");
	printf("Average Response Time : %.1f\n",final[4].avgResponseTime);
	printf("Average Wait Time : %.1f\n",final[4].avgWaitTime);
	printf("Average Turn Around Time :%.1f\n",final[4].avgTurnaround);
	printf("Average throughput :%.1f\n",final[4].avgThroughput);
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
 	printf("Highest Priority First Non Preemptive:\n");
 	printf("Average Response Time : %.1f\n",final[5].avgResponseTime);
 	printf("Average Wait Time : %.1f\n",final[5].avgWaitTime);
 	printf("Average Turn Around Time :%.1f\n",final[5].avgTurnaround);
 	printf("Average throughput :%.1f\n",final[5].avgThroughput);
 	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
}
