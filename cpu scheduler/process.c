#include <stdio.h>
#include <string.h>
#include "process.h"
#include "evaluate.h"



int compareBurst_t(const void *p1, const void *p2){
    const Process *pp1 = (const Process*)p1, *pp2 = (const Process*)p2;
    int burst_comp = (pp1 -> burst_t) - (pp2 -> burst_t);
    if(burst_comp == 0){

        return pp1 -> id - pp2 ->id;
    }
    
    return (pp1 -> burst_t) - (pp2 -> burst_t);
    

}

int comparePriority(const void *p1, const void *p2){
    const Process *pp1 = (const Process*)p1, *pp2 = (const Process*)p2;
    int priority_comp = (pp1 -> priority) - (pp2 -> priority);
    //if priority of pp1 is higher(number is lower), value is < 0
    if(priority_comp == 0){

        return pp1 -> id - pp2 ->id;
    }
    
    return (pp1 -> priority) - (pp2 -> priority);
}

int compareArrival_t(const void *p1, const void *p2){
    const Process *pp1 = (const Process*)p1, *pp2 = (const Process*)p2;
    int arrival_comp = (pp1 -> arrival_t) - (pp2 -> arrival_t);
    if(arrival_comp == 0){

        return pp1 -> id - pp2 ->id;
    }
    
    return (pp1 -> arrival_t) - (pp2 -> arrival_t);

}

int calcTotalBT(Process *p, int size){
    int total = 0;
   for(int i = 0; i < size; i++){
        total+=p[i].burst_t;
    }
    //printf("total burst time: %d\n", total);
    return total;
}


//the capacity of the 
//add p2 to queue of p1
void addProcess(Process *p1, Process *p2,int *size, int n){
//keep track of how many processes there are in the array currently
        // Insert element
        p1[*size] = p2[n];
        (*size)++;
}


void deleteProcess(Process *p, int *size, int n)
{
    // Delete process at index n 
    //Process *p1 = NULL;
    if (*size == 1) {
        // If there's only one element, just reduce the size
        *size = 0;
    } else {
        for (int i = n; i < *size- 1; i++)
        p[i] = p[i + 1];
        (*size)--; 
    }    
    
}

void addArrivalTime(Process *p, int size){

    for(int i = 0; i < size; i++){
        p[i].arrival_t++;
    }
}

void init_job_q(Process *jobq, int p_count){
    //scanf("%d", p_count);
    int i = 0;
    //initialize id and time elapsed to 0
    while(i < p_count){
        jobq[i].id = 0;
        jobq[i].t_elapsed= 0;
        i++;
    }
    i = 0;
    printf("Enter details for job\n");
    printf("Format: id arrival_time burst_time priority\n");
    while(i < p_count){
        jobq[i].id = i+1;
        //randomly generate io burst time
        scanf("%d %d %d", &jobq[i].arrival_t, &jobq[i].burst_t, &jobq[i].priority);
        i++;
    }
}

void set_ready_q(Process *jobq, Process *readyq, int *jobq_size, int *readyq_size, int time_elapsed){
    //move ready processes from job queue to ready queue
    //iterate through each process in jobq and determine if the process has 
    //arrived in ready queue
    int i = 0;
    while (i < *jobq_size) { //iterate as much as the jobq
        if (jobq[i].arrival_t <= time_elapsed) {
            addProcess(readyq, jobq, readyq_size, i);
            deleteProcess(jobq, jobq_size, i);
        } else {
            i++; // Only increment i if no process is moved
        }
    }
    

}

void init_running_q(Process *readyq, Process *runq, int *readyq_size, int *runq_size){
    //there should only be one element in running_q
    if(*runq_size < 1){
        addProcess(runq, readyq, runq_size, 0);
        deleteProcess(readyq, readyq_size, 0);

    }

}

void run(Process *p){
    p[0].t_elapsed++;
    p[0].length++;
    //printf("%d time elapsed: %d\n", p[0].id ,p[0].t_elapsed);
}

int terminate(Process *runq, Process *completeq, int *size1, int *size2, int time_elapsed){
    //if the time elapsed of 
    if(runq[0].t_elapsed >= runq[0].burst_t){
        //printf("process terminated\n");
        //calculate waiting time and turnaround time
        calcTAT(runq, 0, time_elapsed);
        calcWT(runq, 0, time_elapsed);

        //add completed queue to end of finished queue
        addProcess(completeq, runq, size2, 0);

        //delete process from running queue
        deleteProcess(runq, size1, 0);

        //calculate waiting time and turnaround time
        /*
        calcTAT(completeq, *size2-1, time_elapsed);
        calcWT(completeq, *size2-1, time_elapsed);
        */
       return 1;

    }
    return 0;

}

void swap_process(Process *p1, Process *p2, int index1, int index2){
    Process temp = p1[index1];
    p1[index1] = p2[index2];
    p2[index2] = temp;
}


int preemption(Process *p1, Process *p2, int size1, int size2, int index1, int index2, const char *str){
    //each queue should have at least one process
    int i = 0;
    if(size1 < 1 || size2 < 1){
        return 0;
    }
    //need to compare at index
    if((strcmp(str, "priority") == 0)){
        i = comparePriority(p1, p2);
        
    }
    else if((strcmp(str, "arrival time") == 0)){
        i = compareArrival_t(p1, p2);
    }
    else if((strcmp(str, "burst time") == 0))
    {
        i = compareBurst_t(p1, p2);
    }
    else if(((strcmp(str, "time quantum") == 0))){
        if(p2[0].t_elapsed %2 == 0 && p2[0].t_elapsed!=0){
            //if(p1[index1].id < p2[index2].id)
            i = -1;
            
        }
        
    }
    
    if(i <0 ){
    //if p1 has higher priority/shorter arrival time/shorter burst time, swap
        swap_process(p1, p2, index1, index2);
        //for RR, send preempted process to the end of the queue
        if(((strcmp(str, "time quantum") == 0))){
            swap_process(p1, p1, index2, size1-1);
        }
        printf("preempted!\n");
        return 1;
    }
    return 0;

}