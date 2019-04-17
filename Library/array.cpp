#include <stdlib.h>
#include "array.h"

struct Array
{
	int size;
	int maxSize = 1000;
	int *mainArray;
};

// create array
Array *array_create(size_t size)
{
	Array *tmpArray = new Array;
	tmpArray->size = size;
	tmpArray->mainArray = new int[tmpArray->maxSize];
	memset(tmpArray->mainArray, 0, sizeof(int) * tmpArray->maxSize);
	return tmpArray;
}

// delete array, free memory
void array_delete(Array *arr)
{
	delete[] arr->mainArray;
	delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
	if (index < 1000 && index > 0){
		return arr->mainArray[index];
	}
	else {
		return 0;
	}
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
	if (index < 1000 && index > 0) {
		arr->mainArray[index] = value;
		arr->size++;
	}
}

// returns array size
size_t array_size(const Array *arr)
{
	return arr->size;
}
