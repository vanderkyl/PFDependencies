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

int get_task_size(istream&);
int get_rules_size(istream&);
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
    vector< set<int> > v(get_task_size(r) + 1);
    process_lines(r, get_rules_size(r), v);
    while (eval_PFD(v, w));
}

int get_task_size(istream& r)
{
    int task_size;
    r >> task_size;
    return task_size;
}

int get_rules_size(istream& r)
{
    int rule_size;
    r >> rule_size;
    return rule_size;
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
 

void remove_predecessor (vector< set<int> >& v, int x)
{
    for (int i = 1; i < (int)v.size(); ++i)
    {
        v[i].erase(x);
    }
}
    
void print_PFD (ostream& w, int i) {
    assert(i > 0);
    w << i << " ";}



int main()
{
    solve_PFD(cin, cout);
}