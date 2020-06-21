// SORTING_STEP1.C [161113]
// Supplied for use with ELEC278 Lab 6
// ****************************************************************************
// SUGGESTED SOLUTION.
// Requirement is:
// Sort in descending order, and
// Report number of sorts.
// ****************************************************************************
//
// History:
// 161113	Hesham Farahat	First Release
// 171111	DA				Minor tweaking

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


// ****************************************
// Define one of the following two manifests:
//#define ASCENDING_ORDER	1
#define DESCENDING_ORDER	1
// ****************************************
#ifdef ASCENDING_ORDER
#include "maxheap.h"
#endif
#ifdef DESCENDING_ORDER
#include "minheap.h"
#endif


void print(int* a, int n)
// Print contents of array
{
	int i;
	for (i = 0; i < n; i++)	printf("%d ", a[i]);
	printf("\n");
}//print()

// ***************************************************************************
// Just a side note.  From user point of view, the requirement that the list
// be sorted in ascending or descending order is met by seeing the list
// displayed in the required order.  Some may realize that descending order
// can be accomplished by printing the list sorted in ascending order in
// reverse order - in other words, just by rewriting the for-loop above as:
//		for (i = n-1; i <= 0; i--)	printf("%d ", a[i]);
// This prints from the high-index to the low index, thus displaying the list
// in the opposite order.
// ****************************************************************************


void swap (int *a, int *b)
// Swap two integers.  Parameters are pointers to integers, so integers
// can be anywhere.
{
	int t = *a;    *a = *b;    *b = t;
}//swap()


