#include <iostream>
using namespace std;

/*At first, I used n-- or --n in the actural parameter£¬but it changed the value of n in the whole function. 
Thus the for loop ran wrongly. Then I used the skill of n-- and n++ to keep it balanced. 
BUT! I can just use n-1 as the actural parameter! SO EASY!
The main point is you should not always try to change the value of n in this function, you can change it in 
the next funciton.
PS: never use n-- or n++ as the actural parameter!
*/
void insert_sort(int* a,int n){
	int key;
	if (n>1){
		//n--;
		insert_sort(a,n-1);
		//n++;
	}
	
	key=a[n];
	for(int i=n;(i>0)&&(key<a[i-1]);i--)
			a[i]=a[i-1];
		a[i]=key;

}

int main(){
	int a[5]={2,1,3,5,4};
	insert_sort(a,4);
	for (int j=0;j<5;j++)
		cout<<a[j];

return 0;
}