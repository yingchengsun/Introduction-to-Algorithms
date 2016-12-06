#include <iostream>
using namespace std;

/*
int	Partition(float* b,int p,int r){
	float temp;
	float x=b[p];
	int i=p;
	int j=r;
	while(i<j){
		if(b[j]>=x)
			j--;
		else if(b[i]>=x){
					temp=b[i];
					b[i]=b[j];
					b[j]=temp;
				}
			else
				i++;
	}
	return i;
}
*/

int	Partition(int* b,int p,int r){
	int x=b[r];
	int i=p-1;
	for(int j=p;j<r;j++)
		if(b[j]<=x){
			i++;
			swap(b[i],b[j]);
		}
	swap(b[i+1],b[r]);
	return i+1;
}

//Use QuickSort
void Mystery_Sort(int* b,int p,int r){
	int q;
	if(p<r) {
		q=Partition(b,p,r);
		Mystery_Sort(b,p,q-1);
		Mystery_Sort(b,q+1,r);
	}
}

/*
//The main idea is adding a decimal number to every integer element in the array A
void Stable_Sort(int* a, int n){
	//use the arrary b to store float numbers 
	float* b= new float[n];
	float p=1.0/n;
	int i;

	b[0]=a[0];
	//Output the elements in the array B
	cout<<"B = <";
	//add i/n to a[i] from 1 to n-1
	for(i=1;i<n;i++){
		b[i]=a[i]+i*p;
		cout<<b[i-1]<<", ";
	}
	cout<<b[n-1]<<">"<<endl;

	Mystery_Sort(b,0,n-1);

	//cast float b[i] to integer a[i]
	for(i=0;i<n;i++)
		a[i]=(int)b[i];
	delete[] b;
}

*/
void Stable_Sort(int* a, int n){
	int i,j;
	int b[10][10];
	int count[10];

	for(i=0;i<10;i++){
		b[i][0]=-1;
		count[i]=0;
	}
	for(i=0;i<n;i++){
		while(b[a[i]][count[a[i]]]>=0)
			count[a[i]]++;
		b[a[i]][count[a[i]]]=a[i];
	}

	Mystery_Sort(a,0,n-1);

	i=0;
	int p;
	while(i<n){
		p=a[i];
		for(j=0;j<=count[p];j++,i++)
			a[i]=b[a[i]][j];
	}

}

int main(){
	int a[5]={2,1,2,4,2};
	Stable_Sort(a,5);

	//Output the elements ordered in the array A
	cout<<"A = <";
	for (int i=0;i<4;i++)
		cout<<a[i]<<", ";
	cout<<a[4]<<">"<<endl;
return 0;
}