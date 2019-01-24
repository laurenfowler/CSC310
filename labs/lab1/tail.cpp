#include <iostream>
#include <string>
#include <fstream>
using namespace std;
//program to print -n lines from the bottom of the file

int main(int argc, char* argv[]){

    //declare variables
    string lines;
    int num_lines, length;
    string file; 
    char ch;
    int stop = 0;

    //read in number of lines and remove - 
    //then convert to an int
    lines = argv[1];
    num_lines = stoi(lines.substr(1));

    //without this it will print 1 line
    if(num_lines == 0){ 
        return 0;
    }

    //get file arguement and open the file
    file = argv[2];
    fstream infile(file.c_str(), ios::in);

    //get beginning pointer
    infile.seekg(0, ios::beg);
    long start_ptr = infile.tellg();

    //move to end of file
    infile.seekg(-2, ios::end);

    int i = -1;
    //loop to proper pos
    while(stop < num_lines){
        infile.seekg(-2, ios::cur); //go back by -2 to skip over the character you have already read
        if(infile.tellg() == start_ptr){  //need this because if we loop and go past the beginning of the file, the file pointer dies
            break;
        }
        infile.get(ch);
        if(ch == '\n'){
            stop++;
        }
    }

    //print out file
    while(infile.get(ch)){
        cout.put(ch);
    }

    infile.close();   

    return 0;
}
