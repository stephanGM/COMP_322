#include <iostream>
#include <stdlib.h>
#include <functional>

#define LENGTH 10

typedef bool(*compFunction)(int,int);

bool isLessThan(int a, int b);
bool isGreaterThan(int a, int b);


/*!
	generates a random array to be sorted by the other function
	@return p is the random array of size LENGTH
	
 */
int* generateArray(){
	int* p = new int[LENGTH]; // array to sort
	int mod = 10;
	for(int i = 0; i < LENGTH; i++){ // fill array with random values
		p[i] = rand() % mod;
	}
	return p;
}


/**************************************************************************
	Lambda Sorting
 **************************************************************************/

/*!
	sortWithStandardFunction implements bubble sort algorithm
	@param int* p is the array to be sorted
	@param int length is the length of the array
	@param std::function<bool(int,int) is the function deciding the order
	
 */
void sortWithStandardFunction(int* p, int length, std::function<bool(int,int)> compFunction){
	
	int temp;
	int sorted = 0; 					// flag indicating sorted array
	while (sorted == 0){
		sorted = 1;
		for(int i = 0; i < length-1; i++){ 		// run through array
			if (compFunction(p[i+1],p[i])){ 	// call function to compare
				temp = p[i];			// swap when required
				p[i] = p[i+1];
				p[i+1] = temp;
				sorted = 0;
			}
		}
	}
	return;
}

/*!
	generateNearestTo will compare two numbers to see which one is closest to center
	@param center number to be compared to
	@param int a value to be compared with center
	@param int b value to be compared with center
	@return comparison to see which value is closest to specified center
 */
std::function<bool(int,int)> generateNearestTo (int center){
	return [center](int a, int b){return abs(center - abs(a)) < abs(center - abs(b));};
}

/*!
	testSortLambdas tests the Lambda sorting functions usinf a 
	random array. tests ascending, descending and closest to 3 and 10
 */
