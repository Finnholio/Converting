#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_SIZE 256

int toDecimal(int startingBase, string input, int lengthOfInput);
int* decimalToOther(int endingBase, int input);
char* conversion(int startingBase, int endingBase, string input, int lengthOfInput);
int getValue(char input);
string toTrueChar(int array[]);

int main()
{
    printf("Welcome to the Base Converter\n\n");

    int base1 = get_int("Please input the base of the input (2-35): "); //get the inputs
    int base2 = get_int("Please input the desired output base (2-35): ");
    string input = get_string("Please input the number to be converted: ");

    for (int i = 0; i < strlen(input); i++) //test to make sure the user did input them wrong
    {
        if (getValue(input[i]) >= base1)
        {
            printf("ERROR: THE INPUT HAS NUMBERS LARGER THAN POSSIBLE\n");
            exit(0);
        }

    }


    printf("The new number is: %s\n", conversion(base1, base2, input, strlen(input))); //print out the answer
}

char* conversion(int startingBase, int endingBase, string input, int lengthOfInput)
{
    int decimal = toDecimal(startingBase, input, lengthOfInput); //converts input to decimal
    int* arrayOutput = decimalToOther(endingBase, decimal); //converts the input to the desired ending base
    char* stringOutput = toTrueChar(arrayOutput); //converts in input into the correct format

    return stringOutput;
}

int* decimalToOther(int endingBase, int input)
{
    int temp = input;
    int stringLength = 0;

    while (temp > 0) //get the total number of characters in the output
    {
        temp /= endingBase;
        stringLength++;
    }

    int* output;
    output = malloc(MAX_SIZE * sizeof(int));

    temp = input;
    int index = stringLength - 1; //start index at the back side because the division method goes from last number to first

    if (stringLength + 1 > MAX_SIZE)
    {
        printf("ERROR: NUMBER TO LARGE TO BE CONVERTED\n");
        exit(0);
    }

    while (temp > 0)
    {
        output[index + 1] = temp % endingBase; //use index + 1 as the index because the output[0] is = to the size of the array

        temp /= endingBase;
        index--;
    }

    output[0] = stringLength; //storing the size of the array in the first value of the array

    return output;
}

string toTrueChar(int array[])
{
    char* output;
    output = malloc(MAX_SIZE * sizeof(int));

    for (int i = 1; i < array[0] + 1; i++)
    {
        int newInt = array[i]; //converting number to character

        if (newInt > -1 && newInt < 10)
        {
            newInt += 48;
        }
        else if (newInt > 9 && newInt < 36)
        {
            newInt += 55;
        }
        else
        {
            printf("ERROR : CONVERSIONS DONE INCORRECTLY, INVALID CHARACTER\n");
            exit(0);
        }

        char newChar = (char)newInt;
        output[i - 1] = newChar; //must use i - 1 as index because i starts at 1
    }

    return output;
}

int toDecimal(int startingBase, string input, int lengthOfInput)
{
    int output = 0;

    //get each decimal place in the input

    for (int i = 0; i < lengthOfInput; i++)
    {
        int decimalPlace = lengthOfInput - i - 1; //gets the decimal place
        int temp = getValue(input[i]); //gets the number

        output += (temp * (int)(pow(startingBase, decimalPlace) + 0.5)); //formula for converting a number to base 10 from any base
    }

    return output;
}



int getValue(char input)
{
    int output = toupper(input); //converts everything to uppercase for the purposes of converting

    if (!(output > 47 && output < 58)) //converts from ascii to integer
    {
        if (output > 64 && output < 91)
        {
            output -= 7;
        }
        else //if its not a number or a letter returns an error
        {
            printf("ERROR : INVALID CHARACTER\n");
            exit(0);
        }
    }
    output -= 48;

    return output;
}
