//generates .out files
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

enum TransactionType{Add, Delete, ChangeOnhand, ChangePrice};

typedef char String[25];
struct BookRec{
    unsigned int isbn;
    String name;
    String author;
    int onhand;
    float price;
    String type;
};

struct TransactionRec{
    TransactionType ToDo;
    BookRec B;
};



int main(){

    fstream infile("new_transact.dat", ios::in);
    fstream outfile("test_cases.out", ios::out | ios::binary);

    TransactionRec buffer;
    char temp;
    string todo;
    TransactionType tmp;

    while(!infile.eof()){
        infile >> todo;
        if(todo == "Add"){
            buffer.ToDo = Add;
        }
        if(todo == "Delete"){
            buffer.ToDo = Delete;
        }
        if(todo == "ChangeOnhand"){
            buffer.ToDo = ChangeOnhand;
        }       
        if(todo == "ChangePrice"){
            buffer.ToDo = ChangePrice;
        }
        infile >> temp;
        infile >>buffer.B.isbn;
        infile >> temp; //reads in | to temp 
        infile.getline(buffer.B.name, 25, '|'); //reads until 25 or deliminator, automatically reads | so no need to use temp
        infile.getline(buffer.B.author, 25, '|');
        infile >> buffer.B.onhand >> temp >>  buffer.B.price;
        infile >> temp;
        infile.getline(buffer.B.type, 25, '\n'); //reads until 25 or endline character
    }

    outfile.write((char *) &buffer, sizeof(TransactionRec));
    return 0;

}
