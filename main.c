#include <stdio.h>
#include <math.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

/*
 * Function prototypes for the below function definitions, which are to decrypt and encrypt text using a rotation cipher or substitution cipher.
 * The string 'str'(user message input) and variable 'newletter'(keeps track of ascii value) are required for each function. The strings 'key' 
 * and 'alphabet' are required for the substitution ciphers.
 * Choosing between functions is detailed above the user-friendly menu
 */
int DecryptRotationKey(char str[1024], int newletter, FILE *textfile2);
int EncryptRotationKey(char str[1024], int newletter, FILE *textfile2);
int EncryptSubKey(char str[1024], char key[26], int newletter, char alphabet[26], FILE *textfile2);
int DecryptSubKey(char str[1024], char key[26], int newletter, char alphabet[26], FILE *textfile2);

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
    char key[26];
    
    /*
     * Declaration of 3 files
     * keyfile - The file "key" stores the alphabet key for the substitution ciphers
     * textfile - The file "textin" contains the text to be read by the program
     * textfile2 - The file "text2" contains the output text written after the program has run
     */
    FILE *keyfile; //Defines the pointer keyfile as a file
    keyfile = fopen("key", "r"); //Opens the file key and stores it in the variable keyfile(File 'key' holds the alphabet substitutions)
        if(keyfile == NULL) { //Checks that there are no issues with the file
            printf("Error opening file!\n"); //If there are issues, the user is given a warning message
        }
        else {
            fscanf(keyfile, "%[^\n]s", key); //Otherwise, the file is scanned and it's contents stored in the string 'key'
        }
        fclose(keyfile); //File is closed as it no longer needs to be accessed
    
    FILE *textfile; //Defines the pointer textfile as a file
    textfile = fopen("textin", "r"); //Opens the file textin and stores it in the variable textfile(File 'text' holds the phrase to be encrypted or decrypted)
        if(textfile == NULL) { //Checks that there are no issues with the file
            printf("Error opening file!\n"); //If there are issues, the user is given a warning message
        }
        else {
            fscanf(textfile, "%[^\n]s", str); //Otherwise, the file is scanned and it's contents stored in the string 'str'
        }
        fclose(textfile); //Closes textfile since it is no longer required
        
    FILE *textfile2; //Defines the pointer textfile2 as a file
    textfile2 = fopen("text2", "w"); //Opens the file text2 and stores it in the variable textfile2(Encrypted or decrypted data is written to this file)

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
    /*
     * Since there is an issue related to the buffering of the eclipse terminal emulator the fflush(stdout); command is used to clear the
     * output buffer and move the buffered data to the console. This concept is beyond ENGG1003.
     * In essence, it pushes the previous printf(); statements to the console and removes any spaces or data that the scanf(); may pick up 
     * (which is the reason as to why the scanf(); appears to be skipped). This allows the user to provide input data to the program.
     */
    fflush(stdout);
    scanf("%d", &option); //Takes and stores the value provided by user into the variable option.
    
    /*
     * The following 'do... while' loop is for if the default option in the switch statement is triggered. Everytime default within the switch
     * statement is called the loop is repeated until the user inputs a valid choice.
     */
    do {
        varDefault = 0; //Resets 'varDefault' to 0 so that the loop is not called if either case 1 - 4 is selected.
        switch(option) { //Checks the value contained in the variable 'option'
            /*
             * Case 1 - 4 calls the necessary function in accordance with the user-friendly menu above, followed by break; to move out 
             * of the switch statement.
             */
            case 1: EncryptRotationKey(str, newletter, textfile2); break;
            case 2: DecryptRotationKey(str, newletter, textfile2); break;
            case 3: EncryptSubKey(str, key, newletter, alphabet, textfile2); break;
            case 4: DecryptSubKey(str, key, newletter, alphabet, textfile2); break;
            default: printf("Error, choose a valid option.\n"); //Tells the user to select a valid option
                     fflush(stdout); //Flushes stdout to allow for user input
                     scanf("%d", &option); //Takes and stores the value provided by user into the variable option
                     varDefault = 1; //Sets 'varDefault' to 1(true), telling the while loop to repeat
                     continue; //Jumps to start of loop, checks condition first
        }
    } while(varDefault == 1); //Checks whether the loop is to be repeated, only true if the default option was selected in the switch statement

    return 0;
}

