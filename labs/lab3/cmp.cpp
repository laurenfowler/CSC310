//the cmp linux utility
#include <iostream>
#include <fstream>
using namespace std;

//prototypes

int main(int argc, char *argv[]){

    fstream file1 ((argv[argc-2]), ios::in);
    fstream file2 ((argv[argc-1]), ios::in); 

    //check for too many command line arguments
    if(argc > 6 || argc < 3){
       cerr << "cmp: illegal number of parameters" << endl;
       exit(0);
    }


    //check if files opened
    if(file1.fail()){
        cerr << "cmp: " << argv[argc-2] << ": no such file" << endl;
        exit(0);
    }
    if(file2.fail()){
        cerr << "cmp: " << argv[argc-1] << ": no such file" << endl;
        exit(0);
    }


    return 0;
}

