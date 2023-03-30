#include <stdio.h>
#include <time.h>

int main(void)
{
    char str[19];

    time_t time_var = time(NULL);

    strftime(str, sizeof(str), "%D - %I:%M%p", localtime(&time_var));

    puts(str);
} // main