//!  CS2060.002 Homework Assignment #4
/*!
  \file hw04.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \brief A program that calculates the final grades and class average of a class.
  \version 1.0
  \date 02-23-2023
 */

#include <stdio.h>

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
