/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Matthew Ariho
// St.# : 301374078
// Email: mariho@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

// a4.cpp

#include "a4.h"  // no other includes are allowed!

using namespace std;

//
// put your implementation of the 20 function headers from "a4.h" here
//

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
int square(int n){
	return n*n;			//helper function to calaculate squares
}
int sum_of_squares(int n){
	if(n>0){		//recursive case
		return sum_of_squares(n-1)+square(n);		//the square of n is added to the sum of squares of n-1
	}else if(n==0){		//base case - if n is 0, 0 is returned
		return 0;
	}
	return 0;
}

void sum_of_squares_test(){
  cout << "Testing sum of squares ... ";
  assert(sum_of_squares(0) == 0);
  cout<<" sum of squares test 1 passed\n";
  assert(sum_of_squares(1) == 1);
  cout<<" sum of squares test 2 passed\n";
  assert(sum_of_squares(2) == 1 + 4);
  cout<<" sum of squares test 3 passed\n";
  assert(sum_of_squares(3) == 1 + 4 + 9);
  cout<<" sum of squares test 4 passed\n";
  assert(sum_of_squares(4) == 1 + 4 + 9 + 16);
  cout<<" sum of squares test 5 passed\n";
  assert(sum_of_squares(10) == 385);
  cout<<" sum of squares test 6 passed\n";
  assert(sum_of_squares(20) == 2870);
  cout<<" sum of squares test 7 passed\n";
  assert(sum_of_squares(30) == 9455);
  cout<<" sum of squares test 8 passed\n";
  assert(sum_of_squares(100) == 338350);
  cout << "all sum of squares tests passed!\n";
}

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

int sum_of_evens(int n){
	if(n>0){
		return sum_of_evens(n-1) +2*n;		//the 2 multiplied with the value is added to the sum of evens of n-1
	}else if(n==0){
		return 0;			//base case - if n is 0, 0 is returned
	}
	return 0;
}

void sum_of_evens_test(){
  cout << "Testing sum of evens ... ";
  assert(sum_of_evens(0) == 0);
  cout<<" sum of evens test 1 passed\n";
  assert(sum_of_evens(1) == 2);
  cout<<" sum of evens test 2 passed\n";
  assert(sum_of_evens(2) == 2 + 4);
  cout<<" sum of evens test 3 passed\n";
  assert(sum_of_evens(3) == 2 + 4 + 6);
  cout<<" sum of evens test 4 passed\n";
  assert(sum_of_evens(4) == 2 + 4 + 6 + 8);
  cout << "all sum of squares tests passed!\n";
}

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
string fill(char c, int n){
	if(n>0){
		return c + fill(c, n-1);	//the character c is added to the string containing n-1 copies of c
	}else if(n==0){
		return "";			//base case - if n is 0, an emptry string is returned
	}
	return "";
}

void fill_test(){
  cout << "Testing fill ... ";
  assert(fill('*',0) == "");
  cout<<" fill test 1 passed\n";
  assert(fill('*',1) == "*");
  cout<<" fill test 2 passed\n";
  assert(fill('*',2) == "**");
  cout<<" fill test 3 passed\n";
  assert(fill('*',3) == "***");
  cout<<" fill test 4 passed\n";
  assert(fill('*',4) == "****");
  cout<<" fill test 5 passed\n";
  assert(fill('$',10) == "$$$$$$$$$$");
  cout<<" fill test 6 passed\n";
  assert(fill('a',5) == "aaaaa");
  cout<<" fill test 7 passed\n";
  assert(fill(' ',6) == "      ");
  cout << "all fill tests passed!\n";
}
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
bool is_digit(const char&c){
	return c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9';		//helper function to return true or false based on if the character passed to it is a digit
}

bool all_digits(const string& s){
	if(s.length()==0){
		return true;			//base case - if the size of the string passed to the function is 0, true is returned
	}else if(s.length()>0){		
		if(is_digit(s[s.length()-1])){			//if the last character in the string is a digit..
			string n=s;							//a copy of the string is made and the last character is removed and the function is called again with the new string as input
			n.pop_back();
			return true && all_digits(n);
		}else{									//if the last character in the string is not a digit, false is returned
			return false;
		}
	}
	return false;
}

