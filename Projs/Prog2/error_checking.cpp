//error checking
//also turns on flags for main program
#include "includes.h"
#include "prototypes.h"

void check_errors(int argc, char *argv[]){
    
    //handles no option being specified, will exit program if true
    if(argc == 1){
        cerr << "jtar: You must specify one of the options" << endl;
        cerr << "Try 'jtar --help' for more information" << endl;
        exit(0);
    }

    //checks for valid option
    string option = argv[1];
    
    if(option == "-cf"){
        cout << "-cf chosen" << endl; 
        if(argc < 4){
            cerr << "jtar: Invalid format" << endl;
            cerr << "Try 'jtar --help' for more information" << endl;
            exit(0);
        }
        //check for valid files
        for(int i=3; i<argc; i++){
            bool exists = check_file(argv[i]);  
            if(!exists){
                cerr << "jtar: " << argv[i] <<" does not exist." << endl;
                exit(0);
            }         
        }
    }
    else if(option == "-tf"){
        cout << "-tf chosen" << endl;
        if(argc < 3){
            cerr << "jtar: Invalid format" << endl;
            cerr << "Try 'jtar --help' for more information" << endl;
            exit(0);
        }
        bool exists = check_file(argv[2]);
        if(!exists){
            cerr << "jtar: " << argv[2] << " does not exist." << endl;
            exit(0);
        }
    }
    else if(option == "-xf"){
        cout << "-xf chosen" << endl;
        if(argc < 3){
            cerr << "jtar: Invalid format" << endl;
            cerr << "Try 'jtar --help' for more information" << endl;
            exit(0);
        }
        //check for valid files
        for(int i=3; i<argc; i++){
            bool exists = check_file(argv[i]);  
            if(!exists){
                cerr << "jtar: " << argv[i] <<" does not exist." << endl;
                exit(0);
            }         
        }

    }
    else if(option == "--help"){
        cout << "--help chosen" << endl;
    }
    else{
        cerr << "jtar: Invalid option (" << option << ")" << endl;
        cerr << "Try 'jtar --help' for more information" << endl;
        exit(0);
    }
}

bool check_file(string name){

    struct stat s_struct;
    return(stat(name.c_str(), &s_struct) == 0);

}




