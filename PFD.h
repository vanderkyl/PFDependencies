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
#include <vector>
#include <queue>
#include <functional> //reference_wrapper

using namespace std;

class Vertex
{
    static int id_for_num;
    public:
        int num;
        int num_pre; //number of predecessors the vertex has

        vector<reference_wrapper<Vertex>> succeeders; //a set of vertices that this vertex points to

        Vertex()
        {
            num = ++id_for_num;
            num_pre = 0;
        }
};

//function object for the comparison in priority queue of verticses with no predecessors
class Comp_q
{
public:
    bool operator()(Vertex v1, Vertex v2) 
    {
       return v1.num > v2.num;
    }
};

// ---------
// solve_PFD
// ---------

void solve_PFD (std::istream&, std::ostream&);

// ---------
// init_container
// ---------

int get_rules_size (std::istream&);

// ---------
// read_rules
// ---------

void read_rules(istream&, int, vector<Vertex>&);

// ---------
// read_rule
// ---------

void read_rule(istream&, vector<Vertex>&);

// ---------
// eval_PFD
// ---------

void eval_PFD (vector<Vertex>&, ostream&);

// ---------
// remove_predecessors_and_transfer
// ---------

void remove_predecessors_and_transfer (vector<reference_wrapper<Vertex>>&, priority_queue<reference_wrapper<Vertex>, vector<reference_wrapper<Vertex>>, Comp_q>&);

// ---------
// print_vertex
// ---------

void print_vertex (ostream&, int) ;

#endif // PFD_h
