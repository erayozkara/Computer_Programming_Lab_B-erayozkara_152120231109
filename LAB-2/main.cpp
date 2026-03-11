#include <iostream>
#include <string>

using namespace std;

struct Node {
    string title;
    Node* next;
};

Node* head = NULL;

void addSong(string title) {
    Node* newNode = new Node;
    newNode->title = title;
    newNode->next = head;
    head = newNode;

    cout << "Song added to playlist.\n";
}

void listSongs() {
    if (head == NULL) {
        cout << "Playlist is empty.\n";
        return;
    }

    Node* current = head;
    int index = 1;

    while (current != NULL) {
        cout << index << ". " << current->title << endl;
        current = current->next;
        index++;
    }
}

void searchSong(string title) {
    Node* current = head;

    while (current != NULL) {
        if (current->title == title) {
            cout << "Song found in playlist.\n";
            return;
        }
        current = current->next;
    }

    cout << "Song not found.\n";
}

int main() {

    int choice;
    string title;

    while (true) {

        cout << "\n--- Music Playlist Menu ---\n";
        cout << "1. Add Song\n";
        cout << "2. Search Song\n";
        cout << "3. List Songs\n";
        cout << "4. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        if(choice==1){
            cout << "enter song title:";
            getline(cin,title);
            addSong(title);
        }
        else if(choice==2){
            cout << "enter song title to search:";
            getline(cin,title);
            searchSong(title);
        }
        else if(choice==3){
            listSongs();
        }
        else if(choice==4){
            cout << "existing programs...\n";
            break;
        }
        else{
            cout << "invalid choices!!!\n";
        }

        }
        return 0;
}
