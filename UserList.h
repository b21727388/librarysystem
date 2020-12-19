//
// Created by Beşir Kassab on 30.11.2020.
//

#ifndef LIBRARYSYSTEM_USERLIST_H
#define LIBRARYSYSTEM_USERLIST_H
#include <string>

using namespace std;

class UserList{
public:
    struct UsersMovie{
        int movieID;
        string movieTitle;
        int movieYear;
        UsersMovie *next;
    };
    struct UserNode {
        int userID;
        string userName;
        UsersMovie *moviesHead = nullptr;
        UserNode *next;
        UserNode *previous;
    };

    static void addMovie(UserNode** root, MovieList::MovieNode** rootM, int movieId, string movieTitle, int movieYear, string commandTitle){
        if((*root) != nullptr) {
            UserNode *temp = *root;
            do {
                UsersMovie *tempMovieHead = temp->moviesHead;
                if (temp->moviesHead != nullptr) {
                    do {
                        if (temp->moviesHead->movieID == movieId) {
                            cout << "Movie " << movieId << " already exists\n";
                            return;
                        }
                        temp->moviesHead = temp->moviesHead->next;
                    } while (temp->moviesHead != tempMovieHead);
                }
                temp = temp->next;

            } while (temp != *root);
        }
        MovieList::push(rootM,movieId,movieTitle,movieYear,commandTitle);
    }


    static void moviePush(MovieList::MovieNode** movie, UserNode** root, int userId, MovieList::MovieNode** movieHead){
        UsersMovie* newNode = new UsersMovie();
        UserNode* tempUser ;
        if(*root != nullptr) {
            tempUser = *root;
        }else{
            cout << "User "<< userId << " does not exist for checkout\n";
            return;
        }
        while(tempUser->userID != userId){
            tempUser = tempUser->next;
            if(tempUser == (*root)){
                cout << "User "<< userId << " does not exist for checkout\n";
                break;
            }
        }

        if(tempUser->userID == userId) {
            UsersMovie* tempMovie = tempUser->moviesHead;
            newNode->movieID = (*movie)->movieID;
            newNode->movieTitle = (*movie)->movieTitle;
            newNode->movieYear = (*movie)->movieYear;
            newNode->next = tempUser->moviesHead;


            if (tempUser->moviesHead != nullptr) {
                while (tempMovie->next != tempUser->moviesHead) {
                    tempMovie = tempMovie->next;
                }
                tempMovie->next = newNode;
                cout << "Movie " << newNode->movieID << " has been checked out by User " << userId << endl;
                MovieList::deleteNode(movieHead,newNode->movieID, "deleteCheckOut");
            } else {
                newNode->next = newNode;
                cout << "Movie " << newNode->movieID << " has been checked out by User " << userId << endl;
                tempUser->moviesHead = newNode;
                MovieList::deleteNode(movieHead,newNode->movieID, "deleteCheckOut");
            }
        }
    }

    static void push(UserNode** root, int userId, string userName){
        if (*root == nullptr){
            UserNode* newNode = new UserNode();
            newNode->userID = userId;
            newNode->userName = userName;
            newNode->next = newNode->previous = newNode;
            cout << "User " <<  newNode->userID << " has been added\n";
            *root = newNode;
            return;
        }

        UserNode *lastNode = (*root)->previous;
        UserNode *temp = *root;
        UserNode* newNode = new UserNode();

        newNode->userID = userId;
        newNode->userName = userName;
        do {
            if(temp->userID == userId) {
                cout << "User " << temp->userID << " already exist\n";
                return;
            }
            temp = temp->next;
        } while (temp != *root);
        newNode->next = *root;
        cout << "User " << newNode->userID << " has been added\n";
        (*root)->previous = newNode;
        newNode->previous = lastNode;
        lastNode->next = newNode;
    }

