#include <stdio.h>
#include <math.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

int encryptRotation(char str[1024], int newletter);

int main() {
    char str[1024]; //String where the message will be stored
    int newletter = 0;
    
    encryptRotation(str, newletter);
    
    
    return 0;
}

int encryptRotation(char str[1024], int newletter) {
    int rotation, i;
    
    //printf("What is the message?\n"); //Asks what the message is
    scanf("%[^\n]s", str); //Reads a statement which contains a space
    
    //printf("What is the rotation?\n"); //Asks what the rotation is
    scanf("%d", &rotation); //Reads the rotation
    
    //printf("%d\n", rotation); //Tests whether the rotation has been read correctly 
    //printf("%s\n", str); //Tests whether it has read the statement correctly
    
    for(i = 0; str[i] != 0; i++) {
        //printf("%d ", str[i]); //Prints ASCII numbers of the string
        //printf("%d", i);
        newletter = str[i] - rotation; //Calculates new letter after rotation has been taken into account
        //printf("%c", newletter); //Prints the new letter ASCII number
        printf("%c", newletter); //Prints the encrypted phrase with the specified rotation
    }
    return 0;
}