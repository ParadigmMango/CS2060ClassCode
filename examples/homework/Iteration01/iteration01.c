//!  Iteration 01: Implement Fundraiser Project
/*!
  \file implementation01.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \version 1.0
  \date 04-04-2023
 */

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//## General Constants
#define STRING_SIZE 80
#define TIME_STAMP_SIZE 19
#define MAX_CRED_PROMPTS 2
#define MIN_DONATION 0.0
#define MIN_GOAL 0.0
#define TRANSACTION_FEE 0.029

//## Prompt Messages
#define DONATION_PROMPT "Enter your donation amount($): "
#define EMAIL_PROMPT "Enter email address: "
#define EMAIL_VALID_PROMPT "Is this email correct? (y)es or (n)o: "
#define FIRST_NAME_PROMPT "Enter first name: "
#define GOAL_PROMPT "Enter the goal amount you want to raise: "
#define LAST_NAME_PROMPT "Enter last name: "
#define ORG_NAME_PROMPT "Enter your organization's name: "
#define ORG_PURPOSE_PROMPT "State the purpose of your fundraiser: "
#define PASSWORD_PROMPT "Enter password: "
#define RECEIPT_PROMPT "Do you want a receipt, (y)es or (n)o? "
#define URL_PROMPT "Enter URL for your fundraiser: "
#define ZIP_PROMPT "Enter your zip code: "

//## Error Messages
#define DONATION_ERROR "That is not a valid donation amount, please enter another: "
#define EMAIL_ERROR "That email is not valid, please enter another: "
#define EMAIL_MATCH_ERROR "That email does not match, please enter another: "
#define EMAIL_VALID_ERROR "Please enter (y)es or (n)o: "
#define FIRST_NAME_ERROR "That first name is not valid, please enter another: "
#define GOAL_ERROR "That goal amount is not valid, please enter another: "
#define LAST_NAME_ERROR "That last name is not valid, please enter another: "
#define PASSWORD_ERROR "That password is not valid, please enter another: "
#define PASSWORD_MATCH_ERROR "That password does not match, please enter another: "
#define RECEIPT_ERROR "Please enter (y)es or (n)o: "
#define URL_ERROR "That URL is not valid, please enter another: "
#define ZIP_ERROR "That zip code is not valid, please enter another: "

//## Donation Constants
#define ADMIN_MODE "q"
#define ADMIN_NUM -1

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

//## Mode Constants
#define MODE_FAIL -1
#define MODE_SUCCESS 1
#define MODE_SUCCESS_ADMIN 42


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
    double feesSum;

    // donor tracking
    unsigned int numDonors;
} Organization; 

//! An donor struct which packages all relevant information to itself.
typedef struct donor {
    char firstName[STRING_SIZE];
    char lastName[STRING_SIZE];
    char zip[STRING_SIZE];
} Donor;

//## Misc. Functions
//! Wrapper function which clears the input buffer
void clearBuffer(void);
//! Have the user match a credential
/*!
  \param cred the credential to match against
  \param prompt the original prompt for the credential
  \param badMatchError the error to display if the user entered credential doen't match
  \return whether or not the user can match the credential in time
 */
bool matchCredential(const char *cred, const char *prompt, const char
                     *badMatchError);
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
//! Get a line string from the user with a prompt
/*!
  \param word the line string to write into
  \param wordSize the size of the line string
  \param prompt the prompt to give the user
  \return whether or not a string was successfully retrieved
 */
bool getLineWithPrompt(char *line, size_t lineSize, const char *prompt);
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
//! Converts a string to a positive double and returns the result
/*!
  \param str the original string
  \param num the location of the double to write into
  \param min the minimum acceptable number that is considered valid
  \return Whether or not the conversion succeeded
 */
bool strToPosDouble(const char *str, double *num, double min);
//! Gets a valid positive double input from the user.  Primarily for retrieving
//! money.
/*!
  \param num the location of the double to write into
  \param prompt the original user prompt
  \param error the error and follow-up prompt
  \param min the minimum acceptable number
 */
void getPosDouble(double *num, const char *prompt, const char *error, double min);

//## Donation input toolchain
//! Determines if a string is a donation amount.
/*!
  \param donation the string to validate
  \param donationSize the size of the string to validate
  \return Whether or not the string is a valid donation amount
 */
bool isDonation(const char *donation, size_t donationSize);
//! Gets a valid donation from the user.
/*!
  \param donation the address of the double to write the donation into
 */
void getDonation(double *donation);

//## Modes
//! Sets up an org struct with user input.
/*!
  \param org the pointer to the organization to initialize
  \return whether the mode was successful
 */
