



// Setup Includes & Libs
#include <stdio.h>

// Start Program
int main(){
int x = 1.5; /* arbitrary value */

int y = 2.5; /* arbitrary value */

int z = 3.5; /* arbitrary value */

//convert to double

double dx = (double) x;

double dy = (double) y;

double dz = (double) z;

unsigned ux = x;

unsigned uy = y;


if((dx + dy) + dz ==  dx + (dy + dz)){
    printf("Yes 1\n");
}

if((dx * dy) * dz ==  dx * (dy * dz)){
    printf("Yes 2\n");
}


}

