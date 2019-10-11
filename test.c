//Thar Soe
//Assignment 01



#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_ELEMENT 1000
#define NUM_THREADS 10

void *bubbleSort(void *params);   
void *mergeSort(void *params); 
void merge(int low, int mid, int high);
void merge_sort(int low, int high);
int *arr[NUM_ELEMENT];
int thread_partition = 0;
int status;
pid_t p; 
int part = 0;

typedef struct
{
    int from;
    int to;
} parameters;

int main (int argc, const char * argv[])

{

  int i = 0;
	int count;
	int x;
    pthread_t threads[NUM_THREADS];	
	
	
	//generate random numbers no repeats
	srand(time(NULL));
	while (i< NUM_ELEMENT)
	{
		int random = rand()%1000 + 1;
		
		for (x = 0; x < i; x++)
		{
			if (arr[x] == random)
			{
				break;
	
			}
			
		}
		
		if (x == i)
		{
			arr[i++]=random; 
		}
		
	}


		if (fork() == 0)
		{
		parameters *data = (parameters *) malloc (sizeof(parameters));
	//first set of array
			data->from = 0;
			data->to = (NUM_ELEMENT/2) - 1;
			for (int h = 0; h < NUM_THREADS; h++)
			{
				pthread_create(&threads[h], 0, bubbleSort, data);
			}
			// join all the threads

			for (i = 0; i < NUM_THREADS; i++)
				pthread_join(threads[i], NULL);
			}
			
	//second set of array
	
		else
		{
		wait(&status);
		parameters *data = (parameters *) malloc (sizeof(parameters));
		data->from= (NUM_ELEMENT/2);
		data->to= NUM_ELEMENT - 1;
		
		for (int n = 0; n < NUM_THREADS; n++)
		{
			pthread_create(&threads[n], 0, mergeSort, data);
		}
		
		// join all the threads

		for (i = 0; i < NUM_THREADS; i++)
			pthread_join(threads[i], NULL);
			
		}


	merge (0, (NUM_ELEMENT/2 -1) / 2, NUM_ELEMENT/2 -1);
	merge(NUM_ELEMENT/2, NUM_ELEMENT/2 + (NUM_ELEMENT-1-NUM_ELEMENT/2), NUM_ELEMENT-1);
	merge(0, (NUM_ELEMENT-1)/2, NUM_ELEMENT-1);

	printf("\n\n The Sorted Array is: \n");
	for (int i = 0; i < NUM_ELEMENT; i++)
	{
		printf(" %d", arr[i]);
		printf("\n");
		
	}


    return 0;

}
void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void *bubbleSort(void *params)

{

    parameters* par = (parameters *)params;

    int begin = par->from;
    int end = par->to+1;

    int temp;
    int i,j,k;
	int m;
	clock_t t1, t2; 
	
	for (m = begin; m < end; m++)
	{
		printf ("The Original Array: %d\n", arr[m]);
	}
	    printf("\n");


	t1 = clock();
    for(i=0; i< end; i++)

    {

        for(j=0; j< end-i-1; j++)

        {

            if(arr[j] > arr[j+1])

            {
               swap(&arr[j], &arr[j+1]);

            }

        }

    }
	
	t2 = clock();
	
	for (k = begin; k < end; k++)
	{
		printf("After sorting: %d\n", arr[k]); 
		
	}

	

    printf("\n");
	
	double exec_time = (double)(t2 - t1)/CLOCKS_PER_SEC;
	
	printf("The Execution time is: %lf\n", exec_time); 

	printf("\n");
    pthread_exit(0);

}
//merge sort;
void* mergeSort(void *params)
{
	thread_partition++;
	
	int low = thread_partition * (NUM_ELEMENT/10);
	int high = (thread_partition +1) * (NUM_ELEMENT/10) -1;
	
	int mid = low + (high - low)/2;
	if (low < high)
	{
		merge_sort(low, mid);
		merge_sort(mid+1, high);
		merge(low, mid, high);
	}
	
	
	return 0; 
}

void merge_sort(int low, int high)
{
	int mid = low + (high - low) /2;
	if(low < high)
	{
		merge_sort(low, mid);
		merge_sort(mid+1, high);
		merge(low, mid, high);
		

	}
	

}

void merge(int low, int mid, int high)
{

int lsize = mid - low + 1;
int rsize = high - mid;

	
int *left = malloc(lsize * sizeof(int));
int *right= malloc(rsize * sizeof(int));


int i, j;

for (i =0; i < lsize; i++)
{
	left[i] = arr[i + low];

}

for (i = 0; i< rsize; i++)
{
	
	right[i] =arr[i+mid+1];

}

int k = low;
i = 0;
j = 0;

while (i < lsize)
{
	arr[k++] = left[i++];

}
	
while(j < rsize)
{
	arr[k++] = right[j++];
}

free(left);
free(right);	
}










