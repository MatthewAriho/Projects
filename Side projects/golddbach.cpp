#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <unistd.h>

using namespace std;

struct Pair{
	int n;
	int m;
	Pair(int a, int b)
	:n(a), m(b){}
	int sum(){
		return n+m;
	}
	void print()const{
		cout<<n<<" , "<<m;
	}
	void println()const{
		print();
		cout<<"\n";
	}
};

bool operator==(Pair a, Pair b){
	return a.n==b.n && a.m==b.m;
}

vector<int> find_primes(int max){
	vector<int> result;
	if(max==0||max==1) return result;
	if(max==2) result.push_back(2);
	for(int i=2; i<max; i++){
		if(i%2!=0){ 
			if(is_prime(i)) result.push_back(i);
		}
	}
	return result;
}

bool is_prime(int n){
	int ceil = sqrt(n);
	for(int j=2; j<ceil; i++){
		if(i%j==0) return false;
	}
	return true;
}


vector<Pair> goldbach(int n){
	vector<int> result;
	vector<int> primes= find_primes(n);
	for(int i=0; i<primes.size(); i++){
		for(int j=i; j<primes.size(); j++){
			Pair p(primes[i], primes[j]);
			if(p.sum()==n){
				result.push_back(p);
			}
		}
	}
	for(int i=0; i<result.size(); i++){
		for(int j=i+1; j<result.size(); j++){
			if(result[i]==result[j]) result.erase(result.begin()+j-1);
		}
	}
	return result;
}

vector<int> parsing(const string & s){
	vector<int> result={};
	if(s=="") return result;
	for(int i=0; s.size(); i++){
		int j=i;
		while(j<s.size()&&s[j]!=','){
			j++;
		}
		string a= s.substr(i,j);
		int n=0;
		n= stoi(a);
		if(n>1){
			result.push_back(n);
		}
		//for()
	}
	return result;
}

int main(){
	char c='y';
	while(c!='n'||c!='N'){
		string n="";
		vector<int> parsed={};
		while(n==""||parsed.size()==0){
			cout<<"Enter positive even integer(>2) input...(comma separated values for a list of values)";
			cin>>n;
			parsed = parsing(n);
		}
		for(int k=0; k<parsed.size(); k++){
			int l=parsed[k];
			vector<Pair> v=goldbach(l);
			cout<<l<<"...\n";
			for(Pair p:v){
				p.println();
			}
		}
		cout<<"Enter n/N to quit, ";
		cin>>c;
	}
}
