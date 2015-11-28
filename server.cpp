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
#include "page.h"
using namespace std;

std::string getReply(std::string str);

static int connFd;

int main(int argc, char* argv[])
{
    int pId, portNo, listenFd;
    socklen_t len; //store size of the address
    bool loop = false;
    struct sockaddr_in svrAdd, clntAdd;
    
    if (argc < 2)
    {
        cerr << "Syntax : ./server <port>" << endl;
        return 0;
    }
    
    portNo = atoi(argv[1]);
    
    if((portNo > 65535) || (portNo < 2000))
    {
        cerr << "Please enter a port number between 2000 - 65535" << endl;
        return 0;
    }
    
    //create socket
    listenFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if(listenFd < 0)
    {
        cerr << "Cannot open socket" << endl;
        return 0;
    }
    
    bzero((char*) &svrAdd, sizeof(svrAdd));
    
    svrAdd.sin_family = AF_INET;
    svrAdd.sin_addr.s_addr = INADDR_ANY;
    svrAdd.sin_port = htons(portNo);
    
    //bind socket
    if(bind(listenFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd)) < 0)
    {
        cerr << "Cannot bind" << endl;
        return 0;
    }
    
    listen(listenFd, 5);
    
    len = sizeof(clntAdd);

    while (true)
    {
        cout << "Listening" << endl;

        //this is where client connects. svr will hang in this mode until client conn
        connFd = accept(listenFd, (struct sockaddr *)&clntAdd, &len);

        if (connFd < 0)
        {
            cerr << "Cannot accept connection" << endl;
            return 0;
        }
        else
        {
            cout << "Connection successful" << endl;
        }
        
        char test[257];
		std::string str="";
		bool loop = true;
		while(loop)
		{    
			bzero(test, 257);
			int i=read(connFd, test, 256);
			if(i==0) break;
			str += test;
			
			if(str.find("\r\n\r\n")!=std::string::npos) loop=false;
		}
		if(loop) continue;
		std::string reply;
		reply=getReply(str);
		write(connFd, reply.c_str(), reply.length());
		cout << "\nClosing thread and conn" << endl;
		close(connFd);
    }
}

std::string getReply(std::string str)
{
	std::string delimiter = "\r\n";
	std::vector<std::string> tokens;
	size_t pos = 0;
	std::string token;
	while ((pos = str.find(delimiter)) != std::string::npos) {
		token = str.substr(0, pos);
		if(token != "") tokens.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	str=tokens[0];
	std::cout<<str<<" FOO\r\n";
	tokens.clear();
	delimiter = " ";
	while ((pos = str.find(delimiter)) != std::string::npos) {
		token = str.substr(0, pos);
		if(token != "") tokens.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	tokens.push_back(str);
	
	if(tokens.size()!=3) return std::string("HTTP/1.1 400 Bad Request\r\n\r\nNot a valid HTTP request\r\n\r\n");
	if(tokens[0]!="GET") return std::string("HTTP/1.1 501 Not Implemented\r\n\r\nOnly GET method is supported\r\n\r\n");
	if(tokens[2]!="HTTP/1.1") return std::string("HTTP/1.1 501 Not Implemented\r\n\r\nOnly accepts HTTP 1.1\r\n\r\n");
	
	str=tokens[1];
	if(str[str.size()-1]=='=' || str.find("=&") != std::string::npos)
		return std::string("HTTP/1.1 400 Bad Request\r\n\r\nPlease fill out all fields in the form\r\n\r\n");
	tokens.clear();
	delimiter = "?";
	int count=0;
	while ((pos = str.find(delimiter)) != std::string::npos) {
		token = str.substr(0, pos);
		if(token != "") tokens.push_back(token);
		str.erase(0, pos + delimiter.length());
		count++;
	}
	if(count>1) return std::string("HTTP/1.1 400 Bad Request\r\n\r\nThere can only be one ? in the request\r\n\r\n");
	tokens.push_back(str);
	
	std::string URL = tokens[0];
	std::map<std::string, std::string> formFields;
	if(tokens.size()==2&&tokens[1]!="")
	{
		std::vector<std::string> formFieldList;
		str=tokens[1];
		tokens.clear();
		delimiter="&";
		while ((pos = str.find(delimiter)) != std::string::npos) {
			token = str.substr(0, pos);
			if(token != "") formFieldList.push_back(token);
			else return std::string("HTTP/1.1 400 Bad Request\r\n\r\nMissing field\r\n\r\n");
			str.erase(0, pos + delimiter.length());
		}
		if(str != "") formFieldList.push_back(str);
		else return std::string("HTTP/1.1 400 Bad Request\r\n\r\nMissing field\r\n\r\n");
		delimiter="=";
		for(int i=0; i<formFieldList.size(); i++) {
			str=formFieldList[i];
			std::string key="";
			if ((pos = str.find(delimiter)) != std::string::npos) {
				key=str.substr(0, pos);
				if(key=="") return std::string("HTTP/1.1 400 Bad Request\r\n\r\nExpected field name\r\n\r\n");
				str.erase(0, pos + delimiter.length());
				if(str=="") return std::string("HTTP/1.1 400 Bad Request\r\n\r\nPlease fill out all fields in the form\r\n\r\n");
				formFields.insert(std::pair<std::string, std::string>(key, str));
			}
		}
	}
	if(URL[URL.size()-1]=='/') URL+="main.html";
	URL.erase(0, 1);
	try {
		return std::string("HTTP/1.1 200 OK\r\n")+
			"Content-Type: text/html; charset=ASCII\r\n"+
			"Connection:close\r\n\r\n"+
			Pages::getPage(URL, formFields)+"\r\n\r\n";
	} catch (...) {
		return std::string("HTTP/1.1 404 Not Found\r\n")+
			"Content-Type: text/html; charset=ASCII\r\n"+
			"Connection:close\r\n\r\n"+
			URL+" is not an existing page\r\n\r\n";
	}
}