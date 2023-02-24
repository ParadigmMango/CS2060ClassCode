//!  CS2060.002 Homework Assignment #4
/*!
  \file hw04.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \brief A program that calculates the final grades and class average of a class.
  \version 1.0
  \date 02-23-2023
 */

#include <stdio.h>

//! A string indicating the the number associated with each grade category.
#define CATEGORIES "1. Learning Activity 2. Homework 3. Project 4. Midterm 5. Final"
//! The number of grade categories for the class.
#define GRADE_CATEGORIES 5
//! The maximum grade possible in a grade category.
#define MAX_GRADE 105.0
//! The minimum grade possible in a grade category.
#define MIN_GRADE 0.0
//! The total number of students in the class.
#define STUDENTS 4

//! The minimum grade required to earn an A in the class.
#define A_MIN_GRADE 90.0
//! The minimum grade required to earn a B in the class.
#define B_MIN_GRADE 80.0
//! The minimum grade required to earn a C in the class.
#define C_MIN_GRADE 70.0
//! The minimum grade required to earn a D in the class.
#define D_MIN_GRADE 60.0

//! An array containing all of the weights for the grade categories in order.
const double GRADE_CATEGORY_WEIGHTS[] = {0.1, 0.3, 0.3, 0.15, 0.15};


//! Calculates the average value of an array.
/*!
  \param arr the array whose values will be used
  \param size the size of the array
  \return The average of the array
 */
double calcAverage(const double arr[], size_t size);


//! The main function.
/*!
  \return The exit value
 */
int main(void)
{
    double testArr1[] = {1, 2, 3};
    double testArr2[] = {-1.1, 2.2, 0, 333};
    double testArr3[] = {0, 0, 2};

    printf("%lf %lf %lf", calcAverage(testArr1, 3), calcAverage(testArr2, 4),
                          calcAverage(testArr3, 3));

    puts("Hello world!");
}

double calcAverage(const double arr[], size_t size)
{
    double sum = 0.0;

    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    return sum / size;
}