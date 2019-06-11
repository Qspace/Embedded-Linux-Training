/*
Module: Communication with ThingSpeak (on Linux) via TCP Socket
Author:  Pedro Bertoleti
Date:   05/2016
*/

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "ThingSpeakLinux.h"

//defines
#define URL_THINGSPEAK             "api.thingspeak.com"
#define PORT_THINGSPEAK            80
#define BEGIN_OF_HTTP_REQ          "POST /update HTTP/1.1\nHost: api.thingspeak.com\nConnection: close\nX-THINGSPEAKAPIKEY: UK86I0RBBLDUF9JY\nContent-Type: application/x-www-form-urlencoded\n"
#define END_OF_HTTP_REQ            "\r\n\r\n"
#define MAX_SIZE                   9999

//    ostringstream head, data;
//    cout << "Starting ThingSpeak Example" << endl;
//    SocketClient sc("api.thingspeak.com",80);
//    data << "field1=" << getCPUTemperature() << endl;
//    sc.connectToServer();
//    head << "POST /update HTTP/1.1\n"
//         << "Host: api.thingspeak.com\n"
//         << "Connection: close\n"
//         << "X-THINGSPEAKAPIKEY: UK86I0RBBLDUF9JY\n"
//         << "Content-Type: application/x-www-form-urlencoded\n"
//         << "Content-Length:" << string(data.str()).length() << "\n\n";
//    sc.send(string(head.str()));
//    sc.send(string(data.str()));
//    string rec = sc.receive(1024);
//    cout << "[" << rec << "]" << endl;
//    cout << "End of ThingSpeak Example" << endl;
//local variables

//local prototypes

//implementation

//Function: Send some data to a ThingSpeak's channel
//Parameters:  - Number of fields (data to be sent)
//             - Array of integer values (all data that must be sent)
//             - ThingSpeaks's channel Key
//             - Size of ThingSpeak's channel key
//Return:      - 
char SendDataToThingSpeak(int FieldNo, float * FieldArray, char * Key, int SizeOfKey)
{
	int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *ServerTCP;
	int ReqStringSize;
	int i;
	char ReqString[MAX_SIZE];
	char BeginOfHTTPReq[]=BEGIN_OF_HTTP_REQ;
	char EndOfHTTPReq[]=END_OF_HTTP_REQ;
	char *ptReqString;
	
	if (FieldNo <=0)
		return PARAMS_ERROR;
	
	//Setting up HTTP Req. string:
	bzero(&ReqString,sizeof(ReqString));
	sprintf(ReqString,"%s",BeginOfHTTPReq);
	
	ptReqString = &ReqString[0]+(int)strlen(ReqString);
	for(i=1; i<= FieldNo; i++)
	{
		sprintf(ptReqString,"field%d=%.2f",i,FieldArray[i-1]);
		ptReqString = &ReqString[0]+(int)strlen(ReqString);
	}
	
	sprintf(ptReqString,"%s",EndOfHTTPReq);
	printf("%s",EndOfHTTPReq);
	//Connecting to ThingSpeak and sending data:
	portno = PORT_THINGSPEAK;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
	//Step 1: opening a socket
	if (sockfd < 0)
		return OPEN_SOCKET_ERROR;
	
	//Step 2: check if ThingSpeak is online
	ServerTCP = gethostbyname(URL_THINGSPEAK);
	if (ServerTCP == NULL) 
	    return THINGSPEAK_OFFLINE_ERROR;
    
	//Step 3: setting up TCP/IP socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)ServerTCP->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         ServerTCP->h_length);
    serv_addr.sin_port = htons(portno);
    
	//Step 4: connecting to ThingSpeak server (via HTTP port / port no. 80)
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		return THINGSPEAK_CONNECTION_ERROR;
	
	printf("ReqString: %s\n",ReqString);
	//Step 5: sending data to ThingSpeak's channel
    write(sockfd,ReqString,strlen(ReqString));
		
	//Step 6: close TCP connection
    close(sockfd);    
	
	//All done!
	return SEND_OK;
}
	// socketfd = socket(AF_INET, SOCK_STREAM, 0);
    // if (socketfd < 0){
    // 	perror("Socket Client: error opening socket.\n");
    // 	return 1;
    // }
    // server = gethostbyname(serverName.data());
    // if (server == NULL) {
    //     perror("Socket Client: error - no such host.\n");
    //     return 1;
    // }
    // bzero((char *) &serverAddress, sizeof(serverAddress));
    // serverAddress.sin_family = AF_INET;
    // bcopy((char *)server->h_addr,(char *)&serverAddress.sin_addr.s_addr, server->h_length);
    // serverAddress.sin_port = htons(portNumber);

    // if (connect(socketfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
    // 	perror("Socket Client: error connecting to the server.\n");
    // 	return 1;
    // }
		   
