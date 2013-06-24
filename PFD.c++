// ----------------------------
// projects/PFD/PFD.c++
// Copyright (C) 2013
// Ka Seng Chou, Kyle VanderHoof
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <vector>
#include <queue>
#include <algorithm> //for_each

#include "PFD.h"

using namespace std;

void solve_PFD(istream& r, ostream& w)
{
    int task_size, rules_size;
    r >> task_size;
    r >> rules_size;

    //create a vector of Verticses, each vertex represents a task
    vector<Vertex> vertices(task_size);
    for(int i = 1; i <= (int)vertices.size(); ++i)
    {
        vertices[i - 1].num = i;
    }

    read_rules(r, rules_size, vertices);

    eval_PFD(vertices, w);
}

void read_rules(istream& r, int rules_size, vector<Vertex>& vertices)
{
    while(rules_size-- != 0)
    {
        read_rule(r, vertices);
    }
}

void read_rule(istream& r, vector<Vertex>& vertices)
{
    int index, predecessors_size, predecessor;

    r >> index;
    r >> predecessors_size;

    vertices[index-1].num_pre = predecessors_size;

    while(predecessors_size-- != 0)
    {
        r >> predecessor;
        vertices[predecessor-1].succeeders.push_back(&vertices[index-1]);
    }
}


void eval_PFD (vector<Vertex>& vertices, ostream& w)
{
    //priority queue for verticses with no predecessors (cache)
    priority_queue<Vertex*, vector<Vertex*>, Comp_q> vertices_no_p;

    //push the Vertices with no predecessors to the cache
    for_each(vertices.begin(), vertices.end(), Transfer_vertices(&vertices_no_p));
    
    int vertex;
    vector<Vertex*>* succeeders;
    while(!vertices_no_p.empty()) //print task with no predecessor one by one
    {
        vertex = vertices_no_p.top()->num;
        succeeders = &(vertices_no_p.top()->succeeders);
        
        print_vertex(w, vertex);
        
        vertices_no_p.pop();

        //decreases the number of predecessors and push it to the queue of vertices with no predecessors if number of predecessors reach 0
        remove_predecessors_and_transfer(*succeeders, vertices_no_p);
    }

}

void remove_predecessors_and_transfer (vector<Vertex*>& succeeders, priority_queue<Vertex*, vector<Vertex*>, Comp_q>& vertices_no_p)
{
    //decreases the number of predecessors of all succeeders by 1 and push it to the queue of vertices with no predecessors if number of predecessors reach 0
    for_each(succeeders.begin(), succeeders.end(), Remove_predecessors(&vertices_no_p));
}

void print_vertex (ostream& w, int i) 
{
    w << i << " ";
}
