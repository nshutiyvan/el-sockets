#include <stdio.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()
#include <string.h>
#include <stdlib.h>
#include "Auxiliary.h"
#include "HandleTCPChatClient.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */
char* changeCase(char messsage[]);

void HandleTCPChatClient (int clntSocket)
{
		
	// 'clntSocket' is obtained from AcceptTCPConnection()
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int  recvMsgSize;                   /* Size of received message */

    /* Receive message from client */
    recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
    if (recvMsgSize < 0)
    {
        DieWithError ("recv() failed");
    }
    info_d ("Recv", recvMsgSize);
	/* Send received string and receive again until end of transmission */
    while (1)      /* zero indicates end of transmission */
    {
			printf("the buffer is not null \n");
			int val = 0;
			if(val == 0)
			{
				// TODO: add code to print the received string; use printf()
				printf("%s \n",echoBuffer);
				
				int rescmp = strcmp(echoBuffer, "quit");
				if(rescmp == 0)
				{
				   close (clntSocket);    /* Close client socket */
				   info ("close");
				}
				val = 1;	
			}		
			if(val == 1)
			{
				//sedn the values 
				if (send (clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
				{
					DieWithError ("send() failed");
				}
				printf("send the data is %s \n", echoBuffer);
				
				for(int i = 0; i < sizeof(echoBuffer); i++)
				{
					echoBuffer[i] = 0;
				}
				
				val = 2;
			}	
			if(val == 2)
			{
				printf("check of other values \n");
				recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
				if (recvMsgSize < 0)
				{
					DieWithError ("recv() failed");
				}
				val = 0;			
			}
	}
}