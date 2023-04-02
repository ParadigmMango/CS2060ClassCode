//!  Iteration 01: Implement Fundraiser Project
/*!
  \file implementation01.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \version 1.0
  \date 04-04-2023
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
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

//## Misc. Functions
void clearBuffer();

//## Core string input toolchain
/*! Get a line string from the user
  \param line the string to write into
  \param lineSize the size of the line string
  \return whether or not the fgets succeeded
 */
bool getLine(char *line, size_t lineSize);

bool getWord(char *word, size_t wordSize);
void getValidatedWord(char *word, size_t wordSize, bool (*validate)(const char *,
                   size_t), const char *prompt, size_t promptSize, const char
                   *error, size_t errorSize);

//## String input validation functions
bool isEmail(const char *email, size_t emailSize); 
bool isName(const char *name, size_t nameSize);
bool isPassword(const char *password, size_t passwordSize);
bool isURL(const char *url, size_t urlSize);
bool isYesOrNo(const char *yesNo, size_t yesNoSize);
bool isZip(const char *zip, size_t zipSize);

//## String input wrapper functions for getValidatedWord()
void getEmail(char *email, size_t emailSize, const char *prompt, size_t
              promptSize, const char *error, size_t errorSize);
void getName(char *name, size_t nameSize, const char *prompt, size_t promptSize,
             const char *error, size_t errorSize);
void getPassword(char *password, size_t passwordSize, const char *prompt, size_t
                 promptSize, const char *error, size_t errorSize);
void getURL(char *url, size_t urlSize, const char *prompt, size_t promptSize,
            const char *error, size_t errorSize);
bool getYesOrNo(const char *prompt, size_t promptSize, const char *error, size_t
                errorSize);
void getZip(char *zip, size_t zipSize, const char *prompt, size_t promptSize,
            const char *error, size_t errorSize);

//## Double input toolchain
bool strToDouble(const char *str, double *num);
void getDouble(double *num, const char *prompt, size_t promptSize, const char
               *error, size_t errorSize);

//## Donation input toolchain
bool isDonation(const char *donation, size_t donationSize);
void getDonation(double *donation, const char *prompt, size_t promptSize, const
                 char *error, size_t errorSize);


int main(void)
{
    char input[STRING_SIZE];

    bool retVal = getLine(input, STRING_SIZE);

    printf("%d\n", retVal);
    puts(input);

    char str[TIME_STAMP_SIZE];

    time_t time_var = time(NULL);

    strftime(str, sizeof(str), "%D - %I:%M%p", localtime(&time_var));

    puts(str);
} // main


void clearBuffer()
{
    while (getchar() != '\n');
}

bool getLine(char *line, size_t lineSize)
{
    char *fgetsRetVal = fgets(line, lineSize, stdin);

    // old newline sanitization method: difficult to clear buffer with and
    // didn't trim newline chars that weren't at the end of line
    // if (fgetsSuccess != NULL && line[lineSize - 1] == '\n') {
    //     line[lineSize - 1] = '\0';
    // }

    // New newline sanitization method, clears buffer or trims newline using a 
    // pointer to that newline
    // Guard clauses are forbidden, so it is wrapped in an if statement
    if (fgetsRetVal != NULL) {
        char *newLinePtr = strchr(line, '\n');
        if (newLinePtr != NULL) {
            *newLinePtr = '\0';
        } else {
            clearBuffer();
        }
    }

    return fgetsRetVal != NULL;
} // getLine

bool getWord(char *word, size_t wordSize);

void getValidatedWord(char *word, size_t wordSize, bool (*validate)(const char *,
                   size_t), const char *prompt, size_t promptSize, const char
                   *error, size_t errorSize);
