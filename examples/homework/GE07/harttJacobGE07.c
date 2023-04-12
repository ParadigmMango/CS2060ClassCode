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


//## Misc. constants
#define MIN_AGE 1
#define STRING_SIZE 80

//## getYesNo constants
const char YES[STRING_SIZE] = "y";
const char NO[STRING_SIZE] = "n";

//## Misc. messages
#define EMPTYING_LIST_NOTIFICATION "\nEmptying list..."
#define EMPTIED_LIST_NOTIFICATION "Done."
#define LINKED_LIST_EMPTY "There aren't any names in the list."
#define LINKED_LIST_HEADER "The names in alphabetical order:"

//## Prompt messages
#define ADD_PET_PROMPT "\nDo you want to add another pet? (y/n): "
#define AGE_PROMPT "Enter age: "
#define DEL_PET_PROMPT "\nDo you want to delete a pet from the list? (y/n): "
#define NAME_DEL_PROMPT "\nEnter pet's name to delete: "
#define NAME_GET_PROMPT "Enter name: "

//## Error messages
#define ADD_PET_ERROR "Please enter a (y)es or a (n)o: "
#define AGE_ERROR "Please enter a valid age: "
#define DEL_PET_ERROR "Please enter a (y)es or a (n)o: "
#define MEM_ERROR "Not enough memory for new nodes."
#define NAME_DEL_ERROR "Please enter a valid name: "
#define NAME_GET_ERROR "Please enter a valid name: "
#define NODE_DEL_ERROR_EMPTY "There aren't any nodes in the list!"


//! A struct that bundles the name and age of a pet together.
typedef struct pet {
    char name[STRING_SIZE];
    int age;
} Pet;

//! A node for a pet linked list.
typedef struct petNode {
    Pet pet;
    struct petNode *nextNodePtr;
} PetNode;


//## Misc. functions
//! Wrapper function which clears the input buffer
void clearBuffer(void);

//! Compares two strings in a caseless manner.
/*!
  \param str1 the string to compare against
  \param str2 the string to compare with
  \return the return value of strcmp
 */
int strCmpCaseless(const char *str1, const char *str2);

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


//## Node Functions 
//! Deletes a pet from a linked list using a name to match against
/*!
  \param headPtr the location of the head of the linked list
  \param name the name of the pet to remove
 */
void deletePet(PetNode **headPtr, const char *name);

//! Empties a list of all nodes and frees all memory allocated for it from the heap.
/*!
  \param headPtr the location of the head of the linked list
 */
void emptyList(PetNode **headPtr);

//! Inserts a pet into a linked list in alphabetical order of name.
/*!
  \param headPtr the location of the head of the linked list
  \param pet the pet to insert to the list
 */
void insertPet(PetNode **headPtr, Pet pet);

//! Print the contents of a pet linked list.
/*!
  \param headPtr the location of the head of the linked list
 */
void printContents(PetNode **headPtr);


int main(void)
{
    // initialize linked list and a temp pet variable
    PetNode *head = NULL;
    Pet newPet;

    // initialize the pet and insert it into the list
    getName(newPet.name, STRING_SIZE, NAME_GET_PROMPT, NAME_GET_ERROR);
    getAge(&newPet.age);
    insertPet(&head, newPet);

    // ask the user if they want to add another pet until they say no
    while (getYesOrNo(ADD_PET_PROMPT, ADD_PET_ERROR)) {
        // set the newPet with new values and add that to the list
        getName(newPet.name, STRING_SIZE, NAME_GET_PROMPT, NAME_GET_ERROR);
        getAge(&newPet.age);
        insertPet(&head, newPet);
    } // linked list building loop

    printContents(&head);

    // ask the user if they want to remove a pet until they say no
    while (getYesOrNo(DEL_PET_PROMPT, DEL_PET_ERROR)) {
        // get the name of the pet to remove and try to remove it from the list
        char nameToRemove[STRING_SIZE];
        getName(nameToRemove, STRING_SIZE, NAME_DEL_PROMPT, NAME_DEL_ERROR);
        deletePet(&head, nameToRemove);

        printContents(&head);
    } // node deletion loop

    printContents(&head);

    // empty the list
    puts(EMPTYING_LIST_NOTIFICATION);
    emptyList(&head);
    puts(EMPTIED_LIST_NOTIFICATION);

    printContents(&head);

    return 0;
} // main


