//!  Iteration 01: Implement Fundraiser Project
/*!
  \file implementation01.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \version 1.0
  \date 04-04-2023
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


//## General Constants
#define STRING_SIZE 80
#define TIME_STAMP_SIZE 19

//## Prompt Messages
#define EMAIL_PROMPT "Enter email address: "
#define EMAIL_VALID_PROMPT "Is this email correct? (y)es or (n)o "
#define FIRST_NAME_PROMPT "Enter first name: "
#define LAST_NAME_PROMPT "Enter last name: "
#define PASSWORD_PROMPT "Enter password: "
#define URL_PROMPT "Enter URL for your fundraiser: "
#define ZIP_PROMPT "Enter your zip code: "

//## Error Messages
#define EMAIL_ERROR "That email is not valid, please enter another: "
#define EMAIL_VALID_ERROR "Please enter (y)es or (n)o: "
#define FIRST_NAME_ERROR "That first name is not valid, please enter another: "
#define LAST_NAME_ERROR "That last name is not valid, please enter another: "
#define PASSWORD_ERROR "That password is not valid, please enter another: "
#define URL_ERROR "That URL is not valid, please enter another: "
#define ZIP_ERROR "That zip code is not valid, please enter another: "

//## URL Constants
#define LINK_BEGINNING "https:donate.com/"
#define LINK_BEGINNING_SIZE 17
#define LINK_END "?form=popup#"
#define LINK_END_SIZE 12

//## Yes/No Constants
const char YES[STRING_SIZE] = "y";
const char NO[STRING_SIZE] = "n";

//## Zip Constants
#define ZIP_SIZE 5


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
//! Wrapper function which clears the input buffer
void clearBuffer(void);
//! A safer version of strncpy that null terminates all srcs
/*!
  \param dest the destination string to write to
  \param src the source string to copy from
  \param count the number of chars to copy

  \pre The destination size is at least one greater than count
 */
void strNCpySafe(char *dest, const char *src, size_t count);
//! Turns each char in a string into its lowercase version
/*!
  \param rawStr the raw string
  \param lowerStr the string to write the lowercase version of rawStr into
 */
void toLower(const char *rawStr, char *lowerStr);

//## Core string input toolchain
//! Get a line string from the user
/*!
  \param line the string to write into
  \param lineSize the size of the line string
  \return whether or not a string was successfully retrieved
 */
bool getLine(char *line, size_t lineSize);
//! Get a word string from the user
/*!
  \param word the word string to write into
  \param wordSize the size of the word string
  \return whether or not a string was successfully retrieved
 */
bool getWord(char *word, size_t wordSize);
//! Get a validated word string from the user
/*!
  \param word the word string to write into
  \param wordSize the size of the word string
  \param validate the address of the function to validate the word
  \param prompt the original prompt for input
  \param error the error message which also asks for an input again
 */
void getValidatedWord(char *word, size_t wordSize, bool (*validate)(const char
                      *, size_t), const char *prompt, const char *error);

//## String input validation functions
//! Determine if a string is an email address
/*!
  \param email the string to be validated
  \param emailSize the size of the string to be validated
  \return whether or not the string is an email address
 */
bool isEmail(const char *email, size_t emailSize); 
//! Determine if a string is a name
/*!
  \param email the string to be validated
  \param emailSize the size of the string to be validated
  \return whether or not the string is a name
 */
bool isName(const char *name, size_t nameSize);
//! Determine if a string is a valid password
/*!
  \param email the string to be validated
  \param emailSize the size of the string to be validated
  \return whether or not the string is a valid password
 */
bool isPassword(const char *password, size_t passwordSize);
//! Determine if a string is a URL
/*!
  \param url the string to be validated
  \param urlSize the size of the string to be validated
  \return whether or not the string is a URL
 */
