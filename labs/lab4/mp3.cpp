#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
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
     vector<Album> albums;
     bool operator < (Artist another) const { return name < another.name;}
};

string clean_up(string str, char delim);
int main(int argc, char* argv[]){
    //temp objects
    string instr;
    string title, time, artist, album, genre;
    int track;

    if(argc < 2){
        cerr << "mp3: missing filename 'mp3'" << endl;
        exit(0);
    }

    fstream infile(argv[1], ios::in);
    //vector of artists
    vector<Artist> artists;   
    vector<Artist>:: iterator ar_itr;
    //album iterator
    vector<Album>:: iterator al_itr;
    while(getline(infile, instr)){
        bool found = false;
        int tloc = 0;
        int loc = 0;
        int found_loc;
        map <int, Song> songs;
        stringstream tmp(instr); //so it doesnt think its reached eof
     
        //get all info into vars
        tmp >> title >> time >> artist >> album >> genre >> track;

        //clean up time and convert to int
        tloc = time.find(':');
        time.erase(tloc, 1);
        int new_time = stoi(time);
        artist = clean_up(artist, '_');
        album = clean_up(album, '_');

        for(ar_itr = artists.begin(); ar_itr != artists.end(); ar_itr++){
            Artist tmp = *ar_itr;
            if(tmp.name == artist){
                cout << "artist found" << endl;
                found = true;
                found_loc = loc;
            }
            loc++;
        } 
        
        //create song object
        Song new_song;
        new_song.title = clean_up(title, '_');
        new_song.track = track;
        new_song.time = new_time;
 
        
        //if artist was found
        bool album_found = false;
        int aloc;
        int x = 0;

        //if artist is found
        if(found){
            //increment total time and num songs
            artists[found_loc].time+=new_time;
            artists[found_loc].nsongs++;

            //get the album vector
            vector<Album> albums = artists[found_loc].albums;

            //see if songs album exists or not
            for(al_itr = albums.begin(); al_itr!= albums.end(); al_itr++){
                Album tmp_al = *al_itr;
                if(tmp_al.name == album){
                    album_found = true;
                    aloc = x;
                }
                x++;   
            }
            //if album exists
            if(album_found){
                cout << "album found" << endl;
                artists[found_loc].albums[aloc].time+=new_time;
                artists[found_loc].albums[aloc].nsongs++;
                artists[found_loc].albums[aloc].songs[track] = new_song;   
            }
            else{
                //if album does not exist
                Album new_album;
                new_album.name = album;
                new_album.artist = artist;
                new_album.genre = clean_up(genre, '_');
                new_album.time = new_time;
                new_album.nsongs++;
                new_album.songs[track] = new_song;  
                artists[found_loc].albums.push_back(new_album);          

            }
        }
        else{
            //create new artist and album in artist
            Artist new_artist;
            new_artist.name = artist;
            new_artist.time+=new_time;
            new_artist.nsongs++;
            
            Album new_album;
            new_album.name=album;
            new_album.artist = artist;
            new_album.genre = clean_up(genre, '_');
            new_album.time+=new_time;
            new_album.nsongs++;
            new_album.songs[track] = new_song;     

            //add album to artist, and artist to artists vector
            new_artist.albums.push_back(new_album);
            artists.push_back(new_artist);
        } 
    }

    //print out records   
    for(ar_itr = artists.begin(); ar_itr != artists.end(); ar_itr++){
        Artist pArt = *ar_itr;
        cout << pArt.name << ": " << pArt.nsongs << ", " << pArt.time << endl;
        cout << "\t";
        vector<Album> pAlb = pArt.albums;
        for(al_itr = pAlb.begin(); al_itr != pAlb.end(); al_itr++){
            Album out = *al_itr;
            cout << out.name << ": " << out.nsongs << ", " << out.time << endl;
            map <int, Song>:: iterator it;
            for(it = out.songs.begin(); it != out.songs.end(); it++){
                cout << "\t \t";
                Song pSong = it -> second;
                cout << pSong << endl;
            }
        }
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






/*vector<Artist>:: iterator ar_it;
            for(ar_it = artists.begin(); ar_it!=artists.end(); ar_it++){
                Artist tmp = *ar_it;
                if(tmp.name > new_artist.name){
                    //probs need a if it reaches the end, just pushback
                    artists.insert(ar_it, new_artist);
                    break;
                }*/

