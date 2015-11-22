#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main(){
list<int> l;
vector<int> v;
list<int>::iterator it;
list<int> a[3];
l.push_back(2);
v.push_back(3);
it=l.begin();
a[0]=l;
cout<<*((a[0]).begin());
//cout<<v[0];
return 0;
}