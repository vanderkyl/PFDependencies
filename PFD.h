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

/**
 * Object the represents the task
 */
class Vertex
{
    public:
        int num; /*!<the number that represents the task */
        int num_pre; /*!<number of predecessors the vertex has */

        vector<Vertex*> succeeders; /*!<a set of vertices that this vertex points to*/

        /**
        * Default constructor
        */
        Vertex()
        {
            num_pre = 0;
        }
};

/**
 * function object for the comparison in priority queue of verticses with no predecessors
 */
class Comp_q
{
public:
    /**
    * Overload operator (function call) for the comparsion
    * @param v1 a pointer to Vertex
    * @param v2 a pointer to Vertex
    * @return true if the num of v1 is larger than that of v2, false otherwise
    */
    bool operator()(Vertex* v1, Vertex* v2) 
    {
       return v1->num > v2->num;
    }
};

/**
 * function object for getting vertex with no predecessors after the initialization
 */
class Transfer_vertices
{
public:
    priority_queue<Vertex*, vector<Vertex*>, Comp_q>* vertices_no_p; /*!<a pointer to priority queue to hold the queue the verticses get transfered to */

    /**
    * Constructor
    * @param q the priority queue that the verticses get transfered to
    */
    Transfer_vertices(priority_queue<Vertex*, vector<Vertex*>, Comp_q>* q)
    {
        vertices_no_p = q;
    }

    /**
    * Overload operator (function call) for the transfer
    * @param v a reference to Vertex that might get possible get transferred
    */
    void operator()(Vertex& v) 
    {
       if(v.num_pre == 0)
        {
            vertices_no_p->push(&v);
        }
    }
};

/**
 * function object for reducing number of predecessors
 */
class Remove_predecessors
{
public:
    priority_queue<Vertex*, vector<Vertex*>, Comp_q>* vertices_no_p; /*!<a pointer to priority queue to hold the queue from which the reduction of number of predecessors occurs*/

    /**
    * Constructor
    * @param q the priority queue from which the reduction of number of predecessors occurs
    */
    Remove_predecessors(priority_queue<Vertex*, vector<Vertex*>, Comp_q>* q)
    {
        vertices_no_p = q;
    }

    /**
    * Overload operator (function call) for the reduction of number of predecessors
    * @param v a pointer to Vertex whose number of predecessors get reduced
    */
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

/**
* solve the PFD problem given input and output stream
* @param r reference to input stream
* @param w reference to output stream
*/
void solve_PFD(istream& r, ostream& w);

// ---------
// read_rules
// ---------

/**
* read in the input of rules to construct the desired structure for the vector
* @param r reference to input stream
* @param rules_size the number of rules
* @param vertices vector reference where the construction occurs
*/
void read_rules(istream& r, int rules_size, vector<Vertex>& vertices);

// ---------
// read_rule
// ---------

/**
* read in the a single line of rule to construct the desired structure for the vector
* @param r reference to input stream
* @param vertices vector reference where the construction occurs
*/
void read_rule(istream& r, vector<Vertex>& vertices);

// ---------
// eval_PFD
// ---------

/**
* write the solution out
* @param vertices reference to vector
* @param w reference to output stream
*/
void eval_PFD (vector<Vertex>& vertices, ostream& w);

// ---------
// print_vertex
// ---------

/**
* print out a number that represents a task
* @param w reference to output stream
* @param i an integer number the represents the task
*/
void print_vertex (ostream& w, int i);

// ---------
// solved
// ---------

/**
* check if all Vertex in the vector have number of predecessors of 0
* @param vertices reference to vector
* @return boolean (if all numbersof predecessors are 0)
*/
bool solved(vector<Vertex>& vertices);

#endif // PFD_h
