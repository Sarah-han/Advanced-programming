
#include "Document.h"

using namespace document;
using namespace std;

void Document::openfile(const string filename){
    ifstream Filetoopen;
    Filetoopen.open(filename);
    if (Filetoopen.is_open()){
        string line;
        while(getline(Filetoopen, line)){
            this->lines.push_back(line);
        }
    } else {
        throw "File Not Found";
    }
    Filetoopen.close();
}

void Document::savatofile(const string filename){
    ofstream Filetoopen;
    Filetoopen.open (filename);
    for (int i = 0; i < this->lines.size(); i++){
        Filetoopen << this->lines[i] << "\n";
    }
    Filetoopen.close();
}

void Document::changecurrentline(const int line){  this->currentline = line;}

int Document::checkcurrentline(){   return this->currentline;}

string Document::checkline(const int i){return this->lines[i];}

void Document::changeline(const int i, const string line){ this->lines[i] = line;}

void Document::writeline(const int i, const string line){
    if (i > this->lines.size()){
        throw "Document Insert Failed";
    }
    this->lines.insert(lines.begin() + i, line);
}

int Document::linesize(){ return (int)this->lines.size();}

void Document::deletline(const int i){
    if (i >= this->lines.size()){
        throw "Failed to delete";
    }
    this->lines.erase(lines.begin() + i);
}

bool Document::findword(const int i, string word){
    string s1 = this->lines[i];
    size_t found = s1.find(word);
    if(found != std::string::npos)
        return 1;
    return 0;
}