void testSortLambdas(){

	int* p = generateArray();

	std::cout << "unsorted" << std::endl;
	for(int i = 0; i < LENGTH; i++){ // print random array
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "ascending" << std::endl;
	sortWithStandardFunction(p, LENGTH, isLessThan);
	for(int i = 0; i < LENGTH; i++){ // print ascending array
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "descending" << std::endl;
	sortWithStandardFunction(p, LENGTH, isGreaterThan);
	for(int i = 0; i < LENGTH; i++){ // print descending array
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "nearest to 3" << std::endl;
	sortWithStandardFunction(p, LENGTH, generateNearestTo(3));
	for(int i = 0; i < LENGTH; i++){ // print array ordered nearest to 3
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "nearest to 10" << std::endl;
	sortWithStandardFunction(p, LENGTH, generateNearestTo(10));
	for(int i = 0; i < LENGTH; i++){ // print array ordered nearest to 10
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;
}


/**************************************************************************
	Interface Sorting
 **************************************************************************/

/*!
	Base class IComparer houses function isBefore to be overiden by
	derived classes
 */
class IComparer{
	public:
		virtual bool isBefore(int a, int b)= 0; // pure virtual
};

/*!
	LessThanCompare is derived from IComparer and overides isBefore 
	to check less than 
 */
class LessThanComparer : public IComparer {
	public:
		bool isBefore(int a, int b){
			if (a < b) return true;
			return false;
		}
};

/*!
	GreaterThanCompare is derived from IComparer and overides isBefore 
	to check greater than 
 */
class GreaterThanComparer : public IComparer {
	public:
		bool isBefore(int a, int b){
			if (a > b) return true;
			return false;
		}
};

/*!
	IsClosestToCompare is derived from IComparer and overides isBefore 
	to check which number is closer to private member int center_v
 */
class IsClosestToComparer : public IComparer{
	private:
		int center_v;
	public:
		IsClosestToComparer(int c): IComparer(), center_v(c){
			std::cout<< "center is " << center_v << std::endl;
		}

	bool isBefore(int a, int b){
		if(abs(center_v - a) < abs(center_v - b)) return true;
		return false;
	}

};

/*!
	sortWithPointers implements bubble sort algorithm
	@param int* p is the array to be sorted
	@param int length is the length of the array
	@param IComparer* comp is an interface used to compare integers
 */
void sortWithInterface(int* p, int length, IComparer* comp){
	int temp;
	int sorted = 0; 					// flag indicating sorted array
	while (sorted == 0){
		sorted = 1;
		for(int i = 0; i < length-1; i++){ 		// run through array
			if (comp->isBefore(p[i+1],p[i])){ 	// call interface to compare
				temp = p[i];			// swap when required
				p[i] = p[i+1];
				p[i+1] = temp;
				sorted = 0;
			}
		}
	}
	return;
}

/*!
	testSortInterface tests the sorting function by using
	interfaces to sort a random array in ascending and descending order
	as well as arranging them in order of closest to chosen number
	It runs all three and then prints the results and random array
	for comparison
 */
void testSortInterface(){
	IComparer* less = new LessThanComparer;
	IComparer* greater = new GreaterThanComparer;
	IComparer* closest = new IsClosestToComparer(5);

	int* p = generateArray();

	std::cout << "unsorted" << std::endl;
	for(int i = 0; i < LENGTH; i++){ // print random array
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "ascending" << std::endl;
	sortWithInterface(p, LENGTH, less);
	for(int i = 0; i < LENGTH; i++){ // print ascending array
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "descending" << std::endl;
	sortWithInterface(p, LENGTH, greater);
	for(int i = 0; i < LENGTH; i++){ // print descending array
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "closest" << std::endl;
	sortWithInterface(p, LENGTH, closest);
	for(int i = 0; i < LENGTH; i++){ // print closest to array
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;
}

/**************************************************************************
	Pointer Sorting
 **************************************************************************/


/*!
	sortWithPointers implements bubble sort algorithm
	@param int* p is the array to be sorted
	@param int length is the length of the array
	@param bool(*compFunction)(int)(int) is a fn used to compare integers
 */
void sortWithPointers(int* p, int length, bool(*compFunction)(int,int)){
	int temp;
	int sorted = 0; 					// flag indicating sorted array
	while (sorted == 0){
		sorted = 1;
		for(int i = 0; i < length-1; i++){ 		// run through array
			if (compFunction(p[i+1],p[i])){ 	// call compFunction to compare
				temp = p[i];			// swap when required
				p[i] = p[i+1];
				p[i+1] = temp;
				sorted = 0;
			}
		}
	}
	return;
}

/*!
	isLessThan compares two ints
	@param int a should be the lower number
	@param int b should be the higher number
	@return bool returns true if a is less than b
 */
bool isLessThan(int a, int b){
	if (a < b) return true;
	return false;
}

/*!
	isGreaterThan compares two ints
	@param int a should be the higher number
	@param int b should be the lower number
	@return bool returns true if a is greater than b
 */
bool isGreaterThan(int a, int b){
	if (a > b) return true;
	return false;
}

/*!
	testSortPointers tests the sorting function by using
	pointers to isGreaterThan and isLessThan to sort a random array
	in ascending and descending order
	It runs both and then prints the results and random array
	for comparison
 */
void testSortPointers(){
	int* p = generateArray();

	std::cout << "unsorted" << std::endl;
	for(int i = 0; i < LENGTH; i++){ // print random array
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "ascending" << std::endl;
	sortWithPointers(p, LENGTH, isLessThan);
	for(int i = 0; i < LENGTH; i++){ // print ascending array
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "descending" << std::endl;
	sortWithPointers(p, LENGTH, isGreaterThan);
	for(int i = 0; i < LENGTH; i++){ // print descending array
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;
}


int main(){

	std::cout << std::endl;

	std::cout << "======================" << std::endl;
	std::cout << "Testing using Pointers" << std::endl;
	std::cout << "======================" << std::endl;
	testSortPointers();

	std::cout << std::endl;


	std::cout << "======================" << std::endl;
	std::cout << "Testing using Interface" << std::endl;
	std::cout << "======================" << std::endl;
	testSortInterface();

	std::cout << std::endl;

	std::cout << "======================" << std::endl;
	std::cout << "Testing using Lambdas" << std::endl;
	std::cout << "======================" << std::endl;
	testSortLambdas();

	std::cout << std::endl;

	return 0;
}
