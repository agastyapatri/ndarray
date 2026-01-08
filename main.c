#include <stdio.h>
#include "ndarray.h"
#include "ndarray_math.h"

#define NDIMS 3
const size_t SHAPE[NDIMS] = {3,3,3};
const size_t SHAPE2[NDIMS] = {5,3,3};

#define ndarray_null(arg) (arg->data == NULL) ? 1 : 0

int main(){
	// ndarray* arr = ndarray_random_normal(NDIMS, SHAPE, -1, 1);
	ndarray* arr = ndarray_zeroes(NDIMS, SHAPE);

	int ndims2 = 2;
	size_t shape2[2] = {9, 3};
	ndarray* output = ndarray_reshape(arr, ndims2, shape2);	
	for(size_t i = 0; i < output->shape[0]; i++){
		size_t idxs[2] = {i, 0};
		output->data[offset(output, idxs)] = 100;
	}
	for(size_t i = 0; i < output->shape[0]; i++){
		for(size_t j = 0; j < output->shape[1]; j++){
			size_t idxs[2] = {i, j};
			printf("%lf ", output->data[offset(output, idxs)]);
		} 
		printf("\n");
	}
	printf("\n\n");


	int ndims3 = 2;
	size_t shape3[2] = {3, 9};
	ndarray* output2 = ndarray_reshape(output, ndims3, shape3);	
	ndarray_print_shape(output2);

	for(size_t i = 0; i < output2->shape[0]; i++){
		for(size_t j = 0; j < output2->shape[1]; j++){
			size_t idxs[2] = {i, j};
			printf("%lf ", output2->data[offset(output2, idxs)]);
		} 
		printf("\n");
	}
	printf("\n\n");








	ndarray_free(arr);
	ndarray_free(output);
	// ndarray_free(output2);
	return 0;
}
