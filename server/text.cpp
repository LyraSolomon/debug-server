#include "text.h"
#include <iostream>
std::string Text::getContents(std::string URL, std::map<std::string, std::string> formFields) {
	if(URL.compare("text.html")==0) {
		if(formFields.count("size")==1) historySize=std::stoi(formFields["size"]);
		return std::string("<!doctype html><html><head><script src=\"jquery-2.1.4.min.js\">")+ 
			"</script><script>$(function(){setInterval(function(){"
			+ "$('#include').load('dynamic_text.html');}, 300);});</script>"
			+ "<style>table, th, td { border:1px solid black; border-collapse:collapse; }"
			+ "th, td {padding:5px}</style></head>"
			+ "<body><div id=\"foo\"></div><form id=\"history\">"
			+ "history size:<input type=\"text\" name=\"size\">"
			+ "<input type=\"submit\"></input></form>"
			+ "<div id=\"include\"></div></body></html>";
	}
	if(URL.compare("add_text_data.html")==0) {
		if(formFields.count("message")==1 && formFields.count("category")==1 && formFields.count("color")==1) {
			Message m;
			m.message=formFields["message"];
			m.category=formFields["category"];
			m.color=formFields["color"];
			timeval time;
			gettimeofday(&time, 0);
			m.time=(int)(time.tv_sec*1000+time.tv_usec/1000);
			data.push_back(m);
		}
		return std::string("<html><body><form>message:")
				+ "<input type=\"text\" name=\"message\" /><br />"
				+ "category:<input type=\"text\" name=\"category\" value=\""
				+ formFields["category"]+"\" /><br />color:<input type=\"text\""
				+ "name=\"color\" value=\"black\"/>"
				+ "<input type=\"submit\" /></form></html>";
	}
	if(URL.compare("dynamic_text.html")==0) {
		std::string retval="<table><tr><th>category</th><th>message</th><th>time</th></tr><br />";
		for(int i=MIN(data.size()-1, historySize-1); i>=0; i--) {
			retval+="<tr style=\"color:"+data[i].color+";\">"
			+ "<td>["+data[i].category+"]</td><td>"+data[i].message+"</td><td>";
			/*+ std::to_string(data[i].time/3600000)+":"
			+ std::to_string((data[i].time/60000)%60)+":"
			+ std::to_string((data[i].time/1000)%60)+"."
			+ std::to_string(data[i].time%1000)+"</td></tr>";*/
		}
		retval+="</table>";
		return retval;
	}
	return "";
}
