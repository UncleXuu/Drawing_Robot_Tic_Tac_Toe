#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"

    // Store the the information of each shape from file

int readShape (struct Shape *shapeList, FILE *file)
{
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

void freeShape(struct Shape *shapeList)
{
    for (int i = 0; i < numShapes; i++) 
    {
        free(shapeList[i].strokes);
    }
}

void shapeSelection (int *User1,int *User2)
{
    printf("Please User1 Select a Shape (please enter a number 1-5):");
    scanf("%d",User1);
    while (*User1<1 || *User1>5)
    {
        printf("Please Reselct Your Number:");
        scanf("%d", User1);
    }
    printf("Please User2 Select a Shape (please enter a number 1-5):");
    scanf("%d",User2);
    while (*User2<1 || *User2>5 || *User2==*User1)
    {
        printf("Please Reselct Your Number:");
        scanf("%d",User2);
    }
}

void drawTheGrid(void)
{
    //User Select Grid Size
    char buffer[100];
    float gridSize;
    printf("Please Select a Grid Size (30-100)(mm):");
    scanf("%f",&gridSize);
    while(gridSize<30 || gridSize>100)
    {
        printf("Please Reselect the Grid Size:");
        scanf("%f", &gridSize);
    }
    // Initialise the Robot
    sprintf (buffer, "G1 X0 Y0 F1000\n");
    SendCommands(buffer);
    sprintf (buffer, "M3\n");
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);

    //Draw the Grid
    sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, -gridSize/3);
    SendCommands(buffer);
    sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize, -gridSize/3);
    SendCommands(buffer);
    sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, -gridSize*2/3);
    SendCommands(buffer);
    sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize, -gridSize*2/3);
    SendCommands(buffer);
    sprintf (buffer, "G0 X%.2f Y%.2f\n", gridSize/3, 0.0);
    SendCommands(buffer);
    sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize/3, -gridSize);
    SendCommands(buffer);
    sprintf (buffer, "G0 X%.2f Y%.2f\n", gridSize*2/3, 0.0);
    SendCommands(buffer);
    sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize*2/3, -gridSize);
    SendCommands(buffer);
    sprintf (buffer, "G0 X0 Y0\n");
    SendCommands(buffer);
}

// int checkWinner (int buffer)
// {
//     float buffer[3][3];
// }

// void gameProcess (void)
// {
//     while(1)
//     {
//         printf("Please User1 select you");
//     }
// }