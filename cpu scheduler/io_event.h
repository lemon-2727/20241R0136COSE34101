#ifndef IO_EVENT_h
#define IO_EVENT_h
#include <stdio.h>
#include "process.h"


//I/o event happens randomly
void runIO(Process *ready, Process *waitq, int *size1, int *size2);

int IOBurst(Process *runq, Process *waitq, int *size1, int *size2, int p_count, int *io_count, int total_bt, int time_elapsed);
//create move to different qsueue function for io event

//int generateIO{};


#endif