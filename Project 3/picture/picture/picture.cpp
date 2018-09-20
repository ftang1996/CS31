//  Graphics library interface

#include "graphlib.h"
#include <iostream>
using namespace std;

void plotHorizontalLine(int r, int c, int distance, char ch);
void plotVerticalLine(int r, int c, int distance, char ch);
void plotRectangle(int r, int c, int height, int width, char ch);



void plotHorizontalLine(int r, int c, int distance, char ch)
{
    for (int i = 0; i < distance + 1; i++)
    {
        if ((r >= 1 && r <= NROWS) && (c >= 1 && c <= NCOLS))
        {
            setChar(r, c, ch);
            c++;
        }
        else
        {
            c++;
            continue;
        }
    }
}

void plotVerticalLine(int r, int c, int distance, char ch)
{
    for (int i = 0; i < distance + 1; i++)
    {
        if ((r >= 1 && r <= NROWS) && (c >= 1 && c <= NCOLS))
        {
            setChar(r, c, ch);
            r++;
        }
        else
        {
            r++;
            continue;
        }
    }
}

void plotRectangle(int r, int c, int height, int width, char ch)
{
    if (height > 0 && width > 0)
    {
        plotHorizontalLine(r, c, width - 1, ch);
        plotHorizontalLine(r + width - 1, c, width - 1, ch);
        plotVerticalLine(r, c, height - 1, ch);
        plotVerticalLine(r, c + height - 1, height - 1, ch);
    }
    
}



