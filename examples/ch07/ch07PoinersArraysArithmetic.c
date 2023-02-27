//!  Chapter 7: Pointers, Arrays and Arithmetic Explorations
/*!
  \file ch07PoinersArraysArithmetic.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \version 1.0
  \date 02-27-2023

  This program demostrates various ways to work with arrays and pointers, as
  well as the arithmetic and other operations associated with them.
 */


#include <stdio.h>
#include <stdlib.h>

//! Length of the array variable
#define SIZE 5


//! The main function.
/*!
  \return The exit value
 */
int main(void)
{
	// ---------- PART ONE: Length of an Array
	puts("****************************************");
	puts("PART ONE: Length of an Array");

	int array[SIZE] = { -7, 0, 11, 22, 25};

    // First way to calculate an array's length without the SIZE variable:
    //
    // Calculate the length of the array in bytes and divide it by the size in
    // bytes of an element.
    puts("");
    puts("First method:");
	size_t sizeArr = sizeof(array);
	size_t sizeElem = sizeof(array[0]);
	size_t arrayLength = sizeof(array) / sizeof(array[0]);
	printf("sizeof(array): %lu\n", sizeArr);
	printf("sizeofarray[0]): %lu\n", sizeElem);
	printf("sizeof(array) / sizeof(array[0]): %lu\n", arrayLength);

    // Second way to calculate an array's length without the SIZE variable:
    //
    // Perhaps this works in the following way. Incrementing a pointer to an
    // array moves the pointer the same amount as if it were a pointer of the 
    // data type of the array. Then we dereference the pointer which now
    // effectively points to the second element of the method and subtract the
    // memory location of the first element of the array from the second element
    // of the array.  
    puts("");
    puts("Second method:");
	arrayLength = *(&array + 1) - array;
	printf("*(&array + 1) - array: %lu\n", arrayLength);

    puts("");
    puts("");
	

	// ----------- PART TWO: Pointer to an Array
	puts("****************************************");
	puts("Part 2: pointer to an array");

	int* arrayPtr = array;

    // The below code demonstrates only one new thing: the address of an array
    // pointer is equal to the address of the array being pointed to.
    puts("");
	puts("int array[SIZE] = { -7, 0, 11, 22, 25 }");
	puts("int* arrayPtr = array");
	printf("array name value %p\n", array);
	printf("arrayPtr name value %p\n", arrayPtr);
	printf("&array[0] is = %p\n", &array[0]);
	printf("&array[1] is = %p\n", &array[1]);
	printf("&array[2] is = %p\n", &array[2]);

    // The below code demonstrates that the values pointed to by an array and an
    // array pointer (pointing to that array) are the same.
	printf("*array = %d\n", *array);
	printf("*arrayPtr = %d\n\n", *arrayPtr);


	// ---------- PART THREE : Adding and Subtracting Integers to Pointers
	puts("****************************************");
	puts("Part 3: Adding and Subtracting integers to pointers");
	printf("*(array+ 1) = %d\n", *(array + 1));
	printf("*array + 1 = %d\n", *array + 1);
	printf("*(arrayPtr+ 1) = %d\n", *(arrayPtr + 1));
	printf("*arrayPtr + 1 = %d\n", *arrayPtr + 1);
	printf("*(arrayPtr+ 2) =  %d\n", *(arrayPtr + 2));
	printf("*arrayPtr + 2 = %d\n", *arrayPtr + 2);
	printf("*(arrayPtr+ 4) = %d\n", *(arrayPtr + 4));
	printf("*(arrayPtr+ 5) = %d\n", *(arrayPtr + 5));
	printf("*(arrayPtr - 1): =%d\n", *(arrayPtr -1 ));
	printf("*++arrayPtr = %d\n", *++arrayPtr);
	printf("*arrayPtr = %d\n", *arrayPtr);
	printf("*arrayPtr++ = %d\n", *arrayPtr++);
	printf("*arrayPtr = %d\n", *arrayPtr);
	printf("*arrayPtr++ = %d\n", *arrayPtr++);
	printf("*arrayPtr = %d\n", *arrayPtr);
	printf("*--arrayPtr = %d\n", *--arrayPtr);
	printf("*arrayPtr = %d\n", *arrayPtr);
	arrayPtr = array;
	puts("int* arrayPtr = array");
	printf("*arrayPtr = %d\n", *arrayPtr);

	puts("");

	//Part 4 Assign Pointer to another pointer and subtracting pointers
	puts("Assign Pointer to another pointer");
	int* array2Ptr = &array[3];
	puts("int* array2Ptr = &array[3]");
	printf("*array2Ptr = %d\n", *array2Ptr);
	printf("*(array2Ptr +1) = %d\n", *(array2Ptr + 1));
	printf("*(array2Ptr -1) = %d\n", *(array2Ptr - 1));
	printf("array2Ptr - arrayPtr = %llu\n", array2Ptr - arrayPtr);
	printf("arrayPtr - array2Ptr = %llu\n", arrayPtr - array2Ptr);
	puts("Error arrayPtr +array2Ptr = %d\n");


	//Part 5 Refer to Elements in an Array: Pointer Offset and Subscript Notation
	puts("\nPart 5: refer to array elements\n");

	puts("array printed with:\nArray index notation");
	for (size_t i = 0; i < SIZE; ++i)
	{
		printf("array[%llu] = %d\n", i, array[i]);
	}

	puts("\nPointer offset notation");
	for (size_t offset = 0; offset < SIZE; ++offset)
	{
		printf("*(array + %llu) = %d\n", offset, *(array + offset));
	}

	return 0;
}




