
#include "Editor.h"

using namespace std;

static bool realnumber(const string& s){
    string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void Editor::open_file(const string filename){

    this->name = filename;
    this->document.openfile(this->name);
}


void Editor::loop(){
    string markedline;
    getline(cin, markedline);
	
    while (markedline.at(0) != 'q'){
       
        if(realnumber(markedline)){
            int i = stoi(markedline);
            if (i <= 0 || i > this->document.linesize()){cout << "?" <<endl;}
            this->document.changecurrentline(i);
        }
        
        else if(markedline.at(0) == '+' && realnumber(markedline.substr(1))){
            int i = this->document.checkcurrentline() + stoi(markedline.substr(1));
            cout << this->document.linesize() << endl;
            if(i > this->document.linesize()){cout << "?" <<endl;}
            this->document.changecurrentline(i);
        }
        
        else if(markedline.at(0) == '-' && realnumber(markedline.substr(1))){
            int i = this->document.checkcurrentline() - stoi(markedline.substr(1));
            if(i <= 0){cout << "?" <<endl;}
            this->document.changecurrentline(i);
        }
        
        else if(markedline.at(0) == '$'){
            this->document.changecurrentline(this->document.linesize());
        }
        
        else if(markedline.at(0) == 'a'){
            int i = this->document.checkcurrentline();
            string tempLine;
            getline(cin, tempLine); 
            while(tempLine.at(0) != '.'){ 
                try {
                    this->document.writeline(i, tempLine);
                    i++;
                } catch(const exception& e) {
                    throw e;
                }
                getline(cin, tempLine);
            }
;
        }
        
        else if(markedline.at(0) == 'i'){
            int newcurr = 0;
            int i = this->document.checkcurrentline() - 1;
            string tempLine;
            getline(cin, tempLine);
            while(tempLine.at(0) != '.'){
                this->document.writeline(i++, tempLine);
                newcurr++;
                getline(cin, tempLine);
            }
            this->document.changecurrentline(newcurr); 
        }
        
        else if(markedline.at(0) == 'c'){
            int i = this->document.checkcurrentline() - 1;
            string tempLine;
            getline(cin, tempLine);
            while(tempLine.at(0) != '.'){
                this->document.writeline(i++, tempLine);
                getline(cin, tempLine);
            }
            this->document.deletline(i);
        }
        
        else if(markedline.at(0) == 'd'){
            int i = this->document.checkcurrentline() - 1;
            try {
                this->document.deletline(i);
                this->document.changecurrentline(i++);
            } catch(const std::exception& e) {
                throw e;
            }
            this->document.checkcurrentline();
        }
        
        else if(markedline.at(0) == '/'){
            std::string s = markedline.substr(1, markedline.length() - 2);
            bool intxt = true;
            cout << s << endl;
            int i = 0;
            int j = this->document.checkcurrentline();
            for(i = this->document.checkcurrentline(); i < this->document.linesize(); i++){
                intxt = this->document.findword(i, s);
                if(intxt){
                    j = i;
                    break;
                }
            }
            for (i = 0; i <= this->document.checkcurrentline() - 1; i++){
                bool intxt = this->document.findword(i, s);
                if(intxt){
                    j = i;
                    break;
                }
            }
            this->document.changecurrentline(j + 1);
        }
        
      
        
        else if(markedline.at(0) == 's'){
            std::vector<std::string> vector;
			std::string str=markedline.substr(2);
			str.pop_back();
			int i = 0;
			while (str.at(i) != '/'){
			i++;
			}
			if (i - 1 == 0){
				vector.push_back(" ");
			} else {
				vector.push_back(str.substr(0, i));
			}
			if (markedline.substr(2).length() - 1 == i + 1) {
				vector.push_back(" ");
			} else {
			vector.push_back(str.substr(i + 1, str.length() - 1));
			}
            for (int j = 0; j < vector.size(); j++){
                cout << vector[j] << endl;
            }
            
            int k= this->document.checkcurrentline() - 1;
            std::string line = this->document.checkline(k);
            string Helpingline;
            size_t pos = line.find(vector[0]);
            if (pos == string::npos){
                cout << '\'' << vector[0] << '\'' << " is not in line " << this->document.checkcurrentline() << endl;
            } else {
                size_t len = vector[0].length();
                string Helpingline = line.replace(pos, len, vector[1]);
                this->document.changeline(k, Helpingline);
            }
            
        }
        
        else if(markedline.at(0) == 'j'){
            int i = this->document.checkcurrentline() - 1;
            string currline = this->document.checkline(i);
            string next = this->document.checkline(i + 1);
            string connectedline = currline + " " + next;
            this->document.changeline(i, connectedline);
            this->document.deletline(i + 1);
        }
        
        else if(markedline.at(0) == 'w'){this->document.savatofile(markedline.substr(2));}
        
        else if(markedline.at(0) == 'q'){break;}
        
        else{
            cout << "Unrecognized Input Argument " << '\'' << markedline << '\'' << endl;
        }
        getline(cin, markedline);
    }
}

