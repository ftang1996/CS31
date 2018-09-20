//
//  main.cpp
//  Project 4
//
//  Created by Fiona Tang on 2/23/17.
//  Copyright © 2017 Fiona Tang. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int enumerate(const string a[], int n, string target);
int locate(const string a[], int n, string target);
bool locateSequence(const string a[], int n, string target, int& begin, int& end);
int locationOfMin(const string a[], int n);
int moveToEnd(string a[], int n, int pos);
int moveToBeginning(string a[], int n, int pos);
int locateDifference(const string a1[], int n1, const string a2[], int n2);
int eliminateDups(string a[], int n);
bool subsequence(const string a1[], int n1, const string a2[], int n2);
int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max);
int divide(string a[], int n, string divider);

bool isNondecreasing(const string a[], int n);  // checks for arrays of nondecreasing order

int main() {
    string a[6] = {"g", "b", "b", "a", "v", "a"};
    string target = "z";
    int b = divide(a, 6, target);
    cout << b << endl;
    for (int i = 0; i < 6; i++)
        cout << a[i] << " ";
}

int enumerate(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    
    int count = 0;
    for (int i = 0; i < n; i++)
        if (a[i] == target)
            count++;
    return count;
}

int locate(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    
    for (int i = 0; i < n; i++)
        if (a[i] == target)
            return i;   // return position of first location
    return -1;      // if no matches return -1
}

bool locateSequence(const string a[], int n, string target, int& begin, int& end)
{
    if (n < 0)
        return false;
    
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == target && count == 0)
        {
            begin = i;
            end = i - 1;    // while loop will always add at least 1 to end
            while (a[i] == target && i < n)  // continue adding to end until element doesnt equal target
            {
                end++;
                i++;
            }
            return true;    // end function when while loop ends
        }
    }
    return false;
}

int locationOfMin(const string a[], int n)
{
    if (n < 0)
        return -1;
    
    int minPos = 0;
    for (int pos = 1; pos < n; pos++)
        if (a[pos] < a[minPos])     // check if element less than current min
            minPos = pos;       // update min if so
    return minPos;
}

int moveToEnd(string a[], int n, int pos)
{
    if (n < 0 || pos < 0 || pos >= n)
        return -1;
    
    string temp = a[pos];   // temporarily store element of interest
    for (int i = pos; i < n; i++)
    {
        if (i == n-1)       // store element of interest at end
            a[i] = temp;
        else        // move all elements after to the left
            a[i] = a[i+1];
    }
    return pos;
}

int moveToBeginning(string a[], int n, int pos)
{
    if (n < 0 || pos < 0 || pos >= n)
        return -1;
    
    string temp = a[pos];
    for (int i = pos; i >= 0; i--)
    {
        if (i == 0)     // store element of interest in beginning
            a[i] = temp;
        else
            a[i] = a[i-1];      // move all elements before to the right
    }
    return pos;
}

int locateDifference(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0)
        return -1;
    
    int i = 0;
    while (i < n1 && i < n2)    // while within interested regions
    {
        if (a1[i] == a2[i]) // if match, move to next element
            i++;
        else    // end while loop when elements no longer matching
            return i;
    }
    if (n1 < n2)
        return n1;
    else
        return n2;
}

int eliminateDups(string a[], int n)
{
    if (n < 0)
        return -1;
    
    for (int i = 0; i < n; i++)
    {
        while (a[i+1] == a[i])
        {
            if (i+1 >= n)   // prevent going outside region of interest
                break;
            moveToEnd(a, n, i+1);   // move dup to end
            n--;
        }
    }
    return n;
}

bool subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0)
        return false;
    
    int matchCount = 0;
    int pos1 = 0;
    int pos2 = 0;
    
    while (pos1 < n1 && pos2 < n2)
    {
        if (a1[pos1] == a2[pos2])     // check for matching elements
        {
            matchCount++;   // matches counter
            pos2++;    // only move to next element of a2 after a match
        }
        pos1++;
    }
    if (matchCount == n2)   // match counter equals number of interested elements in a2
        return true;
    return false;
}

int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max)
{
    if (n1 < 0 || n2 < 0 || n1 + n2 > max)
        return -1;
    
    if (!isNondecreasing(a1, n1) || !isNondecreasing(a2, n2))
        return -1;
    
    int pos1 = 0;
    int pos2 = 0;
    int i = 0;
    while(i < n1 + n2)  // don't iterate outside of total elements of a1 and a2
    {
        if (pos1 < n1 && pos2 < n2)
        {
            if (a2[pos2] >= a1[pos1])
            // iterate until a1 element is greater than a2
            {
                result[i] = a1[pos1];
                pos1++;
                i++;
            }
            else if (a1[pos1] > a2[pos2])
            // iterate until a2 element is greater than or equal to a1
            {
                result[i] = a2[pos2];
                pos2++;
                i++;
            }
        }
        else if (pos1 < n1 && pos2 >= n2)    // if done adding a2, but still elements of a1 left
        {
            result[i] = a1[pos1];
            i++;
            pos1++;
        }
        else if (pos2 < n2 && pos1 >= n1)    // if done adding a1, but still elements of a2 left
        {
            result[i] = a2[pos2];
            i++;
            pos2++;
        }
    }
    return n1 + n2;
}

int divide(string a[], int n, string divider)
{
    if (n < 0)
        return -1;
    
    int stop = n;
    
    for (int i = 0; i < stop; i++)
    {
        if (a[i] > divider) // move all elements > divider to end
        {
            moveToEnd(a, n, i);
          //  stop--; // update where loop stops
        }
    }
    
    for (int j = 0; j < n; j++)
    {
        if (a[j] < divider) // move all elements < divider to beginning
        {
            moveToBeginning(a, n, j);
        }
    }
    
    int pos = 0;
    while (a[pos] < divider && pos < n)    // return pos of first element not < divider
        pos++;
    return pos;
}

bool isNondecreasing(const string a[], int n)
{
    if (n < 0)
        return false;
    
    for (int i = 0; i < n-1; i++)
        if (a[i] > a[i+1])   // return false for nondecreasing
            return false;
    return true;
}
