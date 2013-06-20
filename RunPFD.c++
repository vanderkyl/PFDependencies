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

// --------
// includes
// --------

#include <iostream> // cin, cout, ios_base


#include <set>
#include <vector>
#include <cstdio> //for NULL
#include <cstdlib> //for rand
#include <ctime>


#define N 10

using namespace std;

#include "PFD.h"


void generate_tests (int test_size)
{
   srand(time(NULL));

   while(test_size-- >= 0)
   {  
     int n = rand() % N + 1;
     int m ;
     do
     {
      m = rand() % n;
     }while(m == n);
     int vertics_being_pointed;
     int preceder_vertics;
     int preceder_size;
     vector< set<int> > record(n + 1);
     set<int> current_record;
     vector<int> vertics_being_pointed_record(n + 1, 0);
     cout << n << " " << m << endl;

     while (m-- != 0)
     {
        do
        {
          vertics_being_pointed = rand() % n + 1;
        }while(vertics_being_pointed_record[vertics_being_pointed] == 1);

        vertics_being_pointed_record[vertics_being_pointed] = 1;

        cout << vertics_being_pointed << " ";

        do
        {
          preceder_size = rand() % (n - record[vertics_being_pointed].size());
        }while(preceder_size == 0);

        cout << preceder_size << " ";

        while(--preceder_size >= 0)
        {
          do
          {
            preceder_vertics = rand() % n + 1;
          }while((record[vertics_being_pointed].find(preceder_vertics) != record[vertics_being_pointed].end()) || (current_record.find(preceder_vertics) != current_record.end()) 
            || (preceder_vertics == vertics_being_pointed));

          cout << preceder_vertics << " ";

          record[preceder_vertics].insert(vertics_being_pointed);
          current_record.insert(preceder_vertics);
        }

        current_record.clear();
        cout << endl;
     }
     cout << endl;
     record.clear();
     vertics_being_pointed_record.clear();
   }

}


// ----
// main
// ----

int main () {

    generate_tests (200);

    //using namespace std;
    //ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    
    //solve_PFD(cin, cout);
    return 0;}
