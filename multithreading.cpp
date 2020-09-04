#include <pthread.h>
#include <iostream> 
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

using namespace std::chrono; 
using namespace std;  

#define SIZE  800
#define MAXTHREAD 2

#define swap(A, a, b) {int tmp; tmp=A[a]; A[a]=A[b]; A[b]=tmp;}

#define THRESHOLD SIZE/MAXTHREAD

static int A[1000];

static int partition(int *A, int low, int high, int pivot_idx);
void read();
void *qsort(void *arg);
static void quick_sort(int *A, int low, int high);
void print();

pthread_t pt[MAXTHREAD];

int main(int argc, char* argv[])
{
    // if(argc > 1) SIZE = atoi(argv[1]);
    // if(argc > 2) SIZE = atoi(argv[1]);

    

    int i,rc;
    rc = 0;
    i = 0;
    pthread_mutex_t lok1;
    pthread_cond_t cond1;

    void *exit_status;
    printf("CALLING THE READ FUNCTION\n");
    read();
    // printf("CALLING THE PRINT FUNCTION\n");
    // print();
    printf("CALLING THE SORT FUNCTION\n"); 
    
    pthread_mutex_init(&lok1, NULL);
    pthread_cond_init(&cond1,NULL);

    auto start = high_resolution_clock::now();

    // pthread_create(&pt[i],NULL, qsort,(void*)i);

    if(rc = pthread_create(&pt[i],NULL, qsort,(void*)i))
    {
        printf("%THREAD FAILED\n", i);
    }   
    pthread_join(pt[i], &exit_status);
    
    printf("\n");

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 
    
    cout <<"\n" << "Duration: " <<  duration.count() << " microseconds" << " for SIZE: " << SIZE << " and THREADS " << MAXTHREAD<< endl;
    
    
    printf("THREAD %d EXITED \n", 1);

    pthread_mutex_destroy(&lok1);
    pthread_cond_destroy(&cond1);
    // print();
    return 0;
}

void *qsort(void *arg)
{
    int i, pivot_idx, rc, start, end;
    i = *((int*)(&arg));
    start = 0;
    end=SIZE-1;
    void *exit_status;
    // printf("%d THREAD CREATED WITH I: %d\n,i");
    if (start >= end)
    {
        return NULL;
    }
    else
    {
        pivot_idx = (start+end/2);
        pivot_idx = partition(A, start, end, pivot_idx);
        if((pivot_idx - start)<= THRESHOLD || (i == MAXTHREAD-1))
        {
            quick_sort(A, start, pivot_idx);
        }
        else if(i <MAXTHREAD)
        {
            ++i;
            if(rc = pthread_create(&pt[i], NULL, qsort, (void *)i))
            {
                printf("%d THREAD FAILED\n",i);
            }
            pthread_join(pt[i],&exit_status);
        }
        if(((end-pivot_idx) <= THRESHOLD) || (i == MAXTHREAD-1))
        {
            quick_sort(A,pivot_idx,end);
        }
        else if(i <MAXTHREAD)
        {
            ++i;
            if(rc = pthread_create(&pt[i], NULL, qsort, (void *)i))
            {
                printf("%d THREAD FAILED\n",i);
            }
            pthread_join(pt[i],&exit_status);
        }
        
    }
    return NULL;
}

static int partition(int *A, int low, int high, int pivot_idx)
{
    pivot_idx = low;
    low++;

    while (low <= high)
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
            swap(A, low, high);
        }
        
    }
    if(high != pivot_idx)
    {
        swap(A, pivot_idx, high);
    }
    
    return high;
}

static void quick_sort(int *A, int low, int high)
{
    int pivot_idx;

    if(low >= high)
    {
        return;
    }
    else
    {
        pivot_idx = (low+high/2);
        pivot_idx = partition(A, low, high, pivot_idx);
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
    int i, chunk;
    chunk = SIZE/MAXTHREAD;
    for(i=0; i<SIZE; i++)
    {
        if(i%chunk == 0)
        {
            printf("|");
        }
        printf(" %d ", A[i]);
    }
    printf("\n\n");
}

