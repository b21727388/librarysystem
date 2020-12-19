#include <iostream>
#include <fstream>
#include "LibrarySystem.h"

using namespace std;

int main(int argc, char** argv) {
    freopen(argv[2], "w", stdout);
    LibrarySystem librarySystem;
    librarySystem.ReadFile(argv[1]);
    return 0;
}