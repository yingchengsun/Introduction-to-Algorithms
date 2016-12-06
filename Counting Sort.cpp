#include <iostream>
using namespace std;

void Counting_Sort(int* a, int* b, int n, int k){
	int *c= new int[k+1];
	int i,j;

	for(i=0;i<=k;i++)
		c[i]=0;
	for(j=0;j<n;j++)
		c[a[j]]=c[a[j]]+1;
	for(i=1;i<=k;i++)
		c[i]=c[i]+c[i-1];
	for(j=n-1;j>=0;j--){
		b[c[a[j]]-1]=a[j];
		c[a[j]]--;
	}
	delete[] c;
}



int main(){
	int a[8]={2,5,3,0,2,3,0,3};
	int b[8];
	Counting_Sort(a,b,8,5);
	for (int i=0;i<8;i++)
		cout<<b[i]<<" ";
	cout<<endl;

return 0;
}