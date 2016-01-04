#include "pages.h"
#include <iostream>
#include <fstream>
#include "graphs.h"

std::vector<DynamicPage*> pages;

std::string getPage(std::string URL, std::map<std::string, std::string> formFields) {
	for(unsigned int i=0; i<pages.size(); i++) {
		std::string retval=pages[i]->getContents(URL, formFields);
    std::cout<<i<<std::endl;
		if(retval.compare("")!=0) return retval;
	}
	std::ifstream file;
	file.open("/home/citrus/code/2015-offseason-projects/vision-server/server/pages/"+URL);
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
  std::cout<<pages.size()<<std::endl;
  pages.push_back(new Graphs());
}
