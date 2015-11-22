#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
	ifstream fin("D:\\stopwords.txt");
	ofstream fout("D:\\tt.txt");
	string s;
	while(fin>>s){
		s="\""+s+"\""+",";
		fout<<s;
	}

return 0;
}