/*
 * DecryptRotationKey is the second option provided to the user, it decrypts text using a given key.
 * Each value in the string(which is a letter) is decreased by the specified rotation to decrypt the given message.
 * Input is provided by the string 'str[1024]'(input message). Output is written to stdout and to 'text2'. Return value is 0 as the program is
 * terminated at the end of the function.
 */
int DecryptRotationKey(char str[1024], int newletter, FILE *textfile2) {
    /*
     * Variable 'rotation' stores the rotation that the user selects
     * Variable 'i' is used within the for loop as a counter for the string 'str'
     */
    int rotation, i;
    char no; //Defines the char 'no', this stores the user's reply as to whether they would like to use file I/O or not
    
    printf("Would you like to read from the text file? (Y/N)\n"); //Asks the user if they would like to use the information in the text file
                                                                  //or not 
    fflush(stdout); //Flushes stdout to allow for user input
    scanf(" %c", &no); //Reads the letter input from the user, only the first letter is stored in no.
    
    if(no == 'N' || no == 'n') { //Tests whether the user said no. If they said no, ask for their input.
        printf("What is the message?\n"); //Asks for the user to input the message
        fflush(stdout); //Flushes stdout to allow for user input
        scanf(" %[^\n]s", str); //Reads data input and stores in the string 'str', [^\n] enables scanf(); to read and store spaces
    }
    
    printf("What is the rotation?\n"); //Asks the user for the rotation
    fflush(stdout); //Flushes stdout to allow for user input
    scanf("%d", &rotation); //Reads and stores the rotation within the variable 'rotation'
    
    
    /*
     * Variable 'i' is initiated to contain the value 0, and increments by 1 each time the loop is repeated.
     * Each string ends with the value 0, while the ASCII value of str[i] does not equal 0, the loop will continue to repeat.
     */
    for(i = 0; str[i] != 0; i++) {
        /*
         * Checks whether the letter is a capital letter, and if the subtraction of the rotation from the ASCII value remains
         * a capital letter. If str[i] - rotation is no longer a capital letter, the program needs to cycle back to the value of 'Z'
         * (which has ASCII value 90) and subtract the difference between 65 and 'str[i] - rotation' from 'Z' to complete the rotation.
         */
        if(str[i] - rotation < 65 && str[i] >= 65 && str[i] <= 90) {
           newletter = str[i] - rotation; //Calculates the rotation
           newletter = 65 - newletter; //Calculates how much the rotation dropped below 'A'
           newletter = 91 - newletter; //Calculates rotation beginning back at 'Z'
        }
        /*
         * The next if statement repeats the process as above with the exception that it is checking for lowercase letters.
         * Checks whether the letter is a lowercase letter, and if the subtraction of the rotation from the ASCII value remains
         * a lowercase letter. If str[i] - rotation is no longer a lowercase letter, the program needs to cycle back to the value of 'z'
         * (which has ASCII value 122) and subtract the difference between 97 and 'str[i] - rotation' from 'z' to complete the rotation.
         */
        else if(str[i] - rotation > 90 && str[i] - rotation < 97 && str[i] >= 97 && str[i] <= 122) {
            newletter = str[i] - rotation; //Calculates the rotation
            newletter = 97 - newletter; //Calculates how much the rotation dropped below 'a'
            newletter = 123 - newletter - 32; //Calculates rotation beginning at 'z', subtraction of 32 is necessary to convert lowercase to uppercase
        }
        else if(str[i] <= 122 && str[i] >= 97){ //Checks if the letter is lowercase(ASCII value between 97 and 122)
            newletter = str[i] - rotation - 32; //Calculates new ASCII value by subtracting the rotation and the number 32 to convert the letter
                                                //into a capital
        }
        else if(str[i] >= 65 && str[i] <= 90) { //Tests whether the letter is a capital(ASCII value between 65 and 90)
            newletter = str[i] - rotation; //Calculates new ASCII value by subtracting the rotation, storing the new value in 'newletter'
        }
        else { //Anything that is not a letter(ASCII values between 65 and 90, and 97 and 122) is skipped
            continue;
        }
        
        str[i] = newletter; //The ASCII value of str[i] takes and stores the value of 'newletter'
        
    }
    printf("%s\n", str); //Prints the entire decrypted phrase with the specified rotation
    fprintf(textfile2, "%s\n", str); //Prints the entire encrypted phrase to the file text2
    fclose(textfile2); //Closes the text2 file
    return 0; //Terminates the program as it has completed its objective
}