bool isURL(const char *url, size_t urlSize);
//! Determine if a string is a yes or no
/*!
  \param yesNo the string to be validated
  \param yesNoSize the size of the string to be validated
  \return whether or not the string is a yes or no
 */
bool isYesOrNo(const char *yesNo, size_t yesNoSize);
//! Determine if a string is an email address
/*!
  \param email the string to be validated
  \param emailSize the size of the string to be validated
  \return whether or not the string is an email address
 */
bool isZip(const char *zip, size_t zipSize);

//## String input wrapper functions for getValidatedWord()
//! Gets a valid email from the user
/*!
  \param email the string to write the email into
  \param emailSize the size of the email string
 */
void getEmail(char *email, size_t emailSize);
//! Gets a valid name from the user
/*!
  \param name the string to write the name into
  \param nameSize the size of the name string
  \param prompt the intial user prompt
  \param error the error prompt which agains asks the user for input
 */
void getName(char *name, size_t nameSize, const char *prompt, const char *error);
//! Gets a valid password from the user
/*!
  \param password the string to write the password into
  \param passwordSize the size of the password string
 */
void getPassword(char *password, size_t passwordSize);
//! Gets a valid url from the user
/*!
  \param url the string to write the URL into
  \param urlSize the size of the URL string
 */
void getURL(char *url, size_t urlSize);
//! Get a yes or no from the user
/*!
  \param prompt the prompt to provide the user with for retrieving a yes or no
  \param error the error which will again prompt for a yes or no
  \return true if yes, false if no
 */
bool getYesOrNo(const char *prompt, const char *error);
//! Gets a valid zip code from the user
/*!
  \param email the string to write the zip into
  \param emailSize the size of the zip string
 */
void getZip(char *zip, size_t zipSize);

//## Double input toolchain
bool strToDouble(const char *str, double *num);
void getDouble(double *num, const char *prompt, size_t promptSize, const char
               *error, size_t errorSize);

//## Donation input toolchain
bool isDonation(const char *donation, size_t donationSize);
void getDonation(double *donation, const char *prompt, const char *error);


int main(void)
{
    char input[STRING_SIZE];

    getZip(input, STRING_SIZE);

    puts(input);

    char str[TIME_STAMP_SIZE];

    time_t time_var = time(NULL);

    strftime(str, sizeof(str), "%D - %I:%M%p", localtime(&time_var));

    puts(str);
} // main


void clearBuffer(void)
{
    while (getchar() != '\n');
} // clearBuffer

void strNCpySafe(char *dest, const char *src, size_t count)
{
    strncpy(dest, src, count);

    dest[count] = '\0';
} // strNCpySafe

void toLower(const char *rawStr, char *lowerStr)
{
    strNCpySafe(lowerStr, rawStr, strlen(rawStr));

    char *currCharPtr = lowerStr;

    while (*currCharPtr != '\0') {
        *currCharPtr = tolower(*currCharPtr);

        currCharPtr++;
    }
} // toLower

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

bool getWord(char *word, size_t wordSize)
{
    bool getLineSuccess = getLine(word, wordSize);

    // if getLine succeded, trim the string at the first space if it exists
    if (getLineSuccess) {
        char *spacePtr = strchr(word, ' ');
        
        if (spacePtr != NULL) {
            *spacePtr = '\0';
        }
    }

    return getLineSuccess;
} // getWord

void getValidatedWord(char *word, size_t wordSize, bool (*validate)(const char
                      *, size_t), const char *prompt, const char *error)
{
    printf("%s", prompt);

    bool getWordSuccess = getWord(word, wordSize);

    // Print errors until a valid word that also passes validate() is found
    while (!getWordSuccess || !(*validate)(word, wordSize)) {
        printf("%s", error);

        getWordSuccess = getWord(word, wordSize);
    }
} // getValidatedWord

bool isEmail(const char *email, size_t emailSize)
{
    return getYesOrNo(EMAIL_VALID_PROMPT, EMAIL_VALID_ERROR);
} // isEmail

