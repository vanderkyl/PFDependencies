// ----------------------------
// Copyright (C) 2013
// Ka Seng Chou, Kyle VanderHoof
// ----------------------------

#include <iostream> // cin, cout, ios_base
#include <set>
#include <vector>
#include <cstdio> //for NULL
#include <cstdlib> //for rand
#include <ctime>

using namespace std;

void generate_tests(int);
void generate_test();
int get_n();
int get_m(int);
void initialize_removable(set<int>&, int, int);
int get_target(set<int>&, int);
int get_preceder_size(int);
int get_preceder(int, set<int>&, set<int>&, int);
void generate_preceders(int, set<int>&, int, int);
bool check_valid_preceder(int, int, set<int>&, set<int>&);
bool check_printed(set<int>&, int);


#define N 100
#define TEST_NUMBER 100


int main()
{
  srand(time(NULL));
	generate_tests(TEST_NUMBER);
}

void generate_tests(int tests_num)
{
	while(tests_num-- != 0)
	{
		generate_test();
	}
}

void generate_test()
{
	int n = rand() % N + 1;
	int m = get_m(n);

   int target;
   int preceder_size;
   set<int> removable;
   cout << n << " " << m << endl;

   initialize_removable(removable, n - m, n);
   while(removable.size() != n)
   {
      target = get_target(removable, n);

      cout << target << " ";

      preceder_size = get_preceder_size(removable.size());

      cout << preceder_size << " ";

      generate_preceders(target, removable, n, preceder_size);
      removable.insert(target);
      cout << endl;
   }
   cout << endl;
}

int get_n()
{
	return rand() % N + 1;
}

int get_m(int n)
{
	int m;
	do
 	{
	  m = rand() % n;
	}while(m == n);
	return m;
}

void initialize_removable(set<int>& removable, int size, int n)
{
  set<int> added;
  int target;
  while(size-- != 0)
  {
    do
    {
      target = rand() % n + 1;
    }while(added.find(target) != added.end());
    added.insert(target);
    removable.insert(target);
  }
}

int get_target(set<int>& record, int n)
{	
	int target;
	do
  {
		target = rand() % n + 1;
  }while(record.find(target) != record.end());
  return target;
}

int get_preceder_size(int max)
{
  return rand() % max + 1;
}

void generate_preceders(int succeeder, set<int>& record, int n, int size)
{
	set<int> check_duplicate_set;

	int preceder;

	 while(size-- != 0)
    {
      preceder = get_preceder(succeeder, check_duplicate_set, record, n);

      cout << preceder << " ";

      check_duplicate_set.insert(preceder);
    }
}

int get_preceder(int succeeder, set<int>& check_duplicate_set, set<int>& record, int n)
{	
	int preceder;
	do
    {
      preceder = rand() % n + 1;
    }while(!check_valid_preceder(preceder, succeeder, check_duplicate_set, record));
    return preceder;
}

bool check_valid_preceder(int preceder, int succeeder, set<int>& check_duplicate_set, set<int>& record)
{
	return (record.find(preceder) != record.end()) &&  check_printed(check_duplicate_set, preceder) && (preceder != succeeder);
}

bool check_printed(set<int>& record, int vertex)
{
	return record.find(vertex) == record.end();
}
