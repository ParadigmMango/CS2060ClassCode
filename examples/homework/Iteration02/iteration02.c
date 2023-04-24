//!  Iteration 02: Expand Fundraiser Project
/*!
  \file implementation01.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \version 2.0
  \date 04-23-2023
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
#define MAX_CRED_PROMPTS 3
#define MIN_DONATION 0.0
#define MIN_GOAL 0.0
#define TRANSACTION_FEE 0.031

//## Prompt Messages
#define DONATION_PROMPT "Enter your donation amount($): "
#define DONATION_SELECT_PROMPT "Select the organization to donate to: "
#define EMAIL_PROMPT "Enter email address: "
#define EMAIL_VALID_PROMPT "Is this email correct? (y)es or (n)o: "
#define GOAL_PROMPT "Enter the goal amount you want to raise: "
#define NEW_ORG_PROMPT "Do you wish to add another fundraiser? (y)es or (n)o: "
#define ORG_NAME_PROMPT "Enter your organization's name: "
#define ORG_PURPOSE_PROMPT "State the purpose of your fundraiser: "
#define FIRST_LAST_NAME_PROMPT "Enter first and last name: "
#define PASSWORD_PROMPT "Enter password: "
#define RECEIPT_PROMPT "Do you want a receipt, (y)es or (n)o? "
#define SELECT_PROMPT "Enter the name of the organization you wish to donate to: "
#define URL_PROMPT "Enter URL for your fundraiser: "
#define ZIP_PROMPT "Enter your zip code: "

//## Error Messages
#define DONATION_ERROR "That is not a valid donation amount, enter another: "
#define EMAIL_ERROR "That email is not valid, please enter another: "
#define EMAIL_MATCH_ERROR "That email does not match, please enter another: "
#define EMAIL_VALID_ERROR "Please enter (y)es or (n)o: "
#define GOAL_ERROR "That goal amount is not valid, please enter another: "
#define MODE_ERROR "A mode error has occurred."
#define NEW_ORG_ERROR "Please enter (y)es or (n)o: "
#define PASSWORD_ERROR "That password is not valid, please enter another: "
#define PASSWORD_MATCH_ERROR "That password does not match, enter another: "
#define RECEIPT_ERROR "Please enter (y)es or (n)o: "
#define SELECT_ERROR "Please enter the valid name of a registered organization: "
#define URL_ERROR "That URL is not valid, please enter another: "
#define ZIP_ERROR "That zip code is not valid, please enter another: "

//## Donation Constants
#define ADMIN_MODE "q"
#define ADMIN_NUM -1

//## String Building Constants
#define LINK_BEGINNING "https:donate.com/"
#define LINK_BEGINNING_SIZE 17
#define LINK_END "?form=popup#"
#define LINK_END_SIZE 12

//## File Cosntants
#define FILE_WRITE_MODE "w"
#define FILE_APPEND_MODE "a"
#define ORGS_PATH "orgs.txt"
#define RECEIPTS_PATH_END "-receipts.txt"
#define RECEIPTS_PATH_END_SIZE 13

//## Password Constants
#define PWD_MIN_UPPER 1
#define PWD_MIN_LOWER 1
#define PWD_MIN_CHARS 7
#define PWD_MIN_NUMS 1


//## Yes/No Constants
const char YES[STRING_SIZE] = "y";
const char NO[STRING_SIZE] = "n";

//## Zip Constants
#define ZIP_SIZE 5

//## Linked List Constants
#define MEM_ERROR "Not enough memory for new nodes."
#define LINKED_LIST_EMPTY "There aren't any names in the list."
#define LINKED_LIST_HEADER "Organization\t\tGoal Amount\t\tCurrent Donations"

//## Mode Constants
#define MODE_SUCCESS_ADMIN 42
#define SETUP_MODE_FLAG 0
#define DONATIONS_MODE_FLAG 1
#define REPORT_MODE_FLAG 2
#define END_PROGRAM_FLAG -1


//! An donor struct which packages all relevant information to itself.
typedef struct donor
{
    char firstLastName[STRING_SIZE];
    char zip[STRING_SIZE];
} Donor;

//! An organization struct which packages all relevant information to itself.
typedef struct organization
{
    // organziation properties
    char name[STRING_SIZE];
    char purpose[STRING_SIZE];
    char receiptPath[STRING_SIZE];
    char url[STRING_SIZE];
    double goalAmount;

    // owner properties
    char ownerEmail[STRING_SIZE];
    char ownerPwd[STRING_SIZE];
    char ownerFirstLastName[STRING_SIZE];

    // donation tracking
    unsigned int numDonations;
    double donationSum;
    double feesSum;

    // donor tracking
    unsigned int numDonors;
} Organization; 

//! A node struct for organization linked lists.
typedef struct orgNode
{
    Organization org;
    struct orgNode *nextNodePtr;
} OrgNode;

//## Mode Constants
#define SETUP_MODE_FLAG 0
#define DONATIONS_MODE_FLAG 1
#define REPORT_MODE_FLAG 2
#define END_PROGRAM_FLAG -1


//## Misc. Functions
//! Wrapper function which clears the input buffer
void clearBuffer(void);
//! Have the user match a credential
/*!
  \param cred the credential to match against
  \param prompt the original prompt for the credential
  \param badMatchError the error to display if the user entered credential
                       doen't match
  \return whether or not the user can match the credential in time
 */
