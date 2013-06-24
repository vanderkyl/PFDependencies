// ----------------------------
// Copyright (C) 2013
// Ka Seng Chou, Kyle VanderHoof
// ----------------------------

// --------
// defines
// --------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

#define TEST_SIZE 1

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <vector>
#include <queue>
#include <algorithm> //for_each

using namespace std;

// --------
// classes
// --------

class Vertex
{
    public:
        static int id_for_num;
        int num;
        int num_pre; //number of predecessors the vertex has

        vector<Vertex*> succeeders; //a set of vertices that this vertex points to

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

    bool operator()(Vertex& v) 
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

    bool operator()(Vertex* v) 
    {
        if(--(v->num_pre) == 0)
        {
            vertices_no_p->push(v);
        }
    }
};


// --------
// function prototypes
// --------

void solve_PFD (std::istream&, std::ostream&);
int get_rules_size (std::istream&);
void read_rules(istream&, int, vector<Vertex>&);
void read_rule(istream&, vector<Vertex>&);
void eval_PFD (vector<Vertex>&, ostream&);
void remove_predecessors_and_transfer (vector<Vertex*>&, priority_queue<Vertex*, vector<Vertex*>, Comp_q>&);
void print_vertex (ostream&, int) ;

void solve_PFD(istream& r, ostream& w)
{
    Vertex::id_for_num = 0;
    int task_size, rules_size;
    r >> task_size;
    r >> rules_size;

    //create a vector of Verticses, each vertex represents a task
    vector<Vertex> vertices(task_size);

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

// ----
// main
// ----

int main () {
    
    int test_size = TEST_SIZE;

    while(test_size-- != 0)
    {
        solve_PFD(cin, cout);
        cout << endl << endl;
    }
    
    return 0;
}