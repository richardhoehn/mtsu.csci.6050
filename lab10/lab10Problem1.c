#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Make Sure I got Values
    if (argc <= 1)
    {
        printf("No integers provided.\n");
        return 1;
    }

    int count = argc - 1; // Number of integers
    int arr[count];

    // Convert arguments to Int Array
    for (int i = 0; i < count; i++)
    {
        arr[i] = atoi(argv[i + 1]);
    }

    // ------------------------------------------
    // Create First Child - Average Value
    // ------------------------------------------
    pid_t pid1 = fork();
    if (pid1 < 0)
        perror("Fork failed");
    if (pid1 == 0)
    {
        int sum = 0;
        for (int i = 0; i < count; i++)
        {
            sum += arr[i];
        }

        // Calculate and display the average
        double average = (double)sum / count;
        printf("The average value is %.2f\n", average);
        exit(0);
    }

    // ------------------------------------------
    // Create Second Child - Minimum Value
    // ------------------------------------------
    pid_t pid2 = fork();
    if (pid2 < 0)
        perror("Fork failed");
    if (pid2 == 0)
    {
        int max = 0;
        for (int i = 0; i < count; i++)
        {
            if (i == 0 || arr[i] > max)
            {
                max = arr[i];
            }
        }

        printf("The maximum value is %d\n", max);
        exit(0);
    }

    // ------------------------------------------
    // Create Third Child - Maximum Value
    // ------------------------------------------
    pid_t pid3 = fork();
    if (pid3 < 0)
        perror("Fork failed");
    if (pid3 == 0)
    {
        int min = 0;
        for (int i = 0; i < count; i++)
        {
            if (i == 0 || arr[i] < min)
            {
                min = arr[i];
            }
        }

        printf("The minimum value is %d\n", min);
        exit(0);
    }

    // Wait to Close
    wait(NULL);
    return (0);
}