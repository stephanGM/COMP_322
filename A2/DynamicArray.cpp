/*! 
	@file DynamicArray.cpp
	@author Stephan Greto-McGrath
	@version 1.0

	@section DESCRIPTION

	The classes contained within are as a dynamic (extensible) array
	and an iterator for the array
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

#define BACKEND_SIZE 10 

template <class T> class DynamicArrayIterator;
template <class T> class DynamicArray;

/*! 
	DynamicArray creates and manages an extensible array
*/
template <class T>
class DynamicArray{
private:
	T *elements;
	unsigned int currentPosition;
	unsigned int capacity;

public:
	unsigned int size;

	/*! 
		Adds an element to the next space of the array. If the array 
		has reached capacity, it doubles the previous array size.
		@param T item is the item to be added to the array
	*/
	void add(T item){
		if (size == capacity){ 				// capacity is full, double size
			T *temp = new T[size];
			for(int i=0; i<size; i++){ 		// temp store values
			    temp[i] = elements[i];
			}
			capacity = capacity * 2;		// double capacity
			delete [] elements;			// kill previous array
			elements = new T[capacity];		// create new array
			for(int i=0; i<size; i++){ 		// populate it
			    elements[i] = temp[i];
			}
			delete [] temp;				// kill temp
		}	
		elements[currentPosition] = item; 		// add item
		currentPosition++;				// increment position
		size++;						// increment size
	}

	/*! 
		Removes the element at position i. If i is in the middle of the array, all values are shifted down to overwrite the space.
		@param int i position at which an item is to be removed from elements
	*/
	T remove(int i){
		T removed = elements[i];
		while(i < size){
			elements [i] = elements [i + 1];
			i++;
		}
		size = size - 1;
		return removed;
	}

	/*! 
		Overloads the [] operator in order to read and write array
		@param int i position at which an array is to be accesed
		@return &elements[i] is the reference to the access point
	*/
	T& operator[](size_t i){ 
		if( i >= size ) {
           cout << "Index out of bounds" << endl; 
           return elements[0];	 			// return first element.
         }
		return elements[i]; 
	}

	/*! 
		Overloads the [] operator in order to read the array
		@param int i position at which an array is to be accesed
		@return elements[i] is value at the access point
	*/
	const T operator[](size_t i) const{ 
		if( i >= size ) {
           cout << "Index out of bounds" << endl; 
           return elements[0];	 			// return first element.
         }
		return elements[i]; 
	}


	/*! 
		Contructs a DynamicArrayIterator set to the begining, going forward
		@return it DynamicArrayIterator configured to start with forward direction
	*/
	DynamicArrayIterator<T> begin(){
		DynamicArrayIterator<T> it = DynamicArrayIterator<T>(this, 0, 1);	
		return it;	

	}

	/*! 
		Contructs a DynamicArrayIterator set to the end, going forward
		@return it DynamicArrayIterator cconfigured to end with forward direction
	*/
	DynamicArrayIterator<T> end(){
		DynamicArrayIterator<T> it = DynamicArrayIterator<T>(this, size, 1);
		return it;

	}

	/*! 
		Contructs a DynamicArrayIterator set to the end, going backward
		@return it DynamicArrayIterator cconfigured to end with backward direction
	*/
	DynamicArrayIterator<T> r_begin(){
		DynamicArrayIterator<T> it = DynamicArrayIterator<T>(this, size-1, -1);	
		return it;

	}

	/*! 
		Contructs a DynamicArrayIterator set to the start, going backward
		@return it DynamicArrayIterator cconfigured to start with backward direction
	*/
	DynamicArrayIterator<T> r_end(){
		DynamicArrayIterator<T> it = DynamicArrayIterator<T>(this, -1, -1);
		return it;
	}


	/*! 
		Constructor for DynamicArray. 
	*/
	DynamicArray(){
		elements = new T[BACKEND_SIZE];	
		size = 0;	
		capacity = BACKEND_SIZE;			
		currentPosition = 0;
	}

	/*! 
		Destructor for DynamicArray. 
	*/
	~DynamicArray() {
		delete [] elements; 
		size = 0;
		capacity = 0;
		currentPosition = 0;
	}

};


/*! 	
	Iterator to be used in the DynamicArray
*/
template <class T> 
class DynamicArrayIterator{
private:
	int currentPosition;
	DynamicArray<T>* array;
	int direction; 					// 1: FORWARD ; -1: BACKWARDS

public:
	/*!  
		Constructor for DynamicArrayIterator. 
		@param DynamicArray<T> *arr points to DynamicArray object
		@param int pos is the current position
		@param dir is the desired direction of iteration
	*/
	DynamicArrayIterator(DynamicArray<T> *arr, int pos, int dir){	
		if (dir != 1 && dir != -1){
			cout << "Invalid direction" << endl;
		}
		currentPosition = pos;
		array = arr;
		direction = dir;
	}

	/*!  
		Overloads the * operator in order to return array values
		using the [] operator which is overloaded in DynamicArray
		@return (*array)[currentPosition] is data from DynamicArray at currentPosition
	*/
	T& operator* (){
		return (*array)[currentPosition];

	}
	
	/*!  
		Overloads the ++ operator in order to increment or decrement 
		the currentPosition variable based on direction of the iterator
		@return void returns void in order to avoid dealing w/ pre and postfix
	*/
	void operator++ (){
		if (direction == 1){ 			// move forward
			if (currentPosition == (*array).size){
				cout << "Index out of bounds" << endl; 
			}else{
				currentPosition++;
			}
		}else if (direction == -1){ 		// move backwards
			if (currentPosition < 0){
				cout << "Index out of bounds" << endl; 
			}else{
				currentPosition--;
			}
		}
	}

	/*!  
		Overloads the == operator in order to compare the contents
		and properties of DynamicArrayIterators and their DynamicArrays
		@param const DynamicArrayIterator& compare is a reference/alias 
		to the object to be compared
		@return bool returns true if DynamicArrayIterators have same 
		contents and properties
	*/
	bool operator == (const DynamicArrayIterator& compare){
		// check to see if content of elements is the same
		for (int i = 0; i < (*array).size; i++){	
			if ((*array)[i] != (*compare.array)[i]){
				return false;
			}
		}
		// check to see if they both have the same current position
		if (currentPosition != compare.currentPosition){
			return false;
		}
		// check to see if they both have the same direction
		if (direction != compare.direction){
			return false;
		}
		// checks have passed
		return true;	
	}

	/*!  
		Overloads the != operator in order to compare the contents
		and properties of DynamicArrayIterators and their DynamicArrays
		@param const DynamicArrayIterator& compare is a reference/alias 
		to the object to be compared
		@return bool returns true if DynamicArrayIterators do not have same 
		contents and properties
	*/
	bool operator != (const DynamicArrayIterator& compare){
		  return !(*this == compare);
	}

};


/*!
	Main function to test functionality of DynamicArray
 */
int main(){
	DynamicArray<int> foo;
	foo.add(3);
	foo.add(2);
	cout << foo[1] << endl;
	foo[1] = 10;
	cout << foo[1] << endl;
	for(DynamicArrayIterator<int> a = foo.begin(); a != foo.end(); ++a) {
		cout << *a << endl;
	}
	for(DynamicArrayIterator<int> a = foo.r_begin(); a != foo.r_end(); ++a) {
	    cout << *a << endl;
	}

}
