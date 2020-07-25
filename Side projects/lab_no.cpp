#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <unistd.h>

using namespace std;

vector<int> prime_divisors(int n){
	vector<int> result;
	for(int i=0; i<n; i++){
		if(n%i==0&&n%(i*i)==0) result.push_back(i);
	}
	for
	return result;
}

int main(){
	char c='y';
	while(c!='n'||c!='N'){
		int n=0;
		while(n<=0){
			cout<<"Enter positive input...";
			cin>>n;
		}
		vector<int> v=divisors(n);
		if(v.size()!=0){
			cout<<"Lab numbers = ";
			for(int i=0; i<v.size(); i++){
				cout<<v[i]<<" is a root and "<<v[i]*v[i]<<" is also a root";
				if(i<v.size()-1){
					cout<<" , ";
				}
			}
			cout<<" .\n";
		}else{
			cout<<"No lab numbers\n";
		}
		cout<<"Enter n/N to quit, ";
		cin>>c;
	}
}