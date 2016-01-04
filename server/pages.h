#ifndef _PAGES_H_
#define _PAGES_H_

#include <vector>
#include <map>
#include <string>

float MAX(float a, float b);
float MIN(float a, float b);

class DynamicPage {
public:
	virtual std::string getContents(std::string URL, std::map<std::string, std::string> formFields)=0;
};

extern std::vector<DynamicPage*> pages;

std::string getPage(std::string URL, std::map<std::string, std::string> formFields);

void initPageList();

#endif
