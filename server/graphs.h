#ifndef _GRAPHS_H_
#define _GRAPHS_H_

#include "pages.h"

class Graph {
public:
        std::string title;
        float min=0, max=0;
        std::vector<float> data;
};

class Graphs : public DynamicPage {
protected:
        std::vector<Graph> contents;
        int historySize=100;
public:
        virtual std::string getContents(std::string URL, std::map<std::string, std::string> formFields);
};

#endif
