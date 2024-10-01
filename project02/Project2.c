/*

Name:  Richard Hoehn
Class: CSCI-6050
Proj:  02
Date:  2024-10-08
Desc:  ASSM to C Code Project.

*/


long MysteryFunction1(long a, int b){
   long res = 1; // This is setting the "1" for the return (%rax)
   int exp = b; // Holds the Exponent
   
   while(1) {
      // Decrement by 1
      exp--; // leal -1(%rsi), $edx

      // Check if we are done <= "0" - testl
      if(exp <= 0){
         break; // Break and Exit!
      }

      // Multiply by "a" by the res 
      res = res * a;
   }

   // Return Vale Expont 
   return res;
}


unsigned int MysteryFunction2(unsigned int num)
{
   unsigned int result = 0; // Set result variable

   unsigned int temp; // Set our Temp result

   // Loop over all 32 bits!
   for (int i = 0; i <= 31; i++) {
      temp = 1U << i;              // Create a mask for bit i

      if ((num & temp) != 0) {     // Check if bit i is set in num
         temp = 0x80000000U >> i;  // Move set bit from position 31 to (31 - i)
         result |= temp;           // OR it onto our temp results
      }
   }
   
   // Retrun the Miroed Bits number
   return result;
}


long MysteryFunction3(long *a, int n){

   // Set max to be the first element in "a[]"
   long max = a[0];

   // Loop over array by the count given in "n"
   for (int i = 1; i < n; i++) {

      // Check if the array pointer is a value greater than our "ax"
      if (a[i] > max) {
         // if "yes" then update our "max"
         max = a[i];
      }
   }

   // Return "max"!
   return max;
}

int MysteryFunction4(unsigned long n)
{
   // Set the accumulator as the sum of bits in this "n"
   int sum = 0;

   // Loop while "n" is not zero
   while (n != 0) {

      // Simple Addition to the sum if the last bit is a "1"
      sum += n & 1; // Add the least significant bit to sum

      // Simple shiift to the right!
      n = n / 2; // Shift n right by 1 bit this is like divind by "2"
   }

   // Retunr the count of bits in this long!
   return sum; 
}



unsigned int MysteryFunction5(unsigned int A, unsigned int B)
{
   // Create a Value from the X-OR of A & B!
   unsigned int n = A ^ B;
   unsigned int sum = 0; // Create our accumlaotr

   // Loop over X while it is not zero!
   while (n != 0) {
      // Simple Addition to the sum if the last bit is a "1"
      sum += n & 1; // Add the least significant bit to sum

      // Simple shiift to the right!
      n = n / 2; // Shift n right by 1 bit this is like divind by "2"
   }

   // Return the count of bits in this X-OR from the input
   return sum; 
}