bool matchCredential(const char *cred, const char *prompt, const char
                     *badMatchError);
//! Prints a receipt for an organization to a given stream.
/*! 
  \param stream the stream to print to
  \param org the organization you wish to have a receipt printed for
  \param donation the amount donated
 */
void fPrintReceipt(FILE *stream, const Organization *org, double donation);
//! Prints a summary for an organization to a given stream.
/*! 
  \param stream the stream to print to
  \param org the organization you wish to have a receipt printed for
 */
void fPrintSummary(FILE *stream, const Organization *org);
//! Compares two strings in a caseless manner.
/*!
  \param str1 the string to compare against
  \param str2 the string to compare with
  \return the return value of strcmp
 */
int caselessStrcmp(const char *str1, const char *str2);
//! Generates a receipt path given an org's name
/*!
  \param receiptPath the string to write the org path into
  \param name the name of the organization
 */
void generateReceiptPath(char receiptPath[STRING_SIZE],
                         const char name[STRING_SIZE]);
//! Generates a url given an org's name
/*!
  \param url the string to write the org's url into
  \param name the name of the organization
 */
void generateUrl(char url[STRING_SIZE], const char name[STRING_SIZE]);
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
//! Turns any input string into lowercase skewercase form
/*!
  \param src the source string
  \param skewerCase the string to write the skewercase version to
 */
void toSkewerCase(const char *src, char *skewerCase);

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
                      *), const char *prompt, const char *error);

//## String input validation functions
//! Determine if a string is an email address
/*!
  \param email the string to be validated
  \return whether or not the string is an email address
 */
bool isEmail(const char *email); 
//! Determine if a string is a valid password
/*!
  \param password the string to be validated
  \return whether or not the string is a valid password
 */
bool isPassword(const char *password);
//! Determine if a string is a yes or no
/*!
  \param yesNo the string to be validated
  \return whether or not the string is a yes or no
 */
bool isYesOrNo(const char *yesNo);
//! Determine if a string is an email address
/*!
  \param zip the string to be validated
  \return whether or not the string is an email address
 */
bool isZip(const char *zip);

//## String input wrapper functions for getValidatedWord()
//! Gets a valid email from the user
/*!
  \param email the string to write the email into
  \param emailSize the size of the email string
 */
void getEmail(char *email, size_t emailSize);
//! Gets a valid password from the user
/*!
  \param password the string to write the password into
  \param passwordSize the size of the password string
 */
void getPassword(char *password, size_t passwordSize);
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
void getPosDouble(double *num, const char *prompt, const char *error,
                  double min);

//## Donation input toolchain
//! Determines if a string is a donation amount.
/*!
  \param donation the string to validate
  \param donationSize the size of the string to validate
  \return Whether or not the string is a valid donation amount
 */
bool isDonation(const char *donation);
//! Gets a valid donation from the user.
/*!
  \param donation the address of the double to write the donation into
 */
void getDonation(double *donation);

//## Linked list functions
//! Empties a list of all nodes and frees all memory allocated for it from the heap.
/*!
  \param headPtr the location of the head of the linked list
 */
void emptyList(OrgNode **headPtr);
//! Inserts an organization into a linked list in alphabetical order of name.
/*!
  \param headPtr the location of the head of the linked list
  \param org the organization to insert to the list
 */
void insertOrgToList(OrgNode **headPtr, Organization org);
//! Print the contents of a  linked list.
/*!
  \param headPtr the location of the head of the linked list
 */
void printListContents(OrgNode **headPtr);
//! Selects an organization from a linked list given it's name
/*!
  \param orgPtr the pointer to point to the org whose name is name
  \param headPtr the location of the head of the linked list
  \param name the name to select for in the list
 */
