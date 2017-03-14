/*! 
	Runtime Comparison compares the runtimes of bubble sort
	and merge sort algorithms for various lengths 
	of unordered int arrays
*/

#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

/*!
	bubbleSort implements the bubble sort algorithm
	@param int* p is the array to be sorted
	@param int length is the length of the array
 */
void bubbleSort(int* p, int length){
	int temp;
	int sorted = 0; // flag indicating array is sorted
	while (sorted == 0){
		sorted = 1;
		for(int i = 0; i < length-1; i++){ // run through array
			if (p[i] > p[i+1]){ // swap when required
				temp = p[i];
				p[i] = p[i+1];
				p[i+1] = temp;
				sorted = 0;
			}
		}
	}
	return;
}

/*!
	merge is a helper function which compares and merges the split arrays
	@param int* p is the array to be sorted
	@param int* left is the left split array portion
	@param int l_length is the length of the left split array portion
	@param int* right is the right split array portion
	@param int r_length is the length of the right split array portion
 */
void merge(int* p, int* left, int l_length, int* right, int r_length){
	int r = 0, l = 0, i = 0;
	while(i < l_length + r_length){ // compare and fill the larger array
		if (l == l_length) p[i++] = right[r++];
		else if (r == r_length)	p[i++] = left[l++];
		else p[i++] = (right[r] > left[l]) ? left[l++] : right[r++];
	}

}

/*!
	mergeSort implements the recursive merge sort algorithm 
	using merge as a helper function
	@param int* p is the array to be sorted
	@param int length is the length of the array
 */
void mergeSort(int* p, int length){
	if (length < 2) return; // return if array is too short to sort
	int mid = length / 2; // determine midpoint of array
	// create arrays to split array in 2
    int left [mid]; 
    int right [length - mid];	
    // fill the arrays
    int j = 0;
	for (int i = 0; j < mid; i++) left[i] = p[j++]; 
	for (int i = 0; j < length; i++) right[i] = p[j++];
	// recursively sort the split arrays
	mergeSort(left, mid);
	mergeSort(right, length-mid);
	// merge the split arrays 
	merge(p, left, mid, right, length - mid);
}



/*!
	The main method runs a comparison between the running times of
	each of the algorithms (bubble and merge sort), 
	continually doubling the length of the array to be sorted 
	while increasing the size of the numbers in the array,
	until bubble sort takes over a second to run.
	It then prints the length of the last array.
 */
int main(){

	int mod = 10; // this var controls the size of the random numbers
	int length = 10; // var specifies the length of the arrays
	int sec = 1; // runtime in seconds
	double bubble_time;
	cout.precision(6);

	clock_t t_merge = 0, t_bubble = 0;

	cout << "n" << "\t" << "bubble" << "\t" << "merge" << endl;
	while(t_bubble < sec * CLOCKS_PER_SEC){
		t_merge = 0;
		t_bubble = 0;
		// create two arrays, one for each algorithm to sort
		// why? because we want the timing to be compared 
		// with the same input to each 
		int* p_merge = new int[length];
		int* p_bubble = new int[length];
		int fill; // temp var to fill arrays

		// create a random array
		for(int i = 0; i < length; i++){
			fill = rand() % mod;
			p_merge[i] = fill;
			p_bubble[i] = fill;
		}

		// time and run merge sort
		t_merge = clock();
		mergeSort(p_merge, length);
		t_merge = clock() - t_merge;

		// time and run bubble sort
		t_bubble = clock();
		bubbleSort(p_bubble, length);
		t_bubble = clock() - t_bubble; 

		cout << length << "\t";
		cout << fixed << (double) t_bubble / CLOCKS_PER_SEC << "\t";
		cout << fixed << (double) t_merge / CLOCKS_PER_SEC << endl;

		length = length * 2; // double the length of the array
		if (mod - length > 0) mod = mod * 10; // generate larger rand #s
		
		// clean up before next iteration
		delete p_merge;
		delete p_bubble;
		p_merge = NULL;
		p_bubble = NULL;

	}
	
	cout << "array length at termination is: " << length/2 << endl;
}