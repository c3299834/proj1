#include <stdio.h>
#include <math.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

/*
 * Function prototypes for the below function definitions, which are to decrypt and encrypt text using a rotation cipher or substitution cipher.
 * The string 'str'(user message input) and variable 'newletter'(keeps track of ascii value) are required for each function. The strings 'key' 
 * and 'alphabet' are required for the substitution ciphers.
 */
int DecryptRotationKey(char str[1024], int newletter);
//int DecryptRotationNoKey(char str[1024], int newletter);
int EncryptRotationKey(char str[1024], int newletter);
int EncryptSubKey(char str[1024], char key[26], int newletter, char alphabet[26]);
int DecryptSubKey(char str[1024], char key[26], int newletter, char alphabet[26]);

int main() {
    char str[1024]; //String where the message will be stored, only need one as the string will be re-initialised everytime the program is run
    /*
     * The variable 'newletter' contains the changed ascii value for the encryption and decryption of the rotation cipher. The string 'str' and
     * the variable 'newletter' are contained within a for loop so the value of 'newletter' does not need to be remembered.
     * 'option' contains the user selected value which is used within the switch statement to decide what function to call.
     * 'varDefault' keeps a track of whether the default option in the switch statement has been called, 1 for true, 0 for false.
     */
    int newletter = 0, option = 1, varDefault = 0;
    //char key[1024]; 
    //Declaration of the alphabet, which is to be used in the encryption and decryption of a substitution cipher
    char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //Hard-code declaration of the key to be used in the encryption and decryption of a substitution cipher (For testing only, temporary)
    char key[26] = "MKLIJRTNADFHZXWVUYQBCEGOPS";

    /*
     * Following is the user-friendly menu, which asks the user to choose the function the program is to perform. The section contains a 
     * sequence of printf(); statements that help the user easily identify the options.
     */
    printf("This is a message encryptor and decryptor.\n");
    printf("What would you like to do?\nPlease select a number option from the following.\n");
    printf("1. Encryption of a rotation cipher with a key.\n");
    printf("2. Decryption of a rotation cipher with a key.\n");
    printf("3. Encryption of a substitution cipher (Letter substitution key required).\n");
    printf("4. Decryption of a substitution cipher (Letter substitution key required).\n");
    //printf("5. Decryption of a rotation cipher without a key.\n");
    //printf("6. Decryption of a substitution cipher without a key.\n");
    /*
     * Since there is an issue related to the buffering of the eclipse terminal emulator the fflush(stdout); command is used to clear the
     * output buffer and move the buffered data to the console. This concept is beyond ENGG1003.
     * In essence, it pushes the previous printf(); statements to the console and removes any spaces or data that the scanf(); may pick up 
     * (which is the reason as to why the scanf(); appears to be skipped). This allows the user to provide input data to the program.
     */
    fflush(stdout);
    scanf("%d", &option); //Takes and stores the value provided by user into the variable option.
    
    
    do {
        varDefault = 0;
        switch(option) {
            case 1: EncryptRotationKey(str, newletter); break;
            case 2: DecryptRotationKey(str, newletter); break;
            case 3: EncryptSubKey(str, key, newletter, alphabet); break;
            case 4: DecryptSubKey(str, key, newletter, alphabet); break;
            //case 5:
            //case 6:
            default: printf("Error, choose a valid option.\n");
                     fflush(stdout);
                     scanf("%d", &option);
                     varDefault = 1;
                     continue;
        }
    } while(varDefault == 1);

    //DecryptRotationKey(str, newletter);*
    //DecryptRotationNoKey(str, newletter);
    //EncryptRotationKey(str, newletter);*
    //EncryptSubKey(str, key, newletter, alphabet, alphabetcap);*
    //DecryptSubKey(str, key, newletter, alphabet, alphabetcap);*
    
    
    
    return 0;
}

int DecryptRotationKey(char str[1024], int newletter) {
    int rotation, i;
    
    printf("What is the message?\n"); //Asks what the message is
    fflush(stdout);
    scanf(" %[^\n]s", str); //Reads a statement which contains a space
    
    printf("What is the rotation?\n"); //Asks what the rotation is
    fflush(stdout);
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
            newletter = 123 - newletter - 32;
        }
        else if(str[i] == 32) {
            newletter = 32;
        }
        else if(str[i] <= 122 && str[i] >= 97){
            newletter = str[i] - rotation - 32; //Calculates new letter after rotation has been taken into account
        }
        else if(str[i] >= 65 && str[i] <= 90) {
            newletter = str[i] - rotation;
        }
        else {
            continue;
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
    int rotation = 1, i = 0;
    
    printf("What is the message?\n"); //Asks what the message is
    fflush(stdout);
    scanf(" %[^\n]s", str); //Reads a statement which contains a space
    
    printf("What is the rotation?\n"); //Asks what the rotation is
    fflush(stdout);
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
            newletter = 96 + newletter - 32;
        }
        else if(str[i] == 32) {
            newletter = 32;
        }
        else if(str[i] <= 122 && str[i] >= 97){
            newletter = str[i] + rotation - 32; //Calculates new letter after rotation has been taken into account
        }
        else if(str[i] >= 65 && str[i] <= 90) {
            newletter = str[i] + rotation;
        }
        else {
            continue;
        }
        
        str[i] = newletter;
        
    }
    printf("%s\n", str); //Prints the encrypted phrase with the specified rotation
    return 0;
}

int EncryptSubKey(char str[1024], char key[26], int newletter, char alphabet[26]) {
    int i, j, a;
    
    printf("What is the message?\n"); //Asks what the message is
    fflush(stdout);
    scanf(" %[^\n]s", str);
    //scanf("%[^\n]s", key);
    for(i = 0; str[i] != 0; i++) {
        if(str[i] <= 122 && str[i] >= 97) {
            for(j = 0; alphabet[j] != 0; j++) {
                if(str[i] == alphabet[j] + 32) {
                    a = key[j];
                }
            
            }
            str[i] = a;
        }
        else if(str[i] <= 90 && str[i] >= 65) {
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

int DecryptSubKey(char str[1024], char key[26], int newletter, char alphabet[26]) {
    int i, j, a;
    
    printf("What is the message?\n"); //Asks what the message is
    fflush(stdout);
    scanf(" %[^\n]s", str);
    
    //scanf("%[^\n]s", key);
    for(i = 0; str[i] != 0; i++) {
        if(str[i] <= 122 && str[i] >= 97) {
            for(j = 0; key[j] != 0; j++) {
                if(str[i] == key[j] + 32) {
                    a = alphabet[j];
                }
            
            }
            str[i] = a;
        }
        else if(str[i] <= 90 && str[i] >= 65) {
            for(j = 0; key[j] != 0; j++) {
                if(str[i] == key[j]) {
                    a = alphabet[j];
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

