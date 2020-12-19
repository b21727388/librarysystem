//
// Created by Beşir Kassab on 30.11.2020.
//

#ifndef LIBRARYSYSTEM_MOVIELIST_H
#define LIBRARYSYSTEM_MOVIELIST_H
#include <string>

using namespace std;

class MovieList{
public:
    struct MovieNode {
        int movieID;
        string movieTitle;
        int movieYear;
        MovieNode *next;
    };

    static void push(MovieNode** root, int movieId, string movieTitle, int movieYear, string commandTitle){
        MovieNode *newNode = new MovieNode();
        MovieNode *temp = *root;
        newNode->movieID = movieId;
        newNode->movieTitle = movieTitle;
        newNode->movieYear = movieYear;
        newNode->next = *root;

        if (*root != nullptr){
            do{
                if(temp->movieID == movieId){
                    cout << "Movie " << movieId << " already exist\n";
                    return;
                }
                temp = temp->next;
            }while (temp->next != *root);
            if(temp->movieID == movieId){
                cout << "Movie " << movieId << " already exist\n";
                return;
            }else {
                temp->next = newNode;
            }
            if(commandTitle == "returnMovie"){
                cout << "Movie " << newNode->movieID << " has been returned\n";
            }else {
                cout << "Movie " << newNode->movieID << " has been added\n";
            }
        }else {
            newNode->next = newNode;
            if(commandTitle == "returnMovie"){
                cout << "Movie " << newNode->movieID << " has been returned\n";
            }else {

                cout << "Movie " << newNode->movieID << " has been added\n";
            }
            *root = newNode;
        }
    }

    static void deleteNode(MovieNode** root, int movieId, string commandTitle){
        // If linked list is empty
        if (*root != nullptr) {
            // If the list contains only a single node
            if ((*root)->movieID == movieId && (*root)->next == *root) {
                if (commandTitle == "deleteMovie") {
                    cout << "Movie " << (*root)->movieID << " has not been checked out\nMovie " << (*root)->movieID
                         << " has been deleted\n";
                }
                free(*root);
                *root = nullptr;
                return;
            }

            MovieNode *last = *root, *d;

            // If head is to be deleted
            if ((*root)->movieID == movieId) {

                // Find the last node of the list
                while (last->next != *root) {
                    last = last->next;
                }

                last->next = (*root)->next;
                if (commandTitle == "deleteMovie") {
                    cout << "Movie " << (*root)->movieID << " has not been checked out\nMovie " << (*root)->movieID
                         << " has been deleted\n";
                }
                free(*root);
                *root = last->next;
            } else {
                while (last->next != *root && last->next->movieID != movieId) {
                    last = last->next;
                }
                // If node to be deleted was found
                if (last->next->movieID == movieId) {
                    //cout << last->next->movieID <<" ";
                    d = last->next;
                    last->next = d->next;
                    if (commandTitle == "deleteMovie") {
                        cout << "Movie " << d->movieID << " has not been checked out\nMovie " << d->movieID
                             << " has been deleted\n";
                    }
                    free(d);
                } else {
                    if (commandTitle == "deleteMovie") {
                        cout << "Movie " << movieId << " does not exist\n";
                    }
                }
            }
        }else{
            if(commandTitle == "deleteMovie"){
                cout << "Movie " << movieId << " does not exist\n";
            }
        }
    }

    static void printList(MovieNode** root, MovieNode** headReferance, string commandTitle, int movieId) {

        if (commandTitle == "showMovie") {
            if((*root) != nullptr) {
                MovieNode *temp = *root;
                do {
                    if (temp->movieID == movieId) {
                        cout << temp->movieID << " " << temp->movieTitle << " " << temp->movieYear
                             << " Not checked out\n";
                        return;
                    }
                    temp = temp->next;
                } while (temp->next != *root);
                if(temp->movieID == movieId){
                    cout << temp->movieID << " " << temp->movieTitle << " " << temp->movieYear
                         << " Not checked out\n";
                }else {
                    cout << "Movie with the id " << movieId << " does not exist\n";
                }

            }else {
                cout << "Movie with the id " << movieId << " does not exist\n";
            }

        } else if (commandTitle == "returnMovie") {
            if((*root) == nullptr){
                cout << "Movie " << movieId << " not exist in the library\n";
            }else {
                //cout << "movie id = " << movieId << endl;
                MovieNode *temp = *root;
                while (temp->next != *root) {
                    if (temp->movieID == movieId) {
                        cout << "Movie " << temp->movieID << " has not been checked out\n";
                        return;
                    }
                    temp = temp->next;

                    if (temp->movieID == movieId) {
                        cout << "Movie " << temp->movieID << " has not been checked out\n";
                        return;
                    }
                }
                cout << "Movie " << movieId << " not exist in the library\n";
            }
        } else {
            if ((*root) != nullptr) {
                //print the last node for the first time
                if ((*root)->next == *headReferance) {
                    cout << (*root)->movieID << " ";
                    cout << (*root)->movieTitle << " ";
                    cout << (*root)->movieYear << " ";
                    cout << "Not checked out\n";
                    return;
                }

                // recursive printing algorithm
                printList(&((*root)->next), headReferance, commandTitle, movieId);

                // After last node printed, print other nodes
                cout << (*root)->movieID << " ";
                cout << (*root)->movieTitle << " ";
                cout << (*root)->movieYear << " ";
                cout << "Not checked out\n";
            }
        }
    }

    static MovieNode* FindMovie(MovieNode** root, int movieId){
        MovieNode *temp = *root;
        if (*root == nullptr) {
            cout << "Movie " << movieId << " does not exist for checkout\n";
        } else {
            while (temp->movieID != movieId) {
                temp = temp->next;
                if (temp == (*root)) {
                    cout << "Movie " << movieId << " does not exist for checkout\n";
                    break;
                }
            }
        }
        return temp;
    }

};

#endif //LIBRARYSYSTEM_MOVIELIST_H
