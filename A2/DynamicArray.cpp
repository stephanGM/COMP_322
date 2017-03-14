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

#define BACKEND_SIZE 10 

template <class T> class DynamicArrayIterator;
template <class T> class DynamicArray;

/*! 
	DynamicArray creates and manages an extensible array
*/
template <class T>
class DynamicArray{
private:
	T *elements_;
	unsigned int currentPosition_;
	unsigned int capacity_;

public:
	unsigned int size;

	/*! 
		Adds an element to the next space of the array. If the array 
		has reached capacity, it doubles the previous array size.
		@param T item is the item to be added to the array
	*/
	void add(T item){
		if (size == capacity_){ 			// capacity is full, double size
			T *temp = new T[size];
			for(int i=0; i<size; i++){ 		// temp store values
			    temp[i] = elements_[i];
			}
			capacity_ = capacity_ * 2;		// double capacity
			delete [] elements_;			// kill previous array
			elements_ = new T[capacity_];	// create new array
			for(int i=0; i<size; i++){ 		// populate it
			    elements_[i] = temp[i];
			}
			delete [] temp;					// kill temp
		}	
		elements_[currentPosition_] = item; // add item
		currentPosition_++;					// increment position
		size++;								// increment size
	}

	/*! 
		Removes the element at position i. If i is in the middle of the array, all values are shifted down to overwrite the space.
		@param int i position at which an item is to be removed from elements
	*/
	T remove(int i){
		T removed = elements_[i];
		while(i < size){
			elements_[i] = elements_[i + 1];
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
			std::cout << "Index out of bounds" << std::endl; 
			return elements_[0];	 			// return first element.
        }
		return elements_[i]; 
	}

	/*! 
		Overloads the [] operator in order to read the array
		@param int i position at which an array is to be accesed
		@return elements[i] is value at the access point
	*/
	const T operator[](size_t i) const{ 
		if( i >= size ) {
			std::cout << "Index out of bounds" << std::endl; 
			return elements_[0];	 			// return first element.
        }
		return elements_[i]; 
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
		elements_ = new T[BACKEND_SIZE];	
		size = 0;	
		capacity_ = BACKEND_SIZE;			
		currentPosition_ = 0;
	}

	/*! 
		Destructor for DynamicArray. 
	*/
	~DynamicArray() {
		delete [] elements_; 
		size = 0;
		capacity_ = 0;
		currentPosition_ = 0;
	}

};


/*! 	
	Iterator to be used in the DynamicArray
*/
template <class T> 
class DynamicArrayIterator{
private:
	int currentPosition_;
	DynamicArray<T>* array_;
	int direction_; 					// 1: FORWARD ; -1: BACKWARDS

public:
	/*!  
		Constructor for DynamicArrayIterator. 
		@param DynamicArray<T> *arr points to DynamicArray object
		@param int pos is the current position
		@param dir is the desired direction of iteration
	*/
	DynamicArrayIterator(DynamicArray<T> *arr, int pos, int dir){	
		if (dir != 1 && dir != -1){
			std::cout << "Invalid direction" << std::endl;
		}
		currentPosition_ = pos;
		array_ = arr;
		direction_ = dir;
	}

	/*!  
		Overloads the * operator in order to return array values
		using the [] operator which is overloaded in DynamicArray
		@return (*array)[currentPosition] is data from DynamicArray at currentPosition
	*/
	T& operator* (){
		return (*array_)[currentPosition_];

	}
	
	/*!  
		Overloads the ++ operator in order to increment or decrement 
		the currentPosition variable based on direction of the iterator
		@return void returns void in order to avoid dealing w/ pre and postfix
	*/
	void operator++ (){
		if (direction_ == 1){ 			// move forward
			if (currentPosition_ == (*array_).size){
				std::cout << "Index out of bounds" << std::endl; 
			}else{
				currentPosition_++;
			}
		}else if (direction_ == -1){ 		// move backwards
			if (currentPosition_ < 0){
				std::cout << "Index out of bounds" << std::endl; 
			}else{
				currentPosition_--;
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
		for (int i = 0; i < (*array_).size; i++){	
			if ((*array_)[i] != (*compare.array_)[i]){
				return false;
			}
		}
		// check to see if they both have the same current position
		if (currentPosition_ != compare.currentPosition_){
			return false;
		}
		// check to see if they both have the same direction
		if (direction_ != compare.direction_){
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
	Main function to test functionality of DynamicArray and DynamicArrayIterator
 */
int main(){
	DynamicArray<int> foo;
	foo.add(3);
	foo.add(2);
	std::cout << foo[1] << std::endl;
	foo[1] = 10;
	std::cout << foo[1] << std::endl;
	for(DynamicArrayIterator<int> a = foo.begin(); a != foo.end(); ++a) {
		std::cout << *a << std::endl;
	}
	for(DynamicArrayIterator<int> a = foo.r_begin(); a != foo.r_end(); ++a) {
	    std::cout << *a << std::endl;
	}

}