/*
 * EncryptRotationKey is the first option provided to the user, it encrypts text using a given key.
 * Each value in the string(which is a letter) is increased by the specified rotation to encrypt the given message.
 * Input is provided by the string 'str[1024]'(input message). Output is written to stdout and to 'text2'. Return value is 0 as the program is
 * terminated at the end of the function.
 */
int EncryptRotationKey(char str[1024], int newletter, FILE *textfile2) {
    /*
     * Variable 'rotation' stores the rotation that the user selects
     * Variable 'i' is used within the for loop as a counter for the string 'str'
     */
    int rotation, i;
    char no; //Defines the char 'no', this stores the user's reply as to whether they would like to use file I/O or not
    
    printf("Would you like to read from the text file? (Y/N)\n"); //Asks the user if they would like to use the information in the text file
                                                                  //or not 
    fflush(stdout); //Flushes stdout to allow for user input
    scanf(" %c", &no); //Reads the letter input from the user, only the first letter is stored in no
    
    if(no == 'N' || no == 'n') { //Tests whether the user said no. If they said no, ask for their input.
        printf("What is the message?\n"); //Asks for the user to input the message
        fflush(stdout); //Flushes stdout to allow for user input
        scanf(" %[^\n]s", str); //Reads data input and stores in the string 'str', [^\n] enables scanf(); to read and store spaces
    }
    
    printf("What is the rotation?\n"); //Asks the user for the rotation
    fflush(stdout); //Flushes stdout to allow for user input
    scanf("%d", &rotation); //Reads and stores the rotation within the variable 'rotation'
    
    /*
     * Variable 'i' is initiated to contain the value 0, and increments by 1 each time the loop is repeated.
     * Each string ends with the value 0, while the ASCII value of str[i] does not equal 0, the loop will continue to repeat.
     */
    for(i = 0; str[i] != 0; i++) {
        /*
         * Checks whether the letter is a capital letter, and if the addition of the rotation from the ASCII value remains
         * a capital letter. If str[i] + rotation is no longer a capital letter, the program needs to cycle back to the value of 'A'
         * (which has ASCII value 65) and add the difference between 90 and 'str[i] + rotation' to 'A' to complete the rotation.
         */
        if(str[i] + rotation > 90 && str[i] >= 65 && str[i] <= 90) {
           newletter = str[i] + rotation; //Calculates the rotation
           newletter = newletter - 90; //Calculates how much the rotation went above 'Z'
           newletter = 64 + newletter; //Calculates rotation beginning back at 'A'
        }
        /*
         * The next if statement repeats the process as above with the exception that it is checking for lowercase letters.
         * Checks whether the letter is a lowercase letter, and if the addition of the rotation from the ASCII value remains
         * a lowercase letter. If str[i] + rotation is no longer a lowercase letter, the program needs to cycle back to the value of 'a'
         * (which has ASCII value 97) and add the difference between 122 and 'str[i] + rotation' to 'a' to complete the rotation.
         */
        else if(str[i] + rotation > 122 && str[i] >= 97 && str[i] <= 122) {
            newletter = str[i] + rotation; //Calculates the rotation
            newletter = newletter - 122; //Calculates how much the rotation went above 'z'
            newletter = 96 + newletter - 32; //Calculates rotation beginning at 'a', subtraction of 32 is necessary to convert lowercase to uppercase
        }
        else if(str[i] <= 122 && str[i] >= 97){ //Checks if the letter is lowercase(ASCII value between 97 and 122)
            newletter = str[i] + rotation - 32; //Calculates new ASCII value by adding the rotation and subtracting the number 32 to convert the letter
                                                //into a capital
        }
        else if(str[i] >= 65 && str[i] <= 90) { //Tests whether the letter is a capital(ASCII value between 65 and 90)
            newletter = str[i] + rotation; //Calculates new ASCII value by adding the rotation, storing the new value in 'newletter'
        }
        else { //Anything that is not a letter(ASCII values between 65 and 90, and 97 and 122) is skipped
            continue;
        }
        
        str[i] = newletter; //The ASCII value of str[i] takes and stores the value of 'newletter'
        
    }
    printf("%s\n", str); //Prints the entire encrypted phrase with the specified rotation
    fprintf(textfile2, "%s\n", str); //Prints the entire encrypted phrase to the file text2
    fclose(textfile2); //Closes the text2 file
    return 0; //Terminates the program as it has completed its objective
}

