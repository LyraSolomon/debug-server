#include "pages.h"
#include <iostream>
#include <fstream>
#include "graphs.h"
#include "text.h"

float MAX(float a, float b) {return a>b ? a : b;}
float MIN(float a, float b) {return a<b ? a : b;}

std::vector<DynamicPage*> pages;

std::string getPage(std::string URL, std::map<std::string, std::string> formFields) {
	for(unsigned int i=0; i<pages.size(); i++) {
		std::string retval=pages[i]->getContents(URL, formFields);
		if(retval.compare("")!=0) return retval;
	}
	std::ifstream file;
	file.open("/home/ubuntu/code/debug-server/server/pages/"+URL);
	if(file.is_open()) {
		std::string line, retval;
		while(getline(file, line)) {
			retval+=line+"\r\n";
		}
		file.close();
		return retval;
	}
	throw(std::string("404"));
}

void initPageList() {
  pages.push_back(new Graphs());
  pages.push_back(new Text());
}
