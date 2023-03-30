//!  Iteration 01: Implement Fundraiser Project
/*!
  \file implementation01.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \version 1.0
  \date 04-04-2023
 */

#include <stdio.h>
#include <time.h>

#define STRING_SIZE 80
#define TIME_STAMP_SIZE 19

//! An organization struct which packages all relevant information to itself.
typedef struct organization {
    // organziation properties
    char name[STRING_SIZE];
    char purpose[STRING_SIZE];
    char url[STRING_SIZE];
    double goalAmount;

    // owner properties
    char ownerEmail[STRING_SIZE];
    char ownerPwd[STRING_SIZE];
    char ownerFirstName[STRING_SIZE];
    char ownerLastName[STRING_SIZE];

    // donation tracking
    unsigned int numDonations;
    double donationSum;

    // donor tracking
    unsigned int numDonors;
} Organization; 

//! An donor struct which packages all relevant information to itself.
typedef struct donor {
    char firstName[STRING_SIZE];
    char fastName[STRING_SIZE];
    char zip[STRING_SIZE];
} Donor;

int main(void)
{
    char str[TIME_STAMP_SIZE];

    time_t time_var = time(NULL);

    strftime(str, sizeof(str), "%D - %I:%M%p", localtime(&time_var));

    puts(str);
} // main
