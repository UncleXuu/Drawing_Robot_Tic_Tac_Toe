#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 3
#define SHAPEUNITS 16
#define GAP 2

struct PenStroke{
    int x;
    int y;
    int penStatus;
} ;

struct Shape{
    char name[50];
    int numStrokes;
    struct PenStroke *strokes;
};

int numShapes;

void SendCommands (char *buffer );
int readShape (struct Shape *shapeList, FILE *file);
void freeShape(struct Shape *shapeList);
void shapeSelection (int *User1,int *User2);
void drawTheGrid(float *gridSize);
int checkWinner (int chessboard[SIZE][SIZE], float gridSize);
float scaleMovements(float gridSize);
int gameLoop (float gridSize);

#endif