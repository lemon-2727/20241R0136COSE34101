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
#include "RR.h"
#include <string.h>


void RR(Process* p, int p_count){

    int io_count = 0;
    //initialize size of queues
            srand(100);

    int jobq_size = 0, readyq_size = 0, runningq_size = 0, waitingq_size = 0, completedq_size = 0, ganttchart_size = 0;
    //user inputs the number of processes
    //scanf("%d", &p_count);

    jobq_size = p_count;
    //initialize queues
    Process *job_queue;
    Process *ready_queue;
    Process *running_queue;
    Process *waiting_queue;
    Process *completed_queue;
    Process *ganttchart;
    

    job_queue = (Process *)malloc(sizeof(Process) * p_count);
    ready_queue = (Process *)malloc(sizeof(Process) * p_count);
    running_queue = (Process *)malloc(sizeof(Process) * p_count);
    waiting_queue = (Process *)malloc(sizeof(Process) * p_count);
    completed_queue = (Process *)malloc(sizeof(Process) * p_count);
    ganttchart = (Process *)malloc(sizeof(Process) * 100);

    //copy original job queue
    memcpy(job_queue, p, p_count * sizeof(int));
    for(int i = 0; i < p_count; i++){
        job_queue[i].id = p[i].id;
        job_queue[i].arrival_t = p[i].arrival_t;
        job_queue[i].burst_t = p[i].burst_t;
        job_queue[i].priority = p[i].priority;
        job_queue[i].t_elapsed= 0;
        job_queue[i].ioburst_t= 0;

    }

    int total_bt = calcTotalBT(job_queue, p_count);
 
    int time_elapsed = 0;

    int time_quantum = 0;
    int tq_elpased = 0;
    printf("Enter time quantum: ");


    scanf("%d", &time_quantum);
    
    
    set_ready_q(job_queue, ready_queue, &jobq_size, &readyq_size, time_elapsed);
    time_elapsed++;

    int show_process = 0;
    printf("Show process?");
    scanf("%d", &show_process);

    printf("Round Robin Scheduling\n");

    //quickSort(ready_queue, 0, readyq_size-1, compareArrival_t);
    printQueue(job_queue, jobq_size, p_count);
    printQueue(ready_queue, readyq_size, p_count);
    while(time_elapsed <= total_bt){


        if(show_process){
            puts("==============================");
            printf("total time elapsed: %d\n", time_elapsed);
            printf("print job queue\n");
            printQueue(job_queue, jobq_size, p_count);
            printf("print ready queue\n");
            printQueue(ready_queue, readyq_size, p_count);

        }
        
        if(IOBurst(running_queue, waiting_queue, &runningq_size, &waitingq_size, p_count, &io_count, total_bt, time_elapsed)){
           //copy this process into the gantt chart
            addProcess(ganttchart, waiting_queue, &ganttchart_size, 0);
            //reset length of process
            waiting_queue[0].length = 0;
            continue;
        }
        
        
        //run I/O for 1 secif a process got sent into the waiting queue
        runIO(ready_queue, waiting_queue, &readyq_size, &waitingq_size);
        
        printf("print waiting queue\n");
        printQueue(waiting_queue, waitingq_size, p_count);
        
    
       if(show_process){
            printf("print waiting queue\n");
            printQueue(waiting_queue, waitingq_size, p_count);
        }


        //choose next process to run
        init_running_q(ready_queue, running_queue, &readyq_size, &runningq_size);

        //check if preemption should happen
        //printf("print run queue\n");
        if(preemption(ready_queue, running_queue, readyq_size, runningq_size, 0, 0, "time quantum", time_quantum)){
            //preempted process should be the first element in ready queue
            //copy this process into the gantt chart
            //if(ready_queue[0].t_elapsed%2 != 0)
                addProcess(ganttchart, ready_queue, &ganttchart_size, readyq_size-1);

        
            //reset length of process
            ready_queue[readyq_size-1].length = 0;
        }

        
        //run process for 1 sec
        if(runningq_size> 0){
            printf("running\n");
            run(running_queue);

        }
        //no processes in runningqueue
        else{
            printf("idleing \n");
            Process *p = (Process *)malloc(sizeof(Process));
            p[0].id = 0;;
            p[0].length = 1;
            p[0].burst_t = 1;
            total_bt++;
            addProcess(ganttchart, p, &ganttchart_size, 0);
            free(p);

        }
        
        //printQueue(running_queue, runningq_size, p_count);
        if(show_process){
            printf("print run queue\n"); 
            printQueue(running_queue, runningq_size, p_count);
        }
        
        
        //check if burst time of process in running queue has ended
       if(terminate(running_queue, completed_queue, &runningq_size, &completedq_size, time_elapsed)){
            //terminated process should be the last element in completed queue
            addProcess(ganttchart, completed_queue, &ganttchart_size, completedq_size-1);
       }
        //printf("print finished queue\n");
        //printQueue(completed_queue, completedq_size, p_count);
        if(show_process){
            printf("print finished queue\n");
            printQueue(completed_queue, completedq_size, p_count);
        }

        //printf("set ready queue\n");
        //reset ready queue
        
        set_ready_q(job_queue, ready_queue, &jobq_size, &readyq_size, time_elapsed);
        //increment time by 1 second
        time_elapsed++;

        

    }
    //printf("print gantt chart\n");

    //printQueue(ganttchart, ganttchart_size, p_count);
    
    int totalWT = calcTotalWT(completed_queue, completedq_size);
    int totalTAT = calcTotalTAT(completed_queue, completedq_size);

    printPinfo(completed_queue, completedq_size);
    
    printf("average waiting time: %d/%d = %lf\n", totalWT, p_count, calcAverage(totalWT, p_count));
    printf("average turnaround time: %d/%d = %lf\n",totalTAT, p_count, calcAverage(totalTAT, p_count));
    printGC(ganttchart, ganttchart_size);

    for(int i = 0; i < p_count; i++){
        completed_queue[i].length = 0;
        completed_queue[i].iot_elapsed = 0;
        completed_queue[i].ioburst_t = 0;
    }
    
    //free queuess
    free(job_queue);
    free(ready_queue);
    free(running_queue);
    free(waiting_queue);
    free(completed_queue);
    free(ganttchart);

}
