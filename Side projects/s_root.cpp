#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <unistd.h>

using namespace std;

vector<int> strange_root(double n){
	double m=sqrt(n);
	string a= to_str(n);
	string b= to_str(m):
	vector<int> result;
	for(int i=0; i<b.size(); i++){
		for(int j=0; j<a.size(); j++){
			if(b[i]==a[j]){
				result.push_back(stoi(a[j]));
			}
		}
	}
	return result;
}

int main(){
	char c='y';
	while(c!='n'||c!='N'){
		double n=0;
		while(n<=0){
			cout<<"Enter positive input...";
			cin>>n;
		}
		vector<int> v=strange_root(n);
		if(v.size()!=0){
			cout<<"Shared digits between "<<n<<" and "<<sqrt(n)<<" = ";
			for(int i=0; i<v.size(); i++){
				cout<<v[i];
				if(i<v.size()-1){
					cout<<" , ";
				}
			}
			cout<<" .\n";
		}else{
			cout<<"No shared digits between "<<n<<" and "<<sqrt(n)<<"\n";
		}
		cout<<"Enter n/N to quit, ";
		cin>>c;
	}
}