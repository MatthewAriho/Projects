#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <unistd.h>

using namespace std;

double cube(double n){
	return n*n*n;
}

double cube_root(const double &d, double f, double c){
	if(d==0) return 0;
	if(d==1) return 1;
	if(d==cube(1000)) return 1000;
	double mid= (f+c)/2;
	double n = cube(mid);
	double diff = n-d;
	if(diff>0.0001){
		return cube_root(d, f, mid);
	}else if(diff<0.0001&&diff<-0.0001){
		return cube_root(d, mid, c);
	}else if(diff<=0.001){
		return mid;
	}
}

double cube_root(double d){
	double ceil=1000;
	double floor=0;
	return cube_root(d, ceil, floor)
}

int main(){
	char c='y';
	while(c!='n'||c!='N'){
		double n=0;
		while(n<=0){
			cout<<"Enter positive input(less than 1 biliion)...";
			cin>>n;
		}
		double m=cube_root(n);
		cout<<"\nCube root of "<<n<<" ="<<m<<"\n";
		cout<<"Enter n/N to quit, ";
		cin>>c;
	}
}