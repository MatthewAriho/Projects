// a4.h

///////////////////////////////////////////////////////////////////////////////
//
// Do not change this file in any way!
//
// Implement the 20 requested functions. Put all your code into a4.cpp.
//
///////////////////////////////////////////////////////////////////////////////

#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// Pre-condition:
//    n >= 0
// Post-condition:
//    Returns the sum of the first n squares, i.e.
//    1^2 + 2^2 + 3^2 + ... + n^2.
//    If n is 0, then 0 is returned.
// Constraints:
//    Must be implemented using recursion (and no loops). You can write
//    helper functions if necessary.
// Note:
//    You don't need to worry about overflow sums that overflow int.
int sum_of_squares(int n);

void sum_of_squares_test();

///////////////////////////////////////////////////////////////////////////////
//
// Pre-condition:
//    n >= 0
// Post-condition:
//    Returns the sum of the first n even numbers starting with 0, i.e.
//    0 + 2 + 4 + ... + (2n-2).
//    If n is 0, then 0 is returned.
// Constraints:
//    Must be implemented using recursion (and no loops). You can write helper
//    functions if necessary.
// Note:
//    You don't need to worry about overflow sums that overflow int.
int sum_of_evens(int n);

void sum_of_evens_test();

///////////////////////////////////////////////////////////////////////////////
//
// Pre-condition:
//    n >= 0
// Post-condition:
//    Returns a string of length n consisting of n copies of c.
//    If n is 0, the empty string is returned.
// Constraints:
//    Must be implemented using recursion (and no loops). You can write helper
//    functions if necessary.
// Note:
//    In practice, this function could easily be implemented as string(c, n),
//    so don't use that here! Your solution must use recursion.
string fill(char c, int n);

void fill_test();

///////////////////////////////////////////////////////////////////////////////
//
// Pre-condition:
//    none
// Post-condition:
//    Returns true if s either empty, or contains only digit characters
//    '0' to '9'.
// Constraints:
//    Must be implemented using recursion (and no loops). You can write helper
//    functions if necessary.
// Note:
//    When testing functions that return bool, makre sure to include some
//    test case that return true, and some that return false.
bool all_digits(const string& s);

void all_digits_test();

///////////////////////////////////////////////////////////////////////////////
//
// Pre-condition:
//    none
// Post-condition:
//    Returns a copy of s, but with all spaces removes. No other characters
//    are changed. For example, shrink(" ab c  d ") returns "abcd". If s
//    is the empty string, then "" is returned.
// Constraints:
//    Must be implemented using recursion (and no loops). You can write helper
//    functions if necessary.
string shrink(const string& s);

void shrink_test();

///////////////////////////////////////////////////////////////////////////////
//
// Pre-condition:
//    none
// Post-condition:
//    Returns the sum of all the positive numbers in v.
// Constraints:
//    Must be implemented using recursion (and no loops). You can write helper
//    functions if necessary.
int sum_pos(const vector<int>& v);

void sum_pos_test();

///////////////////////////////////////////////////////////////////////////////
//
// Pre-condition:
//    a.size() == b.size(), and a.size() > 0
// Post-condition:
//    Returns a vector equal to {a[0]+b[0], a[1]+b[1], a[2]+b[2], ..., a[n]+b[n]},
//    where n == a.size().
// Constraints:
//    Must be implemented using recursion (and no loops). You can write helper
//    functions if necessary.
vector<int> sum_vec(const vector<int>& a, const vector<int>& b);

void sum_vec_test();

///////////////////////////////////////////////////////////////////////////////
//
// Pre-condition:
//    none
// Post-condition:
//    Returns the number of strings in v that are equal to s.
// Constraints:
//    Must be implemented using recursion (and no loops). You can write helper
//    functions if necessary.
int count(const vector<string>& v, const string& s);

void count_test();

///////////////////////////////////////////////////////////////////////////////
//
// Pre-condition:
//    s.size() == t.size()
// Post-condition:
//    Returns a vector<string> where the first string is the first character
//    of s followed by the first character of t, the second string is the
//    second character of s followed by the second character of t, and so on.
//    For example, zip("abc", "xyz") returns {"ax", "by", "cz"}.
//
//    If both s and t are empty, then an empty vector<string> is returned.
// Constraints:
//    Must be implemented using recursion (and no loops). You can write helper
//    functions if necessary.
vector<string> zip(const string& s, const string& t);

void zip_test();

///////////////////////////////////////////////////////////////////////////////
//
// Pre-condition:
//    none
// Post-condition:
//    Returns a string consisting of all the strings in v concatentated
//    together with sep after after string (except for the last). For example,
//    join({"cat", "dog", "house"}, ", ") returns the string
//    "cat, dog, house", and join({"he", "we", "see"}, "") returns the string
//    "hewesee".
//
//    If v is empty, the empty string is returned.
// Constraints:
//    Must be implemented using recursion (and no loops). You can write helper
//    functions if necessary.
string join(const vector<string>& v, const string& sep);

void join_test();