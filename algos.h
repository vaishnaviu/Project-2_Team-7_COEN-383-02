#ifndef _algos_h_
#define _algos_h_
#include "queue.h"

struct average_stats{
	float avgResponseTime;
	float avgWaitTime;
	float avgTurnaround;
	float avgThroughput;
};

typedef struct average_stats averageStats;

averageStats firstComeFirstServe(Queue *processes);
// averageStats shortest_job_first_np(Queue *processes);
// averageStats shortest_remaining_time_p(Queue *processes);
// averageStats round_robin_p(Queue *processes,int time_slice);
averageStats highest_priority_first_p(Queue *processes);
// averageStats highest_priority_first_np(Queue *processes);
// averageStats highest_priority_first_p_aging(Queue *processes);
// averageStats highest_priority_first_np_aging(Queue *processes);
averageStats print_policy_stat(Queue * processes);


#endif