#include <stdio.h>
#include <string.h>     // for strlen()
#include <stdlib.h>     // for exit()

#include "Auxiliary.h"
#include "CreateTCPClientSocket.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */

int main (int argc, char *argv[])
{
    int         sock;                   /* Socket descriptor */
    char *      echoString;             /* String to send to echo server */
    char        echoBuffer[RCVBUFSIZE]; /* Buffer for received string */
    int         echoStringLen;          /* Length of string to echo */
    int         bytesRcvd;              /* Bytes read in single recv() */
    int         i;                      /* counter for data-arguments */

    parse_args (argc, argv);

    sock = CreateTCPClientSocket (argv_ip, argv_port);
    
        
    for (i = 0; i < argv_nrofdata; i++)
    {
        echoString = argv_data [i];
        echoStringLen = strlen (echoString);          /* Determine input length */

        delaying();
        
        char sendBuffer[32];
        //printing the sending data 
        printf("%s \n", argv_data[i]);
        strcpy(sendBuffer, argv_data[i]);
        // TODO: add code to send this string to the server; use send()
        send (sock,sendBuffer,sizeof(sendBuffer), 0);
        // TODO: add code to display the transmitted string in verbose mode; use 
        info_s(sendBuffer, sendBuffer);
        // TODO: add code to receive & display the converted string from the server
        //       use recv() & printf()
        
        bytesRcvd = recv (sock, echoBuffer, RCVBUFSIZE-1, 0);
        
        //check if there is something received 
        if(bytesRcvd < 0)
        {
			printf("there was an error in receiving \n");
		}
		else
		{
			printf("received data are: %s \n", echoBuffer);
            for(int i = 0; i < sizeof(echoBuffer); i++)
			{
					echoBuffer[i] = 0;
			}
		}
        
    }

  
    close (sock);
    info ("close & exit");
    exit (0);
}
