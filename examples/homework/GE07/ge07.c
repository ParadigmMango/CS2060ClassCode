//! Pet Linked List
/*!
  \file ge07.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \version 0.1
  \date 04-12-2023
 */

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MIN_AGE 1
#define STRING_SIZE 80

const char YES[STRING_SIZE] = "y";
const char NO[STRING_SIZE] = "n";

//## Prompt messages
#define AGE_PROMPT "Enter age: "

//## Error messages
#define AGE_ERROR "Please enter a valid age: "


typedef struct pet {
    char name[STRING_SIZE];
    int age;
} Pet;

typedef struct petNode {
    Pet pet;
    struct petNode *nextNodePtr;
} PetNode;

//## Misc. functions
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

//## YesNo Functions
//! Determine if a string is a yes or no
/*!
  \param yesNo the string to be validated
  \param yesNoSize the size of the string to be validated
  \return whether or not the string is a yes or no
 */
bool isYesOrNo(const char *yesNo, size_t yesNoSize);

//! Get a yes or no from the user
/*!
  \param prompt the prompt to provide the user with for retrieving a yes or no
  \param error the error which will again prompt for a yes or no
  \return true if yes, false if no
 */
bool getYesOrNo(const char *prompt, const char *error);


//## Integer input toolchain
//! Converts a string to an int and returns if it succeeded.
/*!
  \param str the original string
  \param num the location of the integer to write into
  \return Whether or not the conversion succeeded
 */
bool strToInt(const char *str, int *num);

//! Gets a valid integer input from the user.
/*!
  \param num the location of the integer to write into
  \param prompt the original user prompt
  \param error the error and follow-up prompt
  \param min the minimum acceptable number
 */
void getInt(int *num, const char *prompt, const char *error, int min);


//## Name functions
//! Determine if a string is a name
/*!
  \param email the string to be validated
  \param emailSize the size of the string to be validated
  \return whether or not the string is a name
 */
bool isName(const char *name, size_t nameSize);

//! Gets a valid name from the user
/*!
  \param name the string to write the name into
  \param nameSize the size of the name string
  \param prompt the intial user prompt
  \param error the error prompt which agains asks the user for input
 */
void getName(char *name, size_t nameSize, const char *prompt, const char *error);


//## Age function
//! Gets an age number from the user and puts it into age
/*!
  \param age the location of the age integer to write into
 */
void getAge(int *age);


int main(void)
{
    int lel;

    getAge(&lel);

    return 0;
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

bool strToInt(const char* str, int *num)
{
	char* end;
	errno = 0;

	long intTest = strtol(str, &end, 10);
    bool isValid;

	if (end == str) {
		isValid = false;
	} else if ('\0' != *end) {
		isValid = false;
	} else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {
		isValid = false;
	} else if (intTest > INT_MAX) {
		isValid = false;
	} else if (intTest < INT_MIN) {
		isValid = false;
	} else {
		*num = (int) intTest;

        isValid = true;
	}

    return isValid;
}

void getInt(int *num, const char *prompt, const char *error, int min)
{
    printf("%s", prompt);

    // Set up input variables
    char word[STRING_SIZE];
    bool getWordSuccess = getWord(word, STRING_SIZE);
    int intTest;

    // Print errors until a valid word that also passes validate() is found
    while (!getWordSuccess || !strToInt(word, &intTest) || intTest < min) {
        printf("%s", error);

        getWordSuccess = getWord(word, STRING_SIZE);
    }

    *num = intTest;
} // getDouble

bool isName(const char *name, size_t nameSize)
{
    return true;
} // isName

void getName(char *name, size_t nameSize, const char *prompt, const char *error)
{
    getValidatedWord(name, nameSize, &isName, prompt, error);
} // getName

void getAge(int *age)
{
    getInt(age, AGE_PROMPT, AGE_ERROR, MIN_AGE);
} // getAge