    static void deleteNode(UserNode** root, MovieList::MovieNode** rootM, MovieList::MovieNode** headReferance, string commandTitle, int deleteId){
        UserNode *temp;
        if(*root != nullptr) {
            temp = *root;
        }else{
            MovieList::deleteNode(rootM, deleteId, "deleteMovie");
            return;
        }

        if(commandTitle == "deleteUser"){
            UserNode* deleteIt = *root;
            if((*root)->userID == deleteId&& (*root)->next == *root){
                cout << "User " << (*root)->userID << " has been deleted\n";
                free(*root);
                *root = nullptr;
                return;
            }
            if((*root)->userID == deleteId){

                // Find the last node of the list
                while(temp->next != *root) {
                    temp = temp->next;
                }

                temp->next = (*root)->next;
                cout << "User " << (*root)->userID << " has been deleted\n";
                *root = temp->next;
                return;
            }
            do {
                if(temp->userID == deleteId) {
                    cout << "User " << temp->userID << " has been deleted\n";
                    (deleteIt->previous)->next = temp->next;
                    (deleteIt->next)->previous = temp->previous;
                    return;
                }
                temp = temp->next;
                deleteIt = temp;
            } while (temp != *root);
            cout << "User " << deleteId << " does not exist\n";
        }else if(commandTitle == "deleteMovie"){

            do {
                UsersMovie* tempMovieHead = temp->moviesHead;
                if(temp->moviesHead != nullptr) {
                    do {
                        if(temp->moviesHead->movieID == deleteId){
                            if(temp->moviesHead->next == temp->moviesHead){
                                cout << "Movie " << temp->moviesHead->movieID << " has been checked out\nMovie " << temp->moviesHead->movieID << " has been deleted\n";
                                temp->moviesHead = nullptr;
                                return;
                            }
                            UsersMovie *last = temp->moviesHead,*d;
                            // If head is to be deleted
                            if(temp->moviesHead->movieID == deleteId){

                                // Find the last node of the list
                                while(last->next != temp->moviesHead) {
                                    last = last->next;
                                }

                                last->next = temp->moviesHead->next;
                                cout << "Movie " << temp->moviesHead->movieID << " has been checked out\nMovie " << temp->moviesHead->movieID << " has been deleted\n";
                                temp->moviesHead = last->next;
                            }else {

                                while (last->next != temp->moviesHead && last->next->movieID != deleteId) {
                                    last = last->next;
                                }
                                // If node to be deleted was found
                                if (last->next->movieID == deleteId) {
                                    //cout << last->next->movieID <<" ";
                                    d = last->next;
                                    last->next = d->next;
                                    cout << "Movie " << d->movieID << " has been checked out\nMovie " << d->movieID << " has been deleted\n";
                                    free(d);
                                } else {
                                    cout << "Movie " << deleteId << " does not exist\n";
                                }
                            }
                            return;
                        }
                        temp->moviesHead = temp->moviesHead->next;
                    } while (temp->moviesHead != tempMovieHead);
                }
                temp = temp->next;

            } while (temp != *root);
            MovieList::deleteNode(rootM, deleteId, "deleteMovie");

        }
    }

    static void printList(UserNode** root, MovieList::MovieNode** rootM, MovieList::MovieNode** headReferance, string commandTitle){
        UserNode* temp = *root;
        if(commandTitle == "showAllMovie") {
            MovieList::printList(rootM, headReferance, commandTitle, 0);
            do {
                UsersMovie* tempMovieHead = temp->moviesHead;
                if(temp->moviesHead != nullptr) {
                    do {
                        cout << temp->moviesHead->movieID << " " << temp->moviesHead->movieTitle << " " << temp->moviesHead->movieYear << " Checked out by User " << temp->userID << endl;
                        temp->moviesHead = temp->moviesHead->next;
                    } while (temp->moviesHead != tempMovieHead);
                }
                temp = temp->next;

            } while (temp != *root);
        }else if(commandTitle == "showUser"){
            if (temp->next == *root && temp->previous == *root) {
                cout << temp->userID << " ";
                cout << temp->userName << " \n";
            } else {
                do {
                    cout << temp->userID << " ";
                    cout << temp->userName << " \n";
                    temp = temp->next;
                } while (temp != *root);
            }
        }
    }

