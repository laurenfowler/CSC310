//In class lab on file pointers
#include <fstream>
#include <iostream>
using namespace std;

int calc_sum(istream& file);

int main(){

    ifstream infile("input_file");
    int total = calc_sum(infile); //infile morphs to istream when passed, dont put & in parameter bc we do not care where the address is in RAM
    cout << total << endl;
    return 0;
}

int calc_sum(istream& file){  //& makes it pass by reference
    
    int total = 0;
    int num;
    char ch;
    while(!file.eof()){
        file >> num; //reads file into num

        if(file.fail()){
            file.clear();
            file >> ch;
            if(ch != ','){
                return -1;
            }
        }
        else{
            total = total + num;
        }
    }
    return total;


}
