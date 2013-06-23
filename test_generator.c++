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
int get_new_head_vertex(vector<int>&, int);
int get_preceder_size(vector< set<int> >&, int, int);
int get_preceder(int, set<int>&, vector< set<int> >&, int);
void generate_preceders(int, vector< set<int> >&, int, int);
bool check_valid_preceder(int, int, set<int>&, vector< set<int> >&);
bool check_cyclic_condition(int, int, vector< set<int> >&);
bool check_printed(set<int>&, int);


#define N 10
#define TEST_NUMBER 10


int main()
{
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

     int vertics_being_pointed;
     int preceder_size;
     vector< set<int> > suc_record(n + 1);
     vector<int> vertics_printed_as_head(n + 1, 0);
     cout << n << " " << m << endl;

     while (m-- != 0)
     {
        vertics_being_pointed = get_new_head_vertex(vertics_printed_as_head, n);

        vertics_printed_as_head[vertics_being_pointed] = 1;

        cout << vertics_being_pointed << " ";

        preceder_size = get_preceder_size(suc_record, n, vertics_being_pointed);

        cout << preceder_size << " ";

        generate_preceders(vertics_being_pointed, suc_record, n, preceder_size);

        cout << endl;
     }
     cout << endl;
     suc_record.clear();
     vertics_printed_as_head.clear();
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

int get_new_head_vertex(vector<int>& record, int n)
{	
	int vertex;
	do
    {
  		vertex = rand() % n + 1;
    }while(record[vertex] == 1);
    return vertex;
}

int get_preceder_size(vector< set<int> >& record, int n, int vertex_point_to)
{
	int size;
	do
    {
  		size = rand() % (n - record[vertex_point_to].size());
    }while(size == 0);
    return size;
}

void generate_preceders(int succeeder, vector< set<int> >& record, int n, int size)
{
	set<int> check_duplicate_set;

	int preceder;

	 while(--size >= 0)
    {
      preceder = get_preceder(succeeder, check_duplicate_set, record, n);

      cout << preceder << " ";

      record[preceder].insert(succeeder);
      check_duplicate_set.insert(preceder);
    }
}

int get_preceder(int succeeder, set<int>& check_duplicate_set, vector< set<int> >& record, int n)
{	
	int preceder;
	do
      {
        preceder = rand() % n + 1;
      }while(!check_valid_preceder(preceder, succeeder, check_duplicate_set, record));
    return preceder;
}

bool check_valid_preceder(int preceder, int succeeder, set<int>& check_duplicate_set, vector< set<int> >& record)
{
	return check_cyclic_condition(succeeder, preceder, record) &&  check_printed(check_duplicate_set, preceder) && (preceder != succeeder);
}

bool check_cyclic_condition(int vertex1, int vertex2, vector< set<int> >& record)
{
	return record[vertex1].find(vertex2) == record[vertex1].end();
}

bool check_printed(set<int>& record, int vertex)
{
	return record.find(vertex) == record.end();
}
