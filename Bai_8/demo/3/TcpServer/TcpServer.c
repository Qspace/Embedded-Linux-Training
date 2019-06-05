#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <string.h>
#include <netdb.h>

const int portNumber = 54321;
int listenConnection(int* socketfd, int* clientSocketfd){
    *socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*socketfd < 0){
    	perror("Socket Server: error opening socket.\n");
    	return 1;
    }
    struct sockaddr_in stServerAddress;
    memset((char *) &stServerAddress,'0', sizeof(stServerAddress));
    stServerAddress.sin_family = AF_INET;
    stServerAddress.sin_addr.s_addr = INADDR_ANY;
    stServerAddress.sin_port = htons(portNumber);
    if (bind(*socketfd, (struct sockaddr *) &stServerAddress, sizeof(stServerAddress)) < 0){
    	perror("Socket Server: error on binding the socket.\n");
    	return -1;
    }
    listen(*socketfd, 5);
    struct sockaddr_in   clientAddress;
    socklen_t clientLength = sizeof(clientAddress);
    *clientSocketfd = accept(*socketfd,
      (struct sockaddr *) &clientAddress,
      &clientLength);
    if (*clientSocketfd < 0){
    	perror("Socket Server: Failed to bind the client socket properly.\n");
    	return -1;
    }
    return 0;
}

int sendTcpMsg(int clientSocketfd, char* writeBuffer, int length){
    int n = write(clientSocketfd, writeBuffer, length);
    if (n < 0){
       perror("Socket Server: error writing to server socket.");
       return -1;
   }
   return 0;
}

int receiveTcpMsg(int socketfd, char* buf, int length){
    char readBuffer[length];
    int n = read(socketfd, readBuffer, sizeof(readBuffer));
    if (n < 0){
       perror("Socket Client: error reading from socket"); 
       return -1;
    }
    printf("%d%s\n",n,readBuffer);
   return n;
}

void closeConnection(int socketfd, int clientSocketfd) {
	close(socketfd);
	close(clientSocketfd);
}

int main(int argc, char** argv)
{
    int serverSocketFd, clientSocketfd;
    //receive data from the server
    char serverResBuf[1024];
         //Send msg to server
    char* msg = "Hello from Server";
    if (listenConnection(&serverSocketFd, &clientSocketfd) <0)
    {
        printf("No connection found\n");
    }
    receiveTcpMsg(clientSocketfd,serverResBuf,1024);
    sendTcpMsg(clientSocketfd,msg,strlen(msg));
    closeConnection(serverSocketFd,clientSocketfd);
    return 0;
}