    static void showMovie(UserNode** root, MovieList::MovieNode** rootM, MovieList::MovieNode** headReferance, string commandTitle, int movieId){
        UserNode* temp = *root;
        do {
            UsersMovie* tempMovieHead = temp->moviesHead;
            if(temp->moviesHead != nullptr) {
                do {
                    if(temp->moviesHead->movieID == movieId){
                        cout << temp->moviesHead->movieID << " " << temp->moviesHead->movieTitle << " " << temp->moviesHead->movieYear << " Checked out by User " << temp->userID << endl;
                        return;
                    }
                    temp->moviesHead = temp->moviesHead->next;
                } while (temp->moviesHead != tempMovieHead);
            }
            temp = temp->next;

        } while (temp != *root);
        MovieList::printList(rootM, headReferance, commandTitle, movieId);
    }

    static void showUser(UserNode** root, int userId){
        UserNode* temp = *root;
        do {
            if(temp->userID == userId) {
                cout << "User id: " << temp->userID << " User name: " << temp->userName << endl;
                cout << "User " << temp->userID << " checked out the following Movies:\n";
                UsersMovie* tempMovieHead = temp->moviesHead;
                if(temp->moviesHead != nullptr) {
                    cout << "Movie id - Movie name - Year\n";
                    do {
                        cout << temp->moviesHead->movieID << " " << temp->moviesHead->movieTitle << " " << temp->moviesHead->movieYear << endl;
                        temp->moviesHead = temp->moviesHead->next;
                    } while (temp->moviesHead != tempMovieHead);
                }
                return;
            }
            temp = temp->next;
        } while (temp != *root);
        cout << "User " << userId << " does not exist\n";
    }

    static void returnMovie(UserNode** root, MovieList::MovieNode** rootM, MovieList::MovieNode** headReferance, string commandTitle, int movieId){
        UserNode* temp = *root;
        do {
            UsersMovie* tempMovieHead = temp->moviesHead;
            if(temp->moviesHead != nullptr) {
                do {
                    if(temp->moviesHead->next == temp->moviesHead && temp->moviesHead->movieID == movieId) {
                        MovieList::push(rootM, temp->moviesHead->movieID, temp->moviesHead->movieTitle,temp->moviesHead->movieYear, commandTitle);
                        temp->moviesHead = nullptr;
                        return;
                    }
                    UsersMovie *last = temp->moviesHead, *d;
                    if(temp->moviesHead->movieID == movieId){
                        while (last->next != temp->moviesHead) {
                            last = last->next;
                        }
                        MovieList::push(rootM,last->next->movieID,last->next->movieTitle,last->next->movieYear,commandTitle);
                        last->next = temp->moviesHead->next;
                        temp->moviesHead = last->next;
                        return;

                    }else if (temp->moviesHead->next != temp->moviesHead && temp->moviesHead->movieID != movieId){
                        while (last->next != temp->moviesHead && last->next->movieID != movieId) {
                            last = last->next;
                        }
                        // If node to be deleted was found
                        if (last->next->movieID == movieId) {
                            MovieList::push(rootM,last->next->movieID,last->next->movieTitle,last->next->movieYear,commandTitle);
                            d = last->next;
                            last->next = d->next;
                            return;
                            //cout << "Movie " << d->movieID << " has been checked out\nMovie " << d->movieID << " has been deleted\n";

                        } else {
                            cout << "Movie " << movieId << " not exist in the library\n";

                        }
                    }
                    //cout <<"\nTEMP= "<< temp->moviesHead->movieID<<"\nTEMP NEXT = " << temp->moviesHead->next->movieID<<"\nTEMPhead = " << tempMovieHead->movieID << endl;

                    temp->moviesHead = temp->moviesHead->next;
                } while (temp->moviesHead != tempMovieHead);
            }
            temp = temp->next;
        } while (temp != *root);
        MovieList::printList(rootM, headReferance, commandTitle, movieId);
    }
};


#endif //LIBRARYSYSTEM_USERLIST_H