/*
 * EncryptSubKey is the third option provided to the user, it encrypts text using a given alphabet key.
 * The function sorts through each value of a given string and compares it to the alphabet. When the alphabet and string values match,
 * the string value is replaced with the key value that corresponds to the alphabet.
 * Input is provided by the strings 'str[1024]'(input message), key[26] and alphabet[26]. Output is written to stdout and to 'text2'. Return value is 0 as the program is
 * terminated at the end of the function.
 */
int EncryptSubKey(char str[1024], char key[26], int newletter, char alphabet[26], FILE *textfile2) {
    /*
     * Variable 'i' is used within the for loop as a counter for the string 'str'
     * Variable 'j' is used as a counter for the alphabet string that is used within the inner for loop
     */
    int i, j;
    char no; //Defines the char 'no', this stores the user's reply as to whether they would like to use file I/O or not
    
    printf("Would you like to read from the text file? (Y/N)\n"); //Asks the user if they would like to use the information in the text file
                                                                  //or not 
    fflush(stdout); //Flushes stdout to allow for user input
    scanf(" %c", &no); //Reads the letter input from the user, only the first letter is stored in no
    
    if(no == 'N' || no == 'n') { //Tests whether the user said no. If they said no, ask for their input.
        printf("What is the message?\n"); //Asks for the user to input the message
        fflush(stdout); //Flushes stdout to allow for user input
        scanf(" %[^\n]s", str); //Reads data input and stores in the string 'str', [^\n] enables scanf(); to read and store spaces
    }

    //scanf("%[^\n]s", key);
    /*
     * Variable 'i' is initiated to contain the value 0, and increments by 1 each time the loop is repeated.
     * Each string ends with the value 0, while the ASCII value of str[i] does not equal 0, the loop will continue to repeat.
     */
    for(i = 0; str[i] != 0; i++) { //For loop scans through all values contained within the given string
        if(str[i] <= 122 && str[i] >= 97) { //Checks whether the letter at position 'i' is a lowercase letter
            for(j = 0; alphabet[j] != 0; j++) { //For loop scans through all values contained within the string 'alphabet'
                if(str[i] == alphabet[j] + 32) { //Each value in the string 'alphabet'(+ 32 since str[i] is lowercase) is compared 
                                                 //with the value 'str[i]', if they are equal,
                    newletter = key[j];          //'newletter' takes the value of the corresponding letter in the key, 
                }                                // i.e. alphabet[16], then newletter = key[16];
            
            }
            str[i] = newletter; //The ASCII value of str[i] takes and stores the value of 'newletter' (Value of i changes for each loop repeat)
        }
        else if(str[i] <= 90 && str[i] >= 65) { //Checks whether the letter at position 'i' is an uppercase letter
            for(j = 0; alphabet[j] != 0; j++) { //For loop scans through all values contained within the string 'alphabet'
                if(str[i] == alphabet[j]) { //Each value in the string 'alphabet' is compared with the value str[i]
                    newletter = key[j]; //'newletter' takes the value of the corresponding letter(of the string 'alphabet') in the key
                }
            }
            str[i] = newletter; //The ASCII value of str[i] takes and stores the value of 'newletter' (Value of i changes for each loop repeat)
        }
        else { //Anything that is not a letter(ASCII values between 65 and 90, and 97 and 122) is skipped
            continue;
        }

    }
    printf("%s\n", str); //Prints the entire encrypted phrase
    fprintf(textfile2, "%s\n", str); //Prints the entire encrypted phrase to the file text2
    fclose(textfile2); //Closes the text2 file
    return 0; //Terminates the program as it has completed its objective
}

