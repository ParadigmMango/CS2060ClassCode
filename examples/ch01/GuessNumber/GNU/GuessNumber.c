// Randomly generate numbers between 1 and 1000 for user to guess.
// Lack of whitespace here detracts from the overall presentation of the code
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Why are these here? These are redundant, and should be in a header file.
void guessGame(void); // function prototype
int isCorrect(int, int); // function prototype

// Void arguments in C are best practice to indicate no arguments used
int main(void)
{
   // srand( time( 0 ) ); // seed random number generator. Without this, the program generate the same answers when run.
   // Below are two lines with inconsistent whitespace
    //update with your name
    puts("Hello Jacob");
   guessGame();
   // Below is random, empty whitespace

// Comments at the end of large functions is best practice
} // end main

// The comments at the beginning of each non-main method help explain the purpose of each method and is best practice.
// guessGame generates numbers between 1 and 1000
// and checks user's guess
void guessGame(void)
{
   // Comments after each variable help explain their purpose.
   int answer; // randomly generated number
   int guess; // user's guess
   int response; // 1 or 2 response to continue game

   // Do while loop ensures at least one round of the game is run.
   // loop until user types 2 to quit game
   do {
      // generate random number between 1 and 1000
      // 1 is shift, 1000 is scaling factor
      answer = 1 + rand() % 1000;

      // prompt for guess
      puts("I have a number between 1 and 1000.\n" 
           "Can you guess my number?\n" 
           "Please type your first guess.");
      printf("%s", "? ");
      scanf("%d", &guess);

      // loop until correct number
      while (!isCorrect(guess, answer)) 
         scanf("%d", &guess);

      // prompt for another game
      puts("\nExcellent! You guessed the number!\n"
         "Would you like to play again?");
      printf("%s", "Please type ( 1=yes, 2=no )? ");
      scanf("%d", &response);

      puts("");
   } while (response == 1);
} // end function guessGame

// isCorrect returns true if g equals a
// if g does not equal a, displays hint
int isCorrect(int g, int a)
{
   // guess is correct
   if (g == a)
      return 1;

   // guess is incorrect; display hint
   if (g < a)
      printf( "%s", "Too low. Try again.\n? " );
   else
      printf( "%s", "Too high. Try again.\n? " );

   return 0;
} // end function isCorrect


// Copyright notices are generally place at the top of a file.
/**************************************************************************
 * (C) Copyright 1992-2012 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
