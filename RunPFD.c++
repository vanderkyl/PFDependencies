// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// -------------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall Collatz.c++ RunCollatz.c++ -o RunCollatz
    % valgrind RunCollatz < RunCollatz.in > RunCollatz.out

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

#define TEST_SIZE 1

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