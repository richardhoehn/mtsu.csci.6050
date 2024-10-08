/*

Name:  Richard Hoehn
Class: CSCI-6050
Lab:   01
Date:  2024-08-27
Desc:  This is a simple applicaiton that converts temperaturs K, C, F

*/

// Setup Includes & Libs
#include <stdio.h>
#include <ctype.h>

// Function Declarations
double conv_c_to_f(double inTemp);
double conv_c_to_k(double inTemp);
double conv_f_to_c(double inTemp);
double conv_f_to_k(double inTemp);
double conv_k_to_c(double inTemp);
double conv_k_to_f(double inTemp);
char getTempType(char* strPrompt);
double getTempValue(char* strPrompt);

// Start Program
int main(){
    // Define Vars
    char inType;
    char outType;
    double inTemp;
    double outTemp;

    // Start
    inType = getTempType("Enter starting temperature scale (F/C/K): ");
    outType = getTempType("Enter target temperature scale (F/C/K): ");
    inTemp = getTempValue("Enter temperature value: ");

    switch(inType){
        case 'F':
            switch(outType){
                case 'C':
                    outTemp = conv_f_to_c(inTemp);
                    break;
                case 'K':
                    outTemp = conv_f_to_k(inTemp);
                    break;
                default:
                    outTemp = inTemp;
                    break;
            }
            break;
        case 'C':
            switch(outType){
                case 'F':
                    outTemp = conv_c_to_f(inTemp);
                    break;
                case 'K':
                    outTemp = conv_c_to_k(inTemp);
                    break;
                default:
                    outTemp = inTemp;
                    break;
            }
            break;
        case 'K':
            switch(outType){
                case 'C':
                    outTemp = conv_k_to_c(inTemp);
                    break;
                case 'F':
                    outTemp = conv_k_to_f(inTemp);
                    break;
                default:
                    outTemp = inTemp;
                    break;
            }
            break;
        default:
            outTemp = 888.888; // Somthing Went Totally Wrong!!!
            break;
    }
    
    // Show Output
    printf("%.2lf°%c is equivalent to %.2lf°%c.\n", inTemp, inType, outTemp, outType);

    return 0;
}

double getTempValue(char* strPrompt){
    double tempValue;

    printf("%s", strPrompt);
    scanf("%lf", &tempValue);

    // Clear the input /"Enter"
    while (getchar() != '\n');

    return tempValue;
}

char getTempType(char* strPrompt){
    char tempType;

    getTemp:
        printf("%s", strPrompt);
        scanf("%c", &tempType);
    
        // Clear the input /"Enter"
        while (getchar() != '\n');
    
        // To UpperCase()
        tempType = toupper(tempType);

    if(tempType != 'C' && tempType != 'F' && tempType != 'K'){
        printf("\nInput issue! Try Again!\n");
        goto getTemp;
    }

    return tempType;
}

double conv_c_to_f(double inTemp){
    return (inTemp * 9/5) + 32;
}

double conv_c_to_k(double inTemp){
    return inTemp + 273.15;
}

double conv_f_to_c(double inTemp){
    return (inTemp - 32.0) * 5/9;
}

double conv_f_to_k(double inTemp){
    return conv_c_to_k(conv_f_to_c(inTemp));
}

double conv_k_to_c(double inTemp){
    return inTemp - 273.15;
}

double conv_k_to_f(double inTemp){
    return conv_c_to_f(conv_k_to_c(inTemp));
}

