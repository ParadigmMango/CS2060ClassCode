//!  CS2060.002 Homework Assignment #3
/*!
  \file hw03.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \brief A program which calculates the daily charges of a parking garage.
  \version 1.0
  \date 02-16-2023
 */

#include <stdbool.h>


//! Calculates how much a car is charged.
/*!
  Calculates the charge accrued when a car is parked in the garage for a 
  certain number of hours.

  \param hours the hours a car has been parked
  \return The charge calculation
 */
double calculateCharge(double hours);

//! Gets a valid input.
/*!
  Repeatedly prompts a user for an input and responds with why invalid inputs
  are not accepted until a valid input is entered, which it then returns.

  \return A valid double input
 */
double getValidInput();

//! Validates numeric inputs.
/*!
  \param input 
  \return A boolean indicating whether an input is valid
 */
bool isNumericInputValid(double input);

//! Prints a car's transaction summary.
/*!
  \param carNum the number of the car
  \param hours the number of hours the car parked in the garage today
  \param charge the charge the car accrued
 */
void printCarSummary(unsigned int carNum, double hours, double charge);

//! Print the day's total cars, hours parked, and charges summary.
/*!
  \param numCars the number of cars parked in the garage today
  \param hours the total hours all cars spent parked in the garage today
  \param charges the total charges all cars accrued in the garage today
 */
void printTotalsSummary(unsigned int numCars, double hours, double charges);


//! The main function
/*!
  \return The exit value
 */
int main(void) {
    return 0;
}
