#include <stdio.h>
#include <iostream>

using namespace std;
/*Different methods for counting number of inversions in an array
  Inversion: a pair of indices (i, j) where i < j but arr[i] > arr[j]
  Input: array containing integers 1,2,3... in some arbitrary order
  Output: # of inversions
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

/*
	Divide and conquer approach 
	Complexity: O(nlogn)
	Idea: piggyback on mergesort
*/
int num_split_inv_merge_and_count(int arr[], int low, int high){
	int mid = (low+high)/2;
	int i = low, j = mid+1; //i pointer for left half, j pointer for right half. For all i, j -> i < j
	int k = 0; //index for temp arr
	int temp[high-low+1];
	int num_split_inv = 0;

	while(i <= mid && j <= high){
		if(arr[i] < arr[j]){
			temp[k++] = arr[i++]; 
		} else {
			//when we copy from right half, we know for sure that 
			//the number of the remaining elements in the left array
			//counts as a split inversion.
			num_split_inv += mid-i+1;
			temp[k++] = arr[j++];
		}
	}

	while(i <= mid){ temp[k++] = arr[i++]; }
	while(j <= high){temp[k++] = arr[j++]; }

	for(int l=low; l<=high; l++){
		arr[l] = temp[l-low];
	}

	return num_split_inv;

}
int num_inversions_sort_and_count(int arr[], int low, int high){
	if (low == high) {//in length of the array = 1
		return 0;
	} else {
		int mid = (low+high)/2, total = 0;
		total += num_inversions_sort_and_count(arr, low, mid);//sort and count left half
		total += num_inversions_sort_and_count(arr, mid+1, high);//sort and count right half
		total += num_split_inv_merge_and_count(arr, low, high);

		return total;
	}
}

int main(){
	const int length = 7;
	// int arr[length] = {1,3,5,2,4,6};
	// int arr[length] = {6,2,5,1,4,3};
	int arr[length] = {3,4,7,1,2,6,5};

	// int arr[length] = {6,5,4,3,2,1};


	int result_brut = num_inversions_brute_force(arr, length);
	int result_rec = num_inversions_sort_and_count(arr, 0, length-1);
	cout<<"(Brute-force) Number of inversions is: "<<result_brut<<endl;
	cout<<"(Recursive) Number of inversions is: "<<result_rec<<endl;


 	return 0;
}
