#include <iostream>
using namespace std;

//original version
/*
int main(){
	int a[6]={5,2,4,6,1,3};
	int i,j,key=0;
	for (i=1;i<6;i++)
		for(j=i;j>0;j--)
			if(a[j-1]>a[j]){
				key=a[j];
				a[j]=a[j-1];
				a[j-1]=key;
			}
	for(i=0;i<6;i++)
		cout<<a[i];

return 0;
}
*/

//improved version
//Decreasing the computing steps at most: n*{(n-1)+(n-2)+(n-3)....1)
int main(){
	int a[6]={5,2,4,6,1,3};
	int i=0,j=0,key=0;
	for(i=1;i<6;i++){
		key=a[i];
		for(j=i;j>0&&key>a[j-1];j--)
				a[j]=a[j-1];
		a[j]=key;
	}
	for(i=0;i<6;i++)
		cout<<a[i];
	return 0;
}