void selectOrgFromList(Organization **orgPtr, OrgNode **headPtr, const char *name);
//! Selects a valid organization from a linked list given user input.
/*!
  \param orgPtr the org which will contain a valid, selected org
  \param headPtr the location of the head of the linked list
 */
void selectValidOrgFromList(Organization **orgPtr, OrgNode **headPtr);

//## Modes
//! Sets up an org linked list with user input.
/*!
  \param headPtr the pointer to the head of the linked list to fill
  \return a mode flag
 */
int setUp(OrgNode **headPtr);
//! Have a user donate an organization.
/*!
  \param headPtr the pointer to the head of the linked list to donate to\
  \param currOrgPtr the pointer to the current org the program is donating to /
                    using for credentials
  \param donor the pointer to a donor struct to track donors
  \return a mode flag
 */
int donate(OrgNode **headPtr, Organization **currOrgPtr, Donor *donor);
//! Enter the reports mode which prints out organization details and ends the
//! program.
/*!
  \param headPtr the pointer to the head of the linked list to donate to\
  \param currOrgPtr the pointer to the current org the program is using for 
                    credentials
  \return a mode flag
 */
int report(OrgNode **headPtr, Organization **currOrgPtr);


int main(void)
{
    OrgNode *headPtr = NULL;
    Organization *currOrgPtr;

    // Ignore this for now: it is an unused variable used to allow donations to 
    // run when donors are not tracked for the moment.
    Donor dummyDonor;

    // new main loop
    int currFlag = SETUP_MODE_FLAG;
    
    // iterate at least one until the program ends
    do {
        // find run each mode and go to the mode which its return value
        // indicates with a flag
        switch (currFlag) {
          case SETUP_MODE_FLAG:
            currFlag = setUp(&headPtr);
            break;
        
          case DONATIONS_MODE_FLAG:
            currFlag = donate(&headPtr, &currOrgPtr, &dummyDonor);
            break;

          case REPORT_MODE_FLAG:
            currFlag = report(&headPtr, &currOrgPtr);
            break;
        
          default:
            currFlag = END_PROGRAM_FLAG;
            puts(MODE_ERROR);
            break;
        } // flag switch
    } while (currFlag != END_PROGRAM_FLAG);

    // old main loop
    // // run a loop until the program ends
    // bool endProgram = false;
    // while (!endProgram) {
    //     // track the output of donation modes to see if the report mode
    //     // should be entered
    //     int donationSuccess = donate(&org, &dummyDonor);

    //     if (donationSuccess == MODE_SUCCESS_ADMIN) {
    //         // track the output of the report mode to see if the program 
    //         // should end
    //         int reportSuccess = report(&org);

    //         if (reportSuccess == MODE_SUCCESS) {
    //             endProgram = true;
    //         }
    //     }
    // }

    // empty the list
    emptyList(&headPtr);

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

void fPrintReceipt(FILE *stream, const Organization *org, double donation)
{
    // create formatted timestamp
    char timeStamp[TIME_STAMP_SIZE];
    time_t time_var = time(NULL);
    strftime(timeStamp, sizeof(timeStamp), "%D - %I:%M%p",
                localtime(&time_var));

    // print the actual receipt
    fprintf(stream, "Organization: %s\n", org->name);
    fprintf(stream, "Donation Amount: $%.2lf\n", donation);
    fprintf(stream, "Donation Date: %s\n", timeStamp);
    fputs("\n", stream);
} // fPrintReceipt

void fPrintSummary(FILE *stream, const Organization *org)
{
    fprintf(stream, "Organization Name: %s\n", org->name);
    fprintf(stream, "Total Number of Donations: %d\n", org->numDonations);
    fprintf(stream, "Total amount raised: $%.2lf\n", org->donationSum);
    fprintf(stream, "Total Credit Card processing: $%.2lf\n", org->feesSum);
    fputs("\n", stream);
} // fPrintSummary

int caselessStrcmp(const char *str1, const char *str2)
{
    // create a lowercase version of each string
    char str1Lower[STRING_SIZE];
    toLower(str1, str1Lower);

    char str2Lower[STRING_SIZE];
    toLower(str2, str2Lower);

    // compare the lowercase strings
    return strcmp(str1Lower, str2Lower);
} // strCmpCaseless

void generateReceiptPath(char receiptPath[STRING_SIZE],
                         const char name[STRING_SIZE]) {
    char nameInPath[STRING_SIZE];
    toSkewerCase(name, nameInPath);

    // Copy the link's beginning, name, and end into url
    strNCpySafe(receiptPath, nameInPath, strlen(nameInPath));
    strncpy(receiptPath + strlen(nameInPath), RECEIPTS_PATH_END, RECEIPTS_PATH_END_SIZE + 1);
} // generateReceiptPath

void generateUrl(char url[STRING_SIZE], const char name[STRING_SIZE]) {
    char nameInUrl[STRING_SIZE];
    toSkewerCase(name, nameInUrl);

    // Copy the link's beginning, name, and end into url
    strNCpySafe(url, LINK_BEGINNING, LINK_BEGINNING_SIZE);
    strncpy(url + LINK_BEGINNING_SIZE, nameInUrl, strlen(nameInUrl));
    strncpy(url + LINK_BEGINNING_SIZE + strlen(nameInUrl), LINK_END,
            LINK_END_SIZE + 1);
} // generateUrl

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

void toSkewerCase(const char *src, char *skewerCase) {
    // lowercases the letters
    toLower(src, skewerCase);

    // replace all spaces in name with dashes
    char *currCharPtr = skewerCase;
    while (*currCharPtr != '\0') {
        if (*currCharPtr == ' ') {
            *currCharPtr = '-';
        }

        currCharPtr++;
    }
} // toSkewerCase

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
                      *), const char *prompt, const char *error)
{
    printf("%s", prompt);

    bool getWordSuccess = getWord(word, wordSize);

    // Print errors until a valid word that also passes validate() is found
    while (!getWordSuccess || !(*validate)(word)) {
        printf("%s", error);

        getWordSuccess = getWord(word, wordSize);
    }
} // getValidatedWord

