// ----------------------------
// Copyright (C) 2013
// Ka Seng Chou, Kyle VanderHoof
// ----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall PFD.c++ RunPFD.c++ -o RunPFD
    % valgrind RunPFD < RunPFD.in > RunPFD.out

To configure Doxygen:
    % doxygen -g
That creates the file "Doxyfile".
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    % doxygen Doxyfile
*/

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

#define TEST_SIZE 100

// --------
// includes
// --------

#include <iostream> // cin, cout, ios_base

using namespace std;

#include "PFD.h"

// ----
// main
// ----

int main () {
    
    int test_size = TEST_SIZE;

    while(test_size-- != 0)
    {
        solve_PFD(cin, cout);
        cout << endl << endl;
    }
    
    return 0;
}