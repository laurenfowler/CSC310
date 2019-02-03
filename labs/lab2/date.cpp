#include <string>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

int translate_canon(string date);

int main(){
   
    string date = "October 12, 2016";
    int new_date = translate_canon(date);
    cout << new_date << endl;
    return 0;
}

int translate_canon(string date){
    
    string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
    map <string, int> months_map;
    int x = 1;
    //populate map
    for(int i = 0; i < 12; i++){
        months_map[months[i]] = x;
        x++;
    }

    string month;
    char tmp;
    int get_date, year;

    stringstream ss;   
    ss.str(date);
    //read in variables
    ss >> month;
    ss >> get_date;
    ss >> tmp;
    ss >> year;

    string canonical = to_string(months_map[month])+ to_string(get_date) + to_string(year);
    
    return stoi(canonical);
    

}
