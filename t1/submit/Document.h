#ifndef Document_hpp
#define Document_hpp
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

namespace document{
class Document {
public:
    vector <string> lines       ;
    int    currentline;
    Document(){
        this->currentline = 1;
    }

    void openfile(const string filename);
    void savatofile  (const string filename);
    void deletline(const int i);
    int  checkcurrentline(              );
    string checkline(const int i  );
    void   changeline(const int i, const string line);
    void changecurrentline(const int line);
    void writeline(const int i, const string line);
    int linesize();
    bool findword(const int i, string word);  
};
};

#endif 
