//!  CS2060.002 Homework Assignment #3
/*!
  \file hw03.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \brief A program which calculates the daily charges of a parking garage.
  \version 1.0
  \date 02-16-2023
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

//! The additional hourly rate past the minimum charge.
#define ADDITIONAL_HOURS_RATE 0.75
//! The the user input which indicates they wish to end the program.
#define END_PROGRAM -1
//! The maximum amount a car may be charged in a day.
#define MAX_CHARGE 12.00
//! The maximum hours a user input may indicate.
#define MAX_HOURS_ALLOWED 24.0
//! The minimum amount a car may be charged in a day.
#define MIN_FLAT_RATE_CHARGE 3.00
//! The maximum time a car can be parked to only pay the minimum charge.
#define MIN_HOURS_AT_FLAT_RATE 3.0


//! Calculates how much a car is charged.
/*!
  Calculates the charge accrued when a car is parked in the garage for a 
  certain number of hours.

  \pre The input is valid.
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


//! The main function.
/*!
  \return The exit value
 */
int main(void) {
    unsigned int carNum = 0;
    double input;
    double totalHours = 0.0;
    double totalCharge = 0.00;

    // Retrieve, calculate and add car values until the user ends the program.
    do {
        input = getValidInput();

        if (input != END_PROGRAM) {
            // Run an individual car's calculations.
            carNum++;

            double charge = calculateCharge(input);

            printCarSummary(carNum, input, charge);

            // Keep a running total of hours and charges.
            totalHours += input;
            totalCharge += charge;
        }
    } while (input != END_PROGRAM);

    printTotalsSummary(carNum, totalHours, totalCharge);

    return 0;
}

double calculateCharge(double hours) {
    double charge = MIN_FLAT_RATE_CHARGE;

    if (hours > MIN_HOURS_AT_FLAT_RATE) {
        // Charge the hourly rate.
        double hoursCharged = ceil(hours - MIN_HOURS_AT_FLAT_RATE);
        charge += hoursCharged * ADDITIONAL_HOURS_RATE;

        // Enforce the maximum charge.
        if (charge > MAX_CHARGE) {
            charge = MAX_CHARGE;
        }
    }

    return charge;
}

double getValidInput() {
    double input;
    bool isInputValid = false;

    do {
        // Retrieve information from the user and clear the buffer.
        puts("Enter the number of hours the car was parked or enter -1 "
              "to quit.");
        
        int retVal = scanf("%lf", &input);

        while(getchar() != '\n');

        // Accept only numeric inputs.
        if (retVal > 0) {
            // Accept only valid numeric inputs.
            if (isNumericInputValid(input)) {
                isInputValid = true;
            } else {
                puts("You did not enter a valid number(input was neither ERROR "
                     "or between 0 and MAX_HOURS_ALLOWED)");
            }
        } else {
            puts("You did not enter a number");
        }
    } while (!isInputValid);

    return input;
}

bool isNumericInputValid(double input) {
    // Ensure that the input is either a valid hour count or END_PROGRAM.
    return input == END_PROGRAM || (input > 0.0 && input <= MAX_HOURS_ALLOWED);
}

void printCarSummary(unsigned int carNum, double hours, double charge) {
    puts("  Car          Hours         Charge");
    printf("  %3u\t       %2.1f\t     $%.2lf\n", carNum, hours, charge);
    puts("");
}

void printTotalsSummary(unsigned int numCars, double hours, double charges) {
    // Print the data header.
    puts("");
    puts("PARKING GARAGE SUMMARY");

    // Print the data only if at least one car parked in the garage today.
    if (numCars == 0) {
        puts("There were no cars parked today.");
    } else {
        puts("Total Cars      Total Hours     Total Charge");
        printf("    %3u\t           %2.1f\t           $%.2lf\n", numCars, hours,
                                                                 charges);
    }
}
