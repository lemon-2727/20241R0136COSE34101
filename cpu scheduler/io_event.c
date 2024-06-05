#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"


void runIO(Process *ready, Process *waitq, int *size1, int *size2){
    if(*size2 > 0){
        waitq[0].iot_elapsed++;
        //waitq[0].time
        //printf("id:%d io time elapsed: %d\n", waitq[0].id, waitq[0].iot_elapsed);
        if( waitq[0].iot_elapsed >= waitq[0].burst_t){
        //move process back to ready queue
        addProcess(ready, waitq, size1, 0);
        //remove process from running queue
        deleteProcess(waitq, size2, 0);
        }
    }

}


//I/o event happens randomly
int IOBurst(Process *runq, Process *waitq, int *size1, int *size2, int p_count, int *io_count, int total_bt, int time_elapsed){
     int max_IO = p_count;
    srand(time(NULL));
    int num = rand() % (2);
    int remaining_t = total_bt - time_elapsed;
    //int randomNumber = (rand() % (max - min + 1)) + min;
    //random i/o burst happens with a 50/50 chance
    //number of I/O burst should not exceed number of processes
    //to simulate actual I/O bursts, burst time is also decided randomly
    //I/O burst cannot happen when there is another process in the waiting queue
    //there also must be a process in the running queue
    //I/O needs to happen at least 1 seconds before total time 
    //for debugging 
    //printf("%d %d %d %d %d %d", num, *io_count, p_count, *size1, *size2, remaining_t);
    int var = 0;
    if((!(num ) && *io_count <= p_count/2) && (*size1 > 0 && *size2 == 0) && remaining_t > 1){
        printf("I/O interrupt! process id: %d\n", runq[0].id);
        //printf("num: %d\n", num);
        //burst time set randomly
        //minimum burst time is 1, max is 10
        srand(time(NULL));
        //!burst time is smaller than the total remaining time
        while(runq[0].burst_t > remaining_t){
            runq[0].burst_t = (rand() % (10 - 1 + 1)) + 1;
            
        }
        runq[0].ioburst_t = runq[0].burst_t;

        //move process to waiting queues
        addProcess(waitq, runq, size2, 0);
        //remove process from running queue
        deleteProcess(runq, size1, 0);
         (*io_count)++;
         return 1;
    }
    return 0;
    
}
