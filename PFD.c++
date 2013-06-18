// ----------------------------
// projects/PFD/PFD.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

#include "PFD.h"


// ------------
// PFD_read
// ------------
  
/* Reads the variable r and places the two ints given by
   r into i and j. Return false if invalid input.     */
int PFD_read_ (std::istream& r) {
    int num_task;
    r >> num_task;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}
    


// -------------
// PFD_print
// -------------

/* Print out the results */
void PFD_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}

// -------------
// PFD_solve
// -------------

/* Solve the problem by calling helper functions. */
void PFD_solve (std::istream& r, std::ostream& w) {
    int i;
    int j;


    while (PFD_read(r, i, j)) {
        const int v = PFD_eval(i, j);
        PFD_print(w, i, j, v);}}
