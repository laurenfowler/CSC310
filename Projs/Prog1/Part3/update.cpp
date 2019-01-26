//perform transactions 
#include <iostream> 
#include <fstream>
#include <string>
#include <map>
using namespace std;

//prototypes
map <int, int> read_master(fstream& file);
void perform_transactions(fstream& master, fstream& transact, fstream& new_master, fstream& error_file, map <int, int> books);

typedef char String[25];
struct BookRec{
    unsigned int isbn;
    String name;
    String author;
    int onhand;
    float price;
    String type;
};

enum TransactionType{Add, Delete, ChangeOnhand, ChangePrice};

struct TransactionRec{
    TransactionType ToDo;
    BookRec B;
};

int main(int argc, char* argv[]){

    //read in command line arguments
    string master = argv[1];    
    string transaction = argv[2];
    string new_master = argv[3];

    //create copy of master
    string command = "cp " + master + " copy.out";
    system(command.c_str());

    //open files for input/output
    fstream master_in("copy.out",  ios::in | ios:: binary);   
    fstream transt_in(transaction.c_str(), ios::in | ios:: binary);
    fstream outfile(new_master.c_str(), ios::out| ios:: binary);
    fstream error_file("ERRORS", ios::out);

    //read in copy.out and create map container
    map <int, int> books = read_master(master_in);
    perform_transactions(master_in, transt_in, outfile, error_file, books);

    //remove copy.out file
    system("rm copy.out");

    return 0;

}

//read copy of master into map
map <int, int> read_master(fstream& file){
    map <int, int> books;
    BookRec buffer;
    int lines = 1;
    int byte_offset = 87; //double check this number

    //unrolling the loop makes the runtime faster
    while(file.read((char *) &buffer, sizeof(BookRec))){
        books[buffer.isbn] = byte_offset*lines;
        file.read((char *) &buffer, sizeof(BookRec));
        lines++;
        books[buffer.isbn] = byte_offset*lines;
        lines++;
    }

}

//read transaction file and write to new_master
void perform_transactions(fstream& master, fstream& transact, fstream& new_master, fstream& error_file, map <int, int> books){

    TransactionRec buffer;    
    while(transact.read((char *) &buffer, sizeof(TransactionRec))){
        cout << buffer.ToDo << endl;
        cout << buffer.B.isbn << endl; 
    }   


}



//need a function to check whether isbn exists or not

