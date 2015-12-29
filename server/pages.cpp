#include "pages.h"
#include <iostream>
#include <fstream>

std::vector<std::shared_ptr<DynamicPage>> pages;

std::string getPage(std::string URL, std::map<std::string, std::string> formFields) {
	return "hello world";
	std::ofstream file;
	file.open("/home/citrus/code/2015-offseason-projects/vision-server/server/pages/main.html");
	file<<"<p>hello world</p>";
	file.close();
	return " ";
}
