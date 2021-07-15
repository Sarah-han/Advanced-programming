#ifndef Editor_hpp
#define Editor_hpp
#include <stdio.h>
#include "Document.h"

using namespace document;
using namespace std;

class Editor{
public:
    document::Document document;
    string name    ;    
    Editor(){
        this->name = "";
    }
    void open_file(const string filename);
    void loop();
};

#endif 
