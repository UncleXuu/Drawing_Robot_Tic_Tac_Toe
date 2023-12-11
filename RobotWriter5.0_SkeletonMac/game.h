#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int ReadShape (struct Shape *shapeList, FILE *file);
void freeShape(struct Shape *shapeList);
void shapeSelection (int *User1,int *User2);
#endif