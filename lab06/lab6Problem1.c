//Write your code in between TODO start and TODO end sections
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
#define MAX_LENGTH 25

typedef struct {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char zipCode[MAX_LENGTH];
    char department[MAX_LENGTH];
    int salary;

} Struct_Employee_Info;


// Creating Definition Functions for the Operators!
int greater_than(int a, int b) { return a > b; }
int less_than(int a, int b) { return a < b; }
int greater_than_or_equal(int a, int b) { return a >= b; }
int less_than_or_equal(int a, int b) { return a <= b; }
int equal(int a, int b) { return a == b; }

// With this special Funciotn we are mapping based on the comparison operator string
// Note: This is a pointer coming back from the function to the definition
int (*get_comp_func(const char *operator))(int, int) {
    if (strcmp(operator, ">") == 0)  return &greater_than;
    if (strcmp(operator, "<") == 0)  return &less_than;
    if (strcmp(operator, ">=") == 0) return &greater_than_or_equal;
    if (strcmp(operator, "<=") == 0) return &less_than_or_equal;
    if (strcmp(operator, "==") == 0) return &equal;
    return NULL;  // Return NULL if operator is invalid
}

// Function to append employee info into the result buffer using snprintf
void append_employee_info(char *result, Struct_Employee_Info e) {
    snprintf(
        result + strlen(result), // Set the location to start writting
        MAX_SIZE - strlen(result), // Max Length to stop
        "Name: %s %s\tZip code: %s\tDepartment: %s\tSalary: %d\n", // Formatted String
        e.firstName, 
        e.lastName, 
        e.zipCode,
        e.department,
        e.salary);
}


char* searchByName(Struct_Employee_Info employees[], int count, const char *firstName, const char *lastName) {
    //creating a character array to store the result of the search operation
    char *result = malloc(MAX_SIZE * sizeof(char));
    /*The bzero() function erases the data in the MAX_SIZE bytes of the memory starting at the location pointed to by
     result, by writing zeros (bytes containing '\0') to that area.*/
    bzero(result,MAX_SIZE);
    //TODO Start:

    // Flag "found"
    int found = 0;

    // Start For-Loop
    for(int i=0; i < count; i++){
        // Create a copy of the Empoyee - Makes Code a bit easier
        Struct_Employee_Info e = employees[i];

        // Check First Name & Last Name
        // I am using a simple "or" and then to see if the value is still "zero"!
        if((strcmp(e.firstName, firstName) | strcmp(e.lastName, lastName)) == 0){
            // Set "found" flag to true
            found = 1;
            // Append Employee to results
            append_employee_info(result, e);
        }
    }

    // Check found Flag
    if(found == 0){
        strcpy(result, "No matching records found.\n");
    }

    //TODo End
    return result;
}

char* searchByZipCode(Struct_Employee_Info employees[], int count, const char *zipCode) {
    //creating a character array to store the result of the search operation
    char *result = malloc(MAX_SIZE * sizeof(char));
    /*The bzero() function erases the data in the MAX_SIZE bytes of the memory starting at the location pointed to by
     result, by writing zeros (bytes containing '\0') to that area.*/
    bzero(result,MAX_SIZE);
    //TODO Start:

    // Flag "found"
    int found = 0;

    // Start For-Loop
    for(int i=0; i < count; i++){
        // Create a copy of the Empoyee - Makes Code a bit easier
        Struct_Employee_Info e = employees[i];

        // Check Zip Code are equal to eachother
        if(strcmp(e.zipCode, zipCode) == 0){
            // Set "found" flag to true
            found = 1;

            // Append Employee to results
            append_employee_info(result, e);
        }
    }

    // Check found Flag
    if(found == 0){
        strcpy(result, "No matching records found.\n");
    }

    //TODo End
    return result;
}

char* searchBySalary(Struct_Employee_Info employees[], int count, int salary, const char *comparisonOperator) {
    //creating a character array to store the result of the search operation
    char *result = malloc(MAX_SIZE * sizeof(char));
    /*The bzero() function erases the data in the MAX_SIZE bytes of the memory starting at the location pointed to by
     result, by writing zeros (bytes containing '\0') to that area.*/
    bzero(result,MAX_SIZE);
    //TODO Start:

    // Flag "found"
    int found = 0;

    // Get the function pointer based on the operator string
    int (*comparison)(int, int) = get_comp_func(comparisonOperator);

     // Start For-Loop
    for(int i=0; i < count; i++){
        // Create a copy of the Empoyee - Makes Code a bit easier
        Struct_Employee_Info e = employees[i];

        if(comparison(e.salary, salary)){
            // Set "found" flag to true
            found = 1;
            
            // Append Employee to results
            append_employee_info(result, e);
        }
    }

    // Check found Flag
    if(found == 0){
        strcpy(result, "No matching records found.\n");
    }

    //TODo End
    return result;
}

int main() {
    FILE *file;
    Struct_Employee_Info employees[MAX_SIZE];
    char line[MAX_SIZE];
    int count = 0;

    file = fopen("records.csv", "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    //Adding the record from records.csv to the employees structure
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",
               employees[count].firstName, employees[count].lastName,
               employees[count].zipCode, employees[count].department,&employees[count].salary);
        count++;
    }

    fclose(file);

    char *searchResult1 = searchByName(employees, count, "Jack", "Sparrow");
    printf("\nSearch Results by Name: %s %s\n", "Jack", "Sparrow");
    printf("%s", searchResult1);
    free(searchResult1);

    char *searchResult2 = searchByZipCode(employees, count, "37128");
    printf("\nSearch Results by Zip Code: %s\n", "37128");
    printf("%s", searchResult2);
    free(searchResult2);

    char *searchResult3 = searchBySalary(employees, count, 45000, ">=");
    printf("\nSearch Results by Salary: %s %d\n", ">=", 45000);
    printf("%s", searchResult3);
    free(searchResult3);

    char *searchResult4 = searchBySalary(employees, count, 500000, "==");
    printf("\nSearch Results by Salary: %s %d\n", "==", 500000);
    printf("%s", searchResult4);
    free(searchResult4);

    return 0;
}
