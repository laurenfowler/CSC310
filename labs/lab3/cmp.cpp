//the cmp linux utility
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//prototypes
void error_checking(int argc, char *argv[], fstream &file1, fstream &file2,  bool &cflag, bool &nflag, int &ignore);

int main(int argc, char *argv[]){

    bool cflag, nflag;
    int ignore;

    fstream file1 ((argv[argc-2]), ios::in);
    fstream file2 ((argv[argc-1]), ios::in); 
    error_checking(argc, argv, file1, file2, cflag, nflag, ignore);

    return 0;
}

void error_checking(int argc, char *argv[], fstream &file1, fstream &file2,  bool &cflag, bool &nflag, int &ignore){

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

    string arg;
    if(argc == 4){
        arg = argv[1];
        if(arg == "-c"){
            cflag = true;
        }
        else if(arg == "-N"){
            cerr << "cmp: invalid bytes number" << endl;
            exit(0);
        }
        else{
            cerr << "cmp: illegal option " << endl;
            exit(0);
        }
    }
    else if(argc == 5){
        arg = argv[1];
        string arg2 = argv[2];
        if(arg == "-N"){
            nflag == true;
            //check if arg2 is digit else throw error
            if(isdigit(arg2[0])){
                ignore = atoi(argv[2]);
            }
            else{
                cerr << "cmp: illegal byte number" << endl;
                exit(0);
            }
        }
        else{
            if(arg == "-c"){
                cerr << "cmp: illegal number of parameters" << endl;
            }
            else{
                cerr << "cmp: illegal options" << endl;
            }
            exit(0); 
        }
    }
    else{
        arg = argv[1];
        if(arg == "-c"){
            cflag = true;
            if (argv[2] == "-N"){
                nflag = true;
                //check digit
            }
            else{
                cerr << "cmp: illegal option" << endl;
                exit(0);
            }
        }
        else if(arg == "-N"){
            nflag = true;
            string arg2 = argv[2];
            if(isdigit(arg2[0]){
                ignore = atoi(argv[2]);
            }
            else{
                cerr << "cmp: illegal byte number" << endl;
                exit(0);
            }
        }

    }
}
