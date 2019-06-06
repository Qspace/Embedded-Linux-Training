#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <string.h>
#include <netdb.h>

const int portNumber = 54321;

int connectToServer(){
	struct hostent *server;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0){
    	perror("Socket Client: error opening socket.\n");
    	return -1;
    }
    server = gethostbyname("207.137.6.115");
    if (server == NULL) {
        perror("Socket Client: error - no such host.\n");
        return -1;
    }
    	// specify an address for the socket
	struct sockaddr_in stServerAddress;
	memset(&stServerAddress, '0', sizeof(stServerAddress));
	stServerAddress.sin_family = AF_INET;
	stServerAddress.sin_port = htons(portNumber);
	memcpy((char *)&stServerAddress.sin_addr.s_addr,(char *)server->h_addr, server->h_length);

    if (connect(socketfd, (struct sockaddr *) &stServerAddress, sizeof(stServerAddress)) < 0){
    	perror("Socket Client: error connecting to the server.\n");
    	return -1;
    }
    return socketfd;
}

int sendMsg(int socketfd, char* writeBuffer, int length){
    int n = write(socketfd, writeBuffer, length);
    if (n < 0){
       perror("Socket Client: error writing to socket");
       return 1;
    }
    return 0;
}

int receive(int socketfd, char* buf, int length){
    char readBuffer[length];
    int n = read(socketfd, readBuffer, sizeof(readBuffer));
    if (n < 0){
       perror("Socket Client: error reading from socket"); 
       return 1;
    }
    return n;
}

int disconnectFromServer(int socketfd){
	close(socketfd);
	return 0;
}

int main() 
{
	//create a socket
	int networkSocketFd;
	networkSocketFd = connectToServer();
	if(networkSocketFd < 0)
	{
		printf("Connect to server err\n");
		return -1;
	}


	//Send msg to server
	char* msg = "Hello from Client";
	sendMsg(networkSocketFd,msg,strlen(msg));

	//receive data from the server
	char serverResBuf[1024];
	recv(networkSocketFd, &serverResBuf, sizeof(serverResBuf), 0);

	//print out the server's response
	printf("Receive data form server: %s\n", serverResBuf);

	//close socket
	disconnectFromServer(networkSocketFd);
	
	return 0;
}
