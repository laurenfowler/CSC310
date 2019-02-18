//the cmp linux utility
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
using namespace std;

//prototypes
void error_checking(int argc, char *argv[], fstream &file1, fstream &file2,  bool &cflag, bool &nflag, int &ignore);
void cmp(fstream &file1, fstream &file2, bool &cflag, bool &nflag, int &ignore, string f1, string f2);
bool compare(char ch1, char ch2);

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

    //call cmp
    cmp(file1, file2, cflag, nflag, ignore, (string) argv[argc-2], (string) argv[argc-1]);


    return 0;
}

void cmp(fstream &file1, fstream &file2, bool &cflag, bool &nflag, int &ignore, string f1, string f2){

    char ch1, ch2; //where file will be read in
    int bytes = 0;
    int lines = 1; 

    //ignore certian # of bytes
    if(nflag){
        bytes = ignore;
        file1.seekg(ignore);
        file2.seekg(ignore);
    }

    while(file1.get(ch1)){
        file2.get(ch2);
        cout << ch1 << " " << ch2 << endl;
        //increment byte count
        bytes++;

        //check for eof
        if(file1.eof()){
            cout << "EOF reached on " << f1 << endl; 
            exit(0);
        }
        if(file2.eof()){
            cout << "EOF reached on " << f2 << endl;
            exit(0);
        }

        //increments line count
        if(ch1 == '\n' && ch2 == '\n'){
            lines++;
        }
        
        //compare characters       
        bool same = compare(ch1, ch2);
        if(!same){
            //oct converts 
            if(cflag){
                cout << f1 << " " << f2 << "differ: char " << bytes << ", line " << lines << " is ";
                cout << oct << (int)ch1 << " " << ch1 << " " << oct << (int) ch2 << " " << ch2 << endl;
            }
            else{
                cout << f1 << " " << f2 << " differ: byte " << bytes << ", line " << lines << endl;
            }
            exit(0);
        }
    }

}

//compares 2 characters
bool compare(char ch1, char ch2){

    if(ch1 == ch2){
        return true;
    }
    return false;
}

//checks for all errors and sets up -c -n and # of bytes to ignore option if in paramters
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
            nflag = true;
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



