#include <iostream>
using namespace std;


void merge-sort(int* A,int p,int r){
	if(p<r){
		q=(r+q)/2;
		merge-sort(A,p,q);
		merge-sort(A,q+1,r);
		merge(A,p,q,r);
	}
}

void merge(int* A,int p,int q,int r){
	int 

}

int main(){
	int A[6]={1,3,4,5,2,6};
	merge-sort(A,1,6);


return 0;
}