/*
 * DecryptSubKey is the fourth option provided to the user, it decrypts text using a given alphabet key.
 * The function sorts through each value of a given string and compares it to the key. When the key and string values match,
 * the string value is replaced with the alphabet value that corresponds to the key.
 * Input is provided by the strings 'str[1024]'(input message), key[26] and alphabet[26]. Output is written to stdout and to 'text2'. Return value is 0 as the program is
 * terminated at the end of the function.
 */
int DecryptSubKey(char str[1024], char key[26], int newletter, char alphabet[26], FILE *textfile2) {
    /*
     * Variable 'i' is used within the for loop as a counter for the string 'str'
     * Variable 'j' is used as a counter for the alphabet string that is used within the inner for loop
     */
    int i, j;
    char no; //Defines the char 'no', this stores the user's reply as to whether they would like to use file I/O or not
    
    printf("Would you like to read from the text file? (Y/N)\n"); //Asks the user if they would like to use the information in the text file
                                                                  //or not 
    fflush(stdout); //Flushes stdout to allow for user input
    scanf(" %c", &no); //Reads the letter input from the user, only the first letter is stored in no
    
    if(no == 'N' || no == 'n') { //Tests whether the user said no. If they said no, ask for their input.
        printf("What is the message?\n"); //Asks for the user to input the message
        fflush(stdout); //Flushes stdout to allow for user input
        scanf(" %[^\n]s", str); //Reads data input and stores in the string 'str', [^\n] enables scanf(); to read and store spaces
    }
    
    /*
     * Variable 'i' is initiated to contain the value 0, and increments by 1 each time the loop is repeated.
     * Each string ends with the value 0, while the ASCII value of str[i] does not equal 0, the loop will continue to repeat.
     */
    for(i = 0; str[i] != 0; i++) { //For loop scans through all values contained within the given string
        if(str[i] <= 122 && str[i] >= 97) { //Checks whether the letter at position 'i' is a lowercase letter
            for(j = 0; key[j] != 0; j++) { //For loop scans through all values contained within the string 'key'
                if(str[i] == key[j] + 32) {  //Each value in the string 'key'(+ 32 since str[i] is lowercase) is compared
                                             //with the value 'str[i]', if they are equal,
                    newletter = alphabet[j]; //'newletter' takes the value of the corresponding letter in the key,
                }                            // i.e. key[16], then newletter = alphabet[16];
            
            }
            str[i] = newletter; //The ASCII value of str[i] takes and stores the value of 'newletter' (Value of i changes for each loop repeat)
        }
        else if(str[i] <= 90 && str[i] >= 65) { //Checks whether the letter at position 'i' is an uppercase letter
            for(j = 0; key[j] != 0; j++) { //For loop scans through all values contained within the string 'key'
                if(str[i] == key[j]) { //Each value in the string 'key' is compared with the value str[i]
                    newletter = alphabet[j]; //'newletter' takes the value of the corresponding letter(of the string 'key') in the alphabet
                }
            }
            str[i] = newletter; //The ASCII value of str[i] takes and stores the value of 'newletter' (Value of i changes for each loop repeat)
        }
        else { //Anything that is not a letter(ASCII values between 65 and 90, and 97 and 122) is skipped
            continue;
        }

    }
    printf("%s\n", str); //Prints the entire decrypted phrase
    fprintf(textfile2, "%s\n", str); //Prints the entire decrypted phrase to the file text2
    fclose(textfile2); //Closes the text2 file
    return 0; //Terminates the program as it has completed its objective
}

