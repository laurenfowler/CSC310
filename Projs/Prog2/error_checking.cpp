//error checking
#include "includes.h"

bool check_file(string name);
int check_errors(int argc, char *argv[]){
    
    //handles no option being specified, will exit program if true
    if(argc == 1){
        cerr << "jtar: You must specify one of the options" << endl;
        cerr << "Try 'jtar --help' for more information" << endl;
        exit(0);
    }

    //checks for valid option
    string option = argv[1];
    
    if(option == "-cf"){
        if(argc < 4){
            cerr << "jtar: Invalid format" << endl;
            cerr << "Try 'jtar --help' for more information" << endl;
            return -1;
        }
        //check for valid files
        for(int i=3; i<argc; i++){
            bool exists = check_file(argv[i]);  
            if(!exists){
                cerr << "jtar: " << argv[i] <<" does not exist." << endl;
                return -1;
            }         
        }
        return 0;
    }
    else if(option == "-tf"){
        if(argc < 3){
            cerr << "jtar: Invalid format" << endl;
            cerr << "Try 'jtar --help' for more information" << endl;
            return -1;
        }
        bool exists = check_file(argv[2]);
        if(!exists){
            cerr << "jtar: " << argv[2] << " does not exist." << endl;
            return -1;
        }
        return 1;
    }
    else if(option == "-xf"){
        if(argc !=3){
            cerr << "jtar: Invalid format" << endl;
            cerr << "Try 'jtar --help' for more information" << endl;
            return -1;
        }
        bool exists = check_file(argv[2]);  
        if(!exists){
            cerr << "jtar: " << argv[2] <<" does not exist." << endl;
            return -1;
        }         
        return 2;
    }
    else if(option == "--help"){
        return 3;
    }
    else{
        cerr << "jtar: Invalid option (" << option << ")" << endl;
        cerr << "Try 'jtar --help' for more information" << endl;
        return -1;
    }
}

bool check_file(string name){

    struct stat s_struct;
    return(stat(name.c_str(), &s_struct) == 0);

}




