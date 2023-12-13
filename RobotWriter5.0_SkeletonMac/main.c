#include <stdio.h>
#include <stdlib.h>

#define MAC

#ifdef MAC
#include <unistd.h>
// #else
// #include <Windows.h>
// #include "rs232.h"
// #include <conio.h>
#endif

#include "serial.h"

#define bdrate 115200               /* 115200 baud */

#include "game.h"

void SendCommands (char *buffer );

int main(void)
{
    // Read the file and store the data
    FILE *file = fopen("ShapeStrokeData.txt", "r");
    if (file == NULL) {
        printf("Error opening file");
        return 1;
    }
    fscanf(file, "NumShapes %d\n", &numShapes); // Read the number of shapes
    struct Shape shapeList[numShapes];
    readShape (shapeList,file);

    // User select favourite shape (1-5)
    int User1, User2;
    shapeSelection (&User1, &User2);


    char buffer[100];
 
    // If we cannot open the port then give up immediatly
    if ( CanRS232PortBeOpened() == -1 )
    {
        printf ("\nUnable to open the COM port (specified in serial.h) ");
        exit (0);
    }

    // Time to wake up the robot
    printf ("\nAbout to wake up the robot\n");

    // We do this by sending a new-line
    sprintf (buffer, "\n");
    // printf ("Buffer to send: %s", buffer); // For diagnostic purposes only, normally comment out
    PrintBuffer (&buffer[0]);
    #ifdef MAC
    sleep(0.1);
    #else
    Sleep(100);
    #endif

    // This is a special case - we wait  until we see a dollar ($)
    WaitForDollar();

    printf ("\nThe robot is now ready to draw\n");

    // Read the size and draw the grid   
    float gridSize;
    drawTheGrid(&gridSize);

    //Scale the movement
    float scale;
    scale = scaleMovements (gridSize);

    // Start the game
    gameLoop(gridSize, shapeList, User1, User2, scale);

    //These commands get the robot into 'ready to draw mode' and need to be sent before any writing commands
    // sprintf (buffer, "G1 X0 Y0 F1000\n");
    // SendCommands(buffer);
    // sprintf (buffer, "M3\n");
    // SendCommands(buffer);
    // sprintf (buffer, "S0\n");
    // SendCommands(buffer);

    // These are sample commands to draw out some information 
    // This is the section that you will replace with your own code
    // sprintf (buffer, "G0 X2.5 Y-2.5\n");
    // SendCommands(buffer);
    // sprintf (buffer, "S1000\n");
    // SendCommands(buffer);
    // sprintf (buffer, "G1 X7.5 Y-2.5\n");
    // SendCommands(buffer);
    // sprintf (buffer, "G1 X7.5 Y-7.5\n");
    // SendCommands(buffer);
    // sprintf (buffer, "G1 X2.5 Y-7.5\n");
    // SendCommands(buffer);
    // sprintf (buffer, "G1 X2.5 Y-2.5\n");
    // SendCommands(buffer);
    // sprintf (buffer, "S0\n");
    // SendCommands(buffer);
    // sprintf (buffer, "G0 X0 Y0\n");
    // SendCommands(buffer);
    // End of sample g-code
    

    // Before we exit the program we need to close the COM port
    CloseRS232Port();
    printf("Com port now closed\n");

    // Free the memory after running
    freeShape(shapeList);
    
    return (0);
}

// Send the data to the robot - note in 'PC' mode you need to hit space twice
// as the dummy 'WaitForReply' has a getch() within the function.
void SendCommands (char *buffer )
{
    // printf ("Buffer to send: %s", buffer); // For diagnostic purposes only, normally comment out
    PrintBuffer (&buffer[0]);
    WaitForReply();
    #ifdef MAC
    sleep(0.1);
    #else
    Sleep(100); // Can omit this when using the writing robot but has minimal effect
    #endif
}
