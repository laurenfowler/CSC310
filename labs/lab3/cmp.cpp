//the cmp linux utility
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
using namespace std;

//prototypes
void error_checking(int argc, char *argv[], fstream &file1, fstream &file2,  bool &cflag, bool &nflag, int &ignore);

int main(int argc, char *argv[]){

    bool cflag, nflag;
    int ignore;

    //check if either files are directories before opening
    struct stat s_struct;
    stat(argv[argc-2], &s_struct); //calls stat on file1 
    if(S_ISDIR(s_struct.st_mode)){
        cerr << "cmp: " << argv[argc-2] << " is a directory" << endl;
        exit(0);
    }

    stat(argv[argc-1], &s_struct); //calls stat on file2
    if(S_ISDIR(s_struct.st_mode)){
        cerr << "cmp: " << argv[argc-1] << " is a directory" << endl;
        exit(0);
    }


    //opens files if neither are directories
    fstream file1 ((argv[argc-2]), ios::in);
    fstream file2 ((argv[argc-1]), ios::in); 
    //error checks
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
    //handles 4 arguements
    if(argc == 4){
        arg = argv[1];
        if(arg == "-c"){
            cflag = true;
        }
        else if(arg == "-N"){
            cerr << "cmp: invalid byte value" << endl;
            exit(0);
        }
        else{
            cerr << "cmp: illegal option " << endl;
            exit(0);
        }
    }
    //handles 5 arguements
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
                cerr << "cmp: illegal byte value" << endl;
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
        //when there are 6 arguements
        arg = argv[1];
        if(arg == "-c"){
            cflag = true;
            string arg2 = argv[2];
            if (arg2  == "-N"){
                nflag = true;
                //check if digit else throw error
                string arg3 = argv[3];
                if(isdigit(arg3[0])){
                    ignore = atoi(argv[3]); 
                }
                else{
                    cerr << "cmp: illegal byte value" << endl;
                    exit(0);
                }
            }
            else{
                cerr << "cmp: illegal option" << endl;
                exit(0);
            }
        }
        else if(arg == "-N"){
            nflag = true;
            string arg2 = argv[2];
            if(isdigit(arg2[0])){
                ignore = atoi(argv[2]);
                string arg3 = argv[3];
                if(arg3 == "-c"){
                    cflag = true;
                }
                else{
                    cerr << "cmp: illegal option" << endl;
                    exit(0);
                }
            }
            else{
                cerr << "cmp: illegal byte number" << endl;
                exit(0);
            }

        }
    }
}



