#ifndef _SERVER_H_
#define _SERVER_H_

#include <string>
#include "pages.h"

std::string getReply(std::string str);
int serverInit(int port);

#endif
