//  Project 5
//
//  Created by Fiona Tang on 5/21/17.
//  Copyright © 2017 Fiona Tang. All rights reserved.

#include <iostream>
#include <cstring>
using namespace std;

const int MAX_MESSAGE = 60;
const int MAX_LEN = 80;

bool decrypt(const char ciphertext[], const char crib[]);
bool findCipherKey(const char crib[], const char messages[][MAX_LEN], int numMessages, char cipherKey[]);
int parseCipher(const char ciphertext[], char messages[][MAX_LEN]);
int parse(const char s[], char sParse[][MAX_LEN]);
bool correctCrib(const char messageParsed[][MAX_LEN], const char cribParsed[][MAX_LEN], int first, int last, int numCribParsed, char cipherKey[]);
int inKey(char cipherKey[], char c);
void makeUpperCase(char s[]);

int main()
{

}

// Deciphers message
bool decrypt(const char ciphertext[], const char crib[])
{
    if (ciphertext[0] == '\0')
        return false;
    
    char messages[MAX_MESSAGE][MAX_LEN] = {};
    int numMessages = parseCipher(ciphertext, messages);    // parse cipher into individual messages

    char cribParsed[MAX_MESSAGE][MAX_LEN] = {};     // return array with only alpha char from crib
    int numCribParsed = parse(crib, cribParsed);
    char cribCat[500] = {};
    for (int cribPos = 0; cribPos < numCribParsed; cribPos++)
        strcat(cribCat, cribParsed[cribPos]);

    char cipherKey[MAX_LEN] = {};
    
    if (findCipherKey(crib, messages, numMessages, cipherKey))  // check crib exists in message
    {
        makeUpperCase(cipherKey);
        for (int nMess = 0; nMess < numMessages; nMess++)
        {
            for (int nStr = 0; messages[nMess][nStr] != '\0'; nStr++)   // decipher text
            {
                int n = inKey(cipherKey, messages[nMess][nStr]);    // if character is in crib
                if (n != -1)                                        // print
                    cout << cribCat[n];
                else                                                // otherwise leave unchanged
                    cout << messages[nMess][nStr];
            }
            cout << endl;
        }
        return true;
    }
    
    return false;   // return false if crib not found in message
}

// Locates crib in cipher and creates a cipher key for decrypting
bool findCipherKey(const char crib[], const char messages[][MAX_LEN], int numMessages, char cipherKey[])
{
    char cribParsed[MAX_MESSAGE][MAX_LEN] = {};
    int numCribParsed = parse(crib, cribParsed);
    
    for (int i = 0; i < numMessages; i++)     // iterate through number of messages
    {
        char messagesParsed[MAX_MESSAGE][MAX_LEN] = {};
        int numMessParsed = parse(messages[i], messagesParsed); // parse message into words w/only alpha characters
        
        for (int j = 0; j < numMessParsed; j++)     // iterate through number of strings in each message
        {
            int correctLen = 0;
            int k = j;
            int l = 0;
            
            // check that consecutive words in message is same length as words in crib
            while (strlen(messagesParsed[k]) == strlen(cribParsed[l]) && l < numCribParsed)
            {
                correctLen++;
                k++;
                l++;
            }
            
            if (correctLen == numCribParsed)    // possible crib match found
            {
                int first = k - numCribParsed;  // identify position of crib in message
                int last = k - 1;
                
                // check that it correctly matches crib
                if(correctCrib(messagesParsed, cribParsed, first, last, numCribParsed, cipherKey))
                    return true;
            }
        }
    }
    return false;
}

// Parses cipher into seperate messages
int parseCipher(const char ciphertext[], char messages[][MAX_LEN])
{
    int n = 0;
    int messPos = 0;
    int i = 0;
    while (ciphertext[i] != '\0')
    {
        int strPos = 0;
        while (ciphertext[i] != '\n' && ciphertext[i] != '\0')
        {
            messages[messPos][strPos] = ciphertext [i];
            strPos++;
            i++;
        }
        messages[messPos][strPos] = '\0';
        messPos++;
        i++;
        n++;
    }
    return n;
}

// Parses strings into words of only alpha charactes
int parse(const char s[], char sParse[][MAX_LEN])
{
    int strNum = 0;
    int i = 0;
    while (i < strlen(s))
    {
        int j = 0;
        while (isalpha(s[i]))
        {
            sParse[strNum][j] = s[i];
            i++;
            j++;
        }
        if (isalpha(s[i-1]))
            strNum++;
        i++;
    }
    return strNum;
}

// Checks that crib discovered in cipher text meets correct guidelines
bool correctCrib(const char messageParsed[][MAX_LEN], const char cribParsed[][MAX_LEN], int first, int last, int numCribParsed, char cipherKey[])
{
    char cribCat[500] = {};
    char testKey[500] = {};
    for (int Pos = first; Pos <= last; Pos++)   // compile testkey into an array of letters
        strcat(testKey, messageParsed[Pos]);
    
    for (int cribPos = 0; cribPos < numCribParsed; cribPos++)   // compile crib into array of letters
        strcat(cribCat, cribParsed[cribPos]);
    
    for (int i = 0; i < strlen(cribCat); i++)
    {
        for (int j = i + 1; j < strlen(cribCat); j++)
        {
            if (toupper(cribCat[i]) == toupper(cribCat[j]))   // check that translation from crib by key is consistent
                if (toupper(testKey[i]) != toupper(testKey[j]))
                    return false;
            if (toupper(testKey[i]) == toupper(testKey[j]))
                if (toupper(cribCat[i]) != toupper(cribCat[j]))
                    return false;

        }
    }
    strcpy(cipherKey, testKey);
    return true;
}

// Searches for character in message in cipherkey and returns position if there
int inKey(char cipherKey[], char c)
{
    for (int pos = 0; cipherKey[pos] != '\0'; pos++)
        if (toupper(c) == cipherKey[pos])
            return pos;
    return -1;
}

// Converts C String to upper case
void makeUpperCase(char s[])
{
    for (int i = 0; s[i] != '\0'; i++)
        s[i] = toupper(s[i]);
}




