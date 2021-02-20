//QUESTION 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *my_strcat( const char * const str1, const char * const str2);

int main()
{
    printf ("%s", my_strcat("Faizan", " Rasool" )); //calls function to execute the code
    return 0;
}
char *my_strcat(const char *const str1, const char *const str2)
{
    int len1 = strlen(str1); //length of str 1
    int len2 = strlen(str2); //length of str 2
    int len3 = len1 + len2 + 1; //plusone is for null character

    char *new_word;
    new_word = (char *) malloc(len3*sizeof(char)); //mallac function call
    new_word[len3-1] = '\0';
    int counter = 0;

    for(counter = 0; counter < strlen(str1); counter++)
    {
        new_word[counter] = str1[counter]; //appends str1 vakues into new_word
    }
    for(counter; counter<(len3-1);counter++)
    {
        new_word[counter] = str2[counter-len1]; //appends str2 values into new word
    }
    return new_word;
}


