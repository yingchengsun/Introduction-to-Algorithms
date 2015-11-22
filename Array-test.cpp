#include <stdio.h>
//include <iostream>
//using namespace std;


void merge(int* A,int n){
	for(int i=0;i<n;i++)
		printf("%4d ", A[i]);
		//cout<<A[i]+A[i]<<" ";
}
void test(int &bbr){
		bbr++;
}
int main(){
	int A[6]={1,3,4,5,2,6},b=100;
	int &br=b;
	test(br);
	printf("%d",b);
    //merge(A,6);
	//cout<<A<<endl;
	//cout<<&A[0];
return 0;
}