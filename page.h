#include <string>
#include <map>
#include <vector>

namespace Pages {
	std::string getPage(std::string URL, std::map<std::string, std::string> form);
	std::string loadFromFile(std::string filename);
}