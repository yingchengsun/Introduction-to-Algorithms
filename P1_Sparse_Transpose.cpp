#include <iostream>
using namespace std;

//First Version, reconstruct the matrix and the transpose matrix,
//but the problem is that the running time is m*n, not k=o(m*n)
/*void Sparse_Transpose(int* R,int* C,int* V,int m,int n,int k){
	int** a=new int* [m];
	int i,j,p;
	for(i=0;i<m;i++)
		a[i]=new int [n];
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			a[i][j]=0;
	for(i=1;i<=m;i++){
		p=R[i]-R[i-1];
		for(j=0;j<p;j++)
			a[i-1][C[j+R[i-1]]]=V[j+R[i-1]];
	}
	
	//transpose, n rows, m columns
	int**b=new int* [n];
	int *r=new int [n+1];
	int *c=new int [R[m]];
	int *v=new int [R[m]];

	for(i=0;i<n;i++)
		b[i]=new int[m];
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			b[j][i]=a[i][j];

	for(i=0;i<=n;i++)
		r[i]=0;

	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(b[i][j]>0){
				r[i+1]=r[i+1]+1;
				c[r[i]+r[i+1]-1]=j;
				v[r[i]+r[i+1]-1]=b[i][j];
			}
		}
		r[i+1]=r[i+1]+r[i];
	}


	for(i=0;i<=n;i++)
		cout<<r[i];
	cout<<endl;

	for(i=0;i<R[m];i++)
		cout<<c[i];
	cout<<endl;

	for(i=0;i<R[m];i++)
		cout<<v[i];
	cout<<endl;

	for(i=0;i<n;i++){
		for(j=0;j<m;j++)
			cout<<b[i][j];
		cout<<endl;
	}
}
*/

//Second Version, compute rcv directly from RCV, but use matrix a[][] to help to understand
/*
void Sparse_Transpose(int* R,int* C,int* V,int m,int n,int k){
	int** a=new int* [m];
	int i,j,p;
	int *r=new int [n+1];
	int *c=new int [k];
	int *v=new int [k];

	for(i=0;i<m;i++)
		a[i]=new int [n];

	for(i=0;i<=n;i++)
		r[i]=0;

	for(i=1;i<=m;i++){
		p=R[i]-R[i-1];
		for(j=0;j<p;j++){
			a[i-1][C[j+R[i-1]]]=V[j+R[i-1]];
			r[C[j+R[i-1]]+1]=r[C[j+R[i-1]]+1]+1;
		}
	}
	for(i=1;i<k;i++)
		r[i]=r[i-1]+r[i];

	for(i=0;i<k;i++)
		cout<<r[i];
	cout<<endl;

	for(i=m-1;i>=0;i--){
		p=R[i+1]-R[i];
		for(j=p-1;j>=0;j--){
			c[r[C[j+R[i]]+1]-1]=i;
			v[r[C[j+R[i]]+1]-1]=V[j+R[i]];
			r[C[j+R[i]]+1]--;
		}
	}

	for(i=0;i<=n;i++)
		cout<<c[i]<<" ";
	cout<<endl;
	for(i=0;i<=n;i++)
		cout<<v[i]<<" ";

}
*/

//Third Version, compute rcv directly from RCV
/*
void Sparse_Transpose(int* R,int* C,int* V,int m,int n,int k){
	int i,j,p;
	int *r=new int [n+1];
	int *c=new int [k];
	int *v=new int [k];

	//Intitialize the array r to all zeros
	for(i=0;i<=n;i++)
		r[i]=0;

	//r[i] now contains the number non-zero elements of every column of the matrix A, i from 1 to n
	for(i=1;i<=m;i++){
		p=R[i]-R[i-1];
		for(j=0;j<p;j++){
			r[C[j+R[i-1]]+1]=r[C[j+R[i-1]]+1]+1;
		}
	}

	//r[i] now contains the number of all non-zero elements from 1 to i rows of the matrix A'
	for(i=1;i<=n;i++)
		r[i]=r[i-1]+r[i];
	
	//Output the values of every element in array r
	cout<<"R'= <";
	for(i=0;i<n;i++)
		cout<<r[i]<<",";
	cout<<r[n]<<">"<<endl;

	/*Traverse every non-zero element in matrix A in reversed order
	  Acturally, we traverse every element in the arrays C and V in reversed order,
	  The running time is O(k)
	  j+R[i] is the location of element in C or V
	  C[j+R[i]] is the column location of the jth non-zero element in the ith row of the matrix A 
	  r[C[j+R[i]]+1] is the number of non-zero elements in the (C[j+R[i])th column of the matrix A,
	                that is, the number of non-zero elements in the (C[j+R[i])th row of the matrix A'
					We store the counting results in the arrary r from r[1] to r[n], so we add 1 to the indice of r
	  c[r[C[j+R[i]]+1]-1] is the column position of the jth non-zero element in the (C[j+R[i]])th row of the matrix A'
	  v[r[C[j+R[i]]+1]-1] is the value of the jth non-zero element in the (C[j+R[i]])th row of the matrix A'
	  *//*
	for(i=m-1;i>=0;i--){
		p=R[i+1]-R[i];
		for(j=p-1;j>=0;j--){
			c[r[C[j+R[i]]+1]-1]=i;
			v[r[C[j+R[i]]+1]-1]=V[j+R[i]];
			r[C[j+R[i]]+1]--;
		}
	}

	//Output the values of every element in array c
	cout<<"C'= <";
	for(i=0;i<k-1;i++)
		cout<<c[i]<<",";
	cout<<c[k-1]<<">"<<endl;

	//Output the values of every element in array v
	cout<<"V'= <";
	for(i=0;i<k-1;i++)
		cout<<v[i]<<",";
	cout<<v[k-1]<<">"<<endl;
}

int main(){
	int R[4]={0,2,3,5},C[5]={1,3,2,0,1},V[5]={9,1,1,3,8};
	int m,n,k;
		m=3;
		n=4;
		k=5;
	Sparse_Transpose(R,C,V,m,n,k);
return 0;
}
*/

