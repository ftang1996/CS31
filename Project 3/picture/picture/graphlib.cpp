//
//  graphlib.cpp
//  picture
//

#include "graphlib.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

static char grid[NROWS][NCOLS];
static bool isGridInitialized = false;

static void drawHorizBorder();
static void checkPos(int r, int c, string func);

void clearGrid()
{
    for (int r = 0; r < NROWS; r++)
        for (int c = 0; c < NCOLS; c++)
            grid[r][c] = ' ';
    isGridInitialized = true;
}

void setChar(int r, int c, char ch)
{
    checkPos(r, c, "setChar");
    grid[r-1][c-1] = ch;
}

char getChar(int r, int c)
{
    checkPos(r, c, "getChar");
    return grid[r-1][c-1];
}

void draw()
{
    // Write header lines of column numbers
    
    cout << "   ";
    for (int c = 1; c <= NCOLS; c++)
    {
        int t = c / 10;
        if (t == 0)
            cout << ' ';
        else
            cout << t;
    }
    cout << "\n   ";
    for (int c = 1; c <= NCOLS; c++)
        cout << (c%10);
    cout << "\n";
    
    // Draw grid
    
    drawHorizBorder();
    for (int r = 1; r <= NROWS; r++)
    {
        cout << setw(2) << r << '|';
        for (int c = 1; c <= NCOLS; c++)
        {
            char ch = grid[r-1][c-1];
            if (isprint(ch))
                cout << ch;
            else
                cout << '?';
        }
        cout << "|\n";
    }
    drawHorizBorder();
}

static void drawHorizBorder()
{
    cout << "  +";
    for (int c = 1; c <= NCOLS; c++)
        cout << '-';
    cout << "+\n";
}

static void checkPos(int r, int c, string func)
{
    if (!isGridInitialized)
    {
        cout << func << ": You must first call clearGrid." << endl;
        exit(1);
    }
    if (r < 1  ||  r > NROWS  ||  c < 1  ||  c > NCOLS)
    {
        cout << func << ": invalid position (" << r << "," << c << ")"
        << endl;
        exit(1);
    }
}