bool isName(const char *name, size_t nameSize)
{
    return true;
} // isName

bool isPassword(const char *password, size_t passwordSize)
{
    return true;
} // isPassword

bool isURL(const char *url, size_t urlSize)
{
    size_t urlLen = strlen(url);

    bool isURLValid = true;

    // Check that there is enough space for at least one character between 
    // link beginning and link end
    if (urlLen < LINK_BEGINNING_SIZE + LINK_END_SIZE + 1) {
        isURLValid = false;
    } else {
        // Check that the link beginning is valid
        char linkBeginning[STRING_SIZE];

        strNCpySafe(linkBeginning, url, LINK_BEGINNING_SIZE);

        if (strcmp(linkBeginning, LINK_BEGINNING) != 0) {
            isURLValid = false;
        } else {
            // Check that there is a questionmark in the string
            char *questionMarkPtr = strchr(url, '?');

            if (questionMarkPtr == NULL) {
                isURLValid = false;
            } else {
                // Check that the link ending is valid
                if (strcmp(questionMarkPtr, LINK_END) != 0) {
                    isURLValid = false;
                } // link end guard clause
            } // question mark guard clause
        } // link beginnning guard clause
    } // url length guard clause

    return isURLValid;
} // isURL

bool isYesNo(const char *yesNo, size_t yesNoSize)
{
    // lowercase the input string
    char lowerYesNo[STRING_SIZE];
    strNCpySafe(lowerYesNo, yesNo, strlen(yesNo));
    toLower(lowerYesNo, lowerYesNo);

    // check if the lowercase string is equal to YES or NO
    return strcmp(lowerYesNo, YES) == 0 ||
           strcmp(lowerYesNo, NO) == 0;
} // isYesNo

bool isZip(const char *zip, size_t zipSize)
{
    bool isZipValid = true;

    // zip length guard clause
    if (strlen(zip) != ZIP_SIZE) {
        isZipValid = false;
    } else {
        // each character must be a digit guard clause
        for (size_t i = 0; i < ZIP_SIZE; i++) {
            if (!isdigit(zip[i])) {
                isZipValid = false;
            }
        }

        // the first character can't be zero guard clause
        if (zip[0] == '0') {
            isZipValid = false;
        }

        // the last character must be null guard clause
        if (zip[ZIP_SIZE] != '\0') {
            isZipValid = false;
        }
    }

    return isZipValid;
} // isZip

void getEmail(char *email, size_t emailSize)
{
    getValidatedWord(email, emailSize, &isEmail, EMAIL_PROMPT, EMAIL_ERROR);
} // getEmail

void getName(char *name, size_t nameSize, const char *prompt, const char *error)
{
    getValidatedWord(name, nameSize, &isName, prompt, error);
} // getName

void getPassword(char *password, size_t passwordSize)
{
    getValidatedWord(password, passwordSize, &isPassword, PASSWORD_PROMPT,
                     PASSWORD_ERROR);
} // getPassword

void getURL(char *url, size_t urlSize)
{
    getValidatedWord(url, urlSize, &isURL, URL_PROMPT, URL_ERROR);
} // getURL

bool getYesOrNo(const char *prompt, const char *error)
{
    // get raw input
    char rawStr[STRING_SIZE];
    getValidatedWord(rawStr, STRING_SIZE, &isYesNo, prompt, error);

    // lower case the raw sting
    char lowerRawStr[STRING_SIZE];
    strNCpySafe(lowerRawStr, rawStr, STRING_SIZE);
    toLower(lowerRawStr, lowerRawStr);

    // compare the lowercase string to the yes string
    return strcmp(YES, lowerRawStr) == 0;
} // getYesOrNo

void getZip(char *zip, size_t zipSize)
{
    getValidatedWord(zip, zipSize, &isZip, ZIP_PROMPT, ZIP_ERROR);
} // getZip
