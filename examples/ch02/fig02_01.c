// Fig. 2.1: fig02_01.c
// A first program in C 
#include <stdio.h>

// function main begins program execution 
int main( void )
{
   int length;
   int width;
   int area;

   int readCode = 0;

   puts("Enter the length");
   readCode = scanf("%d", &length);
   puts("");

   // Test if the user entered valid data
   if (readCode == 1) {
      puts("Enter the width");
      readCode = scanf("%d", &width);
      puts("");

      // Test if the user entered valid data
      if(readCode == 1) {
         area = length * width;

         printf("Length: %d width: %d and area is %d\n", length, width, area);

         double lengthOverWidth = (double) length / width;  // Unused but asked for?

         double sidesAverage = (length + width) / 2.0;
         printf("Average of sides: %.1f\n", sidesAverage);
      } else {
         puts("Error: Please enter one integer value.");
      }
   } else {
      puts("Error: Please enter one integer value.");
   }

   return 0;
} // end function main 


/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
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
 *************************************************************************/
