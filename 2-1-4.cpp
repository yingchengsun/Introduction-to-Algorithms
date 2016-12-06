#include <iostream>
using namespace std;

//2.1-4, watch out for the equal sign "==", it's not "="!
int main(){
	int a[4]={1,0,1,1},b[4]={1,1,0,1},c[5],sum=0,carry=0;
	for(int i=3;i>=0;i--){
		sum=a[i]+b[i]+carry;
		if(sum<2){
			c[i+1]=sum;
			carry=0;
		}
		else if (sum==2){
			c[i+1]=0;
			carry=1;
		}
		else {
			c[i+1]=1;
			carry=1;
		}
	}
	c[0]=carry;
	for(int j=0;j<5;j++)
		cout<<c[j];
return 0;
}