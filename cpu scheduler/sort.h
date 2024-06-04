#ifndef SORT_H
#define SORT_H
#include <stdio.h>
#include "process.h"

// Utility function to swap tp integers
void swap(Process* p1, Process* p2);

int partition(Process *p, int low, int high, int (*compare)(const void*, const void*));

// The Quicksort function Implement

void quickSort(Process *p, int low, int high, int (*compare)(const void *, const void*));

#endif
