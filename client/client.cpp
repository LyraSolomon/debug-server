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
	    close(sockfd);
	    continue;
	}
	server = gethostbyname(url);
	if (server == NULL) {
	    std::cerr<<"ERROR, no such host\n";
	    close(sockfd);
	    continue;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
	    (char *)&serv_addr.sin_addr.s_addr,
	     server->h_length);
	serv_addr.sin_port = htons(portno);

        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
            std::cerr<<"ERROR connecting\n";
	    close(sockfd);
	    continue;
        }
        std::string request="GET / HTTP/1.1\r\n\r\n";
        n = write(sockfd,request.c_str(), request.length());
        if (n < 0) {
            std::cerr<<"ERROR writing to socket\n";
	    close(sockfd);
	    continue;
        }
        char test[257];
	std::string str="";
        int i;
	for(i=0; str.find("\r\n\r\n")==std::string::npos; i++)
	{    
	    bzero(test, 257);
	    n=read(sockfd, test, 256);
	    if(n==0) break;
	    str += test;
	}
	if(i==0) {
	    close(sockfd);
	    continue;
	}
        std::cout<<str<<"\n";
        close(sockfd);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
