#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <map>
#include <sstream>
#include <iterator>
#include <stdio.h>
using namespace std;

class Song {
public:
  string title;
  int time;
  int track;      // Primary key
  bool operator < (Song another) const { return title < another.title;}
};

ostream & operator << (ostream& out, Song & l) {     
        cout << l.track << ".  " << l.title << " " << l.time/100 << ":";
        if ((l.time % 100) < 10) cout << "0";
        cout << l.time % 100;
}

class Album {
  public :
    map<int, Song> songs;
    string name;  // Album's name
    string artist;
    string genre;
    int time;     // Total time of all songs on album
    int nsongs;   // Total number of songs on album
};

class Artist {
   public :
     string name; // Artist's name
     int time;    // Total time of all songs on all albums by this artist
     int nsongs;  // Total number of songs on all albums by this artist
     bool operator < (Artist another) const { return name < another.name;}
};

typedef multimap <Artist, Album> mp3map;
string clean_up(string str, char delim);

int main(int argc, char* argv[]){
    //temp objects
    string instr;
    string title, time, artist, album, genre;
    int track;

    mp3map records; 
    mp3map:: iterator it;   


    //open the file
    fstream infile(argv[1], ios::in);
    
    while(getline(infile, instr)){
        stringstream tmp(instr); //so it doesnt think its reached eof
        //get all info into vars
        tmp >> title >> time >> artist >> album >> genre >> track;

        //clean up time and convert to int
        int loc = time.find(':');
        time.erase(loc, 1);
        int new_time = stoi(time);

        Artist tmp_art;
        tmp_art.name = clean_up(artist, '_');
        tmp_art.time += new_time;
        cout << new_time << endl;;
            
       }           
  
    cout << "exit program" << endl;

    return 0;
}

string clean_up(string str, char delim){
    int loc = str.find(delim);
    while(loc != -1){
        str.replace(loc, 1, " ");
        loc = str.find(delim);
    }
    return str;
}



