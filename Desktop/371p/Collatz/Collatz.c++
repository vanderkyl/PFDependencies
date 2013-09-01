// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

#include "Collatz.h"

#define M 1000000
// Contains largests cycle length in each range with length 1000
// [1, 999], [1000, 1999], [2000, 2999], ..., [999,000, 999,999].
int range_cache[1000];

int cache[M];
bool range_cache_full; 

// ------------
// collatz_read
// ------------
  
/* Reads the variable r and places the two ints given by
   r into i and j. Return false if invalid input.     */
bool collatz_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}
    
// ------------
// collatz_eval
// ------------

/* Find the max cycle length in the range given by two parameters
   i and j. Divide by 2 if even, multiply by 3 and add 1 if odd. */
int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);

    int cycles = 1;
    int n = i;

    // Switch i and j if j is smaller than i.
    if (i > j) {
        n = j;
        j = i;
        i = n;
    }
    assert(j >= i);

    // The max cycle length of the range [a,b] is equal to the 
    // max cycle length of the range [b/2,b] as long as b/2 > a.
    int half_j = j / 2;
    if (half_j > i) 
        i = half_j;
    
    if (!range_cache_full) {
       
        // Iterate through the range and evaluate each cycle length.
        while (n <= j) { //for each number in this range
            
            unsigned int idx = n;
            int temp_cycles = 1;
            while (idx > 1) {
                if (idx < 1000000 && cache[idx] != 0) { // Found cycle length needed
                    temp_cycles = temp_cycles + cache[idx] - 1;
                    break;
                }
                if (idx % 2 == 0)  // even
                    idx = idx / 2;
                else {             // odd
                    idx = (idx >> 1) + idx + 1; // Equivalent to (3*idx + 1)/2
                    temp_cycles++;
                }
                temp_cycles++;
            }
            assert(temp_cycles > 0);
            cache[n] = temp_cycles; 
            assert(cache[n] > 0);
            if (temp_cycles > cycles) { // Check to see which cycle length is larger
                cycles = temp_cycles;
            }
            n++;
        }
    } 
    // If the range_cache has been filled, find the range needed and 
    // check the cache.
    else {
        n = i;
        int end_of_range = i - (i % 1000) + 1000; // Compute the endpoint of the first range needed.
        while ((n <= j) && (n < end_of_range)) {
            if (cache[n] > cycles)
                cycles = cache[n];
            n++;
        }
        n += 999;
        while (n <= j) {
            int n2 = n / 1000; // Use to find the cache's corresponding location in the range_cache. 
            if (range_cache[n2] > cycles)
                cycles = range_cache[n2];
            n += 1000;
        }
        while (n <= j) { // Check the rest.
            if (cache[n] > cycles)
                cycles = cache[n];
            n++; 
        }
    }   
    assert(cycles > 0);
    return cycles;}

// ------------
// collatz_cache_generator
// ------------

/* Compute the max cycle length for each range of size 1000 and store it in range_cache */
int collatz_cache_generator(bool testing) {
    int i = 1;
    int j = 999;
    int idx = 0;
    int test = 0;
    range_cache[idx] = collatz_eval(i, j);
    assert(range_cache[idx] > 0);
    i = 1000;
    while (i < 1000000) { // Iterate through each range.
        idx++;
        j = i + 999;
        range_cache[idx] = collatz_eval(i, j);
        i += 1000;
    }
    if (testing)
        test = range_cache[1];
    return test;
}

// -------------
// collatz_print
// -------------

/* Print out the results */
void collatz_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

/* Solve the problem by calling helper functions. */
void collatz_solve (std::istream& r, std::ostream& w) {
    int i;
    int j;

    range_cache_full = false;
    // Generate max cycle lengths for each 1000 size range
    collatz_cache_generator(false);
    range_cache_full = true;

    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
