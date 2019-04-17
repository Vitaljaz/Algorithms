#include <stdlib.h>
#include "vector.h"

struct Vector
{
	size_t size = 0;
	size_t vSize = 0;
	int *container = new int[0];
};

Vector *vector_create()
{
	Vector *vector = new Vector();
	return vector;
}

void vector_delete(Vector *vector)
{
	delete[] vector->container;
	delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
	if (index > 0 && vector->size >= index) {
		return vector->container[index];
	}
	else {
		std::cout << "Invalid index" << std::endl;
		return 0;
	}
}

void vector_set(Vector *vector, size_t index, Data value)
{
	if (index > 0 && vector->size >= index) {
		vector->container[index] = value;
		vector->vSize = index + 1;
	}
	else {
		vector_resize(vector, index + 1);
		vector->container[index] = value;
	}
}

size_t vector_size(const Vector *vector)
{
	return vector->vSize;
}

void vector_resize(Vector *vector, size_t size)
{

	size_t oldSize = vector->vSize;
	if (vector->size < size) {
		vector->vSize = size;

		if (vector->size * 2 > size || vector->size == 0)
			size = (vector->size > 0) ? (vector->size * 2) : 1;

		int *array = new int[size];
		for (size_t i = 0; i < vector->vSize; ++i) {
			if (i < oldSize) {
				array[i] = vector->container[i];
			}
			else {
				array[i] = 0;
			}
		}

		delete[] vector->container;
		vector->container = array;
		vector->size = size;
	}
	else if (vector->size > size) {
		vector->vSize = size;
		for (size_t i = oldSize; i < vector->vSize; ++i) {
			vector->container[i] = 0;
		}
	}
}