void clearBuffer(void)
{
    while (getchar() != '\n');
} // clearBuffer

int strCmpCaseless(const char *str1, const char *str2)
{
    // create a lowercase version of each string
    char str1Lower[STRING_SIZE];
    toLower(str1, str1Lower);

    char str2Lower[STRING_SIZE];
    toLower(str2, str2Lower);

    // compare the lowercase strings
    return strcmp(str1Lower, str2Lower);
} // strCmpCaseless

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
    // prepare variables for validation
	char* end;
	errno = 0;

	long intTest = strtol(str, &end, 10);
    bool isValid;

    // Test all possible cases where input is invalid
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
        // set the input to the conversion if valid int
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

    // Print errors until a valid word that is also a valid int is found
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

void deletePet(PetNode **headPtr, const char *name)
{
    // test for the edge case where the list is already empty
    if (*headPtr == NULL) {
        puts(NODE_DEL_ERROR_EMPTY);
    } else {
        // initialize node pointer for iteration
        PetNode *currNodePtr = *headPtr;
        PetNode *prevNodePtr = NULL;

        // iterate until the end of the list is reach or the name is found
        while (currNodePtr != NULL && strCmpCaseless(currNodePtr->pet.name,
               name) != 0) {
            // move the node pointers forward
            prevNodePtr = currNodePtr;
            currNodePtr = currNodePtr->nextNodePtr;
        }

        if (prevNodePtr == NULL) {
            // handles special case where the pet called name is found at the 
            // beginning of the linked list
            *headPtr = (*headPtr)->nextNodePtr;
        
            free(currNodePtr);
            currNodePtr = NULL;        
        } else if (currNodePtr != NULL) {
            // handles most cases(when the pet called name is found after the 
            // first node)
            prevNodePtr->nextNodePtr = currNodePtr->nextNodePtr;

            free(currNodePtr);
            currNodePtr = NULL;
        } else {
            // edge case where the list does not contain a pet called name
            printf("%s is not in the list of pets!\n", name);
        }
    }
} // delete pet

void emptyList(PetNode **headPtr)
{
    // set up node pointers for iteration
    PetNode *currNodePtr = *headPtr;
    PetNode *nextNodePtr = NULL;

    // free the current node until there are no nodes left
    while (currNodePtr != NULL) {
        nextNodePtr = currNodePtr->nextNodePtr;
        free(currNodePtr);
        currNodePtr = nextNodePtr;
    }

    // set the head pointer to NULL
    *headPtr = NULL;
} // emptyList

void insertPet(PetNode **headPtr, Pet pet)
{
    // attempt to allocate memory
    PetNode *newNodePtr = malloc(sizeof(PetNode));

    // test for the edge case in which the os cannot give enough memory for the
    // node
    if (newNodePtr == NULL) {
        puts(MEM_ERROR);
    } else {
        // initialize newNode
        newNodePtr->nextNodePtr = NULL;
        newNodePtr->pet = pet;

        // initialize node pointers for iteration
        PetNode *prevNodePtr = NULL;
        PetNode *currNodePtr = *headPtr;

        // iterate forward until the end of the list or the new pet's name
        // is lexicologically after the current pet's name
        while (currNodePtr != NULL &&
               strCmpCaseless(pet.name, currNodePtr->pet.name) > 0) {
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

void printContents(PetNode **headPtr)
{
    puts("");

    // handle if a linked list is empty
    if (*headPtr == NULL) {
        puts(LINKED_LIST_EMPTY);
    } else {
        // print the header for the contents of the linked list
        puts(LINKED_LIST_HEADER);

        // use a node pointer to iterate throught the linked list until the end
        PetNode *currNode = *headPtr;
        while (currNode != NULL) {
            // print the current pet's data
            Pet currPet = currNode->pet;
            printf("%s is %d years old.\n", currPet.name, currPet.age);

            currNode = currNode->nextNodePtr;
        }
    }
} // printContents
