#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <string>

extern float vision_x;
extern float vision_y;

void processServerResponse(std::string str);
int clientInit(int port, char* url);

#endif
