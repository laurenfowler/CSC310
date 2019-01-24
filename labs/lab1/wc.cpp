#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
//program to simulate the wc command

//prototypes
string read_file_into_string(string filename);

int main(int argc, char* argv[]){
    //get file name and open
    string file = argv[argc-1];
    fstream infile(file.c_str(), ios::in); 
    string arg;
    //put file into string
    string total = read_file_into_string(file);

    bool c_flag = 0;
    bool l_flag = 0;
    bool w_flag = 0;

    //turn on flags
    for(int i=1; i<argc; i++){
        arg = argv[i];
        if(arg == "-c"){
            c_flag = 1;
        }
        if(arg == "-l"){
            l_flag = 1;
        }   
        if(arg == "-w"){
            w_flag = 1;
        }
    }

    string line;
    int line_count = 0;
    int word_count = 0;
    int byte_count = 0;

    //count number of lines
    while(getline(infile, line)){
        line_count++;
    }

    //count bytes and words
    for(int i=0; i<total.length(); i++){
       byte_count++;
       if(total[i] == ' ' || total[i] == '\n'){
            word_count++;
        }
    }

    bool add_tab = 0;

    //handle parameters
    if(l_flag){
        cout << line_count;
        add_tab = 1;
    }
    if(w_flag){
        if(add_tab){
            cout << '\t';
        }   
        cout << word_count;
    }
    if(c_flag){
        if(add_tab){
            cout << '\t';
        }
        cout << byte_count;
    }
    if(l_flag || c_flag || w_flag){
        cout << " " << file << endl;    
    }
    else{
        cout << line_count << '\t' << word_count << '\t' << byte_count << " " << file << endl;
    }
    
    return 0;
}

//function that takes whole file and puts it into a string
string read_file_into_string(string file){
    ifstream infile(file.c_str());
    ostringstream long_string;
    char ch;

    while(long_string && infile.get(ch)){
        long_string.put(ch);
    }
    return long_string.str();
}

