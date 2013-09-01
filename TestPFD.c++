// --------------------------------
// projects/PFD/TestPFD.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall PFD.c++ TestPFD.c++ -o TestPFD -lcppunit -ldl
    % valgrind TestPFD >& TestPFD.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>
#include <algorithm>
#include <cstdio>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "PFD.h"

class Match_vertex
{
public:
	int value;
	Match_vertex(int x)
	{
		value = x;
	}
	bool operator()(Vertex *v)
	{
		if(v->num == value)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
		
// -----------
// TestPFD
// -----------

struct TestPFD : CppUnit::TestFixture {

    // ---------
    // solve_PFD
    // ---------
    
    void test_solve_1 () 
    {
        std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        std::ostringstream w;
        solve_PFD(r, w);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4 ");
    }

    void test_solve_2 () 
    {
        std::istringstream r("5 0");
        std::ostringstream w;
        solve_PFD(r, w);
        CPPUNIT_ASSERT(w.str() == "1 2 3 4 5 ");
    }

    void test_solve_3 () 
    {
        std::istringstream r("17 12\n12 5 15 1 3 6 8\n5 5 12 3 6 15 8\n13 5 12 5 8 6 1\n4 4 12 5 15 13\n2 5 15 3 1 6 5\n14 3 1 5 2\n10 9 13 1 5 12 14 8 4 2 15\n7 8 8 1 10 14 6 12 4 3\n17 4 14 13 15 5\n16 13 2 12 10 14 6 15 8 3 17 1 13 4 5\n9 2 8 17\n11 4 16 10 7 14");
        std::ostringstream w;
        solve_PFD(r, w);
        CPPUNIT_ASSERT(w.str() == "1 3 6 8 15 12 5 2 13 4 14 10 7 17 9 16 11 ");
    }
    
    // ----------
    // read_rules
    // ----------

    void test_read_rules_1 () 
    {
        std::istringstream r("");
        vector<Vertex> v(5);
        for(int i = 0, j = 1; i < 5; ++i, ++j)
        {
            v[i].num = j;
        }
        read_rules(r, 0, v);
        CPPUNIT_ASSERT(v[0].num_pre == 0);
        CPPUNIT_ASSERT(v[1].num_pre == 0);
        CPPUNIT_ASSERT(v[2].num_pre == 0);
        CPPUNIT_ASSERT(v[3].num_pre == 0);
        CPPUNIT_ASSERT(v[4].num_pre == 0);
    }
  
    void test_read_rules_2 () 
    {
        std::istringstream r("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        vector<Vertex> v(5);
        for(int i = 0, j = 1; i < 5; ++i, ++j)
        {
            v[i].num = j;
        }
        read_rules(r, 4, v);
        CPPUNIT_ASSERT(v.size() == 5);
    }

    void test_read_rules_3 () 
    {
        std::istringstream r("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        vector<Vertex> v(5);
        for(int i = 0, j = 1; i < 5; ++i, ++j)
        {
            v[i].num = j;
        }
        read_rules(r, 4, v);
        CPPUNIT_ASSERT(v[0].num_pre == 0);
        CPPUNIT_ASSERT(v[1].num_pre == 2);
        CPPUNIT_ASSERT(v[2].num_pre == 2);
        CPPUNIT_ASSERT(v[3].num_pre == 1);
        CPPUNIT_ASSERT(v[4].num_pre == 1);
        
        CPPUNIT_ASSERT(find_if(v[0].succeeders.begin(), v[0].succeeders.end(), Match_vertex(5)) != v	[0].succeeders.end()); 
        CPPUNIT_ASSERT(find_if(v[0].succeeders.begin(), v[0].succeeders.end(), Match_vertex(3)) != v	[0].succeeders.end()); 
        CPPUNIT_ASSERT(v[1].succeeders.empty()); 
        CPPUNIT_ASSERT(find_if(v[2].succeeders.begin(), v[2].succeeders.end(), Match_vertex(2)) != v	[2].succeeders.end()); 
        CPPUNIT_ASSERT(find_if(v[2].succeeders.begin(), v[2].succeeders.end(), Match_vertex(4)) != v	[2].succeeders.end()); 
        CPPUNIT_ASSERT(v[3].succeeders.empty());
        CPPUNIT_ASSERT(find_if(v[4].succeeders.begin(), v[4].succeeders.end(), Match_vertex(3)) != v	[4].succeeders.end());
        CPPUNIT_ASSERT(find_if(v[4].succeeders.begin(), v[4].succeeders.end(), Match_vertex(2)) != v	[4].succeeders.end());
        
    }

    // ---------
    // read_rule
    // ---------

    void test_read_rule_1 () 
    {
        std::istringstream r("4 1 3");
        vector<Vertex> v(5);
        for(int i = 0, j = 1; i < 5; ++i, ++j)
        {
            v[i].num = j;
        } 
        read_rule(r, v);
        CPPUNIT_ASSERT(v[3].num_pre == 1);
        CPPUNIT_ASSERT(find_if(v[2].succeeders.begin(), v[2].succeeders.end(), Match_vertex(4)) != v	[2].succeeders.end()); 
    }
  
    void test_read_rule_2 () 
    {
        std::istringstream r("18 5 8 6 4 1 17"); 
        vector<Vertex> v(20);
        for(int i = 0, j = 1; i < 20; ++i, ++j)
        {
            v[i].num = j;
        } 
        read_rule(r, v);
        CPPUNIT_ASSERT(v[17].num_pre == 5);
        
        CPPUNIT_ASSERT(find_if(v[7].succeeders.begin(), v[7].succeeders.end(), Match_vertex(18)) != v	[7].succeeders.end()); 
	CPPUNIT_ASSERT(find_if(v[5].succeeders.begin(), v[5].succeeders.end(), Match_vertex(18)) != v	[5].succeeders.end()); 
	CPPUNIT_ASSERT(find_if(v[3].succeeders.begin(), v[3].succeeders.end(), Match_vertex(18)) != v	[3].succeeders.end()); 
	CPPUNIT_ASSERT(find_if(v[0].succeeders.begin(), v[0].succeeders.end(), Match_vertex(18)) != v	[0].succeeders.end()); 
	CPPUNIT_ASSERT(find_if(v[16].succeeders.begin(), v[16].succeeders.end(), Match_vertex(18)) != v	[16].succeeders.end()); 
        
    }

    void test_read_rule_3 () 
    {
        std::istringstream r("3 1 2");
        vector<Vertex> v(4);
        for(int i = 0, j = 1; i < 4; ++i, ++j)
        {
            v[i].num = j;
        } 
        read_rule(r, v);
        CPPUNIT_ASSERT(v[2].num_pre == 1);
    }

    // --------
    // eval_PFD
    // --------

    void test_eval_1 () 
    {
        std::istringstream r("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
	std::ostringstream w;
        int m = 4; 
        vector<Vertex> v(5);
        for(int i = 0, j = 1; i < 5; ++i, ++j)
        {
            v[i].num = j;
        }
	read_rules(r, m, v);
        eval_PFD(v, w);
        CPPUNIT_ASSERT(w.str() == "1 5 3 2 4 ");
    }
  
    void test_eval_2 () 
    {
	std::istringstream r("");
        std::ostringstream w;
        int m = 0; 
        vector<Vertex> v(5);
        for(int i = 0, j = 1; i < 5; ++i, ++j)
        {
            v[i].num = j;
        }
        read_rules(r, m, v);
        eval_PFD(v, w);
	CPPUNIT_ASSERT(w.str() == "1 2 3 4 5 ");
    }

    void test_eval_3 () 
    {
        std::istringstream r("12 5 15 1 3 6 8\n5 5 12 3 6 15 8\n13 5 12 5 8 6 1\n4 4 12 5 15 13\n2 5 15 3 1 6 5\n14 3 1 5 2\n10 9 13 1 5 12 14 8 4 2 15\n7 8 8 1 10 14 6 12 4 3\n17 4 14 13 15 5\n16 13 2 12 10 14 6 15 8 3 17 1 13 4 5\n9 2 8 17\n11 4 16 10 7 14");
	std::ostringstream w;
        int m = 12;
        vector<Vertex> v(17);
        for(int i = 0, j = 1; i < 17; ++i, ++j)
        {
            v[i].num = j;
        }
        read_rules(r, m, v);
        eval_PFD(v, w);
	CPPUNIT_ASSERT(w.str() == "1 3 6 8 15 12 5 2 13 4 14 10 7 17 9 16 11 ");
    }

    // ------------
    // print_vertex
    // ------------

    void test_print_1 () 
    {
        int i = 99;
	std::ostringstream w;
        print_vertex(w, i);
        CPPUNIT_ASSERT(w.str() == "99 ");
    }
  
    void test_print_2 () 
    {
	int i = 1;
	std::ostringstream w;
        print_vertex(w, i);
        CPPUNIT_ASSERT(w.str() == "1 ");
    }

    void test_print_3 () 
    {
	int i = 53;
	std::ostringstream w;
        print_vertex(w, i);
        CPPUNIT_ASSERT(w.str() == "53 ");
    }

    // ------
    // solved
    // ------

    void test_solved_1 () 
    {
	vector<Vertex> v(17);
        for(int i = 0, j = 1; i < 17; ++i, ++j)
        {
            v[i].num = j;
        }
        v[4].num_pre = 2;
        bool s = solved(v);
        CPPUNIT_ASSERT(s == false);
    }
  
    void test_solved_2 () 
    {
	vector<Vertex> v(5);
        for(int i = 0, j = 1; i < 5; ++i, ++j)
        {
            v[i].num = j;
        }
        v[0].num_pre = 1;
        bool s = solved(v);
        CPPUNIT_ASSERT(s == false);
    }

    void test_solved_3 () 
    {
	vector<Vertex> v(5);
        for(int i = 0, j = 1; i < 5; ++i, ++j)
        {
            v[i].num = j;
        }
        bool s = solved(v);
        CPPUNIT_ASSERT(s == true);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_read_rules_1);
    CPPUNIT_TEST(test_read_rules_2);
    CPPUNIT_TEST(test_read_rules_3);
    CPPUNIT_TEST(test_read_rule_1);
    CPPUNIT_TEST(test_read_rule_2);
    CPPUNIT_TEST(test_read_rule_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solved_1);
    CPPUNIT_TEST(test_solved_2);
    CPPUNIT_TEST(test_solved_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestPFD.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestPFD::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
