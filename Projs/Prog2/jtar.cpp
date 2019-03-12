//jtar software
#include "file.h"
#include "prototypes.h"

int main(int argc, char *argv[]){

    int type = check_errors(argc,  argv);

    //swtich statement to handle request type
    switch(type){
        //error was found 
        case -1:
            exit(0);
            break;
        case 0: 
            cout << "-cf chosen" << endl;
            break;
        case 1:
            cout << "-tf chosen" << endl;
            break;
        case 2:
            cout << "-xf chosen" << endl;
            break;
        case 3: 
            system("cat help");
            break;

    }


    return 0;
}
