#include <stdlib.h>
#include "AdptArray.h"

// The struct. contain the size of the Array, a pointer to the elements of the array and 3 functions: 1. Function that copy element. 2. Function that delete element. 3. Function that print the element
typedef struct AdptArray_ {
	int size;
	PElement* elements;
	COPY_FUNC copy_func;
    	DEL_FUNC del_func;
    	PRINT_FUNC print_func;
}AdptArray;

// This func creating a new array by getting the 3 functions and return a pointer to the array
PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func) {

	// Creating a pointer that contaion the place in the memory for the array 
    	PAdptArray array = (PAdptArray)malloc(sizeof(AdptArray));
    	
    	// Condition for extreme case
    	if (array == NULL) {
        	return NULL;
    	}
	
	// Initialize variables and functions
    	array->size = 0;
    	array->elements = NULL;
    	array->copy_func = copy_func;
    	array->del_func = del_func;
    	array->print_func = print_func;

    	return array;
}

// This fun delete the array and its elements
void DeleteAdptArray(PAdptArray array) {
	
	// Condition for extreme case
    	if (array == NULL) {
        	return;
    	}
	
	// Go over all of the elements in the array and if an element is not NULL then use the delete function to delete it
    	for (int i = 0; i < array->size; i++) {
    		if (array->elements[i] != NULL) {
        		array->del_func(array->elements[i]);
        	}
    	}	
	
	// release the memory
    	free(array->elements);
    	free(array);
}

// This func change the element at index in array to the element that the user want 
Result SetAdptArrayAt(PAdptArray array, int index, PElement element) {

	// Condition for extreme case
    	if (array == NULL || index < 0) {
        	return FAIL;
    	}
    	
    	// If the index is "out of bounds" then get in
    	if (index >= array->size) {
    		
    		// create a new pointer of the elements and move the elements in the array to a new memory and add more place until you get to the necessary index 
        	PElement* new_elements = (PElement*)realloc(array->elements, (index + 1) * sizeof(PElement));
        	
        	// Condition for extreme case
        	if (new_elements == NULL) {
            	return FAIL;
        	}
		
		// Update the pointer to the elements to be the new pointer
		array->elements = new_elements;

		// Update the value of the new empty elements to be NULL
        	for (int i = array->size; i <= index; i++) {
            	array->elements[i] = NULL;
        	}
		
		// Update the size of the array
        	array->size = index + 1;
        	
        // If there is an element at this index that isn't NULL then we use the delete function to delete it.
    	} else if (array->elements[index] != NULL) {
        	array->del_func(array->elements[index]);
    	}

    	// Change the element at the index to a copy of the new element by using the copy function
    	array->elements[index] = array->copy_func(element);
    	return SUCCESS;
}

// This func is getting a copy of element by the index in the array
PElement GetAdptArrayAt(PAdptArray array, int index) {

	// Condition for extreme case
    	if (array == NULL || index < 0 || index >= array->size || array->elements[index] == NULL) {        
        	return NULL;
    	}
    	
    	// return a copy using the copy func
    	return array->copy_func(array->elements[index]);
}

// This function return the size of the array
int GetAdptArraySize(PAdptArray array) {
	
	// Condition for extreme case
    	if (array == NULL) {
        	return -1;
    	}

    	return array->size;
}

// This function print the array
void PrintDB(PAdptArray array) {
	
	// Condition for extreme case
    	if (array == NULL) {
        	return;
    	}
	
	// Go over all the elements in the array
    	for (int i = 0; i < array->size; i++) {
    	
    		
    		// Check if its not NULL then print it by using the print func
        	if (array->elements[i] != NULL) {
        		array->print_func(array->elements[i]);
        		printf("\n");
        	}
    	}
}
