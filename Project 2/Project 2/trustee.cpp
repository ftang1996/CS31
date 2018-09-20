//
//  main.cpp
//  Project 2
//
//  Created by Fiona Tang on 4/17/17.
//  Copyright © 2017 Fiona Tang. All rights reserved.
//

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main()
{
    string assetName, category;
    double assetValue;
    
    cout << "Asset Name: ";
    getline(cin, assetName);
    if (assetName == "")    // check that asset name is not an empty string
    {
        cout <<"---\nYou must enter an asset name." << endl;
        return 1;
    }
    

    cout << "Value (in thousands): ";
    cin >> assetValue;
    if (assetValue < 0)     // check that asset value is nonnegative
    {
        cout << "---\nThe asset value must be nonnegative." << endl;
        return 1;
    }
    
    cout << "Category: ";
    cin.ignore(10000, '\n');
    getline(cin, category);
    if (category == "")     // check that category is not an empty string
    {
        cout <<"---\nYou must enter an asset category." << endl;
        return 1;
    }
    
    double const LOW_FEE_RATE = 0.013;  // declare rates as constant so they can't be changed
    double const MID_FEE_RATE1 = 0.002;
    double const MID_FEE_RATE2 = 0.01;
    double const HIGH_FEE_RATE = 0.009;
    double trusteeDouble;
    
    if (assetValue <= 1000)     // calculate trustee fee based on asset value
        trusteeDouble = assetValue*1000*LOW_FEE_RATE;
    else if (assetValue <= 10000 && (category == "royalty" || category == "mutual fund"))
        trusteeDouble = 1000*(1000*LOW_FEE_RATE + (assetValue-1000)*MID_FEE_RATE1);
    else if (assetValue <= 10000)
        trusteeDouble = 1000*(1000*LOW_FEE_RATE + (assetValue-1000)*MID_FEE_RATE2);
    else if (assetValue > 10000 && (category == "royalty" || category == "mutual fund"))
        trusteeDouble = 1000*(1000*LOW_FEE_RATE + 9000*MID_FEE_RATE1 + (assetValue-10000)*HIGH_FEE_RATE);
    else
        trusteeDouble = 1000*(1000*LOW_FEE_RATE + 9000*MID_FEE_RATE2 + (assetValue-10000)*HIGH_FEE_RATE);

    
        
    int trusteeInt, trusteeFee;
    trusteeInt = floor(trusteeDouble);      // round to nearest integer
    if (trusteeDouble - trusteeInt < 0.5)
        trusteeFee = floor(trusteeDouble);
    else
        trusteeFee = ceil(trusteeDouble);
    
    
    cout << "---\nThe trustee fee for " << assetName << " is $" << trusteeFee << "." << endl;   // output trustee fee
    
    
    return 0;
}