bool isEmail(const char *email)
{
    return getYesOrNo(EMAIL_VALID_PROMPT, EMAIL_VALID_ERROR);
} // isEmail

bool isPassword(const char *password)
{
    // Declare counts
    unsigned int upperCount = 0;
    unsigned int lowerCount = 0;
    unsigned int numCount = 0;
    unsigned int charCount = 0;

    bool nullCharReached = false;

    // char pointer for iteration through the string
    const char *currCharPtr = password;

    // iterate the length of the string or until a null char is reached
    while (charCount < (strlen(password) + 1) && nullCharReached == false) {
        char currChar = *currCharPtr;

        // handle null char reached
        if (currChar == '\0') {  
            nullCharReached = true;
        } else { 
            // count up the relevant character type counters
            if (isupper(currChar)) {
                upperCount++;
            } else if (islower(currChar)) {
                lowerCount++;
            } else if (isdigit(currChar)) {
                numCount++;
            }

            // count up the general character counter
            charCount++;

            // iterate the char pointer forwards along the string
            currCharPtr++;
        }
    } // character loop

    // determin if the password is valid using the minimums and whether the 
    // end was reached
    bool isPasswordValid;
    if (upperCount < PWD_MIN_UPPER || lowerCount < PWD_MIN_LOWER || 
            numCount < PWD_MIN_NUMS || charCount < PWD_MIN_CHARS || 
            !nullCharReached) {
        isPasswordValid = false;
    } else {
        isPasswordValid = true;
    }

    return isPasswordValid;
} // isPassword

bool isYesNo(const char *yesNo)
{
    // check if the string is caselessly equal to YES or NO
    return caselessStrcmp(yesNo, YES) == 0 ||
           caselessStrcmp(yesNo, NO) == 0;
} // isYesNo

bool isZip(const char *zip)
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

void getPassword(char *password, size_t passwordSize)
{
    getValidatedWord(password, passwordSize, &isPassword, PASSWORD_PROMPT,
                     PASSWORD_ERROR);
} // getPassword

bool getYesOrNo(const char *prompt, const char *error)
{
    // get raw input
    char rawStr[STRING_SIZE];
    getValidatedWord(rawStr, STRING_SIZE, &isYesNo, prompt, error);

    // caselessly compare the lowercase string to the yes string
    return caselessStrcmp(YES, rawStr) == 0;
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
	if (end != str && '\0' == *end && !(doubleTest == HUGE_VAL &&
            ERANGE == errno) && doubleTest > min) {
        *num = doubleTest;

        isValid = true;
	}

    return isValid;
} // strToDouble

void getPosDouble(double *num, const char *prompt, const char *error,
                  double min)
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

bool isDonation(const char *donation)
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

