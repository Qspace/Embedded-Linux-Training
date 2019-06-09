#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>

const int portNumber = 54321;
//Create socket 
//bind to port
//listen connection
//create new socket for communicate with client based on the return of accept function
int main(int argc, char** agrv)
{
    int serverFd, newSocket, valueRead;
    struct sockaddr_in address;
    int opt=1;
    int addlen = sizeof(address);
    char buf[1024] = {0};
    char* serverMsg = "Hello from sever";

    // create socket
    if((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socker failed");
        exit(EXIT_FAILURE);
    }

     // Forcefully attaching socket to the port 8080 
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(portNumber);

    if(bind(serverFd,(struct sockaddr*)&address,sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if ((listen(serverFd,5)) < 0)
    {
        perror("no connection listen");
        exit(EXIT_FAILURE);
    }

    if ( (newSocket = accept(serverFd,(struct sockaddr*)&address,(socklen_t*)&addlen)) < 0)
    {
        perror("err accept new sk");
        exit(EXIT_FAILURE);
    }

    valueRead = read(newSocket, buf, 1024);
    printf("%s \n",buf);
    send(newSocket,serverMsg, strlen(serverMsg), 0);

    return 0;
}