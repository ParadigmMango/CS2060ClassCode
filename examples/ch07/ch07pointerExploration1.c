//!  Pointers Exploration
/*!
  \file ch07pointerExploration1.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \version 1.0
  \date 02-27-2023
 */

#include <stdio.h>


int main ()
{
	// Initalize the variables and the pointer
	int houseNum = 13;
	int calcHouseNum1 = 0;
	int calcHouseNum2 = 0;
	int *houseNumPtr = &houseNum;
	
    // Print out details pertaining to houseNum
	printf("houseNum = %d\n", houseNum);
	printf("&houseNum = %p\n", &houseNum);
    puts("");

    // Print out details pertaining to houseNumPtr
	printf("*houseNumPtr = %d\n", *houseNumPtr);
	printf("houseNumPtr = %p\n", houseNumPtr);
	printf("&houseNumPtr = %p\n", &houseNumPtr);
    puts("");

    // Demonstrate how dereferenced pointers can still be used for arithmetic.
	calcHouseNum1 =  *houseNumPtr + *houseNumPtr;
	printf("*houseNumPtr + *houseNumPtr is %d\n", calcHouseNum1);
    puts("");

    // Demonstrate how other arithmetic (i.e. multiplication) can be used on
    // dereferenced pointers.
	calcHouseNum2 = 2 * (*houseNumPtr);
	printf("2 * (*houseNumPtr) is %d\n", calcHouseNum2);
    puts("");

    // Demonstrate how &* and *& cancel each other out as & and * are opposite
    // operations.
	printf("&*houseNumPtr = %p\n", &*houseNumPtr);
    printf("*&houseNumPtr = %p\n", *&houseNumPtr);
			
	return 0;
}
