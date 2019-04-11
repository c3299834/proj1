#include <stdio.h>
#include <math.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

//int DecryptRotationKey(char str[1024], int newletter);*
//int DecryptRotationNoKey(char str[1024], int newletter);
//int EncryptRotationKey(char str[1024], int newletter);*
int EncryptSubKey(char str[1024], char key[26], int newletter, char alphabet[26]);

int main() {
    char str[1024]; //String where the message will be stored
    int newletter = 0;
    //char key[1024];
    char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
    char key[26] = "mklijrtnadfhzxwvuyqbcegops";
    
    //DecryptRotationKey(str, newletter);*
    //DecryptRotationNoKey(str, newletter);
    //EncryptRotationKey(str, newletter);*
    EncryptSubKey(str, key, newletter, alphabet);
    
    
    
    return 0;
}

int DecryptRotationKey(char str[1024], int newletter) {
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
        if(str[i] - rotation < 65 && str[i] >= 65 && str[i] <= 90) {
           newletter = str[i] - rotation;
           newletter = 65 - newletter;
           newletter = 91 - newletter;
        }
        else if(str[i] - rotation > 90 && str[i] - rotation < 97 && str[i] >= 97 && str[i] <= 122) {
            newletter = str[i] - rotation;
            newletter = 97 - newletter;
            newletter = 123 - newletter;
        }
        else if(str[i] == 32) {
            newletter = 32;
        }
        else {
            newletter = str[i] - rotation; //Calculates new letter after rotation has been taken into account
        }
        
        str[i] = newletter;
        
    }
    printf("%s\n", str); //Prints the encrypted phrase with the specified rotation
    return 0;
}

/*int DecryptRotationNoKey(char str[1024], int newletter) {
    int rotation, i, a = 0;
    
    //printf("What is the message?\n"); //Asks what the message is
    scanf("%[^\n]s", str); //Reads a statement which contains a space
    
    //printf("What is the rotation?\n"); //Asks what the rotation is
    //scanf("%d", &rotation); //Reads the rotation
    
    //printf("%d\n", rotation); //Tests whether the rotation has been read correctly 
    //printf("%s\n", str); //Tests whether it has read the statement correctly
    while(a == 0) {
        for(i = 0; str[i] != 0; i++) {
            //printf("%d ", str[i]); //Prints ASCII numbers of the string
            //printf("%d", i);
            if(str[i] - rotation < 65 && str[i] >= 65 && str[i] <= 90) {
                newletter = str[i] - rotation;
                newletter = 65 - newletter;
                newletter = 91 - newletter;
            }
            else if(str[i] - rotation > 90 && str[i] - rotation < 97 && str[i] >= 97 && str[i] <= 122) {
                newletter = str[i] - rotation;
                newletter = 97 - newletter;
                newletter = 123 - newletter;
            }
            else if(str[i] == 32) {
                newletter = 32;
            }
            else {
                newletter = str[i] - rotation; //Calculates new letter after rotation has been taken into account
            }
        
            str[i] = newletter;
        
        }
        dictionary("parameters");
        if(dictionary() == 1) {
            
        }
    }

    printf("%s\n", str); //Prints the encrypted phrase with the specified rotation
    return 0;
}*/

int EncryptRotationKey(char str[1024], int newletter) {
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
        if(str[i] + rotation > 90 && str[i] >= 65 && str[i] <= 90) {
           newletter = str[i] + rotation;
           newletter = newletter - 90;
           newletter = 64 + newletter;
        }
        else if(str[i] + rotation > 122 && str[i] >= 97 && str[i] <= 122) {
            newletter = str[i] + rotation;
            newletter = newletter - 122;
            newletter = 96 + newletter;
        }
        else if(str[i] == 32) {
            newletter = 32;
        }
        else {
            newletter = str[i] + rotation; //Calculates new letter after rotation has been taken into account
        }
        
        str[i] = newletter;
        
    }
    printf("%s\n", str); //Prints the encrypted phrase with the specified rotation
    return 0;
}

int EncryptSubKey(char str[1024], char key[26], int newletter, char alphabet[26]) {
    int i, j, a;
    
    scanf("%[^\n]s", str);
    //printf("ok");
    //scanf("%[^\n]s", key);
    //printf("what");
    for(i = 0; str[i] != 0; i++) {
        if(str[i] <= 122 && str[i] >= 97) {
            for(j = 0; alphabet[j] != 0; j++) {
                if(str[i] == alphabet[j]) {
                    a = key[j];
                }
            
            }
            str[i] = a;
        }
        else {
            continue;
        }

    }
    printf("%s\n", str);
    return 0;
}