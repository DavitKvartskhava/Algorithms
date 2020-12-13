/*
  This file includes different implementations of matrix multiplication.
*/

#include <stdio.h>
#include <iostream>
using namespace std;

// Helper function to print the matrices
void print_matrix(int **mat, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout<<mat[i][j]<<" ";
		}
		cout<<endl;
	}
}
// Helper function to initialize 2d arrays
int **init_matrix(int size){
	int **mat = new int *[size];
	for(int i = 0; i < size; i++){
		mat[i] = new int[size];
	}
	return mat;
}

/*
  The most straightforward version of matrix multiplication
  that follows from the definition.
*/
void matrix_mult_basic(int **A, int **B, int **result, int n){

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			result[i][j] = 0;
			for(int k = 0; k < n; k++){
				result[i][j] += A[i][k]*B[k][j];
			}
		}
	}
}

/*
	mat_add and mat_subtract are helper functions for Strassen's
	multiplication algorithm. 
*/
//Return A+B
int **mat_add(int **A, int**B, int n){
	int **res = init_matrix(n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			res[i][j] = A[i][j]+B[i][j];
		}
	}
	return res;
}
//Return A-B
int **mat_subtract(int **A, int**B, int n){
	int **res = init_matrix(n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			res[i][j] = A[i][j]-B[i][j];
		}
	}
	return res;
}

// strassen's disgusting algorithm //
// Assuming n = 2^k for some k
int **strassens_multiplication(int **X, int **Y, int n){
	int **result = init_matrix(n);

	if(n == 1){
		matrix_mult_basic(X, Y, result, n);
		return result;
	} else {
		/* Initialize block matrices, where:
			X = [A B] and Y = [E F]
				[C D]         [G H] */
		int **A = init_matrix(n/2);
		int **B = init_matrix(n/2);
		int **C = init_matrix(n/2);
		int **D = init_matrix(n/2);
		int **E = init_matrix(n/2);
		int **F = init_matrix(n/2);
		int **G = init_matrix(n/2);
		int **H = init_matrix(n/2);

		//populate the block matrices with actual values
		for(int i = 0; i < n/2; i++){
			for(int j = 0; j < n/2; j++){
				A[i][j] = X[i][j];
				E[i][j] = Y[i][j];
				B[i][j] = X[i][j+n/2];
				F[i][j] = Y[i][j+n/2];
				C[i][j] = X[i+n/2][j];
				G[i][j] = Y[i+n/2][j];
				D[i][j] = X[i+n/2][j+n/2];
				H[i][j] = Y[i+n/2][j+n/2];
			}
		}

		int **P1 = init_matrix(n/2);
		int **P2 = init_matrix(n/2);
		int **P3 = init_matrix(n/2);
		int **P4 = init_matrix(n/2);
		int **P5 = init_matrix(n/2);
		int **P6 = init_matrix(n/2);
		int **P7 = init_matrix(n/2);


		P1 = strassens_multiplication(A, mat_subtract(F,H,n/2), n/2);//A(F-H)
		P2 = strassens_multiplication(mat_add(A,B,n/2), H, n/2);//(A+B)H
		P3 = strassens_multiplication(mat_add(C,D,n/2), E, n/2);//(C+D)E
		P4 = strassens_multiplication(D, mat_subtract(G,E,n/2), n/2);//D(G-E)
		P5 = strassens_multiplication(mat_add(A,D,n/2), mat_add(E,H,n/2), n/2);//(A+D)(E+H)
		P6 = strassens_multiplication(mat_subtract(B,D,n/2), mat_add(G,H,n/2), n/2);//(B-D)(G+H)
		P7 = strassens_multiplication(mat_subtract(A,C,n/2), mat_add(E,F,n/2), n/2);//(A-C)(E+F)


		//plug values into resulting matrix
		for(int i = 0; i < n/2; i++){
			for(int j = 0; j < n/2; j++){
				result[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
				result[i][j+n/2] = P1[i][j] + P2[i][j];
				result[i+n/2][j] = P3[i][j] + P4[i][j];
				result[i+n/2][j+n/2] = P1[i][j] + P5[i][j] - P3[i][j] - P7[i][j];
			}
		}
		return result;

	}
}

int main(){
	// Initialize three matrices
	const int n = 4;

	int **A = init_matrix(n);
	int **B = init_matrix(n);
	int **result = init_matrix(n);

	//populate A, B with arbitrary values
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			A[i][j] = (i+1)*(j+1);
			B[i][j] = j+1;
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
	cout<<"The result of basic multiplication:"<<endl;
	print_matrix(result, n);
	cout<<endl;


	int **result_from_strassens = strassens_multiplication(A, B, n);
	cout<<"The result of Strassen's multiplication:"<<endl;
	print_matrix(result_from_strassens, n);

	return 0;
}