void emptyList(OrgNode **headPtr)
{
    // set up node pointers for iteration
    OrgNode *currNodePtr = *headPtr;
    OrgNode *nextNodePtr = NULL;

    // free the current node until there are no nodes left
    while (currNodePtr != NULL) {
        nextNodePtr = currNodePtr->nextNodePtr;
        free(currNodePtr);
        currNodePtr = nextNodePtr;
    }

    // set the head pointer to NULL
    *headPtr = NULL;
} // emptyList

void insertOrgToList(OrgNode **headPtr, Organization org)
{
    // attempt to allocate memory
    OrgNode *newNodePtr = malloc(sizeof(OrgNode));

    // test for the edge case in which the os cannot give enough memory for the
    // node
    if (newNodePtr == NULL) {
        puts(MEM_ERROR);
    } else {
        // initialize newNode
        newNodePtr->nextNodePtr = NULL;
        newNodePtr->org = org;

        // initialize node pointers for iteration
        OrgNode *prevNodePtr = NULL;
        OrgNode *currNodePtr = *headPtr;

        // iterate forward until the end of the list or the new pet's name
        // is lexicologically after the current pet's name
        while (currNodePtr != NULL &&
               caselessStrcmp(org.name, currNodePtr->org.name) > 0) {
            prevNodePtr = currNodePtr;
            currNodePtr = currNodePtr->nextNodePtr;
        }

        // assign new node pointer to the prevNode's nextPtr or headPtr
        // depending on if the linked list is empty
        if (prevNodePtr == NULL) {
            *headPtr = newNodePtr;
        } else {
            prevNodePtr->nextNodePtr = newNodePtr;
        }

        // finally, reattach the follwoing nodes to the list by having the 
        // newNode's nextPtr point to currNode
        newNodePtr->nextNodePtr = currNodePtr;
    }
} // insertPet

void printListContents(OrgNode **headPtr)
{
    puts("");

    // handle if a linked list is empty
    if (*headPtr == NULL) {
        puts(LINKED_LIST_EMPTY);
    } else {
        // print the header for the contents of the linked list
        puts(LINKED_LIST_HEADER);

        // use a node pointer to iterate throught the linked list until the end
        OrgNode *currNode = *headPtr;
        while (currNode != NULL) {
            // print the current org's data
            Organization currOrg = currNode->org;
            printf("%-20s\t$%-16.2f\t$%-16.2f\n", currOrg.name,
                   currOrg.goalAmount, currOrg.donationSum);

            currNode = currNode->nextNodePtr;
        }
    }
} // printContents

void selectOrgFromList(Organization **orgPtr, OrgNode **headPtr, const char *name)
{
    OrgNode *currNodePtr = *headPtr;

    while (currNodePtr != NULL &&
           caselessStrcmp(currNodePtr->org.name, name) != 0) {
        currNodePtr = currNodePtr->nextNodePtr;
    }

    if (currNodePtr == NULL) {
        *orgPtr = NULL;
    } else {
        *orgPtr = &(currNodePtr->org);
    }
} // selectOrgFromList

void selectValidOrgFromList(Organization **orgPtr, OrgNode **headPtr)
{
    char name[STRING_SIZE];
    getLineWithPrompt(name, STRING_SIZE, SELECT_PROMPT);

    selectOrgFromList(orgPtr, headPtr, name);

    while (*orgPtr == NULL) {
        getLineWithPrompt(name, STRING_SIZE, SELECT_ERROR);

        selectOrgFromList(orgPtr, headPtr, name);
    }
} // selectValidOrgFromList

int setUp(OrgNode **headPtr)
{
    // Create an organization to add to a node
    Organization org;

    // Grab user inputs
    getLineWithPrompt(org.name, STRING_SIZE, ORG_NAME_PROMPT);
    getLineWithPrompt(org.purpose, STRING_SIZE, ORG_PURPOSE_PROMPT);
    getLineWithPrompt(org.ownerFirstLastName, STRING_SIZE, 
                      FIRST_LAST_NAME_PROMPT);
    getPosDouble(&org.goalAmount, GOAL_PROMPT, GOAL_ERROR, MIN_GOAL);
    getEmail(org.ownerEmail, STRING_SIZE);
    getPassword(org.ownerPwd, STRING_SIZE);
    generateUrl(org.url, org.name);

    // Initialize count and sum variables
    org.numDonations = 0;
    org.donationSum = 0.0;
    org.numDonors = 0;
    org.feesSum = 0.0;
    
    // Generate the receipt's path
    generateReceiptPath(org.receiptPath, org.name);

    // Create the receipts file, if it already exists, wipe it
    FILE *receiptsFile = fopen(org.receiptPath, FILE_WRITE_MODE);
    fclose(receiptsFile);

    // Insert the org to the linked list
    insertOrgToList(headPtr, org);

    // Print out thank you message. Not a constant in case more variables in the
    // message are desired
    printf("Thank you %s. The url to raise funds for %s is %s.\n\n",
           org.ownerFirstLastName, org.name, org.url);

    // Figure out whether to add another organization with a flag
    int retFlag;
    if (getYesOrNo(NEW_ORG_PROMPT, NEW_ORG_ERROR)) {
        retFlag = SETUP_MODE_FLAG;
    } else {
        retFlag = DONATIONS_MODE_FLAG;
    }

    return retFlag;
} // setUp

