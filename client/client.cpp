#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <pthread.h>
#include <map>
#include <chrono>
#include "client.h"
#include <thread>
using namespace std;

float x;
float y;
int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;

int clientInit(int port, char* url)
{
    
    while (true)
    {
        portno=port;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
	    std::cerr<<"ERROR opening socket\n";
	    return 0;
	}
	server = gethostbyname(url);
	if (server == NULL) {
	    std::cerr<<"ERROR, no such host\n";
	    exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
	    (char *)&serv_addr.sin_addr.s_addr,
	     server->h_length);
	serv_addr.sin_port = htons(portno);

        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
            std::cerr<<"ERROR connecting\n";
            return 0;
        }
        std::cerr<<"got here2\n";
        std::string request="GET / HTTP/1.1\r\n\r\n";
        n = write(sockfd,request.c_str(), request.length());
        if (n < 0) {
             std::cerr<<"ERROR writing to socket\n";
             return 0;
        }
        std::cerr<<"got here3\n";
        char buffer[256];
        bzero(buffer,256);
        std::cerr<<"got here6\n";
        n = read(sockfd,buffer,255);
        std::cerr<<"got here7\n";
        if (n < 0) {
             std::cerr<<"ERROR reading from socket\n";
        }
        std::cout<<buffer<<"\n";
        close(sockfd);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
