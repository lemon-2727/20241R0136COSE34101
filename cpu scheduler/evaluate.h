#include <stdio.h>
#include "process.h"

#ifndef EVALUATE_H
#define EVALUATE_H

void calcTAT(Process *p, int index, int time_elapsed);

void calcWT(Process *p, int index, int time_elapsed);

int calcTotalTAT(Process *p, int size);

int calcTotalWT(Process *p, int size);

double calcAverage(int total, int size);

#endif