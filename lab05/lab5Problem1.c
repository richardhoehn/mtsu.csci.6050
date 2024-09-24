/*
Name:  Richard Hoehn
Class: CSCI-6050
Lab:   05
Prob:  01
Date:  2024-09-24
Desc:  Reading CSV and Sorting Student Data
*/

// Constants
#define FILENAME "student.csv"  // Filename of the CSV file to be read
#define MAXCHAR 1000  // Maximum length of a row in the CSV
#define MAX_STUDENTS 100  // Maximum number of students that can be read

// Setup Includes & Libs
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Setup of Student Struct / Object
struct Struct_Student_Info {
    int ID;  // Student ID
    char StudentName[50];  // Name of the student (up to 50 characters)
    double Score;  // Score of the student
};

// Define Prototypes
void display(struct Struct_Student_Info* students, int size);  // Function to display student info
struct Struct_Student_Info* sortByScore(struct Struct_Student_Info* students, int size);  // Function to sort students
int compareStudents(const void* a, const void* b);  // Comparison function for qsort


// Start Application
int main() {

    // Setup Vars
    FILE *fp;          // File Pointer to read the CSV
    char row[MAXCHAR]; // Holds each row read from the CSV
    char *token;       // Token to hold each separated value from the CSV row
    struct Struct_Student_Info students[MAX_STUDENTS];  // Array to hold the students
    int student_count = 0;  // Counter to keep track of the number of students

    // Open File for reading!
    fp = fopen(FILENAME, "r");  // Open the CSV file

    // Check if the file was opened successfully
    if (fp == 0) { 
        printf("Error - Missing '%s' file!\n", FILENAME);
        return 1;  // Exit if the file is missing
    } 

    // Skip the first line (header)
    fgets(row, MAXCHAR, fp);

    // Process the file line by line
    while (fgets(row, MAXCHAR, fp) != NULL && student_count < MAX_STUDENTS) {
        // Parse the Name (first token)
        token = strtok(row, ",");
        if (token != NULL) {
            strncpy(students[student_count].StudentName, token, 50);  // Copy token to StudentName
            students[student_count].StudentName[49] = '\0'; // Ensure null-termination for safety
        }

        // Parse the ID (second token)
        token = strtok(NULL, ",");
        if (token != NULL) {
            students[student_count].ID = atoi(token);  // Convert token to integer for student ID
        }

        // Parse the Score (third token)
        token = strtok(NULL, ",");
        if (token != NULL) {
            students[student_count].Score = atof(token);  // Convert token to double for student score
        }

        // Increment the student count after processing each row
        student_count++;
    }

    // Close the file after reading
    fclose(fp); 

    // Sort the student array and get a sorted copy
    struct Struct_Student_Info* sorted_students = sortByScore(students, student_count);

    // Display the sorted students
    display(sorted_students, student_count);

    // Free the dynamically allocated memory after use
    free(sorted_students);

    return 0;
}

// Function to display all student info
void display(struct Struct_Student_Info* students, int size){
    for(int i=0; i<size; i++){
        printf("%s %d %.2f\n", students[i].StudentName, students[i].ID, students[i].Score);  // Print Name, ID, and Score
    }
    return;
}

// Sort students by score (returns a sorted copy of the array)
struct Struct_Student_Info* sortByScore(struct Struct_Student_Info* students, int size){
    // Allocate memory for a copy of the students array
    struct Struct_Student_Info* sorted_students = malloc(size * sizeof(struct Struct_Student_Info));

    // Copy the original array to the new array
    for (int i = 0; i < size; i++) {
        sorted_students[i] = students[i];
    }

    // Sort the copied array using qsort
    qsort(sorted_students, size, sizeof(struct Struct_Student_Info), compareStudents);

    // Return the pointer to the sorted array
    return sorted_students;
}

// Comparison function for qsort
int compareStudents(const void* a, const void* b) {
    struct Struct_Student_Info* studentA = (struct Struct_Student_Info*)a;
    struct Struct_Student_Info* studentB = (struct Struct_Student_Info*)b;

    // First compare by Score (Acending order)
    if (studentA->Score > studentB->Score) {
        return 1;  // Return 1 if studentA has a higher score
    }
    else if (studentA->Score < studentB->Score) {
        return -1;  // Return -1 if studentB has a higher score
    }
    else {
        // If the scores are the same, compare by StudentName (alphabetical order)
        return strcmp(studentA->StudentName, studentB->StudentName);
    }
}
