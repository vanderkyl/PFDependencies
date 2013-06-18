// ----------------------------
// projects/PFD/PFD.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

<<<<<<< HEAD
#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <set>
#include <vector>

//#include "PFD.h"

using namespace std;

void solve_PFD(istream&, ostream&);
int init_container(istream&, vector< set<int> >&);
void process_lines(istream&, int, vector< set<int> >&);
void process_line(istream&, vector< set<int> >&);
void add_predecessor(set<int>&, int);
bool eval_PFD (vector< set<int> >&, ostream&);
void remove_predecessor (vector< set<int> >&, int);
void print_PFD (ostream&, int);
void PFD_solve (istream&, ostream&);




void solve_PFD(istream& r, ostream& w)
{
    vector< set<int> > v;
    int lines = init_container(r, v);
    process_lines(r, lines, v);
    while (eval_PFD(v, w));
}

int init_container(istream& r, vector< set<int> >& v)
{
    if(!r)
    {
        return -1;
    }
    int n, m;
    r >> n;
    r >> m;
    v.reserve(n + 1);

    return m;
}

void process_lines(istream& r, int lines, vector< set<int> >& v)
{
    while(lines-- != 0)
    {
        process_line(r, v);
    }
}

void process_line(istream& r, vector< set<int> >& v)
{
    int index, num_predecessors, elem;

    r >> index;
    r >> num_predecessors;

    while(num_predecessors-- != 0)
    {
        r >> elem;
        add_predecessor(v[index], elem);
    }
}

void add_predecessor(set<int>& s, int elem)
{
    s.insert(elem);
}

bool eval_PFD (vector< set<int> >& v, ostream& w)
{
    for (int i = 1; i < (int)v.size(); ++i)
    {
        if(v[i].empty())
        {
            print_PFD(w, i);
            v[i].insert(101);
            remove_predecessor (v, i);
            return true;
        }
    }
    return false;
}
 

void remove_predecessor (vector< set<int> >& v, int i)
{
    for (int i = 1; i < (int)v.size(); ++i)
    {
        v[i].erase(i);
    }
}
=======
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
    

>>>>>>> d9b4f3d3e7990411a728d6b2cd3ef60c5396bbf4

// -------------
// PFD_print
// -------------

/* Print out the results */
<<<<<<< HEAD
void print_PFD (ostream& w, int i) {
    assert(i > 0);
    w << i << " ";}



int main()
{
    solve_PFD(cin, cout);
}
=======
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
>>>>>>> d9b4f3d3e7990411a728d6b2cd3ef60c5396bbf4
