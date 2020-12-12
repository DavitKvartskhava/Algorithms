#include <stdio.h>
#include <iostream>

using namespace std;
void merge(int arr[], int low, int high){
	int mid = (low+high)/2;
	int i=low, j=mid+1, k=0;
	int temp[high-low+1];

	while (i<=mid and j<=high){
		if (arr[i] > arr[j]){
			temp[k++] = arr[j++];
		} else {
			temp[k++] = arr[i++];
		}
	}

	while(i<=mid){
		temp[k++] = arr[i++];
	}

	while(j<=high){
		temp[k++] = arr[j++];
	}

	for(int l=low; l<=high; l++){
		arr[l] = temp[l-low];
	}

}

void mergesort(int arr[], int low, int high){
	if (low<high){

		int mid = (high+low)/2;

		mergesort(arr, low, mid);
		mergesort(arr, mid+1, high);
		merge(arr, low, high);
	}	
}

int main(){
	int arr[8] = {121,9,4,13,61,1,83,2};

	mergesort(arr, 0, 7);
	for(int i = 0; i < 8; i++){
		cout<<arr[i]<<endl;
	}
	return 0;
}