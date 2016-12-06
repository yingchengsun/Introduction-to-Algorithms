#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Solution {
public:
       string convertToTitle(int n) {
        string letter[27]={"Z","A","B","C","D","E","F","G","H","I","J","K","L","M","N",
							"O","P","Q","R","S","T","U","V","W","X","Y","Z"};
		int k=n;
		int l;
		string result;

		while(k>0){
			l=k%26;
			k=k/26;
			result=letter[l]+result;
			if(l==0)
				k--;
		}
		return result;
    }
};

int main(){

 string s("abc");
 strrev((char *)s.c_str());
 cout << s <<endl;

return 0;
}