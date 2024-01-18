#include <iostream>
#include <string>
#include "Playlist.h"

using namespace std;

Playlist* playPtr;

void MenuDisplay(string t1){    //a function that allows for a menu of options to be viewed
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
    if(choice == 'q'){    //checks to see if user input is the char 'q' in order to quit the program
        return;
    }
    else if(choice == 'a'){    //checks to see if user input is the char 'a' in order to ask user for inputs to add a new song
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
    else if (choice == 'd'){ //checks to see if user input is the char 'd' in order task for user input to find a song and delete it
        cout << "REMOVE SONG" << endl;
        cout << "Enter Song's unique ID: " << endl;
        getline(cin,ID);
        playPtr->removeSong(ID);
        cout << endl;
        MenuDisplay(t1);
    }
    else if (choice == 'o') { //checks to see if user input is the char 'o' in order to display a full list of the songs available
        playPtr->OutputPlayList(t1);
        MenuDisplay(t1);
    }
    else if (choice == 's'){ //checks to see if user input is the char 's' in order to ask user for an artist and find songs created only by that artist
        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
        cout << "Enter artist's name:" << endl;
        cout << endl;
        string name;
        getline(cin,name);
        playPtr->specificArtistSong(name);
        MenuDisplay(t1);
    }
    else if (choice == 't'){ //checks to see if user input is the char 't' in order to calculate the length of the playlist in seconds and display it
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
        playPtr->playlistLength();
        cout << endl;
        MenuDisplay(t1);
    }
    else if (choice == 'c'){ //checks to see if user input is the char 'c' in order to ask the user the location the song should be moved to in the playlist
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
