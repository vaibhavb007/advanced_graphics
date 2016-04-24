#include <iostream>
#include <vector>
using namespace std;

struct bqw
{
	vector<int> a;
};


struct sqw
{
	vector<bqw> v;
};


int main(){
	sqw a;
	bqw y;
	y.a.push_back(2);
	a.v.push_back(y);
	bqw *x= &(a.v[0]);
	x->a.push_back(3);
	cout<<a.v[0].a[0]<<" "<<a.v[0].a[1]<<endl;
}