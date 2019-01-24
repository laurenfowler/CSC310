//read a text file and create binary file records of type BookRec
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef char String[25];
struct BookRec{
    unsigned int isbn;
    String name;
    String author;
    int onhand;
    float price;
    String type;
}; 

int main(int argc, char *argv[]){

    //read in textfile from command line arguements
    string file = argv[1];

    fstream infile(file, ios::in);
    fstream outfile("library.out", ios::out | ios:: binary);

    BookRec buffer;
    char temp;
    long check_isbn;
    long prev_isbn = 0;
    int lines;
    bool write = 1; //can the line be written to file


    while(infile >> check_isbn){
        lines++;
        buffer.isbn = check_isbn;
        infile >> temp; //reads in | to temp 
        infile.getline(buffer.name, 25, '|'); //reads until 25 or deliminator, automatically reads | so no need to use temp
        infile.getline(buffer.author, 25, '|');
        infile >> buffer.onhand >> temp >>  buffer.price;
        infile >> temp;
        infile.getline(buffer.type, 25, '\n'); //reads until 25 or endline character

        //check for errors
        if(check_isbn < 1){
            cerr << "Illegal ISBN number on line " << lines << " of data file -- record ignored" << endl;
            write = 0;   
        }

        // && write keeps multiple errors from appearing,
        // will only print out first error that makes input invalid

        if(buffer.onhand < 0 && write){
            cerr << "Negative amount onhand on line " << lines << "of data file -- record ignored" << endl;
            write = 0;
        }

        if(buffer.price < 0 && write){
            cerr << "Negative price on line " << lines << " of data file -- record ignored" << endl;
        }   

        if(check_isbn <= prev_isbn && write){
            cerr << "ISBN number out of sequence on line " << lines << " of data file" << endl;
        }
        else if(write){
            //sets the current isbn to the previous isbn
            //only if not proven illegal/ignored after all checks
            prev_isbn = check_isbn;
        }

        if(write){
            outfile.write((char *) &buffer, sizeof(BookRec)); //writes the line to library.out
        }
        
        //reset bool
        write = 1;

    }

    return 0;
} 






