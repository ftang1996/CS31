// Graphics library interface

#ifndef GRAPHLIB_INCLUDED
#define GRAPHLIB_INCLUDED

const int NROWS = 20;
const int NCOLS = 30;

void clearGrid();
void setChar(int r, int c, char ch);
char getChar(int r, int c);
void draw();

#endif // GRAPHLIB_INCLUDED
