// ----------------------------
// projects/PFD/PFD.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

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

// -------------
// PFD_print
// -------------

/* Print out the results */
void print_PFD (ostream& w, int i) {
    assert(i > 0);
    w << i << " ";}



int main()
{
    solve_PFD(cin, cout);
}