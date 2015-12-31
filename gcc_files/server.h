#ifndef _SERVER_H_
#define _SERVER_H_

#include <string>
#include "vision.h"

std::string getReply(std::string str);
int serverInit(int port);
std::string dataAsString();

#endif