void all_digits_test(){
	cout << "Testing all_digits ... ";
	assert(all_digits("") == true);
	cout<<" all of digits test 1 passed\n";
	assert(all_digits("1a01") == false);
	cout<<" all of digits test 2 passed\n";
	assert(all_digits("101") == true);
	cout<<" all of digits test 3 passed\n";
	assert(all_digits("21bd") == false);
	cout<<" all of digits test 4 passed\n";
	assert(all_digits("4gd7") == false);
	cout<<" all of digits test 5 passed\n";
	assert(all_digits("12345") != false);
	cout<<" all of digits test 6 passed\n";
	assert(all_digits("67890") != false);
	cout << "all all_digits tests passed!\n";
}

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
int search_for_spaces(const string& s){			//helper function that returns the index of the first space character in a string
	int result =-1;								//if the string does not contain a space, a flag(-1) is returned
	for(int i=0; i<s.size(); i++){
		if(s[i]==' ') return i;
	}
	return result;
}

string shrink(const string& s){
	//cout<<"Shrink called\n";
	int n=s.size(); 
	if(n>0){		//recursive case
		int first_space =  search_for_spaces(s);	//index of first space is found
		if(first_space!=-1){		//if first_space is not -1
			string new_s="";		//new strign variable created to store string
			for(int i=0; i<first_space; i++){
				new_s+= s[i];		//all characters before and after space are added to the new string
			}				// only done if first space index is not equal to the last element
			for(int i=first_space+1; i<s.size(); i++){
				new_s+=s[i];
			}
			return shrink(new_s);	//then shrink is called again with the new string as input
		}else{
			return s;				//if no spaces are found, the string is returned unchanged
		}
	}else if(n==0){			//base case - if n(size of string) is 0, an empty strings is returned
		return "";
	}
	return "";
}

void shrink_test(){
  cout << "Testing fill ... ";
  assert(shrink("a b c d e") == "abcde");
  cout<<" shrink test 1 passed\n";
  assert(shrink("ab c d e") == "abcde");
  cout<<" shrink test 2 passed\n";
  assert(shrink("abc d e") == "abcde");
  cout<<" shrink test 3 passed\n";
  assert(shrink("abcd e") == "abcde");
  cout<<" shrink test 4 passed\n";
  assert(shrink("abcde") == "abcde");
  cout<<" shrink test 5 passed\n";
  assert(shrink("abcde    ") == "abcde");
  cout<<" shrink test 6 passed\n";
  assert(shrink("abcde ") == "abcde");
  cout<<" shrink test 7 passed\n";
  assert(shrink("    abcde") == "abcde");
  cout<<" shrink test 8 passed\n";
  assert(shrink("               ") == "");
  cout << "all shrink tests passed!\n";
}

///////////////////////////////////////////////////////////////////////////////
//
// Pre-condition:
//    none
// Post-condition:
//    Returns the sum of all the positive numbers in v.
// Constraints:
//    Must be implemented using recursion (and no loops). You can write helper
//    functions if necessary.
int sum_pos(const vector<int>& v){
	if(v.size()>0){			//if the vector passed to the function is not empty
		int sum =0;			//a sum variable is created to keep track of the sum so far
		if(v[v.size()-1]>0) sum = v[v.size()-1];		//if the last element of the vector is positive then it is added to the sum variable
		vector<int> s =v;	//a copy of the vector is made and the last element is deleted
		s.pop_back();
		return sum + sum_pos(s);		//the new sum (sum of the current sum and the sum of positives with the new vector as input) is returned
	}else if(v.size()==0){		//base case - if the size of the vector is 0, 0 is returned
		return 0;
	}
	return 0;
}

