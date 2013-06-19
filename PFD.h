// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------

#ifndef PFD_h
#define PFD_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <set>
#include <vector>

using namespace std;
// ---------
// solve_PFD
// ---------

void solve_PFD (std::istream&, std::ostream&);

// ---------
// init_container
// ---------

int init_container (std::istream&, vector< set<int> >&);

// ---------
// get_task
// ---------

int get_task_size (std::istream&);

// ---------
// get_rules_size
// ---------

int get_rules_size (std::istream&);

// ---------
// process_lines
// ---------

void process_lines (std::istream&, int, vector< set<int> >&);

// ---------
// process_line
// ---------

void process_line (std::istream&, vector< set<int> >&);

// ---------
// add_pred
// ---------

void add_pred (set<int>&, int);

// ---------
// eval_PFD
// ---------

bool eval_PFD (vector< set<int> >&, std::ostream&);

// ---------
// remove_pred
// ---------

void remove_pred (vector< set<int> >&, int);

// ---------
// print_PFD
// ---------

void print_PFD (std::ostream&, int);

#endif // PFD_h
