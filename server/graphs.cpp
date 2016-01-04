#include "graphs.h"
#include <iostream>

std::string Graphs::getContents(std::string URL, std::map<std::string, std::string> formFields) {
        if(URL.compare("add_graph_data.html")==0) {
                if(formFields.count("title")>0 && formFields.count("data")>0 ) {
                        int index=-1;
                        for(unsigned int i=0; i<contents.size(); i++) {
                                if(contents[i].title.compare(formFields["title"])==0) {
                                        index=i;
                                        break;
                                }
                        }
                        if(index==-1) {
                                contents.push_back(Graph());
                                index=contents.size()-1;
                                contents[index].title=formFields["title"];
                        }
                        float f=std::stof(formFields["data"]);
                        contents[index].data.push_back(f);
                        if(contents[index].data.size()==1) {
                                contents[index].min=f;
                                contents[index].max=f;
                        } else {
                                contents[index].min=MIN(contents[index].min, f);
                                contents[index].max=MAX(contents[index].max, f);
                        }
                }
                return std::string("<html><body><form>value:<input type=\"text\" name=\"data\" /><br />") +
                        "title:<input type=\"text\" name=\"title\" value=\""+formFields["title"]+"\" />" +
                        "<input type=\"submit\" /></form></html>";
        }
        if(URL.compare("graphs.html")==0) {
                if(formFields.count("size") > 0) historySize=std::stoi(formFields["size"]);
                return std::string("<!doctype html><html><head><script src=\"jquery-2.1.4.min.js\"></script>") +
                        "<script>$(function(){setInterval(function(){" + 
                        "$('#include').load('dynamic_graphs.html');}, 300);});" +
                        "</script></head><body><div id=\"foo\"></div><form id=\"history\">" +
                        "history size:<input type=\"text\" name=\"size\"><input type=\"submit\"></input></form>" +
                        "<div id=\"include\"></div></body></html>";
        }
        if(URL.compare("dynamic_graphs.html")==0) {
                std::string retval="<h1>Graph Viewer</h1>";
		if(contents.size()==0) retval+="<p>(no graphs yet)</p>";
                for(unsigned int i=0; i<contents.size(); i++) {
                        retval+="<h2>"+contents[i].title+"</h2><svg width=\"200\" height=\"110\">" +
                                "<polygon points=\"0,5 100,5 100,105 0,105\" " +
                                "style=\"fill:none;stroke:black;stroke-width:1;\" />";
                        if(contents[i].max>contents[i].min && historySize>1) {
                                retval+="<polyline points=\"";
                                int start=MAX(0, ((float)(contents[i].data.size()))-historySize);
                                for(unsigned int j=start; j<contents[i].data.size(); j++) {
                                        retval+=std::to_string((j-start)*100/(contents[i].data.size()-start-1));
                                        retval+=",";
                                        retval+=std::to_string((-(contents[i].data[j]-contents[i].min)/
                                                        (contents[i].max-contents[i].min)+1)*100+5);
                                        retval+=" ";
                                }
                                retval+=std::string("\" style=\"fill:none;stroke:blue;stroke-width:2;\" />") +
                                        "<text x=\"100\" y=\"10\" fill=\"black\">" + std::to_string(contents[i].max) + 
                                        "</text><text x=\"100\" y=\"110\" fill=\"black\">" + 
                                        std::to_string(contents[i].min) + "</text></svg>";
                        }
                        if(contents[i].data.size()>0){
                                retval+=std::string("<p>currently: ")+
                                        std::to_string(contents[i].data[contents[i].data.size()-1])+"</p>";
                        }
                }
                return retval;
        }
        return "";
}
