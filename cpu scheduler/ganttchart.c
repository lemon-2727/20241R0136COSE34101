#include <stdio.h>
#include "process.h"
#include "ganttchart.h"

/*
void ganttarr(Process *queue, Process *ganttarr, int *size, int index){
    for(int i = 0; i < *size; i++){
        addProcess(queue, ganttarr, size, 0);
    }
    
}
*/

void printQueue(Process *p, int size, int p_count){
    for(int i = 0; i< p_count; i++){
        printf("------");
    }
    printf("\n");
    printf("|");
    for(int i = 0; i < size; i++){
        printf("P%d", p[i].id);
        for(int j = 0; j< 2; j++){
            printf(" ");

        }
        printf("|");
    }
    printf("\n");
    for(int i = 0; i< p_count; i++){
        printf("------");
    }
    printf("\n");
    printf("\n");
}
//print table of process information from terminated queue

void printGC(Process *p, int size){
    //length == burst time or time elapsed print as much as 
    int total = 0;
    //line 1
    for(int i = 0; i < calcTotalBT(p, size); i++){
        printf("=");
    }
    printf("\n");
    //line 2
    printf("|");
    for(int i = 0; i < size; i++){
        printf("P%d", p[i].id);
        for(int j = 0; j< p[i].length; j++){
            printf(" ");

        }
        printf("|");
    }
    printf("\n");
    ///line 3
    printf("0");
    int buffer;
    for(int i = 0; i < size; i++){
        printf("  ");
        buffer = 0;
        //two digits change spacing, so use a buffer to adjust for extra spacing
        if(total >= 10){
                buffer = 1;
            }
        for(int j = buffer+0; j< p[i].length; j++){
            printf(" ");

        }
        //printf(" ");
        total+=p[i].length;
        printf("%d", total);
    }
    printf("\n");

}