//*******************Insertion Sort**************************
long insertionSort(int *array, int n)
{
	int i, j;
	int ctr = 0;

	for (i = 1; i < n; i++) {
#ifdef ASCENDING_ORDER
		for (j = i; j > 0 && (array[j - 1] > array[j]); j--) {
#endif
#ifdef DESCENDING_ORDER
		for (j = i; j > 0 && (array[j - 1] < array[j]); j--) {
#endif
			swap(&array[j], &array[j - 1]);
			ctr++;
		}
	}
	return ctr;
}


long insertionSortQ(int *array, int left, int right) {
	int i, j;
	int ctr = 0;
	for (i = left + 1; i < right + 1; i++) {
#ifdef ASCENDING_ORDER
		for (j = i; j > 0 && (array[j - 1] > array[j]); j--) {
			swap(&array[j], &array[j - 1]);
			ctr++;
		}
#endif
#ifdef DESCENDING_ORDER
		for (j = i; j > 0 && (array[j - 1] < array[j]); j--) {
			swap(&array[j], &array[j - 1]);
			ctr++;
			}
#endif
	}
	return ctr;
}


//*******************Bubble Sort**************************
long bubbleSort(int* array, int n) {
	int i, j, swapped;
	long ctr = 0;

	for (i = 0; i < n; ++i) {
		swapped = 0;
		for (j = n - 1; j > i; --j) {
#ifdef ASCENDING_ORDER
			if (array[j] < array[j - 1]) {
#endif
#ifdef DESCENDING_ORDER
			if (array[j] > array[j - 1]) {
#endif
				swapped = 1;
				swap(&array[j], &array[j - 1]);
				ctr++;
			}
		}
		if (swapped == 0) break;
	}
	return ctr;
}


//*******************Quick Sort**************************

int partition(int* a, int left, int right, long* swaps)
{
	int i = left;
	int j = right - 1;
	int pivot_index = left + (right - left) / 2;
	int pivot = a[pivot_index];
	swap(&a[right], &a[pivot_index]);
	(*swaps)++;
	while (i < j) {
#ifdef ASCENDING_ORDER
		while (a[i] < pivot) i++;
		while (a[j] > pivot) j--;
#endif
#ifdef DESCENDING_ORDER
		while (a[i] > pivot) i++;
		while (a[j] < pivot) j--;
#endif
		if (i <= j) {
			swap(&a[i], &a[j]);
			(*swaps)++;
			i++;
			j--;
		}
	}
	a[right] = a[i];
	a[i] = pivot;
	(*swaps)++;
	return i;
}


long quickSort(int* a, int left, int right) {
	long swaps = 0;
	if (right - left > 2) {
		int pivot = partition(a, left, right, &swaps);
		quickSort(a, left, pivot - 1);
		quickSort(a, pivot + 1, right);
	} else {
		 insertionSortQ(a, left, right);
	}
	return swaps;
}

//*******************Heap Sort**************************

long heapSort(int* a, int n)
{
	Heap* h = heapify2(a, n);
	long swaps = 0;
	int i;
	for (i = n - 1; i > 0; i--) {
		swap(&h->a[0], &h->a[i]);
		swaps++;
		h->last--;
		swaps += reheapDown(h, 0);
	}
	return swaps;
}

//*******************Merge Sort**************************

long merge(int*a, int start, int middle, int end, int*b)
{
	int i;
	int j = start;
	int k = middle + 1;
	long	swaps = 0;

	for (i = start; j <= middle && k <= end; i++) {
#ifdef ASCENDING_ORDER
		if (a[j] < a[k]) {
			b[i] = a[j];
			j++;
		} else {
			b[i] = a[k];
			k++;
			}
#endif
#ifdef DESCENDING_ORDER
		if (a[j] > a[k]) {
			b[i] = a[j];
			j++;
			swaps++;
		} else {
			b[i] = a[k];
			k++;
			swaps++;
			}
#endif
	}
	while (j <= middle)	{
		b[i++] = a[j++];
		swaps++;
		}

	while (k <= end)	{
		b[i++] = a[k++];
		swaps++;
		}

	for (i = start; i <= end; i++)
		a[i] = b[i];
	return swaps;
}

//*******************Merge Sort**************************

long mergeSortR(int* a, int start, int end, int* b)
{
	int		middle;
	long	swaps = 0;
	if (start >= end) return 0;

	middle = start + (end - start) / 2;
	swaps += mergeSortR(a, start, middle, b);
	swaps += mergeSortR(a, middle + 1, end, b);
	swaps += merge(a, start, middle, end, b);
	return swaps;
}

long mergeSort(int* a, int n)
{
	int* b = malloc(sizeof(int) * n);
	int i;
	for (i = 0; i < n; i++) {
		b[i] = a[i];
	}
	return mergeSortR(a, 0, n - 1, b);
}

//*******************Bucket Sort**************************

void bucketSort(int *a, int n, int b)
{
	int* buckets = malloc(sizeof(int) * b);
	int i, j, k;
	for (i = 0; i < b; i++) // initialize the buckets array
		buckets[i] = 0;
	for (i = 0; i < n; i++) // count number of  repeated data in each bucket
		buckets[a[i]]++;
	i = 0;
	for (j = 0; j < b; j++) { // loop for every bucket
		for (k = 0; k < buckets[j]; k++) {
			a[i] = j;
			i++;
		}
	}
}

//*******************Radix Sort**************************

long radixSort(int *a, int n, int p)
{
	int i, j, k;
	for (k = 0; k < p; k++) {
		int count[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		int* tmp = malloc(sizeof(int) * n);
		int* offset = malloc(sizeof(int) * 10);
		for (i = 0; i < n; i++)
#ifdef ASCENDING_ORDER
			count[(a[i] / (int) pow(10, k)) % 10]++;
#endif
#ifdef DESCENDING_ORDER
			count[9-(a[i] / (int) pow(10, k)) % 10]++;
#endif
		offset[0] = 0;
		for (i = 1; i < 10; i++) {
			offset[i] = 0;
			for (j = 0; j < i; j++) {
				offset[i] += count[j];
			}
		}

		for (i = 0; i < n; i++) {
#ifdef ASCENDING_ORDER
			tmp[offset[(a[i] / (int) pow(10, k)) % 10]++] = a[i];
#endif
#ifdef DESCENDING_ORDER
			tmp[offset[9-(a[i] / (int) pow(10, k)) % 10]++] = a[i];
#endif
		}
		for (i = 0; i < n; i++) {
			a[i] = tmp[i];
		}
	}
	return 0;
}


void initArray(int* a) {
	a[0] = 10;
	a[1] = 24;
	a[2] = 5;
	a[3] = 32;
	a[4] = 1;
	a[5] = 84;
	a[6] = 19;
}


int main() {
	int a[] = { 10, 24, 5, 32, 1, 84, 19 };
	int n = 7;
	long	swaps = 0;
	printf("Before   Sorting:\t\t");
	print(a, n);
	printf("*****\n");

	swaps = insertionSortQ(a, 0, n - 1);
	printf("After Insertion Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n",swaps);

	initArray(a);
	swaps = bubbleSort(a, n);
	printf("After Bubble Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n",swaps);

	initArray(a);
	swaps = quickSort(a, 0, n - 1);
	printf("After Quick Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n",swaps);


	initArray(a);
	swaps = heapSort(a, n);
	printf("After Heap  Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n",swaps);


	initArray(a);
	swaps = mergeSort(a, n);
	printf("After Merge Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n*****\n",swaps);


	initArray(a);
	swaps = radixSort(a, n, 3);
	printf("After Radix Sort:\t\t");
	print(a, n);
	printf("Number of swaps: %ld\n",swaps);


	return 0;
}
