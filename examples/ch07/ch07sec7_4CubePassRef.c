//! Passing Primitive Data Types and Pointers
/*!
  \file ch07sec7_4CubePassRef.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \version 1.0
  \date 02-27-2023

  The program demostrates the differences between passing by reference and
  passing by value in C.
 */

#include <stdio.h>	
#include <stdlib.h>


//! Cubes a integer number non-destructively.
/*!
  Calculates a valid cube and returns it, but does not change the input variable
  to the cube.

  \param number the number to be cubed
  \return The cube of the number
 */
int cubePass1(int number);

//! Cubes a integer number destructively.
/*!
  Calculates a valid cube, returns it and changes the input variable to the cube
  of the input variable.

  \param number the number to be cubed
  \return The cube of the number
 */
int cubePass2(int * numberPtr);


int main(void) {
	int numberMain = 5;
	int result = 0;
	
    // Run cubePass1 and print out various details about the relevant variables
    // before and after the method is run.
	puts("In main before cubePass1");
    printf("numberMain = %d\n", numberMain);
	printf("&numberMain = %p\n", &numberMain);
	result = cubePass1(numberMain);
	puts("In main after cubePass1");
    printf("numberMain = %d\n", numberMain);
	printf("Result = %d\n", result);

    puts("");
    puts("");

    // Run cubePass2 and print out various details about the relevant variables
    // before and after the method is run.
	puts("In main before cubePass2");
    printf("numberMain = %d\n", numberMain);
	result = cubePass2(&numberMain);
	puts("In main after cubePass2");
    printf("numberMain = %d\n", numberMain);
	printf("result = %d\n", result);
} // main


int cubePass1 (int number) 
{
	int cube = 0;

    puts("");
	puts("In cubePass1");

    // Print the arguent and it's pointer.
	printf("number = %d\n", number);
	printf("&number = %p\n", &number);

    // Calculate the cube and display it.
	cube = number * number * number;
	printf("cube = %d\n", cube);

    // Set the pass by value argugment to cube. (non-destructive)
	number = cube;
	printf("number = %d\n", number);

    puts("");

	return cube;
} // cubePass1

int cubePass2 (int * numberPtr) 
{
	int cube = 0;

    puts("");
	puts("In cubePass2");

    // Print the argument, what it points to, and its pointer.
	printf("numberPtr = %p\n", numberPtr);
	printf("*numberPtr = %d\n", *numberPtr);
	printf("&numberPtr = %p\n", &numberPtr);

    // Calculate the cube and set the value the argument points to with the new
    // cube calculation. (destructive)
	cube = (*numberPtr) * (*numberPtr) * (*numberPtr); 
	*numberPtr = cube;

    // Display the value the argument points to.
	printf("*numberPtr = %d\n", *numberPtr);

    puts("");

	return cube;
} // cubePass