void sum_pos_test(){
	cout << "Testing sum of positives ... ";
	assert(sum_pos({}) == 0);
	cout<<" sum of positives test 1 passed\n";
	assert(sum_pos({0,1,-1}) == 1);
	cout<<" sum of positives test 2 passed\n";
	assert(sum_pos({0,1,-1,2,-2}) == 1 + 2);
	cout<<" sum of positives test 3 passed\n";
	assert(sum_pos({0,1,-1,2,-2,3,-3}) == 1 + 2 + 3);
	cout<<" sum of positives test 4 passed\n";
	assert(sum_pos({0,1,-1,2,-2,3,-3,4,-4}) == 1 + 2 + 3 + 4);
	cout<<" sum of positives test 5 passed\n";
	assert(sum_pos({0,-1,-2,-2,-2,-3,-3,-4,-4}) == 0);
	cout<<" sum of positives test 6 passed\n";
	assert(sum_pos({1,2,2,2,3,3,4,4}) == 1+2+2+2+3+3+4+4);
	cout << "all sum of positives tests passed!\n";
}

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
int sum_vec_elements(const vector<int>& a, const vector<int>& b, int n){
	//cout<<a[n] <<" + "<<b[n]<<" = "<<a[n]+ b[n]<<"\n";
	return a[n]+b[n];			//helper function to calculate sum of elements(of the same index) of two vectors
}
vector<int> sum_vec(const vector<int>& a, const vector<int>& b){
	if(a.size()==b.size()){		//if the two vectors passed to the function are of equal size...
		if(a.size()>0){			//if the vectors of a size greater than 0..
			int n=a.size()-1;	
			vector <int> sum;	//a vector to keep track of the sum is created
			int sum_elements = sum_vec_elements(a,b,n);	//the sum of the last elements of the vectors is calculated and added to the sum vector
			sum.push_back(sum_elements);
			vector<int> c=a;		//copies of the two vectors are created and the last elements are removed
			vector<int> d=b;
			c.pop_back();
			d.pop_back();
			vector <int> sum_part = sum_vec(c,d);		// recursive call- the vector containing the sum of the rest of the vectors is calculated 
			sum.insert(sum.begin(), sum_part.begin(), sum_part.end());		//and placed at the end of the first sum vector
			return sum;		//full vector returned
		}else if(a.size()==0){			//based case- if the size of one of the vectors is 0, an empty vector is returned
			vector <int> sum={};	
			return sum;
		}
	}else{			//if the two vectors passed to the function are of different sizes then an empty vector is returned
		vector <int> sum={};
		return sum;	
	}
	vector <int> sum={};
	return sum;	
}

void sum_vec_test(){
  cout << "Testing sum of vectors ... ";
	vector<int> test={};
  assert(sum_vec({0},{0,1}) == test);
  cout<<" sum of vectors test 1 passed\n";
	test.push_back(1); test.push_back(3);
  assert(sum_vec({1,2},{0,1}) == test);
  cout<<" sum of vectors test 2 passed\n";
	test.push_back(5);
  assert(sum_vec({1,2,3},{0,1,2}) == test);
  cout<<" sum of vectors test 3 passed\n";
	test.clear();
  assert(sum_vec({1,2,3},{0,1}) == test);
  cout<<" sum of vectors test 4 passed\n";
  vector<int> a,b,c;
  for(int i=0; i<10; i++){
  	a.push_back(i);
  	b.push_back(i+1);
  	c.push_back((2*i)+1);
  }
  assert(sum_vec(a,b) == c);
  cout << "all sum of vectors tests passed!\n";
}

///////////////////////////////////////////////////////////////////////////////
//
// Pre-condition:
//    none
// Post-condition:
//    Returns the number of strings in v that are equal to s.
// Constraints:
//    Must be implemented using recursion (and no loops). You can write helper
//    functions if necessary.
int count(const vector<string>& v, const string& s){
	if(v.size()>0){		//if the size of the vector passed to the function is greater than 0..
		vector<string> temp =v;		//a copy of the vector is made
		if(temp[temp.size()-1]==s){		//if the last element of the vector is the string s
			temp.pop_back();			//the last element is removed from the vector
			return 1+ count(temp,s);	//1 is added to the count and added to the count for the rest of the vector
		}else{
			temp.pop_back();			//otherwise, the last element of the vector is removed and a recursive call on the remainder of the vector is made
			return count(temp,s);
		}
	}else if(v.size()==0){		//base case- if the size of the vector is 0, 0 is returned
		return 0;
	}
	return 0;
}

void count_test(){
  cout << "Testing count ... ";
  assert(count({},"dog") == 0);
  cout<<" counts test 1 passed\n";
  assert(count({"cat"},"dog") == 0);
  cout<<" counts test 2 passed\n";
  assert(count({"cat","dog"},"cat") == 1);
  cout<<" counts test 3 passed\n";
  assert(count({"cat","dog","cat"},"cat") == 2);
  cout<<" counts test 4 passed\n";
  assert(count({"cat","dog","cat","cat","cat"},"cat") == 4);
  cout<<" counts test 5 passed\n";
  assert(count({"dog","dog","dog","dog","dog"},"cat") == 0);
  cout << "all count tests passed!\n";
}

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
void print(const vector<string>&v){
	cout<<"{ ";
	for(int i=0; i<v.size(); i++){
		if(i==v.size()-1){ 
			cout<<i<<" = "<<v[i]<<"} \n";
		}else{
			cout<<i<<" = "<<v[i]<<",";
		}
	}
}

string rest(const string& s){		//helper function that takes a string as input and returns the same string with the excpetion of the first character
	string result="";
	for(int i=1; i<s.size(); i++){
		result+=s[i];
	}
	return result;
}

