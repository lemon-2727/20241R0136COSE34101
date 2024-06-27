#include <stdio.h>
#include "process.h"
#include "sort.h"

//in cases where the priority/burst time/ arrival time is the same,choose the one with the higher id

void swap(Process* p1, Process* p2)
{
    Process temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(Process *p, int low, int high, int (*compare)(const void*, const void*))
{
    // choose pivot
    Process pivot = p[high];

    int i = (low - 1);

    for (int j = low; j <= high; j++) {
        if (compare(&p[j], &pivot) < 0) {
            i++;
            swap(&p[i], &p[j]);
        }
    }
    swap(&p[i + 1], &p[high]);
    return (i + 1);
}


void quickSort(Process *p, int low, int high, int (*compare)(const void *, const void*)){

    // when low is less than high
    if (low < high) {
        int part = partition(p, low, high, compare);
        quickSort(p, low, part - 1, compare);
        quickSort(p, part + 1, high, compare);
    }
}
