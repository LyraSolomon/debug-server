#ifndef _PAGES_H_
#define _PAGES_H_

#include <vector>
#include <map>
#include <string>
#include <memory>

class DynamicPage {
public:
	virtual std::string getContents(std::string URL, std::map<std::string, std::string> formFields)=0;
};

extern std::vector<std::shared_ptr<DynamicPage>> pages;

std::string getPage(std::string URL, std::map<std::string, std::string> formFields);

#endif
