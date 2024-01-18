#include <iostream>
#include <string>
#include "Playlist.h"

using namespace std;

PlaylistNode:: PlaylistNode(){
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
}
PlaylistNode:: PlaylistNode(string _uniqueID, string _songName, string _artistName, int _songLength){
    uniqueID = _uniqueID;
    songName = _songName;
    artistName = _artistName;
    songLength = _songLength;
    nextNodePtr = nullptr;;
}
void PlaylistNode:: InsertAfter(PlaylistNode* newNode){
    PlaylistNode* temp = nextNodePtr;
    nextNodePtr = newNode;
    newNode->SetNext(temp);
}
void PlaylistNode:: SetNext(PlaylistNode* next){
    nextNodePtr = next;
}
string PlaylistNode:: GetID() const{
    return uniqueID;
}
string PlaylistNode:: GetSongName() const{
    return songName;
}
string PlaylistNode:: GetArtistName() const{
    return artistName;
}
int PlaylistNode:: GetSongLength() const{
    return songLength;
}
PlaylistNode* PlaylistNode:: GetNext() const{
    return nextNodePtr;
}
void PlaylistNode:: PrintPlaylistNode() const{
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}
Playlist::Playlist(){
    head = nullptr;
    tail = nullptr;
}
void Playlist:: removeSong(string ID){
    if(head == 0){
        cout << "Playlist is empty" << endl;
        return;
    }
    else if (head->GetID() == ID){
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
        if(curr){
            string removeSong = curr->GetSongName();
            prev->SetNext(curr->GetNext());
            if(curr->GetNext() == nullptr){
                tail = prev;
                cout <<'"' << removeSong <<'"' << " removed." << endl;
                return;
            }
        }
    }
}
void Playlist:: addSong(PlaylistNode* newSong){
    if(head == 0){
        head = newSong;
        tail = newSong;
    }
    else{
        tail->SetNext(newSong);
        tail = newSong;
    }
}
void Playlist:: OutputPlayList(string title){
    PlaylistNode* list;
    int num = 1;
    list = head;
    cout << title << " - OUTPUT FULL PLAYLIST" << endl;
    if (head == 0){
        cout << "Playlist is empty" << endl;
        cout << endl;
        return;
    }
    else{
        while (list){
            cout << num << "." << endl;
            list->PrintPlaylistNode();
            cout << endl;
            ++num;
            list = list->GetNext();
        }
    }
}

void Playlist:: changePos(){
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
    if (beginningNode < 1){
        cout << "invalid position," << endl;
        return;
    }
    while (nodeCounter < beginningNode){
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
    if (previousNode){
        previousNode->SetNext(currentNode->GetNext());
    }
    else{
        head = currentNode->GetNext();
    }
    if (currentNode == tail){
        tail = previousNode;
    }
    if (newPosition <= 1){
        if(head == 0){
            tail = currentNode;
        }
        currentNode->SetNext(head);
        head = currentNode;
        cout << '"' << currentNode->GetSongName() << '"' << "moved to position 1" << endl;
        cout << endl;
    }
    else{
        if(head == 0){
            head = currentNode;
            cout << '"' << currentNode->GetSongName() << " moved to position 1" << endl;
        }
        else{
            int nodeCounter1 = 2;
            PlaylistNode* previousNode1 = head;
            PlaylistNode* currentNode1 = head->GetNext();
            while (nodeCounter1 < newPosition && currentNode1){
                previousNode1 = currentNode1;
                currentNode1 = currentNode1->GetNext();
                nodeCounter1++;
            }
            previousNode1->InsertAfter(currentNode);
            if (currentNode1 == nullptr){
                tail = currentNode;
            }
            cout << currentNode->GetSongName() << " moved to position " << nodeCounter << endl;
        }
    }
}

void Playlist::specificArtistSong(string artist){
    int num;
    num = 1;
    PlaylistNode* artistSong;
    artistSong = head;
    while (artistSong){
        if (artistSong->GetArtistName() == artist){
            cout << num << "." << endl;
            artistSong->PrintPlaylistNode();
            cout << endl;
        }
        ++num;
        artistSong = artistSong->GetNext();
    }
}
void Playlist:: playlistLength(){
    int num = 0;
    PlaylistNode* curr;
    curr = head;
    while (curr){
        num += curr->GetSongLength();
        curr = curr->GetNext();
    }
    cout << "Total time: " << num << " seconds" << endl;
}
