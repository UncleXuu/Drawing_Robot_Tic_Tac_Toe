#include <stdio.h>
#include <stdlib.h>

#include "serial.h"

#define MAC

#ifdef MAC
#include <unistd.h>
#else
#include <conio.h>
#include <Windows.h>
#include "rs232.h"
#endif

// #define Serial_Mode

#ifdef Serial_Mode   // Code for running with robot

// Open port with checking
int CanRS232PortBeOpened ( void )
{
    char mode[]= {'8','N','1',0};
    if(RS232_OpenComport(cport_nr, bdrate, mode))
    {
        printf("Can not open comport\n");

        return(-1);
    }
    return (0);      // Success
}

// Function to close the COM port
void CloseRS232Port (void)
{
    RS232_CloseComport(cport_nr);
}

// Write text out via the serial port
int PrintBuffer (char *buffer)
{
    RS232_cputs(cport_nr, buffer);
    printf("sent: %s\n", buffer);

    return (0);

}


int WaitForDollar (void)
{
    int i, n;

    unsigned char buf[4096];

    while(1)
    {
        printf (".");
        n = RS232_PollComport(cport_nr, buf, 4095);

        if(n > 0)
        {
            printf ("RCVD: N = %d ", n);
            buf[n] = 0;   /* always put a "null" at the end of a string! */

            for(i=0; i < n; i++)
            {
                if(buf[i] == '$')  /* replace unreadable control-codes by dots */
                {
                    printf("received %i bytes: %s \n", n, (char *)buf);
                    printf("\nSaw the Dollar");
                    return 0;
                }
            }

            printf("received %i bytes: %s \n", n, (char *)buf);

            if ( (buf[0] == 'o') && (buf[1] == 'k') )
                return 0;
        }

        Sleep(100);
    }

    return(0);

}

int WaitForReply (void)
{
    int i, n;

    unsigned char buf[4096];

    while(1)
    {
        printf (".");
        n = RS232_PollComport(cport_nr, buf, 4095);

        if(n > 0)
        {
            printf ("RCVD: N = %d ", n);
            buf[n] = 0;   /* always put a "null" at the end of a string! */

            for(i=0; i < n; i++)
            {
                if(buf[i] < 32)  /* replace unreadable control-codes by dots */
                {
                    buf[i] = '.';
                }
            }

            printf("received %i bytes: %s\n", n, (char *)buf);

            if ( (buf[0] == 'o') && (buf[1] == 'k') )
                return 0;
        }

        Sleep(100);
    }

    return(0);

}

#else  // Code for testing with emulator

// Open port with checking
int CanRS232PortBeOpened ( void )
{
    return (0);      // Success
}

// Function to close the COM port
void CloseRS232Port (void)
{
    return;
}

// Print the buffer contents to the terminal
int PrintBuffer (char *buffer)
{
    printf("%s \n",buffer);
    return (0);
}

// Dummy function, will wait for key press
int WaitForReply (void)
{
    getc(stdin);
    return (0);
}

// Dummy function, will wait for key press
int WaitForDollar (void)
{
    getc(stdin);
    return (0);
}

#endif 




