#include <stdio.h>
#include <iostream>

using namespace std;
/*Different methods for counting number of inversions in an array
  Inversion: a pair of indices (i, j) where i < j but arr[i] > arr[j]
*/


//Inneficient brute-force implementation.
int num_inversions_brute_force(int arr[], int length){
	int counter = 0;
	for(int i = 0; i < length - 1; i++){//no need to assign i to the last element of the array
		for(int j = i; j < length; j++){

			if (arr[i] > arr[j]){ counter++; } 
		}
	}
	return counter;
}
int main(){
	const int length = 6;
	// int arr[length] = {1,3,5,2,4,6};
	int arr[length] = {6,5,4,3,2,1};

	
	int result = num_inversions_brute_force(arr, length);
	cout<<"Number of inversions is: "<<result<<endl;
 	return 0;
}
