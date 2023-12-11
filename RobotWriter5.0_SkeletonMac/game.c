#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"

    // Store the the information of each shape from file

int ReadShape (struct Shape *shapeList, FILE *file)
    {
    //printf("0");

    //printf("2");
    for (int i = 0; i < numShapes; i++) 
    {
        struct Shape shape;
        fscanf(file, "%s %d", shape.name, &shape.numStrokes); // Read shape name and number of strokes
        
        shape.strokes = malloc(shape.numStrokes * sizeof(struct PenStroke)); // Allocate memory for strokes

        for (int j = 0; j < shape.numStrokes; j++) 
        {
            fscanf(file, "%d %d %d", &shape.strokes[j].x, &shape.strokes[j].y, &shape.strokes[j].penStatus);
        }

        // Display shape data
        printf("%s %d\n", shape.name, shape.numStrokes);
        for (int j = 0; j < shape.numStrokes; j++) 
        {
            printf("%d %d %d\n", shape.strokes[j].x, shape.strokes[j].y, shape.strokes[j].penStatus);
        }
        shapeList[i] = shape;
    }

    fclose (file);
    return 1;
    }

    void freeShape(struct Shape *shapeList){
    for (int i = 0; i < numShapes; i++) 
    {
        free(shapeList[i].strokes);
    }
    }

    void shapeSelection (int *User1,int *User2)
{
    printf("Please User1 Select a Shape (please enter a number 1-5)");
    scanf("%d",User1);
    while (*User1<1 || *User1>5)
    {
        printf("Please Reselct Your Number");
        scanf("%d", User1);
    }
    printf("Please User2 Select a Shape (please enter a number 1-5)");
    scanf("%d",User2);
    while (*User2<1 || *User2>5 || *User2==*User1)
    {
        printf("Please Reselct Your Number");
        scanf("%d",User2);
    }
}