int setUp(Organization *org);
//! Have a user donate to the organization.
/*!
  \param org the pointer to the organization to donate to
  \param donor the pointer to a donor struct to track donors
  \return whether the mode was successful or if to go to admin mode
 */
int donate(Organization *org, Donor *donor);
//! Enter the reports mode which prints out organization details and ends the program
/*!
  \param org the organization to print details about
  \return whether the mode was succeeded or to go back to donations mod
 */
int report(const Organization *org);


int main(void)
{
    Organization org;

    // Ignore this for now: it is an unused variable used to allow donations to 
    // run when donors are not tracked for the moment.
    Donor dummyDonor;
    
    // setup
    setUp(&org);

    // run a loop until the program ends
    bool endProgram = false;
    while (!endProgram) {
        // track the output of donation modes to see if the report mode should 
        // be entered
        int donationSuccess = donate(&org, &dummyDonor);

        if (donationSuccess == MODE_SUCCESS_ADMIN) {
            // track the output of the report mode to see if the program should
            // end
            int reportSuccess = report(&org);

            if (reportSuccess == MODE_SUCCESS) {
                endProgram = true;
            }
        }
    }

    return 0;
} // main


void clearBuffer(void)
{
    while (getchar() != '\n');
} // clearBuffer

bool matchCredential(const char *cred, const char *prompt, const char
                     *badMatchError)
{
    // Grab the initial credential to test against
    printf("%s", prompt);
    char inputCred[STRING_SIZE];
    getWord(inputCred, STRING_SIZE);

    unsigned int numPrompts = 1;
    bool isValid;

    // special case here is that MAX_CRED_PROMPTS means no limit on cred prompts
    if (MAX_CRED_PROMPTS == 0) {
        // Print errors and grab creds until a valid one is obtained
        while (strcmp(cred, inputCred) != 0) {
            printf("%s", badMatchError);

            getWord(inputCred, STRING_SIZE);

            numPrompts++;
        }

        isValid = true;
    }
    // prompt an additional, limited number of times
    else {
        // print erros and grab inputs until a valid one is found or the user
        // runs out of prompts
        while (strcmp(cred, inputCred) != 0 && numPrompts < MAX_CRED_PROMPTS) {
            printf("%s", badMatchError);

            getWord(inputCred, STRING_SIZE);

            numPrompts++;
        }

        isValid = strcmp(cred, inputCred) == 0;
    }

    return isValid;
} // matchCredential

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

bool getLineWithPrompt(char *line, size_t lineSize, const char *prompt)
{
    printf("%s", prompt);

    return getLine(line, lineSize);
} // getLineWithPrompt

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

bool strToPosDouble(const char *str, double *num, double min)
{
    // vars for validation
	char *end;
	errno = 0;

    bool isValid = false;

	double doubleTest = strtod(str, &end);

    // Test for a successful conversion
	if (end != str && '\0' == *end && !(doubleTest == HUGE_VAL && ERANGE == errno)
        && doubleTest > min) {
        *num = doubleTest;

        isValid = true;
	}

    return isValid;
} // strToDouble

void getPosDouble(double *num, const char *prompt, const char *error, double min)
{
    printf("%s", prompt);

    // Set up input variables
    char word[STRING_SIZE];
    bool getWordSuccess = getWord(word, STRING_SIZE);
    double doubleTest;

    // Print errors until a valid word that also passes validate() is found
    while (!getWordSuccess || !strToPosDouble(word, &doubleTest, min)) {
        printf("%s", error);

        getWordSuccess = getWord(word, STRING_SIZE);
    }

    *num = doubleTest;
} // getDouble

bool isDonation(const char *donation, size_t donationSize)
{
    bool isValid = false;

    // determine if the string is a double that is above the minimum donation
    double moneyNum;
    bool isDonationDouble = strToPosDouble(donation, &moneyNum, MIN_DONATION);
    
    if (isDonationDouble) {
        isValid = true;
    } else {
        // Test for ADMIN_MODE
        char lowerDonation[STRING_SIZE];
        toLower(donation, lowerDonation);

        if (strcmp(lowerDonation, ADMIN_MODE) == 0) {
            isValid = true;
        }
    }

    return isValid;
} // isDonation

void getDonation(double *donation)
{    
    // get a valid donation string
    char rawDonation[STRING_SIZE];
    getValidatedWord(rawDonation, STRING_SIZE, &isDonation, DONATION_PROMPT,
                     DONATION_ERROR);

    // lowercase the string to test against ADMIN_MODE
    char lowerDonation[STRING_SIZE];
    toLower(rawDonation, lowerDonation);

    if (strcmp(lowerDonation, ADMIN_MODE) == 0) {
        // if string is ADMIN_MODE, return ADMIN_NUM to indicate an exit
        *donation = ADMIN_NUM;
    } else {
        // set validnumbers
        strToPosDouble(rawDonation, donation, MIN_DONATION);
    }
} // getDonation

