//!  CS2060.002 Homework Assignment #4
/*!
  \file hw04.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \brief A program that calculates the final grades and class average of a class.
  \version 1.0
  \date 02-23-2023
 */

#include <stdbool.h>
#include <stdio.h>

//! A string indicating the the number associated with each grade category.
#define CATEGORIES "1. Learning Activity 2. Homework 3. Project 4. Midterm 5. Final"
//! The number of grade categories for the class.
#define GRADE_CATEGORIES 5
//! The maximum grade possible in a grade category.
#define MAX_GRADE 105.0
//! The minimum grade possible in a grade category.
#define MIN_GRADE 0.0
//! The total number of students in the class.
#define STUDENTS 4

//! The minimum grade required to earn an A in the class.
#define A_MIN_GRADE 90.0
//! The minimum grade required to earn a B in the class.
#define B_MIN_GRADE 80.0
//! The minimum grade required to earn a C in the class.
#define C_MIN_GRADE 70.0
//! The minimum grade required to earn a D in the class.
#define D_MIN_GRADE 60.0

//! An array containing all of the weights for the grade categories in order.
const double GRADE_CATEGORY_WEIGHTS[] = {0.1, 0.3, 0.3, 0.15, 0.15};


//! Calculates the average value of an array.
/*!
  \param arr the array whose values will be used
  \param size the size of the array
  \return The average of the array
 */
double calcAverage(const double arr[], size_t size);

//! Calculates the final grade of a student for the class.
/*!
  \param studentGrades the input 2D array of class grades
  \param studentNum the students number / row in the 2D array
  \param numGradeCategories the number of grade categories stored in the array
  \return The final grade of a student
 */
double calcFinalGrade(double studentGrades[][GRADE_CATEGORIES],
                      unsigned int studentNum, unsigned int numGradeCategories);

//! Prompts the user to fill the student grades array with valid grades.
/*!
  \pre numStudents is the number of rows in studentGrades.
  \param studentGrades 2D array of doubles which will store the input grades
  \param numStudents the number of rows in studentGrades
  \param numGradeCategories the number of columns in studentGrades
 */
void enterGrades(double studentGrades[][GRADE_CATEGORIES], size_t numStudents, 
                 size_t numGradeCategories);

//! Gets a valid grade.
/*!
  Repeatedly prompts the user for a valid input until one is entered, which the
  function then returns.

  \param studentNum the number of the student who's grade is being retreive
  \param gradeCategoryNum the category number of the grade being retreived
  \return A valid grade value 
 */
double getGrade(unsigned int studentNum, unsigned int gradeCategoryNum);

//! Determines whether the input can be considered a valid grade.
/*!
  \param grade the numerical value to determine whether or not is a valid grade
  \return Whether or not the input grade is valid
 */
bool isGradeValid(double grade);

//! Returns the corresponding grade letter for a valid grade in the class.
/*!
  \pre The input grade is valid.
  \param grade the numerical value for a single grade category of a student
  \return The corresponding grade letter for the input grade
 */
char letterGrade(double grade);


//! The main function.
/*!
  \return The exit value
 */
int main(void)
{
    puts("This program will calculate the grades for these categories:");
    puts(CATEGORIES);
    puts("");

    puts("The category weights are:");
    for (int gradeCategoryNum = 0; gradeCategoryNum < GRADE_CATEGORIES;
                                   gradeCategoryNum++) {
        printf("Category %d weight is %.2lf\n", gradeCategoryNum + 1,
               GRADE_CATEGORY_WEIGHTS[gradeCategoryNum]);
    }
    puts("");

    double studentGrades[STUDENTS][GRADE_CATEGORIES];

    enterGrades(studentGrades, STUDENTS, GRADE_CATEGORIES);

    puts("Grades entered for each student");
    for (int student = 0; student < STUDENTS; student++) {
        printf("Student %d:", student + 1);

        for (int gradeCategoryNum = 0; gradeCategoryNum < GRADE_CATEGORIES;
                                       gradeCategoryNum++) {
            printf("  %3.1lf", studentGrades[student][gradeCategoryNum]);
        }

        puts("");
    }
    puts("");

    puts("Final grades for students, respectively:"); 
    for (int studentNum = 0; studentNum < STUDENTS; studentNum++) {
        double finalGrade = calcFinalGrade(studentGrades, studentNum,
                                           GRADE_CATEGORIES);

        printf("Student %d: %3.1lf %c\n", studentNum + 1, finalGrade,
               letterGrade(finalGrade));
    }

    puts("Hello world!");
}

double calcAverage(const double arr[], size_t size)
{
    double sum = 0.0;

    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    return sum / size;
}

double calcFinalGrade(double studentGrades[][GRADE_CATEGORIES],
                      unsigned int studentNum, unsigned int numGradeCategories)
{
    double sum = 0.0;

    for (int gradeCategoryNum = 0; gradeCategoryNum < numGradeCategories;
                                   gradeCategoryNum++) {
        sum += studentGrades[studentNum][gradeCategoryNum] *
               GRADE_CATEGORY_WEIGHTS[gradeCategoryNum];
    }
    
    return sum;
}

void enterGrades(double studentGrades[][GRADE_CATEGORIES], size_t numStudents, 
                 size_t numGradeCategories)
{
    for (int studentNum = 0; studentNum < numStudents; studentNum++) {
        for (int gradeCategoryNum = 0; gradeCategoryNum < numGradeCategories;
                                       gradeCategoryNum++) {
            studentGrades[studentNum][gradeCategoryNum] = getGrade(studentNum,
                                                            gradeCategoryNum);
        }

        puts("");
    }
}

double getGrade(unsigned int studentNum, unsigned int gradeCategoryNum)
{
    int retVal;
    double grade;

    bool isInputValid;

    do {
        printf("Enter a valid number for student %d's category %d grade: ",
               studentNum + 1, gradeCategoryNum + 1);
        
        retVal = scanf("%lf", &grade);

        while (getchar() != '\n');

        isInputValid = (retVal >= 1) && isGradeValid(grade);
    } while (!isInputValid);

    return grade;
}

bool isGradeValid(double grade)
{
    return (grade >= MIN_GRADE) && (grade <= MAX_GRADE);
}

char letterGrade(double grade)
{
    char gradeLetter;

    if (grade >= A_MIN_GRADE) {
        gradeLetter = 'A';
    } else if (grade >= B_MIN_GRADE) {
        gradeLetter = 'B';
    } else if (grade >= C_MIN_GRADE) {
        gradeLetter = 'C';
    } else if (grade >= D_MIN_GRADE) {
        gradeLetter = 'D';
    } else {
        gradeLetter = 'F';
    }

    return gradeLetter;
}
