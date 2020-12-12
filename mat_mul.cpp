#include <stdio.h>
#include <iostream>
using namespace std;

/*
  Different implementations of square matrix multiplication.
*/


// Helper function to print the matrices
void print_matrix(int **mat, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout<<mat[i][j]<<" ";
		}
		cout<<endl;
	}
}

/*
  The most straightforward version of matrix multiplication
  that follows from the definition.
*/
void matrix_mult_basic(int **A, int **B, int **result, int n){

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < n; k++){
				result[i][j] += A[i][k]*B[k][j];
			}
		}
	}
}


int main(){
	// Initialize three matrices
	const int n = 3;

	int **A = new int *[n];
	int **B = new int *[n];
	int **result = new int *[n];

	for(int i = 0; i < n; i++){
		A[i] = new int[n];
		B[i] = new int[n];
		result[i] = new int[n];
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			A[i][j] = (i+1)*(j+1);
			B[i][j] = 1;
			result[i][j] = 0;
		}
	}
	cout<<"This is matrix A"<<endl;
	print_matrix(A, n);
	cout<<endl;
	
	cout<<"This is matrix B"<<endl;
	print_matrix(B, n);
	cout<<endl;

	////////////////////////////////////////
	// Multiply A, B and display the result.
	matrix_mult_basic(A, B, result, n);
	cout<<"The result of multiplication:"<<endl;
	print_matrix(result, n);


	return 0;
}