#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// Define Struct to Pass to Thread!
typedef struct {
    int count;
    int *arr;
} Arr;

// Get Minimum
void *getMin(void *arg) {
    Arr *arrArgs = (Arr *)arg;

    int min = arrArgs->arr[0];
    for (int i = 1; i < arrArgs->count; i++) {
        if (arrArgs->arr[i] < min) {
            min = arrArgs->arr[i];
        }
    }

    printf("The minimum value is %d\n", min);
    return NULL;
}

// Get Maximum
void *getMax(void *arg) {
    Arr *arrArgs = (Arr *)arg;

    int max = 0;
    for (int i = 1; i < arrArgs->count; i++) {
        if (arrArgs->arr[i] > max) {
            max = arrArgs->arr[i];
        }
    }

    printf("The maximum value is %d\n", max);
    return NULL;
}

// Get Average
void *getAvg(void *arg) {
    Arr *arrArgs = (Arr *)arg;

    int sum = 0;
    for (int i = 0; i < arrArgs->count; i++)
    {
        sum += arrArgs->arr[i];
    }

    // Calculate and display the average
    double average = (double)sum / arrArgs->count;
    printf("The average value is %.2f\n", average);

    return NULL;
}

// Main app!
int main(int argc, char *argv[])
{
    // Make Sure I got Values
    if (argc <= 1)
    {
        printf("No integers provided.\n");
        return 1;
    }

    // Create the Struct for Passing to the Threads
    Arr arrArgs;
    arrArgs.count = argc - 1; // Number of integers
    arrArgs.arr = (int*)malloc(arrArgs.count * sizeof(int)); // Dynamically allocate memory for the array

    for (int i = 0; i < arrArgs.count; i++) {
        arrArgs.arr[i] = atoi(argv[i + 1]); // Convert string to integer
    }

    // Create a thread to find the minimum value
    pthread_t thread1;
    pthread_create(&thread1, NULL, getMin, (void *)&arrArgs);

    // Create a thread to find the maximum value
    pthread_t thread2;
    pthread_create(&thread2, NULL, getMax, (void *)&arrArgs);

    // Create a thread to find the maximum value
    pthread_t thread3;
    pthread_create(&thread3, NULL, getAvg, (void *)&arrArgs);

    // Wait For Threads To Complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Free the allocated memory when done
    free(arrArgs.arr);
    printf("Done!\n");

    return (0);
}