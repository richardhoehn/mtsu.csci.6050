



// Setup Includes & Libs
#include <stdio.h>
#include "Project2.h"


// Start Program
int main() {

    printf("Val: %ld\n", MysteryFunction1(1, 1));
    printf("Val: %ld\n", MysteryFunction1(1, 2));
    printf("Val: %ld\n", MysteryFunction1(2, 1));
    printf("Val: %ld\n", MysteryFunction1(2, 2));
    printf("Val: %ld\n", MysteryFunction1(3, 3));
    printf("*\n*\n");

    printf("Val: %X\n", MysteryFunction2(1));
    printf("Val: %x\n", MysteryFunction2(2));
    printf("Val: %x\n", MysteryFunction2(-1));
    printf("*\n*\n");


    long array[] = {5, 1113, 9, 9, 6};
    printf("Val: %ld\n", MysteryFunction3(array, 5));
    printf("*\n*\n");

    printf("Val: %d\n", MysteryFunction4(0));
    printf("Val: %d\n", MysteryFunction4(1));
    printf("Val: %d\n", MysteryFunction4(2));
    printf("Val: %d\n", MysteryFunction4(3));
    printf("Val: %d\n", MysteryFunction4(4));
    printf("Val: %d\n", MysteryFunction4(5));
    printf("Val: %d\n", MysteryFunction4(6));
    printf("Val: %d\n", MysteryFunction4(7));
    printf("Val: %d\n", MysteryFunction4(-1));
    printf("*\n*\n");

    printf("Val: %d\n", MysteryFunction5(0,1));
    printf("Val: %d\n", MysteryFunction5(1,1));
    printf("Val: %d\n", MysteryFunction5(2,4));
    printf("Val: %d\n", MysteryFunction5(3,56));
    printf("Val: %d\n", MysteryFunction5(4344,34));
    printf("Val: %d\n", MysteryFunction5(52,564));
    printf("Val: %d\n", MysteryFunction5(6,3));
    printf("Val: %d\n", MysteryFunction5(7,3));
    printf("Val: %d\n", MysteryFunction5(-1,0));
    printf("*\n*\n");

    return 0;
}