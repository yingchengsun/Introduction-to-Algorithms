#include <iostream>
using namespace std;
/*
Selection Sort
*/

/* 
//Version 1.0
int main(){
	int a[5]={3,2,4,5,1},key=0,sign=0,i,j;
	for (i=0;i<4;i++){//did not realize only n-1 times iterations are OK
		key=a[i];
		sign=i;//did not be considered in the first time
		for(j=i+1;j<=4;j++)
			if(a[j]<key){
				key=a[j];
				sign=j;
			}
		a[sign]=a[i];
		a[i]=key;
	}
	for(i=0;i<5;i++)
		cout<<a[i];
return 0;
}
*/

/* Version 2.0 
int main(){
	int key=0,i,j;
	int a[5]={2,1,3,5,4};
	for(i=0;i<4;i++){
		key=a[i];
		for(j=i+1;j<=4;j++)
			if(a[j]<a[i]){
				a[i]=a[j];//Exchanging elements does not meet the claim.
				a[j]=key;// In addtion, it increases unnecessary overhead
			}
		cout<<a[i];
		}
	cout<<a[i];
	return 0;
}
*/

//Version 3.0 
int main(){
	int key=0,i,j,temp;
	int a[5]={2,1,3,5,4};
	for(i=0;i<4;i++){
		key=i;
		for(j=i+1;j<=4;j++)
			if(a[j]<a[key])
				key=j;//Very Clever!

		temp=a[key];
		a[key]=a[i];
		a[i]=temp;

		cout<<a[i];
		}
	cout<<a[i];
	return 0;
}

