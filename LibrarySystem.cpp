//
// Created by Beşir Kassab on 27.11.2020.
//

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "LibrarySystem.h"
#include "MovieList.h"
#include "UserList.h"

using namespace std;

MovieList::MovieNode* movieListHead = nullptr;
UserList::UserNode* userListHead = nullptr;
ofstream outputfile ;

string previousTitle = "";

void printTitle(string title){
    if(title != previousTitle){
        cout << "\n==="<< title << "() method test=== \n";

        previousTitle = title;
    }
}

void LibrarySystem::ReadFile(std::string filePath) {

    int counter = 0;
    ifstream file(filePath);
    string str;
    while (getline(file, str)){
        if(str.find("\r") != std::string::npos) {
            str = str.substr(0, str.length() - 1);
        }
        std::istringstream ss(str);
        std::string token;
        std::string lineArray[6];
        while(std::getline(ss, token, '\t')) {

            lineArray[counter++] = token;

        }
        counter = 0;

        if(lineArray[0] == "addMovie"){
            printTitle(lineArray[0]);
            addMovie(stoi(lineArray[1]), lineArray[2], stoi(lineArray[3]));

        }else if(lineArray[0] == "deleteMovie"){
            printTitle(lineArray[0]);
            deleteMovie(stoi(lineArray[1]));

        }else if(lineArray[0] == "addUser"){
            printTitle(lineArray[0]);
            addUser(stoi(lineArray[1]), lineArray[2]);

        }else if(lineArray[0] == "deleteUser"){
            printTitle(lineArray[0]);
            deleteUser(stoi(lineArray[1]));

        }else if(lineArray[0] == "checkoutMovie"){
            printTitle(lineArray[0]);
            checkoutMovie(stoi(lineArray[1]),stoi(lineArray[2]));

        }else if(lineArray[0] == "returnMovie"){
            printTitle(lineArray[0]);
            returnMovie(stoi(lineArray[1]));

        }else if(lineArray[0] == "showAllMovie"){
            printTitle(lineArray[0]);
            showAllMovies();

        }else if(lineArray[0] == "showMovie"){
            printTitle(lineArray[0]);
            showMovie(stoi(lineArray[1]));

        }else if(lineArray[0] == "showUser"){
            printTitle(lineArray[0]);
            showUser(stoi(lineArray[1]));

        }


    }
}



void LibrarySystem::addMovie(const int movieId, string movieTitle, const int year) {
    UserList::addMovie(&userListHead,&movieListHead,movieId,movieTitle,year,previousTitle);
    //MovieList::push(&movieListHead,movieId,movieTitle, year, previousTitle);
}

void LibrarySystem::addUser(const int userId, string userName) {
    UserList::push(&userListHead,userId,userName);
}

void LibrarySystem::checkoutMovie(const int movieId, const int userId) {
    if(movieListHead == nullptr){
        cout << "Movie " << movieId << " does not exist for checkout\n";
    }else {
        MovieList::MovieNode *movie = MovieList::FindMovie(&movieListHead, movieId);
        if (movie->movieID == movieId) {
            UserList::moviePush(&movie, &userListHead, userId, &movieListHead);
        }
    }
}


void LibrarySystem::deleteMovie(const int movieId) {
    UserList::deleteNode(&userListHead, &movieListHead, &movieListHead, previousTitle, movieId);

}

void LibrarySystem::deleteUser(const int userId) {
    UserList::deleteNode(&userListHead, &movieListHead, &movieListHead, previousTitle, userId);
}

void LibrarySystem::returnMovie(const int movieId) {
    if(movieListHead == nullptr && userListHead == nullptr){
        cout << "Movie " << movieId << " not exist in the library\n";
    }else {
        UserList::returnMovie(&userListHead, &movieListHead, &movieListHead, previousTitle, movieId);
    }
}

void LibrarySystem::showAllMovies() {
    cout << "Movie id - Movie name - Year - Status\n";
    UserList::printList(&userListHead, &movieListHead, &movieListHead, previousTitle);
}

void LibrarySystem::showMovie(const int movieId) {
    UserList::showMovie(&userListHead, &movieListHead, &movieListHead, previousTitle, movieId);
}

void LibrarySystem::showUser(const int userId) {
    UserList::showUser(&userListHead, userId);
}

LibrarySystem::LibrarySystem() {
    cout << "===Movie Library System===\n";
}

LibrarySystem::~LibrarySystem() {
}
