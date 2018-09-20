//
//  lines.cpp
//  picture


#include "graphlib.h"
#include <iostream>
#include <cctype>
#include <cassert>

using namespace std;

const int HORIZ = 0;
const int VERT = 1;

const int BG = 0;
const int FG = 1;

int executeCommands(string commandString, char& plotChar, int& mode, int& badPos);
void clearCommand(int& pos, int& X, int& Y, char& plotChar, int& mode);
int plotCommand(string command, int dir, int& pos, int& X, int& Y, char& plotChar, int& mode, int& badPos);
int modeCommand(string command, int& pos, char& plotChar, int& mode, int& badPos);

bool plotLine(int r, int c, int dir, int distance, char plotChar, int fgbg);
bool checkBounds(int r, int c, int dir, int distance);

int main()
{
    clearGrid();
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = executeCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
            case 0:
                draw();
                break;
            case 1:
                cout << "Syntax error at position " << position+1 << endl;
                break;
            case 2:
                cout << "Cannot execute command at position " << position+1 << endl;
                break;
            default:
                // It should be impossible to get here.
                cerr << "executeCommands returned " << status << "!" << endl;
        }
    }
}

int executeCommands(string commandString, char& plotChar, int& mode, int& badPos)
{
    int pos = 0;
    int currentX = 1;
    int currentY = 1;
    int dir;
    
    while (pos != commandString.size())
    {
        if (tolower(commandString[pos]) == 'c')
        {
            clearCommand(pos, currentX, currentY, plotChar, mode);
            continue;   // skip rest of body of while loop
        }
        else if (tolower(commandString[pos]) == 'h' || tolower(commandString[pos]) == 'v')
        {
            if (tolower(commandString[pos]) == 'h')
                dir = HORIZ;
            else
                dir = VERT;
            
            int check1 = plotCommand(commandString, dir, pos, currentX, currentY, plotChar, mode, badPos);
            if (check1 == 1) // syntax error
                return 1;
            else if (check1 == 2)    // command out of bounds
                return 2;
            continue;
        }
        else if (tolower(commandString[pos]) == 'b' || tolower(commandString[pos]) == 'f')
        {
            int check2 = modeCommand(commandString, pos, plotChar, mode, badPos);
            if (check2 == 1)    // syntax error
                return 1;
            continue;
        }
        else
        {
            badPos = pos;
            return 1;
        }
    }
    
    return 0;
}

// function to execute clear command
void clearCommand(int& pos, int& X, int& Y, char& plotChar, int& mode)
{
    clearGrid();
    X = 1;
    Y = 1;
    plotChar = '*';
    mode = FG;
    pos++;
}

// function to execute line plot commands, return 1 if syntax error, return 2 if command out of bounds
int plotCommand(string command, int dir, int& pos, int& X, int& Y, char& plotChar, int& mode, int& badPos)
{
    pos ++;
    string distanceString = "";
    
    if (command[pos] == '-')    // check for a negative sign, add to distance if so
    {
        distanceString += '-';
        pos++;
    }
    
    if (isdigit(command[pos]))    // check for numerical argument
    {
        distanceString += command[pos];
        pos++;
    }
    else    // if no numerical, returns error
    {
        badPos = pos;
        return 1;
    }
    
    if (isdigit(command[pos]))    // check for a second digit, add to distance if so
    {
        distanceString += command[pos];
        pos++;
    }
    
    int distance = stoi(distanceString);    // convert to int distance
    
    if (!checkBounds(Y, X, dir, distance))  // check command is within bounds, returns error if not
    {
        badPos = pos - distanceString.size() - 1;
        return 2;
    }
    
    plotLine(Y, X, dir, distance, plotChar, mode); // plot line for correct command
    
    if (dir == HORIZ)   // update current coordinates
        X += distance;
    else
        Y += distance;
    
    return 0;
}

int modeCommand(string command, int& pos, char& plotChar, int& mode, int& badPos)
{
    if (tolower(command[pos]) == 'f')  // change mode
        mode = FG;
    else
        mode = BG;
    pos ++;
    
    if (isprint(command[pos]))  // check for printable character
    {
        plotChar = command[pos];
        pos++;
    }
    else        // otherwise return false and error position
    {
        badPos = pos;
        return 1;
    }
    
    return 0;
}

// function for plotting lines
bool plotLine(int r, int c, int dir, int distance, char plotChar, int fgbg)
{
    // error messages for failed inputs
    if (dir != 0 && dir != 1)       // must be VERT or HORIZ
        return false;
    if (fgbg != 0 && fgbg != 1)     // must be FG or BG
        return false;
    if (!isprint(plotChar))     // non-printable character
        return false;
    if (!checkBounds(r, c, dir, distance))  // every position of line must be in grid bounds
        return false;
    
    if (dir == HORIZ)       // if HORIZ, plot horizontal line
    {
        if (distance > 0)   // for rightward lines
        {
            for (int col = c; col <= c + distance; col++)
            {
                if (fgbg == BG)     // background lines
                {
                    if (getChar(r, col) == ' ')     // doesn't print if nonspace character
                        setChar(r, col, plotChar);
                }
                else        // foreground settings
                    setChar(r, col, plotChar);
            }
        }
        
        else    // leftward lines or lines w/distance 0
        {
            for (int col = c; col >= c + distance; col--)
            {
                if (fgbg == BG)
                {
                    if (getChar(r, col) == ' ')
                        setChar(r, col, plotChar);
                }
                else
                    setChar(r, col, plotChar);
            }
        }
    }
    
    else if (dir == VERT)   // if VERT, plot vertical line
    {
        if (distance > 0)   // for downward lines
        {
            for (int row = r; row <= r + distance; row++)
            {
                if (fgbg == BG)
                {
                    if (getChar(row, c) == ' ')
                        setChar(row, c, plotChar);
                }
                else
                    setChar(row, c, plotChar);
            }
        }
    
        else    // upward lines or lines w/distance 0
        {
            for (int row = r; row >= r + distance; row--)
            {
                if (fgbg == BG)
                {
                    if (getChar(row, c) == ' ')
                        setChar(row, c, plotChar);
                }
                else
                    setChar(row, c, plotChar);
            }
        }
    }
    
    return true;    // return true for successful program
}

// function for checking that line will be witin limits of grid
bool checkBounds(int r, int c, int dir, int distance)
{
    if (r < 1 || r > NROWS || c < 1 || c > NCOLS)   // if initial point is out of bound
        return false;
    
    if (dir == HORIZ)   // for horizontal lines
    {
        if (distance > 0)
        {
            for (int col = c; col <= c + distance; col++)
            {
                if (col > NCOLS)
                    return false;
            }
        }
        
        if (distance < 0)
        {
            for (int col = c; col >= c + distance; col--)
            {
                if (col < 1)
                    return false;
            }
        }
    }
    
    if (dir == VERT)    // for vertical lines
    {
        if (distance > 0)
        {
            for (int row = r; row <= r + distance; row++)
            {
                if (row > NROWS)
                    return false;
            }
        }
        
        if (distance < 0)
        {
            for (int row = r; row >= r + distance; row--)
            {
                if (row < 1)
                    return false;
            }
        }
    }
    return true;
}


