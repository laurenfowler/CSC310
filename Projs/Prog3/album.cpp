#include "album.h"

string Album::getUPC(){
    return string(UPC);
}

string Album::getArtist(){
    return string(Artist);
}

string Album::getTitle(){
    return string(Title);
}

int Album::recordSize(){
    return (strlen(UPC)+strlen(Artist)+strlen(Title));
}

Album::Album(String myUPC, String myArtist, String myTitle){
    strcpy(UPC, myUPC);
    strcpy(Artist, myArtist);
    strcpy(Title, myTitle);
}

Album::Album(){
    strcpy(UPC, "\0");
    strcpy(Artist, "\0");
    strcpy(Title, "\0");
}

Album::Album(const Album& otherAlbum){
    strcpy(UPC, otherAlbum.UPC);
    strcpy(Artist, otherAlbum.Artist);
    strcpy(Title, otherAlbum.Title);
}

Album & Album::operator = (const Album& otherAlbum){
    strcpy(UPC, otherAlbum.UPC);
    strcpy(Artist, otherAlbum.Artist);
    strcpy(Title, otherAlbum.Title);
    return *this;
}

bool operator < (const Album& a, const Album& b){
    return a.UPC < b.UPC; 
}

ostream & operator << (ostream & stream, Album & C){
    stream << C.UPC << " " << C.Artist << " " << C.Title;
}

istream & operator >> (istream & stream, Album & C){
    stream >> C.UPC >> C.Artist >> C.Title;
}
