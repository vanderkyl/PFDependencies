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
#include <functional> //reference_wrapper
#include <algorithm> //for_each

#include "PFD.h"

using namespace std;

class Vertex
{
    static int id_for_num;
    public:
        int num;
        int num_pre; //number of predecessors the vertex has

        set<reference_wrapper<vertex>> succeeders; //a set of vertices that this vertex points to

        Vertex()
        {
            num = ++id_for_num;
            num_pre = 0;
        }
};
int Vertex::id_for_num = 0;

//function object for the comparison in priority queue of verticses with no predecessors
class Comp_q
{
public:
    bool operator()(Vertex& v1, Vertex& v2) 
    {
       return v1.num > v2.num;
    }
};

void solve_PFD(istream& r, ostream& w)
{
    int task_size, rules_size;
    r >> task_size;
    r >> rules_size;

    //create a vector of Verticses, each vertex represents a task
    vector<Vertex> vertices(task_size + 1); //add 1 beacuse the index 0 is not used

    read_rules(r, rules_size, v);

    eval_PFD(v, w);
}

void read_rules(istream& r, int rules_size, vector<Vertex>& vertices)
{
    while(rules_size-- != 0)
    {
        read_rule(r, v);
    }
}

void read_rule(istream& r, vector<Vertex>& v)
{
    int index, predecessors_size, predecessor;

    r >> index;
    r >> predecessors_size;

    v[index].num_pre = predecessors_size;

    while(predecessors_size-- != 0)
    {
        r >> predecessor;
        v[predecessor].succeeders.insert(v[index]);
    }
}


void eval_PFD (vector<Vertex>& v, ostream& w)
{
    //priority queue for verticses with no predecessors
    priority_queue<reference_wrapper<Vertex>, vector<reference_wrapper<Vertex>>, Comp_q_no_p> vertices_no_p();

    //push the Vertices in their corresponding queues
    for_each(v.begin(), v.end(), [&vertices_no_p](Vertex& v){
        if(v.num_pre == 0)
        {
            vertices_no_p.push(v);
        }
    });

    int vertex, ;
    while(!vertices_no_p.empty())
    {
        vertex = vertices_no_p.top().get().num;
        print_vertex(w, vertex);

        vertices_no_p.pop();

        //decreases the number of predecessors and push it to the queue of vertices with no predecessors if number of predecessors reach 0
        remove_predecessors_and_transfer(vertices_no_p.top().get().succeeders, vertices_no_p);
    }

}

void remove_predecessors_and_transfer (set<reference_wrapper<vertex>>& succeeders, priority_queue<reference_wrapper<Vertex>, vector<reference_wrapper<Vertex>>, Comp_q_no_p> vertices_no_p)
{
    //decreases the number of predecessors of all succeeders by 1 and push it to the queue of vertices with no predecessors if number of predecessors reach 0
    for_each(succeeders.begin(), succeeders.end(), [](Vertex& v){
        if(--v.num_pre == 0)
        {
            vertices_no_p.push(v);
        }
    });
}

void print_vertex (ostream& w, int i) 
{
    assert(i > 0);
    w << i << " ";
}