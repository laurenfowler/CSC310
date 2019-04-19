#include <iostream>
#include <fstream>
#include "album.h"
#include "btree.h"
#include <string>

int main(int argc, char *argv[]){

    fstream infile;
    infile.open(argv[1], ios::in);

    Album tmp;

    while(!infile.eof()){
        infile >> tmp;
        cout << tmp << endl;
    }

    return 0;
}
