//!  Iteration 01: Implement Fundraiser Project
/*!
  \file implementation01.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \version 1.0
  \date 04-04-2023
 */

#include <stdio.h>
#include <time.h>

int main(void)
{
    char str[19];

    time_t time_var = time(NULL);

    strftime(str, sizeof(str), "%D - %I:%M%p", localtime(&time_var));

    puts(str);
} // main