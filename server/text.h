#ifndef _TEXT_H_
#define _TEXT_H_

#include <string>
#include <vector>
#include <sys/time.h>
#include "pages.h"

class Message {
public:
	int time;
	std::string message;
	std::string category;
	std::string color;
};

class Text : public DynamicPage {
protected:
	std::vector<Message> data;
	int historySize=20;
public:
	virtual std::string getContents(std::string URL, std::map<std::string, std::string> formFields);
};

#endif
