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
    printf("Please User1 Select a Shape (please enter a number 1-6):");
    scanf("%d",User1);
    while (*User1<1 || *User1>6)
    {
        printf("Please Reselct Your Number:");
        scanf("%d", User1);
    }
    printf("Please User2 Select a Shape (please enter a number 1-6):");
    scanf("%d",User2);
    while (*User2<1 || *User2>6 || *User2==*User1)
    {
        printf("Please Reselct Your Number:");
        scanf("%d",User2);
    }
}

void drawTheGrid(float *gridSize)
{
    //User Select Grid Size
    char buffer[50];
    printf("Please Select a Grid Size (30-100)(mm):");
    scanf("%f", gridSize);
    while((*gridSize)<30 || (*gridSize)>100)
    {
        printf("Please Reselect the Grid Size:");
        scanf("%f", gridSize);
    }
    // Initialise the Robot
    sprintf (buffer, "G1 X0 Y0 F1000\n");
    SendCommands(buffer);
    sprintf (buffer, "M3\n");
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);

    //Draw the Grid
    sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, -(*gridSize)/3);
    SendCommands(buffer);
    sprintf (buffer, "S1000\n");
    SendCommands(buffer);
    sprintf (buffer, "G1 X%.2f Y%.2f\n", (*gridSize), -(*gridSize)/3);
    SendCommands(buffer);
    sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, -(*gridSize)*2/3);
    SendCommands(buffer);
    sprintf (buffer, "G1 X%.2f Y%.2f\n", (*gridSize), -(*gridSize)*2/3);
    SendCommands(buffer);
    sprintf (buffer, "G0 X%.2f Y%.2f\n", (*gridSize)/3, 0.0);
    SendCommands(buffer);
    sprintf (buffer, "G1 X%.2f Y%.2f\n", (*gridSize)/3, -(*gridSize));
    SendCommands(buffer);
    sprintf (buffer, "G0 X%.2f Y%.2f\n", (*gridSize)*2/3, 0.0);
    SendCommands(buffer);
    sprintf (buffer, "G1 X%.2f Y%.2f\n", (*gridSize)*2/3, -(*gridSize));
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);
    sprintf (buffer, "G0 X0 Y0\n");
    SendCommands(buffer);
}

int checkWinner (int chessboard[SIZE][SIZE],float gridSize)
{
    char buffer[50];
    if(chessboard[0][0]==1 && chessboard[1][0]==1 && chessboard[2][0]==1)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, -gridSize*5/6);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize, -gridSize*5/6);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[0][1]==1 && chessboard[1][1]==1 && chessboard[2][1]==1)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, -gridSize/2);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize, -gridSize/2);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[0][2]==1 && chessboard[1][2]==1 && chessboard[2][2]==1)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, -gridSize/6);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize, -gridSize/6);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[0][0]==1 && chessboard[0][1]==1 && chessboard[0][2]==1)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", gridSize/6, 0.0);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize/6, -gridSize);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[1][2]==1 && chessboard[1][1]==1 && chessboard[1][2]==1)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", gridSize/2, 0.0);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize/2, -gridSize);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[2][0]==1 && chessboard[2][1]==1 && chessboard[2][2]==1)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", gridSize*5/6, 0.0);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize*5/6, -gridSize);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[0][0]==1 && chessboard[1][1]==1 && chessboard[2][2]==1)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, -gridSize);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize, 0.0);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[0][2]==1 && chessboard[1][1]==1 && chessboard[2][0]==1)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, 0.0);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize, -gridSize);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[0][0]==2 && chessboard[1][0]==2 && chessboard[2][0]==2)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, -gridSize*5/6);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize, -gridSize*5/6);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[0][1]==2 && chessboard[1][1]==2 && chessboard[2][1]==2)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, -gridSize/2);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize, -gridSize/2);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[0][2]==2 && chessboard[1][2]==2 && chessboard[2][2]==2)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, -gridSize/6);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize, -gridSize/6);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[0][0]==2 && chessboard[0][1]==2 && chessboard[0][2]==2)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", gridSize/6, 0.0);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize/6, -gridSize);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[1][0]==2 && chessboard[1][1]==2 && chessboard[1][2]==2)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", gridSize/2, 0.0);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize/2, -gridSize);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[2][0]==2 && chessboard[2][1]==2 && chessboard[2][2]==2)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", gridSize*5/6, 0.0);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize*5/6, -gridSize);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[0][0]==2 && chessboard[1][1]==2 && chessboard[2][2]==2)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, -gridSize);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize, 0.0);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else if(chessboard[0][2]==2 && chessboard[1][1]==2 && chessboard[2][0]==2)
    {
        printf("Congraduation!User1 Wins!");
        sprintf (buffer, "G0 X%.2f Y%.2f\n", 0.0, 0.0);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%.2f Y%.2f\n", gridSize, -gridSize);
        SendCommands(buffer);
        sprintf (buffer, "S0\n");
        SendCommands(buffer);
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        return 1;
    }
    else
    {
        return 0;
    }
}

int gameLoop (float gridSize)
{
    int x,y;
    int chessboard[SIZE][SIZE]={{0,0,0},{0,0,0},{0,0,0}};
    while(1)
    {
        int n=0;
        printf("Please User1 select you cordinate x y (0<x,y<4):");
        scanf("%d %d", &x, &y);
        while(chessboard[x-1][y-1]!=0 || x<1 || x>3 || y<1 || y>3)
        {
            printf("Please reselect:");
            scanf("%d %d", &x, &y);
        }
        chessboard[x-1][y-1]=1;
        n=checkWinner(chessboard, gridSize);
        if(n==1)
        {
            return 1;
        }
        printf("Please User2 select you cordinate x y (0<x,y<4):");
        scanf("%d %d", &x, &y);
        while(chessboard[x-1][y-1]!=0 || x<1 || x>3 || y<1 || y>3)
        {
            printf("Please reselect:");
            scanf("%d %d", &x, &y);
        }
        chessboard[x-1][y-1]=2;
        n=checkWinner(chessboard, gridSize);
        if(n==1)
        {
            return 1;
        }
    }
}