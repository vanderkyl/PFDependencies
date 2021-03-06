// ----------------------------
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
#include <cstdio> //for NULL

#include "PFD.h"

using namespace std;

void solve_PFD(istream& r, ostream& w)
{
    assert(r != NULL);
    assert(w != NULL);

    int task_size, rules_size;
    r >> task_size;
    r >> rules_size;

    assert(task_size > 0);
    assert(task_size <= 100);
    assert(rules_size >= 0);
    assert(rules_size < task_size);

    //create a vector of Verticses, each vertex represents a task
    vector<Vertex> vertices(task_size);
    //assign the corresponding number the Vertices represent
    for(int i = 0, j = 1; i < (int)vertices.size(); ++i, ++j)
    {
        vertices[i].num = j;
    }

    read_rules(r, rules_size, vertices);

    eval_PFD(vertices, w);
}

void read_rules(istream& r, int rules_size, vector<Vertex>& vertices)
{
    assert(r != NULL);
    assert(rules_size >= 0);
    assert(rules_size < 100);
    assert(!vertices.empty());
    assert(vertices.size() <= 100);

    while(rules_size-- != 0)
    {
        read_rule(r, vertices);
    }
}

void read_rule(istream& r, vector<Vertex>& vertices)
{
    assert(r != NULL);
    assert(!vertices.empty());
    assert(vertices.size() <= 100);

    int index, predecessors_size, predecessor;

    r >> index;
    r >> predecessors_size;

    assert(index > 0);
    assert(index <= 100);
    assert(predecessors_size >= 0);
    assert(predecessors_size < 100);

    vertices[index-1].num_pre = predecessors_size;

    while(predecessors_size-- != 0)
    {
        r >> predecessor;
        vertices[predecessor-1].succeeders.push_back(&vertices[index-1]);
    }
}


void eval_PFD (vector<Vertex>& vertices, ostream& w)
{
    assert(w != NULL);
    assert(!vertices.empty());
    assert(vertices.size() <= 100);

    //priority queue for verticses with no predecessors (cache)
    priority_queue<Vertex*, vector<Vertex*>, Comp_q> vertices_no_p;

    //push the Vertices with no predecessors to the cache
    for_each(vertices.begin(), vertices.end(), Transfer_vertices(&vertices_no_p));
    
    assert(!vertices_no_p.empty()); //the problem is solvable

    int vertex;
    vector<Vertex*>* succeeders;
    while(!vertices_no_p.empty()) //print task with no predecessor one by one
    {
        vertex = vertices_no_p.top()->num;
        succeeders = &(vertices_no_p.top()->succeeders);
        
        print_vertex(w, vertex);
        
        vertices_no_p.pop();

        //decreases the number of predecessors of all succeeders by 1 and push it to the queue of vertices with no predecessors if number of predecessors reach 0
        for_each(succeeders->begin(), succeeders->end(), Remove_predecessors(&vertices_no_p));
    }

    assert(solved(vertices)); //all tasks have been displayed (test if all tasks have no predecessor)
}

void print_vertex (ostream& w, int i) 
{
    assert(i > 0);
    assert(i <= 100);
    w << i << " ";
}

bool solved(vector<Vertex>& vertices)
{
    assert(!vertices.empty());
    assert(vertices.size() <= 100);

    for(int i = 0; i < (int)vertices.size(); ++i)
    {
        if(vertices[i].num_pre != 0)
        {
            return false;
        }
    }
    return true;
}