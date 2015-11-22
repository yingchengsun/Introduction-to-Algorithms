#include <iostream>
using namespace std;


int	Partition(int* a,int p,int r){
	int temp;
	int x=a[p];
	int i=p;
	int j=r;
	while(i<j){
		if(a[j]>=x)
			j--;
		else if(a[i]>=x){
					temp=a[i];
					a[i]=a[j];
					a[j]=temp;
				}
			else
				i++;
	}
	for(int k=0;k<5;k++)
		cout<<a[k];
	cout<<endl;
	return i;
}

/*
int	Partition(int* a,int p,int r){
	int temp;
	int x=p;
	int i=r;

	while(i!=x){
		if(i<x){
			if(a[x]<a[i]){
					temp=a[x];
					a[x]=a[i];
					a[i]=temp;
			}
			temp=x;
			x=i;
			i=temp;

			i++;
		}
		else { if(a[x]>a[i]){
					temp=a[x];
					a[x]=a[i];
					a[i]=temp;

					temp=x;
					x=i;
					i=temp;
				}
		i--;
		}
	}
	for(int k=0;k<10;k++)
		cout<<a[k];
	cout<<endl;
	return i;
}
*/

void QuickSort(int* a,int p,int r){
	int q;
	if(p<r) {
		q=Partition(a,p,r);
		QuickSort(a,p,q-1);
		QuickSort(a,q+1,r);
	}
}

int main(){
	//int a[10]={3,0,1,8,7,2,5,4,9,6};
	int a[5]={2,1,2,4,2};
		QuickSort(a,0,4);
return 0;
}