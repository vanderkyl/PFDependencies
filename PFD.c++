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
#include <set>
#include <vector>

class Vertex
{
    public:
        int num;
        int num_pre;
        set<vertex&> succeeders;
        Vertex()
        {
            num_pre = 0;
        }
};


//#include "PFD.h"

using namespace std;

void solve_PFD(istream& r, ostream& w)
{
    vector<Vertex> v(get_task_size(r) + 1);
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

void process_lines(istream& r, int lines, vector<Vertex>& v)
{
    while(lines-- != 0)
    {
        process_line(r, v);
    }
}

void process_line(istream& r, vector<Vertex>& v)
{
    int index, num_predecessors, predecessor;

    r >> index;
    r >> num_predecessors;

    v[index].num_pre = num_predecessors;

    while(num_predecessors-- != 0)
    {
        r >> predecessor;
        v[predecessor].succeeders.insert(v[index]);
    }
}


bool eval_PFD (vector<Vertex>& v, ostream& w)
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
 

void remove_predecessor (vector<Vertex>& v, int x)
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