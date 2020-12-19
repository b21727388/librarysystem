//
// Created by Beşir Kassab on 27.11.2020.
//

#ifndef LIBRARYSYSTEM_LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_LIBRARYSYSTEM_H
#include <string>

class LibrarySystem{
public:
    LibrarySystem();
    ~LibrarySystem();

    static void ReadFile(std::string filePath);

    static void addMovie(int movieId, std::string movieTitle, int year);
    static void deleteMovie(int movieId);

    static void addUser(int userId, std::string userName);
    static void deleteUser(int userId);

    static void checkoutMovie(int movieId, int userId);
    static void returnMovie(int movieId);

    static void showAllMovies();
    static void showMovie(int movieId);
    static void showUser(int userId);
};


#endif //LIBRARYSYSTEM_LIBRARYSYSTEM_H
