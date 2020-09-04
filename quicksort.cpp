/* C implementation QuickSort */
#include<stdio.h> 
#include <cstdlib>
#include <iostream> 
using namespace std::chrono; 
using namespace std;  

#define SIZE 300
static int A[SIZE];
// A utility function to swap two elements 
void swap(int* a, int* b) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 

/* This function takes last element as pivot, places 
the pivot element at its correct position in sorted 
	array, and places all smaller (smaller than pivot) 
to left of pivot and all greater elements to right 
of pivot */
int partition (int arr[], int low, int high) 
{ 
	int pivot = arr[high]; // pivot 
	int i = (low - 1); // Index of smaller element 

	for (int j = low; j <= high- 1; j++)
	{ 
		// If current element is smaller than or 
		// equal to pivot 
		if (arr[j] <= pivot) 
		{ 
			i++; // increment index of smaller element 
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[high]); 
	return (i + 1); 
} 

static unsigned Partition(int arr[], int low, int high, int pivot_idx)
{
    if (pivot_idx != low)
    {
        swap(low, pivot_idx);
    }
    pivot_idx = low;
    low++;
    while (low<=high)
    {
        if(A[low] <= A[pivot_idx])
        {
            low++;
        }
        else if(A[high] > A[pivot_idx])
        {
            high--;
        }
        else
        {
            swap(low, high);
        }
        
    }
    if(high != pivot_idx)
    {
        swap(pivot_idx, high);
    }
    return high;
}


/* The main function that implements QuickSort 
arr[] --> Array to be sorted, 
low --> Starting index, 
high --> Ending index */
void quickSort(int arr[], int low, int high) 
{ 
	if (low < high) 
	{ 
		/* pi is partitioning index, arr[p] is now 
		at right place */
		int pi = partition(arr, low, high); 

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1); 
		quickSort(arr, pi + 1, high); 
	} 
} 

static void quick_sort(int arr[], int low, int high)
{
    int pivot_idx;

    if(low >= high)
    {
        return;
    }
    else
    {
        pivot_idx = (low+high/2);
        pivot_idx = Partition(A, low, high, pivot_idx);
        if(low < pivot_idx)
        {
            quick_sort(A, low, pivot_idx-1);
        }
        if(pivot_idx < high)
        {
            quick_sort(A, pivot_idx+1, high);
        }
    }
}

void read()
{
    int i;
    for(i=0; i<SIZE; i++)
    {
        A[i] = rand()%10 +1;
    }
}

void print()
{
    int i;
    for(i=0; i<SIZE; i++)
    {
        printf(" %d ", A[i]);
    }
    printf("\n\n");
}

/* Function to print an array */
void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", arr[i]); 
	printf("n"); 
} 

// Driver program to test above functions 
int main() 
{ 
	int n = sizeof(A)/sizeof(A[0]); 
	read();
	// print();
	auto start = high_resolution_clock::now();
	quickSort(A,0,n);
	auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 
	cout <<"\n" << "Duration: " <<  duration.count() << "  microseconds for ROWS: "<< SIZE << endl;
	// print();
	return 0; 
} 

