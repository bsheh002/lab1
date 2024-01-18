#include <iostream>
#include <string>
#include "Playlist.h"

using namespace std;

Playlist* playPtr;

void MenuDisplay(string t1){
    char choice;

    string songName;
    string artistName;
    string ID;
    int songLength;
    PlaylistNode* newSong;

    cout << t1 << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;

    cout << "Choose an option:" << endl;
    cin >> choice;
    cin.ignore();
    if(choice == 'q'){
        return;
    }
    else if(choice == 'a'){
        cout << "ADD SONG" << endl;
        cout << "Enter song's unique ID:" << endl;
        getline(cin,ID);
        cout << "Enter song's name:" << endl;
        getline(cin,songName);
        cout << "Enter artist's name:" << endl;
        getline(cin, artistName);
        cout << "Enter song's length (in seconds):" << endl;
        cin >> songLength;
        cin.ignore();

        newSong = new PlaylistNode(ID,songName, artistName,songLength);

        playPtr->addSong(newSong);
        cout << endl;
        MenuDisplay(t1);
    }
    else if (choice == 'd'){
        cout << "REMOVE SONG" << endl;
        cout << "Enter Song's unique ID: " << endl;
        getline(cin,ID);
        playPtr->removeSong(ID);
        cout << endl;
        MenuDisplay(t1);
    }
    else if (choice == 'o') {
        playPtr->OutputPlayList(t1);
        MenuDisplay(t1);
    }
    else if (choice == 's'){
        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
        cout << "Enter artist's name:" << endl;
        cout << endl;
        string name;
        getline(cin,name);
        playPtr->specificArtistSong(name);
        MenuDisplay(t1);
    }
    else if (choice == 't'){
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
        playPtr->playlistLength();
        cout << endl;
        MenuDisplay(t1);
    }
    else if (choice == 'c'){
        cout << "CHANGE POSITION OF SONG" << endl;
        playPtr->changePos();
        MenuDisplay(t1);
    }
}

int main() {

    string playlistTitle;

    cout << "Enter playlist's title:" << endl << endl;
    getline(cin,playlistTitle);
    playPtr = new Playlist();
    MenuDisplay(playlistTitle);
}
