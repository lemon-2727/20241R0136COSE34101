#include <stdio.h>
#include "process.h"
#include "evaluate.h"

void calcTAT(Process *p, int index, int time_elapsed){
    p[index].turnaround_t = time_elapsed - p[index].arrival_t;
    //printf("tat: %d\n", p[index].turnaround_t );
}

void calcWT(Process *p, int index, int time_elapsed){
    p[index].waiting_t = p[index].turnaround_t - p[index].burst_t;
    //printf("wt: %d\n", p[index].waiting_t );
}
//need a copy of the job queue? or some array that stores all the values 
int calcTotalTAT(Process *p, int size){
    int total = 0;
    for(int i = 0; i < size; i++){
        total+= p[i].turnaround_t;
    }
    return total;
}

int calcTotalWT(Process *p, int size){
    int total = 0;
    for(int i = 0; i < size; i++){
        total+= p[i].waiting_t;
    }
    return total;
}

double calcAverage(int total, int size){
    return (double)total/size;
}
