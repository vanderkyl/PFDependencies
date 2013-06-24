// ----------------------------
// Copyright (C) 2013
// Ka Seng Chou, Kyle VanderHoof
// ----------------------------

#ifndef PFD_h
#define PFD_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <vector>
#include <queue>

using namespace std;

// --------
// classes
// --------

class Vertex
{
    public:
        int num;
        int num_pre; //number of predecessors the vertex has

        vector<Vertex*> succeeders; //a set of vertices that this vertex points to

        Vertex()
        {
            num_pre = 0;
        }
};

//function object for the comparison in priority queue of verticses with no predecessors
class Comp_q
{
public:
    bool operator()(Vertex* v1, Vertex* v2) 
    {
       return v1->num > v2->num;
    }
};

//function object for getting vertex with no predecessors after the initialization
class Transfer_vertices
{
public:
    priority_queue<Vertex*, vector<Vertex*>, Comp_q>* vertices_no_p;

    Transfer_vertices(priority_queue<Vertex*, vector<Vertex*>, Comp_q>* q)
    {
        vertices_no_p = q;
    }

    void operator()(Vertex& v) 
    {
       if(v.num_pre == 0)
        {
            vertices_no_p->push(&v);
        }
    }
};

//function object for removing number of predecessors
class Remove_predecessors
{
public:
    priority_queue<Vertex*, vector<Vertex*>, Comp_q>* vertices_no_p;

    Remove_predecessors(priority_queue<Vertex*, vector<Vertex*>, Comp_q>* q)
    {
        vertices_no_p = q;
    }

    void operator()(Vertex* v) 
    {
        if(--(v->num_pre) == 0)
        {
            vertices_no_p->push(v);
        }
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
// print_vertex
// ---------

void print_vertex (ostream&, int) ;

// ---------
// solved
// ---------

bool solved(vector<Vertex>&);

#endif // PFD_h