vector<string> zip(const string& s, const string& t){
	if(s.size()==t.size()){		//if the two vectors have the same size...
		//cout<<"Flag 1\n";
		//cout<<"String1 = "<<s<<", String2 = "<<t<<"\n";
		if(s.size()>0){			//if the vectors are of size greater than 0...
			//cout<<"Flag 2\n";
			//int n=s.size();
			//cout<<"Flag 3\n";
			vector <string> new_vec;		//a new vector is created to store the new elements
			//cout<<"Flag 4\n";
			//print(new_vec);
			string c=s;			//copies of the strings are made
			string d=t;
			char a=c[0];
			char b=d[0];
			//cout<< a <<" , "<<b<<"\n";
			string sum_elements ={a,b};		//the first characters of each string are added together to form a string which is added to the new_vec vector
			//sum_elements += a + b;
			//cout<<"Flag 5\n";
			new_vec.push_back(sum_elements);
			//cout<<"Flag 6\n";
			//print(new_vec);
			c=rest(c);		//the first characters of the strings are removed and the modified strings are used as input in the new recursive call of zip
			d=rest(d);
			vector <string> part = zip(c,d);	//the part vector containing the other elements is created using a recursive call
			//cout<<"Flag 7\n";
			//print(new_vec);
			new_vec.insert(new_vec.end(), part.begin(), part.end());		//the part vector is added to the end of the initial new_vec vector
			//cout<<"Flag 8\n";
			//print(new_vec);
			return new_vec;		//the full vector is returned
		}else if(s.size()==0){			//-base case- if the vectors are of size -, an empty vector is returned
			vector <string> new_vec={};
			return new_vec;
		}
	}else{
		vector <string> new_vec={};		//if the two vectors are of different sizes, an empty vector is returned
		return new_vec;
	}
	vector <string> new_vec={};
	return new_vec;
}

void zip_test(){
	cout << "Testing zip ... ";
	vector<string> test={};
	assert(zip("","ab") == test);
	cout<<" zip test 1 passed\n";
	vector <string> test1={"ac","bd"};
	assert(zip("ab","cd") == test1);
	cout<<" zip test 2 passed\n";
	vector <string> test2={"ad","be","cf"};
	assert(zip("abc","def") == test2);
	cout<<" zip test 3 passed\n";
	vector <string> test3={"ae","bf","cg","dh"};
	assert(zip("abcd","efgh") == test3);
	cout<<" zip test 4 passed\n";
	vector <string> test4={"af","bg","ch","di","ej"};
	assert(zip("abcde","fghij") == test4);
	cout << "all zip tests passed!\n";
}

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
void new_vec_assign(const vector<string>& v, vector<string>& new_vec){
	for(int i =1; i<v.size(); i++){
			new_vec[i-1]=v[i];		//the second vector is assigned strings from the first vector(except the first element)
	}
}

string join(const vector<string>& v, const string& sep){
	if(v.size()>1){
		int n=v.size();
		vector <string> new_vec(n-1,"");
		new_vec_assign(v, new_vec); 		//a copy of the rest of vector(without the first element) passed to function is made
		//string result = v[0] + sep + join(new_vec, sep);
		//cout<<" Result so far = "<<result<<"\n";			//the string being returned is the sum of the first element of the initial vector, the separator string
		return v[0] + sep + join(new_vec, sep);				//and the string returned from a recursive call(using the modified vector as input)
	}else if(v.size()==1){	//base case- if the vector contains only one element, that string is returned
		return v[0];		
	}else if(v.size()==0){	//base case- if the vector is empty, the empty string is returned
		return "";
	}
	return "";
}

void join_test(){
	cout << "Testing join ... ";
	assert(join({},"") == "");
	cout<<" join test 1 passed\n";
	assert(join({"ab","cd"}, "") == "abcd");
	cout<<" join test 2 passed\n";
	assert(join({"ab", "cd", "ef"},",") == "ab,cd,ef");
	cout<<" join test 3 passed\n";
	assert(join({"ab", "cd","ef", "gh"},"") == "abcdefgh");
	cout<<" join test 4 passed\n";
	assert(join({"ab", "cd","ef", "gh", "ij"},",") == "ab,cd,ef,gh,ij");
	cout<<" join test 5 passed\n";
	cout << "all join tests passed!\n";
}

// You can use this main function (which calls all the test functions), or
// re-write it any way you like. The marker will be using their own main
// function.
int main() {
	
}
