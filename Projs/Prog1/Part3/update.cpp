//perform transactions 
#include <iostream> 
#include <fstream>
#include <string>
#include <map>
#include <iterator>
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

enum TransactionType{Add, Delete, ChangeOnhand, ChangePrice};

struct TransactionRec{
    TransactionType ToDo;
    BookRec B;
};

//prototypes
map <unsigned int, int> read_master(fstream& file);
void perform_transactions(fstream& master, fstream& transact, fstream& new_master, fstream& error_file, map <unsigned int, int>& books);
bool isbn_exist(unsigned int isbn, map<unsigned int, int>& books);
void add(fstream& master, map <unsigned int, int>& books, TransactionRec& buffer);

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
    map <unsigned int, int> books = read_master(master_in);
    perform_transactions(master_in, transt_in, outfile, error_file, books);

    //remove copy.out file
    system("rm copy.out");

    return 0;

}

//read copy of master into map
map <unsigned int, int> read_master(fstream& file){
    map <unsigned int, int> books;
    BookRec buffer;
    int lines = 0;
    //int byte_offset = sizeof(BookRec); //double check this number

    while(file.read((char *) &buffer, sizeof(BookRec))){
        books[buffer.isbn] = lines * sizeof(BookRec);
        lines++;
    }

/*  cout << "check everything put in map" << endl;
    map <unsigned int, int> :: iterator it;
    for(it = books.begin(); it != books.end(); it++){
        cout << it -> first << " " << it -> second << endl;
    }
    cout << endl;*/

    return books;

}

//read transaction file and write to new_master
void perform_transactions(fstream& master, fstream& transact, fstream& new_master, fstream& error_file, map <unsigned int, int>& books){

    //revive file pointer
    master.clear();

    TransactionRec buffer;  
    int transact_num = 0;  
    map<unsigned int, int> :: iterator it;
    while(transact.read((char *) &buffer, sizeof(TransactionRec))){
        transact_num++;
        switch(buffer.ToDo){
            case(Add):
                //if isbn exists add error message to ERRORS, if not, add book to map and master.out
                if(isbn_exist(buffer.B.isbn, books)){
                    cerr << "Error in transaction number " << transact_num << ": cannot add---duplicate key " << buffer.B.isbn << endl;
                    //write it to the ERRORS file
                }
                else{
                    books[buffer.B.isbn] = books.size() * sizeof(BookRec);
                    //put file pointer at end of file
                    master.seekg(ios::end);
                    master.write((char*) &buffer.B, sizeof(BookRec));               
                }
                break;
            case(Delete):
                //if isbn doesnt exist, add error message to ERRORS, else, erase the book from the map
                //no need to do anything to the master file
                if(!isbn_exist(buffer.B.isbn, books)){
                    cerr << "Error in transaction number " << transact_num << ": cannot delete---no such key" << buffer.B.isbn << endl;
                }
                else{
                    books.erase(buffer.B.isbn);
                }
                break;
            case(ChangeOnhand):
                //if isbn exists, change the onhand amout 
                if(isbn_exist(buffer.B.isbn, books)){
                    //check for errors
                    int onhand_change = buffer.B.onhand;
                    BookRec tmp;
                    int offset =  books[buffer.B.isbn];
                    master.seekp(offset);
                    master.read((char *) &tmp, sizeof(BookRec));
                    //cout << tmp.isbn << endl;
                    cout << buffer.B.isbn << " " << tmp.isbn << endl;
                    //cout << tmp.onhand << endl;
                    tmp.onhand = tmp.onhand + onhand_change;
                    //cout << tmp.onhand << endl;
                    master.write((char*) &tmp, sizeof(BookRec));
                }
                else{

                }
                break;
            case(ChangePrice):
                //cout << isbn_exist(buffer.B.isbn, books) << endl;
                cout << "change price" << endl;
                break;
        }
     }   


}

/*void add(fstream& master, map <unsigned int, BookRec>& books, TransactionRec& buffer){
    
    
    map <unsigned int, BookRec>:: iterator it;
    
    //add buffer to map
    books[buffer.B.isbn] = 0; 
    
    for(it = books.begin(); it != books.end(); it++){
        cout << it -> first << " " << it -> second << endl;
    }

    //set byte offset of books at buffer.B.isbn
    it = books.find(buffer.B.isbn);
    it++;
    books[buffer.B.isbn] = it -> second;

    //fix all other byte offsets
    it = books.find(buffer.B.isbn);
    it++;
    while(it != books.end()){
        it -> second = (it -> second) +  sizeof(BookRec);
        it++;
    }

    cout << endl;
    cout << "after reset" << endl; 
    for(it = books.begin(); it != books.end(); it++){
        cout << it -> first << " " << it -> second << endl;
    }


}
*/

//function to check whether isbn exists or not
bool isbn_exist(unsigned int isbn, map<unsigned int, int>& books){
    //map <int, int>:: iterator it;
    if(books.find(isbn) == books.end()){
        return 0;
    }
    else{
        return 1;    
    }
}
