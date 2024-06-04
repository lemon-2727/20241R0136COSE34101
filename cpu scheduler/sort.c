#include <stdio.h>
#include "process.h"
#include "sort.h"

//in cases where the priority/burst time/ arrival time is the same,choose the one with the higher 

// Utility function to swap tp integers
void swap(Process* p1, Process* p2)
{
    Process temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(Process *p, int low, int high, int (*compare)(const void*, const void*))
{
    // choose the pivot
    Process pivot = p[high];

    // Index of smaller element and Indicate
    // the right position of pivot found so far
    int i = (low - 1);

    for (int j = low; j <= high; j++) {
        // If current element is smaller than the pivot
        if (compare(&p[j], &pivot) < 0) {
            // Increment index of smaller element
            i++;
            swap(&p[i], &p[j]);
        }
    }
    swap(&p[i + 1], &p[high]);
    return (i + 1);
}

// The Quicksort function Implement

void quickSort(Process *p, int low, int high, int (*compare)(const void *, const void*)){

    // when low is less than high
    if (low < high) {
        int part = partition(p, low, high, compare);
        quickSort(p, low, part - 1, compare);
        quickSort(p, part + 1, high, compare);
    }
}