
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define LENGTH 26

bool exploreValidateInt(const char* buff, int *num);
bool validateInt(char* buff, int* const validInt);
void printLimits();

int main(void)
{
	char inputStr[LENGTH]; // create char arintray
	size_t inputLength = 0;

	printLimits();

	for (unsigned int counter = 1; counter < 6; counter++)
	{
		puts("\nEnter an integer");
		fgets(inputStr, LENGTH, stdin);

		inputLength = strnlen(inputStr, LENGTH);

		if (inputLength > 0 && inputStr[inputLength - 1] == '\n') {
			inputStr[inputLength - 1] = '\0';
		}

        int num_main;

		bool isValid = exploreValidateInt(inputStr, &num_main);
        
        // printf("\nisValid: %d\nnum_main: %d\n", isValid, num_main);
	}

}



void printLimits()
{
	printf("The number of bits in a byte %d\n", CHAR_BIT);

	printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);
	printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);
	printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);

	printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);
	printf("The maximum value of SHORT INT = %d\n", SHRT_MAX);

	printf("The minimum value of INT = %d\n", INT_MIN);
	printf("The maximum value of INT = %d\n", INT_MAX);

	printf("The minimum value of CHAR = %d\n", CHAR_MIN);
	printf("The maximum value of CHAR = %d\n", CHAR_MAX);

	printf("The minimum value of LONG = %ld\n", LONG_MIN);
	printf("The maximum value of LONG = %ld\n", LONG_MAX);
}


bool exploreValidateInt(const char* buff, int *num)
{
    // declares an end pointer to pass to strol() and allows for the detection
    // of not only non-decimal inputs, but also if extra characters are at the
    // end of the input.
	char* end;
    // sets the internal errno variable to zero, ensuring that in case strol
    // succeeds, errno remains 0 and not whatever it contained before.
	errno = 0;
    // an integer variable which will store the integer cast of inttest if the 
    // input is valid.
	int validInt = 0;
    // 1. Declares intTest, a long.
    // 2. Sets intTest to the long equivalent of the chars in buff if the input
    //    is a long, sets end to the end of buffer if it succeeds, sets end to 
    //    buff if it doesn't succeed, and will interpret buff as base 10 numbers
	long intTest = strtol(buff, &end, 10);
    // return value variable since early escapes are forbidden in this class
    bool isValid = false;

    // handles inputs where the input is not a decimal number by using the end
    // pointer and comparing it with buff
	if (end == buff) {
		fprintf(stderr, "%s: not a decimal number\n", buff);
	}
    // handles inputs where the decimal is not cleanly seperated at the end:
    // this handles float inputs and random characters at the end.
	else if ('\0' != *end) {
		fprintf(stderr, "%s: extra characters at end of input: %s\n", buff, end);
	}
    // handles inputs larger than the long max or min by testing against LONG_MIN,
    // LONG_MAX, and the ERANGE error macro.
	else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {
		fprintf(stderr, "%s out of range of type long\n", buff);
	}
    // handles all inputs larger than the integer maximum by simple comparison
	else if (intTest > INT_MAX) {
		fprintf(stderr, "%ld greater than INT_MAX\n", intTest);
	}
    // handles all inputs smaller than the integer minimum by simple comparison
	else if (intTest < INT_MIN) {
		fprintf(stderr, "%ld less than INT_MIN\n", intTest);
	}
    // handles all valid inputs
	else {
        // casts the long input to an int variable
		validInt = (int)intTest;
        // sets the input number to validInt
        *num = validInt;
        // confirms a valid int was read
        isValid = true;
		printf("%d is integer value ", validInt);
	}

    // returns whether or not the int is valid.
    return isValid;
}
