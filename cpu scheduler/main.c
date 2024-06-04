#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "sort.h"
#include "FCFS.h"
#include "Priority.h"
#include "ganttchart.h"
#include "io_event.h"
#include <time.h>
#include <unistd.h>
#include "evaluate.h"
#include <string.h>
#include "RR.h"
#include "SJF.h"

int main(){
    
    
    //user can choose number of random I/O processes
    int p_count;
    int io_count;
    int i = 0, jobq_size = 0, readyq_size = 0, runningq_size = 0, waitingq_size = 0, completedq_size = 0, ganttchart_size = 0;
    //user inputs the number of processes
    printf("Enter number of processes: ");
    scanf("%d", &p_count);

    
    //initialize queues
    Process *job_queue;
    job_queue = (Process *)malloc(sizeof(Process) * p_count);
    init_job_q(job_queue, p_count);
    //Shortest job first (non-preemptive)
    FCFS(job_queue, p_count);
    SJF(job_queue, p_count, 0);
    //Shortest job first (non-preemptive)
    SJF(job_queue, p_count, 1);
    //priority (non-preemptive)
    Priority(job_queue, p_count, 0);
    //Priority (preemptive)
    Priority(job_queue, p_count, 1);
    //round robin
    RR(job_queue, p_count);


    

    



}