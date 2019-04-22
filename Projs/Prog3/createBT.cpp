#include <iostream>
#include <fstream>
#include "album.h"
#include "btree.h"
#include <string>

int main(int argc, char *argv[]){

    //open album file
    fstream infile;
    infile.open(argv[1], ios::in);

    //initalize b-tree
    BTree btree;
    btree.writeHeader(argv[2]); //initalize root and dummy nodes

    Album tmp;

    //was reading in extra time so refactored loop
    infile >> tmp;
    while(!infile.eof()){
        btree.insert(tmp);
        infile >> tmp;
    }
    
    //btree.printTree();
    

    return 0;
}
