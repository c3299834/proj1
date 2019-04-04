#include <stdio.h>
#include <math.h>
#include <strings.h>

char setValue(char *str, int TOTAL);

int main() {
    char str[] = "abcdefghijklmnopqrstuvwxyz"; //Defines the alphabet string
    int /*i = 0,*/ TOTAL = 26; //Defining a counting variable and the string size as TOTAL (includes \0)
    
    setValue(str, TOTAL);
    
    /*for(i = 0; i < TOTAL; i++) {
        printf("%d: %c\n", i, str[i] );
    }*/

    

    return 0;
}

// Function which changes each string segment and gives it a value
char setValue(char *str, int TOTAL) {
    int u = 0; //Define a counter
    //printf("Hello\n"); //Testing whether code has passed this point
    
    for(u = 0; u < TOTAL; u++) {
        str[u] = u;
        printf("%d", str[u] );
        //printf("%d: Hi\n", u); //Testing whether code has passed this point
    }
    return 0;
}