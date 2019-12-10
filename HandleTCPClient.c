#include <stdio.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()
#include <string.h>
#include <stdlib.h>
#include "Auxiliary.h"
#include "HandleTCPClient.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */
char * changeCase(char message[],int elementsCount);

void HandleTCPClient (int clntSocket)
{
    // 'clntSocket' is obtained from AcceptTCPConnection()

    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int  recvMsgSize;                   /* Size of received message */

    /* Receive message from client */
    recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
	printf("SIze:%d",recvMsgSize );
    if (recvMsgSize < 0)
    {
        DieWithError ("recv() failed");
    }
    info_d ("Recv", recvMsgSize);

   
    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
		char sender_message[recvMsgSize];
		int val = 0;
		if(val == 0)
		{
			/*
			printf("am in value 0 \n");
			*/
			printf("Received : %s \n", echoBuffer);
			
			// TODO: add code to print the received string; use printf()
			//printf("echo buffer is %s \n",echoBuffer);
			// TODO: add code to convert the upper/lower chars of the received string
		
			/* Echo message back to client */
			int count = sizeof(echoBuffer);
			char* message = changeCase(echoBuffer,count);
			
			strcpy(sender_message, message);
			
			val = 1;
			
		}
		
	    if(val == 1)
		{

			if(send (clntSocket,sender_message, sizeof(sender_message), 0) != recvMsgSize)
			{
				DieWithError ("send() failed");
			}
			printf("Sendind:%s",sender_message);
			bzero(echoBuffer,sizeof(echoBuffer));	
			val = 2;			
		}
		
		if(val == 2)
		{
			printf("am in value 2 \n");
			// receive next string i will do this after 
		    recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
		    if (recvMsgSize < 0)
			{
					DieWithError ("recv() failed");
			}	
			info_d ("recv", recvMsgSize);
			val = 0;
		}

    }

    close (clntSocket);    /* Close client socket */
    info ("close");
}

char * changeCase(char message[],int elementsCount){
	char* s = malloc(elementsCount);
	int i=0;
    while(message[i] !='\0') 
     {
        if(message[i] >= 'A' && message[i] <= 'Z') {        
         message[i] += 32;
         s[i] = message[i];
        }else if(message[i]>='a' && message[i]<='z'){
           message[i] -= 32;
           s[i] = message[i];
        }
        else{
           s[i] =  message[i];
        }
        i++;
     }
    return s; 
}
