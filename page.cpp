#include "page.h"
#include <stdlib.h>
#include <fstream>

namespace Pages {
	std::string getPage(std::string URL, std::map<std::string, std::string> form) {
		std::string retval=loadFromFile(URL);
		retval=URL;
		if (retval=="") throw "404";
		return retval;
	}
	std::string loadFromFile(std::string filename) {
		std::ifstream t;
		t.open(filename.c_str());
		std::string buffer;
		std::string line;
		while(t){
			std::getline(t, line);
			buffer+=line;
		}
		t.close();
		return buffer;
	}
}