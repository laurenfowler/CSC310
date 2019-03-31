#include <iostream>
#include "album.h"

int main(){

    String UPC = "11115";
    String name = "Starry Nights";
    String artist = "Van Gough";
    Album album(UPC, artist, name);
    Album empty;
    Album test(album);

    String UPC1 = "11114";
    String name1 = "Sunflower";
    String artist1 = "post malone";

    Album comp(UPC1, artist1, name1);

    cout << album.getUPC() << " " << album.getTitle() << " " << album.getArtist() << endl;
    cout << empty.getUPC() << " " << empty.getTitle() << " " << empty.getArtist() << endl;
    cout << test.getUPC() << " " << test.getTitle() << " " << test.getArtist() << endl;
    
    empty = test;
    cout << empty.getUPC() << " " << empty.getTitle() << " " << empty.getArtist() << endl;

    cout << (album < comp) << endl;
    cout << (comp < album) << endl;

    cout << album << endl;


}


