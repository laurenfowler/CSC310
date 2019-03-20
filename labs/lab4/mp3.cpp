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
     bool operator == (Artist another) const {return name == another.name;}
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

    if(argc < 2){
        cerr << "mp3: missing filename 'mp3'" << endl;
        exit(0);
    }

    //open the file
    fstream infile(argv[1], ios::in);
    
    while(getline(infile, instr)){
        map <int, Song> songs;
        bool exists = false;
        bool same_album = false;
        stringstream tmp(instr); //so it doesnt think its reached eof
        //get all info into vars
        tmp >> title >> time >> artist >> album >> genre >> track;

        //clean up time and convert to int
        int loc = time.find(':');
        time.erase(loc, 1);
        int new_time = stoi(time);

        //create song entry
        Song new_song;
        new_song.title = clean_up(title, '_');
        new_song.time = new_time;
        new_song.track = track;  

        Artist new_art;
        new_art.name = clean_up(artist, '_');
        Artist store;

        for(it = records.begin(); it != records.end(); it++){
            Artist cmp = it -> first;
            Album cmpA = it -> second;
            if(cmp == new_art){
                exists = true; //turn on flag so if wont run
                //update artist information for each instance
                cmp.time+=new_time;
                cmp.nsongs++;

                //check for album match
                if(cmpA.name == clean_up(album, '_')){
                    cout << "new song" << endl;
                    same_album = true; //turn on flag so if wont run
                    //update album info
                    cmpA.time+=new_time;
                    cmpA.nsongs++;
                    songs = cmpA.songs;
                    songs[track] = new_song;
                }
                else{
                    new_art = cmp; //store for new album entry
                }  
            }
        }

        //creates a new entry if it is a new album and artist already exists
        if(!same_album && exists){
            cout << "same artist, new album" << endl;
            //create new album, same artist
            Album new_album;
            new_album.name = clean_up(album, '_');
            new_album.genre = clean_up(album, '_');
            new_album.time+=new_time;
            songs = new_album.songs;
            songs[track] = new_song;
            records.insert({new_art, new_album});

        }

        //create a new entry
        if(!exists){
            cout << "new artist" << endl;
            //update artist info
            new_art.time+=new_time;
            new_art.nsongs++;

            //create album
            Album new_album;
            new_album.name = clean_up(album, '_');
            new_album.genre = clean_up(album, '_');
            new_album.time+=new_time;
            songs = new_album.songs;
            songs[track] = new_song;
            records.insert({new_art, new_album});
        }    
            
    }          
  
    Artist artist_obj;

    for(it = records.begin(); it!= records.end(); it++){
        artist_obj = it -> first;
        cout << artist_obj.name << endl;
    } 

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



