#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

string compress(string input);
string uncompress(string input);

int main(){
    string myInput = "93 93 93 93 92 91 91 94 94 94 94 94 95 95 95 73 73 73 73 73 73 73";
    string compact = compress(myInput);
    cout << compact << endl;
    cout << uncompress(compact) << endl;

}

string compress(string input){

    int curr, prev, count;
    string output, tmp_string, tmp;

    //convert to stringstream
    stringstream ss;
    ss.str(input);

    //reads in first integer
    ss >> prev;
    tmp_string = to_string(prev) + " ";
    count = 1;


    //reads in integers, ignoring white space
    while(ss >> curr){
        if(curr == prev){
            tmp_string = tmp_string + to_string(curr) + " ";
            count++;
        }
        else{
            if(count < 4){
                output += tmp_string;
            }
            else{
                //pad with 0's if less than 10, else just convert to string
                if(count < 10){
                    tmp = to_string(count);
                    tmp.insert(0, "0");
                }
                else{
                    tmp = to_string(count);
                }
                output = output + "ff " + to_string(prev) + " "+ tmp + " ";    
            } 
            //reset vals
            count = 1;
            prev = curr;
            tmp_string = to_string(curr) + " ";
        }

    }
    //get last of input
    if(count < 4){
        output += tmp_string;
    }
    else{
        //pad with 0's if less than 10, else just convert to string
        if(count < 10){
            tmp = to_string(count);
            tmp.insert(0, "0");
        }
        else{
            tmp = to_string(count);
        }
        output = output + "ff " + to_string(prev) + " "+ tmp + " ";    
    } 
    
    return output;

}

string uncompress(string input){

    string output;
    int curr, num, times;

    //convert to stringstream
    stringstream ss, tmp;
    ss.str(input);

    //read in as hex so file pointer wont die
    while(ss >> hex >> curr){
        //this indicates ff
        if(curr == 255){
            ss >> dec >> num;
            ss >> times;
            for(int i=0; i<times; i++){
                output = output + to_string(num) + " ";
            }
        }
        else{
            //go back and read in var again as decimal
            ss.seekg(-2, ios::cur);
            ss >> dec >> curr;
            output = output + to_string(curr) + " ";
        }
    }

    return output;

}


