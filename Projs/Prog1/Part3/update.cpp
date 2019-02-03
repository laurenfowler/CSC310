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
void perform_transactions(int total_bytes, fstream& master, fstream& transact, fstream& error_file, fstream& new_master, map <unsigned int, int>& books);
bool isbn_exist(unsigned int isbn, map<unsigned int, int>& books);

int main(int argc, char* argv[]){

    //read in command line arguments
    string master = argv[1];    
    string transaction = argv[2];
    string new_master = argv[3];

    //create copy of master
    string command = "cp " + master + " copy.out";
    system(command.c_str());

    //open files for input/output
    fstream master_in("copy.out",  ios::in | ios::out| ios:: binary); //ios::out is crucial to be able to write new stuff  
    fstream transt_in(transaction.c_str(), ios::in | ios:: binary);
    fstream outfile(new_master.c_str(), ios::out| ios:: binary);
    fstream error_file("ERRORS", ios::out);

    //read in copy.out and create map container
    map <unsigned int, int> books = read_master(master_in);
    int total_bytes = books.size() * sizeof(BookRec);
    perform_transactions(total_bytes, master_in, transt_in, error_file, outfile, books);

    //close
    master_in.close();
    transt_in.close();
    error_file.close();
    outfile.close();

    //remove copy.out file
    system("rm copy.out");

    return 0;

}

//read copy of master into map
map <unsigned int, int> read_master(fstream& file){
    map <unsigned int, int> books;
    BookRec buffer;
    int lines = 0;
    
    while(file.read((char *) &buffer, sizeof(BookRec))){
        books[buffer.isbn] = lines * sizeof(BookRec);
        lines++;
    }

    return books;

}

//read transaction file and write to new_master
void perform_transactions(int total_bytes, fstream& master, fstream& transact, fstream& error_file, fstream& new_master,  map <unsigned int, int>& books){

    //revive master file pointer
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
                    string msg = "Error in transaction number " + to_string(transact_num) + ": cannot add---duplicate key " + to_string(buffer.B.isbn);
                    //write it to the ERRORS file
                    error_file << msg << endl;
                }
                else{
                    //cout << "adding " << buffer.B.name << " isbn " << buffer.B.isbn;
                    books[buffer.B.isbn] = total_bytes;
                    //cout << " hopfully to " << total_bytes;
                    //update total bytes
                    total_bytes = total_bytes + sizeof(BookRec);
                    master.clear();
                    master.seekp(books[buffer.B.isbn]);
                    master.clear();
                    //cout << " " << buffer.B.author;
                    //BookRec tmp;
                    //master.read((char *) &tmp, sizeof(BookRec));
                    //cout << tmp.author << endl;
                    //cout << " but actually to pos " <<  master.tellp() << endl;
                    master.write((char*) &buffer.B, sizeof(BookRec));  
                    master.clear();   
                    //cout << "master.clear() bring file pointer to " << master.tellp() << endl;          
                }
                break;
            case(Delete):
                //if isbn doesnt exist, add error message to ERRORS, else, erase the book from the map
                //no need to do anything to the master file
                if(!isbn_exist(buffer.B.isbn, books)){
                    string msg =  "Error in transaction number " + to_string(transact_num) + ": cannot delete---no such key" + to_string(buffer.B.isbn);
                    error_file << msg << endl;
                }
                else{
                    //cout << "deleting book" << endl;
                    books.erase(buffer.B.isbn);
                }
                break;
            case(ChangeOnhand):
                //if isbn exists, change the onhand amout 
                if(isbn_exist(buffer.B.isbn, books)){
                   // cout << "changing onhand" << endl;
                    //check for errors
                    int onhand_change = buffer.B.onhand;
                    BookRec tmp;
                    int offset =  books[buffer.B.isbn];
                    master.seekp(offset);
                    master.read((char *) &tmp, sizeof(BookRec));
//                    cout << "before " << tmp.onhand << endl;
                    tmp.onhand = tmp.onhand + onhand_change;
//                    cout << "after " << tmp.onhand << endl;
                    if(tmp.onhand < 0){
                        string msg =  "Error in transaction number " + to_string(transact_num) + " count == " + to_string(tmp.onhand) + " for key " + to_string(tmp.isbn);
                        error_file << msg << endl;
                        tmp.onhand = 0;
                    }
                    //go back to original offset so wont write over next book record
                    master.seekp(offset);
                    master.write((char*) &tmp, sizeof(BookRec));
                }
                else{
                    string msg = "Error in transaction number " + to_string(transact_num) + " cannot change count--no such key " + to_string(buffer.B.isbn);
                    error_file << msg << endl;
                }
                break;
            case(ChangePrice):
                if(isbn_exist(buffer.B.isbn, books)){
                    //cout << "changing price" << endl;
                    int offset =  books[buffer.B.isbn];
                    master.seekp(offset);
                    master.write((char *) &buffer.B, sizeof(BookRec));
                }
                else{
                    string msg =  "Error in transaction number " + to_string(transact_num) + " cannot change price--no such key " + to_string(buffer.B.isbn);
                    error_file << msg << endl;
                }
                break;
        }
    }    
    
    //write to new_master
    BookRec buffer1;
    for(it = books.begin(); it != books.end(); it++){
        master.clear();
        master.seekp(it -> second);
        master.read((char *) &buffer1, sizeof(BookRec));
        new_master.write((char *) &buffer1, sizeof(BookRec));
    }

  
}

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
