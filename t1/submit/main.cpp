
#include <iostream>
#include "Editor.h"

int main(int argc, const char * argv[]){
    Editor editor;
    switch(argc){
        case 1: //ed
            editor.document.changecurrentline(0);
            break;
        case 2: //ed test.txt
            try {
                editor.open_file(argv[1]);
            } catch (const std::exception& e) {
                cout  << e.what() << endl;
                return 1;
            }
            break;
        default:
            cout << "Too many input arguments." << endl;

            return 1;
    }

        editor.loop();
   
    return 0;
}