//Forth Version, use "this" pointer to return three arrays
class Matrix{
public:
	void Sparse_Transpose(int* R,int* C,int* V,int m,int n,int k){
		int i,j,p;
		r=new int [n+1];
		c=new int [k];
		v=new int [k];
		rr=new int [n+1];

		//Intitialize the array r to all zeros
		for(i=0;i<=n;i++)
			r[i]=0;

		//r[i] now contains the number non-zero elements of every column of the matrix A, i from 1 to n
		for(i=1;i<=m;i++){
			p=R[i]-R[i-1];
			for(j=0;j<p;j++){
				r[C[j+R[i-1]]+1]=r[C[j+R[i-1]]+1]+1;
			}
		}

		//r[i] now contains the number of all non-zero elements from 1 to i rows of the matrix A'
		for(i=1;i<=n;i++)
			r[i]=r[i-1]+r[i];
	
		//Copy array r to rr, since the values of array r will be changed in the next codes
		for(i=0;i<=n;i++)
			rr[i]=r[i];

		/*Traverse every non-zero element in matrix A in reversed order
		Acturally, we traverse every element in the arrays C and V in reversed order,
		The running time is O(k)
		j+R[i] is the location of element in C or V
		C[j+R[i]] is the column location of the jth non-zero element in the ith row of the matrix A 
		r[C[j+R[i]]+1] is the number of non-zero elements in the (C[j+R[i])th column of the matrix A,
	                that is, the number of non-zero elements in the (C[j+R[i])th row of the matrix A'
					We store the counting results in the arrary r from r[1] to r[n], so we add 1 to the indice of r
		c[r[C[j+R[i]]+1]-1] is the column position of the jth non-zero element in the (C[j+R[i]])th row of the matrix A'
		v[r[C[j+R[i]]+1]-1] is the value of the jth non-zero element in the (C[j+R[i]])th row of the matrix A'
		*/
		for(i=m-1;i>=0;i--){
			p=R[i+1]-R[i];
			for(j=p-1;j>=0;j--){
				c[r[C[j+R[i]]+1]-1]=i;
				v[r[C[j+R[i]]+1]-1]=V[j+R[i]];
				r[C[j+R[i]]+1]--;
			}
		}
	//return *this;
	}

	int* get_c(){
		return c;
	}
	int* get_v(){
		return v;
	}
	int* get_rr(){
		return rr;
	}

//We can also define all the variables public instead of using three "get" functions, but that will make the program not robust
private:
	int *r;
	int *c;
	int *v;
	int *rr;
};

int main(){
	int R[4]={0,2,3,5},C[5]={1,3,2,0,1},V[5]={9,1,1,3,8};
	int m,n,k,i;
		m=3;
		n=4;
		k=5;
	Matrix matrix;
	matrix.Sparse_Transpose(R,C,V,m,n,k);

	//Output the values of every element in array r
	cout<<"R'= <";
	for(i=0;i<n;i++)
		cout<<matrix.get_rr()[i]<<",";
	cout<<matrix.get_rr()[n]<<">"<<endl;

	//Output the values of every element in array c
	cout<<"C'= <";
	for(i=0;i<k-1;i++)
		cout<<matrix.get_c()[i]<<",";
	cout<<matrix.get_c()[k-1]<<">"<<endl;

	//Output the values of every element in array v
	cout<<"V'= <";
	for(i=0;i<k-1;i++)
		cout<<matrix.get_v()[i]<<",";
	cout<<matrix.get_v()[k-1]<<">"<<endl;

return 0;
}