int donate(OrgNode **headPtr, Organization **currOrgPtr, Donor *donor)
{
    puts(DONATION_SELECT_PROMPT);
    printListContents(headPtr);
    puts("");

    selectValidOrgFromList(currOrgPtr, headPtr);

    Organization *currOrg = *currOrgPtr;

    // Print out org info. Not constants in case more variables in the
    // printf statements are desired.
    puts(currOrg->url);
    puts("MAKE A DIFFERENCE BY YOUR DONATION");
    printf("Organization: %s\n", currOrg->name);
    printf("Purpose: %s\n", currOrg->purpose);
    printf("We currently have raised $%.2lf.\n", currOrg->donationSum);
    if (currOrg->donationSum >= currOrg->goalAmount) {
        puts("We have reached our goal but can still use the donations.");
    } else {
        printf("We are %2.2lf%% towards our goal of $%.2lf.\n",
               (currOrg->donationSum / currOrg->goalAmount) * 100,
               currOrg->goalAmount);
    }
    puts("");

    // Retrieve the user's donation
    double donation = 0;
    getDonation(&donation);

    int retFlag;

    // exit to reports mode
    if (donation == ADMIN_NUM) {
        retFlag = REPORT_MODE_FLAG;
    }
    // add donation
    else {
        // get donor info
        getLineWithPrompt(donor->firstLastName, STRING_SIZE, 
                          FIRST_LAST_NAME_PROMPT);
        getZip(donor->zip, STRING_SIZE);

        // track donations and fees
        double fee = donation * TRANSACTION_FEE;
        currOrg->feesSum += fee;

        double effectiveDonation = donation - fee;
        currOrg->donationSum += effectiveDonation;

        currOrg->numDonations++;

        // print donation thank you
        printf("Thank you for your donation. There is a %.1lf%% credit card" 
               "processing fee of $%.2lf. $%.2lf will be donated.\n",
                100 * TRANSACTION_FEE, fee, effectiveDonation);

        
        // Ask user for receipt
        if (getYesOrNo(RECEIPT_PROMPT, RECEIPT_ERROR)) {
            fPrintReceipt(stdout, currOrg, donation);

            FILE *receipts = fopen(currOrg->receiptPath, FILE_APPEND_MODE);
            fPrintReceipt(receipts, currOrg, donation);
            fclose(receipts);
        }

        retFlag = DONATIONS_MODE_FLAG;
    }

    puts("");

    return retFlag;
} // donate

int report(OrgNode **headPtr, Organization **currOrgPtr)
{
    int exitFlag;

    // get the org at org ptr
    Organization *currOrg = *currOrgPtr;

    // Determines if the email address is valid
    if (matchCredential(currOrg->ownerEmail, EMAIL_PROMPT, EMAIL_MATCH_ERROR)) {
        // dermines if the password is valid
        if (matchCredential(currOrg->ownerPwd, PASSWORD_PROMPT,
                PASSWORD_MATCH_ERROR)) {
            // open orgs file
            FILE *orgsFile = fopen(ORGS_PATH, FILE_WRITE_MODE);

            puts("");

            // iterate through the linked list
            OrgNode *currNodePtr = *headPtr;
            while (currNodePtr != NULL) {
                // prints summary to orgs file and stdout
                fPrintSummary(stdout, &(currNodePtr->org));
                fPrintSummary(orgsFile, &(currNodePtr->org));
                currNodePtr = currNodePtr->nextNodePtr;
            }

            fclose(orgsFile);

            exitFlag = END_PROGRAM_FLAG;
        } else {
            exitFlag = DONATIONS_MODE_FLAG;
        }
    } else {
        exitFlag = DONATIONS_MODE_FLAG;
    }

    return exitFlag;
} // report
