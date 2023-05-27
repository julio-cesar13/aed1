// C program for implementation
// of Bubble sort
#include <stdio.h>
#include <stdbool.h>

// Swap function
void swap(int *arr,int i,int j){
	int temp=arr[i];
	arr[i]=arr[j];
	arr[j]=temp;
}

// Function to print an array
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	printf("%d ",arr[i]);
	printf("\n");
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
    int i, j;
	int cont=0;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) 
		{
            if (arr[j] > arr[j + 1])
			{
                swap(arr, j, j + 1);
                swapped = true;
				cont++;
            }
			printArray(arr, n);
        }
		printf("\n");
  
        // IF no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
		{
			printArray(arr, n);
            break;
		}
    }
	printf("\nNumeror de trocas: %d\n", cont);
}

// Driver code
int main()
{
	int arr[] = {1, 2, 3, 4, 5};
	int N = sizeof(arr) / sizeof(arr[0]);
	bubbleSort(arr, N);
	
	return 0;
}
