#ifndef PROCESS
#define PROCESS
#include <stdio.h>

typedef struct process{
    int id;
    int ioburst_t;
    int burst_t;
    int priority; 
    int arrival_t;
    int turnaround_t;
    int waiting_t;
    
    int t_elapsed;
    int iot_elapsed;
    int length;
    int time_quantum;
    //char process_state[20];

}Process;

//void printQueue(Process *p, int size);

int compareBurst_t(const void *p1, const void *p2);

int comparePriority(const void *p1, const void *p2);

int compareArrival_t(const void *p1, const void *p2);

int compareId(const void *p1, const void *p2);

int calcTotalBT(Process *p, int size);

void addProcess(Process *p1, Process *p2, int *size1, int n);

void deleteProcess(Process *p, int *size, int n);

void addArrivalTime(Process *p, int size);

void init_job_q(Process *jobq, int p_count);

void set_ready_q(Process *jobq, Process *readyq, int *size1, int *size2, int time_elapsed);

void init_running_q(Process *readyq, Process *runq, int *runq_size, int *readyq_size);

void run(Process *p);

int terminate(Process *runq, Process *completeq, int *size1, int *size2, int time_elapsed);

int preemption(Process *p1, Process *p2, int size1, int size2, int index1, int index2, const char *str, int time_quantum);

void swap_process(Process *p1, Process *p2, int index1, int index2);

#endif

void swap_process(Process *p1, Process *p2, int index1, int index2);

#endif
