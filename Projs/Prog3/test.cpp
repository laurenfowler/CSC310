#include <iostream>
#include <fstream>
#include "album.h"
#include "btree.h"
#include <string>

int main(int argc, char *argv[]){

    BTree test; 

    //test reset function
    test.reset(argv[2]);
    test.writeHeader(argv[2]);



}
