#include <iostream>
#include <string>
#include "Playlist.h"

using namespace std;

PlaylistNode:: PlaylistNode(){ //constructor
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
}
PlaylistNode:: PlaylistNode(string _uniqueID, string _songName, string _artistName, int _songLength){ //copy constructor
    uniqueID = _uniqueID;
    songName = _songName;
    artistName = _artistName;
    songLength = _songLength;
    nextNodePtr = nullptr;;
}
void PlaylistNode:: InsertAfter(PlaylistNode* newNode){ //inserts selected song after a specified song
    PlaylistNode* temp = nextNodePtr;
    nextNodePtr = newNode;
    newNode->SetNext(temp);
}
void PlaylistNode:: SetNext(PlaylistNode* next){ //sets the node's pointer to the next one
    nextNodePtr = next;
}
string PlaylistNode:: GetID() const{ //gets the ID of a song
    return uniqueID;
}
string PlaylistNode:: GetSongName() const{ //gets the name of a song
    return songName;
}
string PlaylistNode:: GetArtistName() const{ //gets the name of the artist that created a song
    return artistName;
}
int PlaylistNode:: GetSongLength() const{ //gets the length of a song
    return songLength;
}
PlaylistNode* PlaylistNode:: GetNext() const{ //gets the next node
    return nextNodePtr;
}
void PlaylistNode:: PrintPlaylistNode() const{ //prints the full info of a song
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}
Playlist::Playlist(){ //sets both head and tail to null
    head = nullptr;
    tail = nullptr;
}
void Playlist:: removeSong(string ID){ //removes a song by checking for its song ID
    if(head == 0){ //checks to see if playlist is empty
        cout << "Playlist is empty" << endl;
        return;
    }
    else if (head->GetID() == ID){ //checks to see if the ID matches with the ID of head
        string removeSong = head->GetSongName();
        head = head->GetNext();
        cout << removeSong << " removed" << endl;
        return;
    }
    else{
        PlaylistNode* prev = head;
        PlaylistNode* curr = head->GetNext();
        while(curr != nullptr && curr->GetID() != ID){
            prev = curr;
            curr = curr->GetNext();
        }
        if(curr){ //checks to see if there is more songs in the list
            string removeSong = curr->GetSongName();
            prev->SetNext(curr->GetNext());
            if(curr->GetNext() == nullptr){ //checks to see if the songs on the list ended
                tail = prev;
                cout <<'"' << removeSong <<'"' << " removed." << endl;
                return;
            }
        }
    }
}
void Playlist:: addSong(PlaylistNode* newSong){ //adds a new song to the playlist
    if(head == 0){ //checks to see if playlist is empty
        head = newSong;
        tail = newSong;
    }
    else{
        tail->SetNext(newSong);
        tail = newSong;
    }
}
void Playlist:: OutputPlayList(string title){ //outputs a list of the songs on the playlist
    PlaylistNode* list;
    int num = 1;
    list = head;
    cout << title << " - OUTPUT FULL PLAYLIST" << endl;
    if (head == 0){ //checks to see if playlist is empty
        cout << "Playlist is empty" << endl;
        cout << endl;
        return;
    }
    else{
        while (list){ //iterates till there are no more songs in the playlist
            cout << num << "." << endl;
            list->PrintPlaylistNode();
            cout << endl;
            ++num;
            list = list->GetNext();
        }
    }
}

void Playlist:: changePos(){ //changes the position of a given song
    int nodeCounter = 1;
    PlaylistNode* currentNode;
    PlaylistNode* previousNode;
    int beginningNode;
    int newPosition;
    cout << "Enter song's currentNode position:" << endl;
    cin >> beginningNode;
    cout << "Enter new position for song:" << endl;
    cin >> newPosition;

    currentNode = head;
    previousNode = nullptr;
    if (beginningNode < 1){ //checks for extreme cases where position cannot be changed to
        cout << "invalid position," << endl;
        return;
    }
    while (nodeCounter < beginningNode){ //checks to see if it a valid position to change to
        if (currentNode){
            previousNode = currentNode;
            currentNode = currentNode->GetNext();
            ++nodeCounter;
            if(currentNode == nullptr){
                cout << "Invalid position" << endl;
                return;
            }
        }
        else{
            cout << "Invalid position" << endl;
            return;
        }
    }
    if (previousNode){ //checks to see if node is not equal to nullptr
        previousNode->SetNext(currentNode->GetNext());
    }
    else{
        head = currentNode->GetNext();
    }
    if (currentNode == tail){ //checks to see if currentNode is at the end of the list
        tail = previousNode;
    }
    if (newPosition <= 1){ //makes sure position is a valid position to change to
        if(head == 0){ //checks to see if head is null
            tail = currentNode;
        }
        currentNode->SetNext(head);
        head = currentNode;
        cout << '"' << currentNode->GetSongName() << '"' << "moved to position 1" << endl;
        cout << endl;
    }
    else{
        if(head == 0){ //checks to see if head is null
            head = currentNode;
            cout << '"' << currentNode->GetSongName() << " moved to position 1" << endl;
        }
        else{
            int nodeCounter1 = 2;
            PlaylistNode* previousNode1 = head;
            PlaylistNode* currentNode1 = head->GetNext();
            while (nodeCounter1 < newPosition && currentNode1){ //iterates till currentNode reaches the selected position
                previousNode1 = currentNode1;
                currentNode1 = currentNode1->GetNext();
                nodeCounter1++;
            }
            previousNode1->InsertAfter(currentNode);
            if (currentNode1 == nullptr){ //checks to see if the list has ended
                tail = currentNode;
            }
            cout << currentNode->GetSongName() << " moved to position " << nodeCounter << endl;
        }
    }
}

void Playlist::specificArtistSong(string artist){ //looks for a given artist's list of songs
    int num;
    num = 1;
    PlaylistNode* artistSong;
    artistSong = head;
    while (artistSong){ //iterates while there is a song
        if (artistSong->GetArtistName() == artist){ //checks to see if artist matches given artist
            cout << num << "." << endl;
            artistSong->PrintPlaylistNode();
            cout << endl;
        }
        ++num;
        artistSong = artistSong->GetNext();
    }
}
void Playlist:: playlistLength(){ //checks to see the length of all the songs in the list in seconds
    int num = 0;
    PlaylistNode* curr;
    curr = head;
    while (curr){ //checks to see if there is more songs in the list
        num += curr->GetSongLength();
        curr = curr->GetNext();
    }
    cout << "Total time: " << num << " seconds" << endl;
}