int setUp(Organization *org)
{
    // Grab user inputs
    getLineWithPrompt(org->name, STRING_SIZE, ORG_NAME_PROMPT);
    getLineWithPrompt(org->purpose, STRING_SIZE, ORG_PURPOSE_PROMPT);
    getName(org->ownerFirstName, STRING_SIZE, FIRST_NAME_PROMPT, FIRST_NAME_ERROR);
    getName(org->ownerLastName, STRING_SIZE, LAST_NAME_PROMPT, LAST_NAME_ERROR);
    getPosDouble(&org->goalAmount, GOAL_PROMPT, GOAL_ERROR, MIN_GOAL);
    getEmail(org->ownerEmail, STRING_SIZE);
    getPassword(org->ownerPwd, STRING_SIZE);
    getURL(org->url, STRING_SIZE);

    // Initialize count and sum variables
    org->numDonations = 0;
    org->donationSum = 0.0;
    org->numDonors = 0;
    org->feesSum = 0.0;
    
    // Print out thank you message. Not a constant in case more variables in the
    // message are desired.
    printf("Thank you %s %s. The url to raise funds for %s is %s.\n\n",
           org->ownerFirstName, org->ownerLastName, org->name, org->url);

    return MODE_SUCCESS;
} // setUp

int donate(Organization *org, Donor *donor)
{
    int exitValue;

    // Print out org info. Not constants in case more variables in the
    // printf statements are desired.
    puts(org->url);
    puts("MAKE A DIFFERENCE BY YOUR DONATION");
    printf("Organization: %s\n", org->name);
    printf("Purpose: %s\n", org->purpose);
    printf("We currently have raised $%.2lf.\n", org->donationSum);
    if (org->donationSum >= org->goalAmount) {
        puts("We have reached our goal but can still use the donations.");
    } else {
        printf("We are %2.0lf%% towards our goal of $%.2lf.\n",
               (org->donationSum / org->goalAmount) * 100, org->goalAmount);
    }
    puts("");

    // Retrieve the user's donation
    double donation = 0;
    getDonation(&donation);

    // exit to reports mode
    if (donation == ADMIN_NUM) {
        exitValue = MODE_SUCCESS_ADMIN;
    }
    // add donation
    else {
        // get donor info
        getName(donor->firstName, STRING_SIZE, FIRST_NAME_PROMPT, FIRST_NAME_ERROR);
        getName(donor->lastName, STRING_SIZE, LAST_NAME_PROMPT, LAST_NAME_ERROR);
        getZip(donor->zip, STRING_SIZE);

        // track donations and fees
        double fee = donation * TRANSACTION_FEE;
        org->feesSum += fee;
        
        donation -= fee;
        org->donationSum += donation;

        org->numDonations++;

        // print donation thank you
        printf("Thank you for your donation. There is a %.1lf%% credit card" 
               "processing fee of %.2lf. %.2lf will be donated.\n",
                100 * TRANSACTION_FEE, fee, donation);
        
        if (getYesOrNo(RECEIPT_PROMPT, RECEIPT_ERROR)) {
            // create formatted timestamp
            char timeStamp[TIME_STAMP_SIZE];
            time_t time_var = time(NULL);
            strftime(timeStamp, sizeof(timeStamp), "%D - %I:%M%p",
                     localtime(&time_var));

            // print the actual receipt
            puts("");
            printf("Organization: %s\n", org->name);
            printf("Donation Amount: $%.2lf\n", fee + donation);
            printf("Donation Date: %s\n", timeStamp);
        }

        exitValue = MODE_SUCCESS;
    }

    puts("");

    return exitValue;
} // donate

int report(const Organization *org)
{
    int exitValue;

    puts("");

    // Determines if the email address is valid
    if (matchCredential(org->ownerEmail, EMAIL_PROMPT, EMAIL_MATCH_ERROR)) {
        // dermines if the password is valid
        if (matchCredential(org->ownerPwd, PASSWORD_PROMPT,
                PASSWORD_MATCH_ERROR)) {
            // prints summary
            printf("~~~~~ %s ~~~~~\n", org->name);
            printf("You collected %u donation(s) totaling $%.2lf after $%.2lf "
                   "in fees.\n", org->numDonations, org->donationSum,
                   org->feesSum);

            exitValue = MODE_SUCCESS;
        } else {
            exitValue = MODE_FAIL;
        }
    } else {
        exitValue = MODE_FAIL;
    }

    return exitValue;
} // report
