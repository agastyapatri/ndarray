#include "ndarray.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ndarray_math.h"
// #include <math.h>


bool NDARRAY_NULL(const ndarray* arr){
	return (arr==NULL || arr->data==NULL) ? true : false;
}
bool NDARRAY_EQUAL_SHAPE(const ndarray* inp1, const ndarray* inp2){
	if(NDARRAY_NULL(inp1) || NDARRAY_NULL(inp2)){
		NDARRAY_ERROR("NULL argument(s) in NDARRAY_EQUAL_SHAPE()\n");
	}
	if(inp1->ndims != inp2->ndims) return false;
	for(int i = 0; i < inp1->ndims; i++){
		if(inp1->shape[i] != inp2->shape[i]){
			return false;
		}
	}
	return true;
}

void NDARRAY_ERROR(char* msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

void ndarray_print_shape(const ndarray *arr){
	if(NDARRAY_NULL(arr)){
		NDARRAY_ERROR("NULL argument in ndarray_print_shape()\n");
	}
	printf("(");
	for(int i = 0; i < arr->ndims; i++){
		printf("%li", arr->shape[i]);
		if(i != arr->ndims-1) printf(", ");
	}
	printf(")\n");
}

ndarray* ndarray_alloc(const int NDIMS, const size_t* SHAPE){
	if(NDIMS > MAX_DIMS){
		printf("Invalid NDIMS provided in ndarray_alloc(); ensure NDIMS <= %d\n", MAX_DIMS);
		exit(EXIT_FAILURE);
	}
	ndarray* arr = (ndarray*)malloc(sizeof(ndarray));
	if(!arr){
		NDARRAY_ERROR("Invalid memory allocation in ndarray_alloc()\n");
	}

	arr->ref_count = (int*)calloc(1, sizeof(int));
	(*(arr->ref_count))++;

	arr->ndims = NDIMS;
	arr->size = 1;
	size_t _stride = 1;

	//	populating the ndarray shape, shape and strides
	for(int i = 0; i < arr->ndims; i++){
		arr->shape[i] = SHAPE[i];
		arr->size *= arr->shape[i];
		arr->strides[arr->ndims - i - 1] = _stride;
		_stride *= arr->shape[arr->ndims - i - 1];
	}

	arr->data = (double*)malloc(arr->size*sizeof(double));
	if(!arr->data){
		perror("Invalid memory allocation for ndarray.data in ndarray_alloc()\n");
		exit(EXIT_FAILURE);
	}
	return arr;
}

void ndarray_free(ndarray* arr){
	if(NDARRAY_NULL(arr)){
		NDARRAY_ERROR("NULL argument in ndarray_free()\n");
	}
	(*(arr->ref_count))--;
	if(*(arr->ref_count) == 0){
		free(arr->ref_count);
		free(arr->data);
	}
	free(arr);
}




ndarray* ndarray_zeroes(const int NDIMS, const size_t* SHAPE){
	if(NDIMS > MAX_DIMS){
		printf("Invalid NDIMS provided in ndarray_zeroes(); ensure NDIMS <= %d\n", MAX_DIMS);
		exit(EXIT_FAILURE);
	}
	ndarray* arr = (ndarray*)malloc(sizeof(ndarray));
	if(!arr){
		perror("Invalid memory allocation in ndarray_zeroes()\n");
		exit(EXIT_FAILURE);
	}
	arr->ref_count = (int*)calloc(1, sizeof(int));
	(*(arr->ref_count))++;

	arr->ndims = NDIMS;
	arr->size = 1;
	size_t _stride = 1;

	//	populating the ndarray shape, shape and strides
	for(int i = 0; i < arr->ndims; i++){
		arr->shape[i] = SHAPE[i];
		arr->size *= arr->shape[i];
		arr->strides[arr->ndims - i - 1] = _stride;
		_stride *= arr->shape[arr->ndims - i - 1];
	}

	arr->data = (double*)calloc(arr->size, sizeof(double));
	if(!arr->data){
		perror("Invalid memory allocation for ndarray.data in ndarray_zeros()\n");
		exit(EXIT_FAILURE);
	}
	return arr;
}


ndarray* ndarray_ones(const int NDIMS, const size_t* SHAPE){
	ndarray* arr = ndarray_alloc(NDIMS, SHAPE);
	for(size_t i = 0; i < arr->size; i++)
		arr->data[i] = 1;
	return arr;
}



//	TODO: this needs to be fixed to allow for printing of the dimensions separately 
void ndarray_print(const ndarray* arr){
	if(NDARRAY_NULL(arr)){
		perror("NULL argument provided to ndarray_print()\n");
		exit(EXIT_FAILURE);
	}
	printf("ndarray[");
	for(size_t i = 0; i < arr->size; i++){
		printf("%lf ", arr->data[i]);
	}




	printf("]\n");
} 

size_t offset(const ndarray* arr, const size_t* idxs){
	size_t index = 0;
	for(int i = 0; i < arr->ndims; i++){
		if(idxs[i] > arr->shape[i]){
			printf("Invalid; index being queried at dim = %d is greater than the dimensionality\n", i);
			exit(EXIT_FAILURE);
		}
		index += arr->strides[i]*idxs[i];
	}
	return index;
}

bool ndarray_shape_equality(ndarray* arr1, ndarray* arr2){
	if(arr1->ndims != arr2->ndims){
		return false;
	}
	for(int i = 0; i < arr1->ndims; i++){
		if(arr1->shape[i] != arr2->shape[i])
			return false;
	}
	return true;
}



void ndarray_add(ndarray* inp1, ndarray* inp2, ndarray* outs){
	if(NDARRAY_NULL(inp1) || NDARRAY_NULL(inp2) || NDARRAY_NULL(outs)){
		perror("Argument(s) are NULL in ndarray_add()\n");
		exit(EXIT_FAILURE);
	}
	if(!ndarray_shape_equality(inp1, inp2)){
		perror("Dimensionality and shape of the operands must be equal in ndarray_add()\n");
		exit(EXIT_FAILURE);
	}
	if(inp1->ndims != outs->ndims){
		perror("Dimensionality of the arguments must be equal in ndarray_add()\n");
	}
	for(size_t i = 0; i < inp1->size; i++){
		outs->data[i] = inp1->data[i] + inp2->data[i];
	}
}


void ndarray_sub(ndarray* inp1, ndarray* inp2, ndarray* outs){
	if(NDARRAY_NULL(inp1) || NDARRAY_NULL(inp2) || NDARRAY_NULL(outs)){
		perror("Argument(s) are NULL in ndarray_add()\n");
		exit(EXIT_FAILURE);
	}
	if(!ndarray_shape_equality(inp1, inp2)){
		perror("Dimensionality and shape of the operands must be equal in ndarray_add()\n");
		exit(EXIT_FAILURE);
	}
	if(inp1->ndims != outs->ndims){
		perror("Dimensionality of the arguments must be equal in ndarray_add()\n");
	}
	for(size_t i = 0; i < inp1->size; i++){
		outs->data[i] = inp1->data[i] - inp2->data[i];
	}

}

void ndarray_hadamard(ndarray* inp1, ndarray* inp2, ndarray* outs){
	if(NDARRAY_NULL(inp1) || NDARRAY_NULL(inp2) || NDARRAY_NULL(outs)){
		perror("Argument(s) are NULL in ndarray_add()\n");
		exit(EXIT_FAILURE);
	}
	if(!ndarray_shape_equality(inp1, inp2)){
		perror("Dimensionality and shape of the operands must be equal in ndarray_add()\n");
		exit(EXIT_FAILURE);
	}
	if(inp1->ndims != outs->ndims){
		perror("Dimensionality of the arguments must be equal in ndarray_add()\n");
	}
	for(size_t i = 0; i < inp1->size; i++){
		outs->data[i] = inp1->data[i] * inp2->data[i];
	}
}

ndarray* ndarray_random_uniform(const int NDIMS, const size_t* SHAPE, const double left, const double right){
	ndarray* arr = ndarray_alloc(NDIMS, SHAPE);
	for(size_t i = 0; i < arr->size; i++){
		arr->data[i] = (double)(rand() / (double)RAND_MAX)*(right - left) + left;
	}
	return arr;

}

ndarray* ndarray_random_normal(const int NDIMS, const size_t* SHAPE, const double mu, const double sigma){
	ndarray* arr = ndarray_alloc(NDIMS, SHAPE);
	for(size_t i = 0; i < arr->size; i++){
		double x = (rand() / (double)RAND_MAX);
		double temp = ((x-mu)*(x-mu)) / ((sigma*sigma));
		arr->data[i] = (1 / sqrt(2*PI*sigma*sigma))*exp(-0.5*temp);
	}
	return arr;
}

void ndarray_map(ndarray* arr, double (*function)(double x)){
	if(NDARRAY_NULL(arr)){
		perror("NULL argument in ndarray_map()\n");
		exit(EXIT_FAILURE);
	}
	for(size_t i = 0; i < arr->size; i++)
		arr->data[i] = function(arr->data[i]);
}

void ndarray_map_arithmetic(ndarray* inp1, ndarray* inp2, ndarray* output, double (*function)(double x, double y)){
	if(NDARRAY_NULL(inp1) ||NDARRAY_NULL(inp2) || NDARRAY_NULL(output)){
		perror("NULL argument(s) in ndarray_map_arithmetic()\n");
		exit(EXIT_FAILURE);
	}
	if(!( NDARRAY_EQUAL_SHAPE(inp1, inp2) && NDARRAY_EQUAL_SHAPE(inp1, output))){
		NDARRAY_ERROR("All arugments must have the same shape and dimensionality in ndarray_map_arithmetic()\n");
	}
	for(size_t i = 0; i < output->size; i++)
		output->data[i] = function(inp1->data[i], inp2->data[i]);
}


void ndarray_scale(ndarray* arr, double scalar){
	if(NDARRAY_NULL(arr)){
		perror("NULL argument in ndarray_scale()\n");
		exit(EXIT_FAILURE);
	}
	for(size_t i = 0; i < arr->size; i++)
		arr->data[i] = arr->data[i]*scalar; 

}

ndarray* ndarray_reshape(ndarray* arr, int new_ndim, size_t* new_shape){
	if (NDARRAY_NULL(arr)) {
		NDARRAY_ERROR("NULL argument in ndarray_reshape()\n");
	}
	size_t new_size = 1;
	for(int i = 0; i < new_ndim; i++){
		new_size *= new_shape[i];
	}
	if(new_size != arr->size){
		NDARRAY_ERROR("Incompatible shapes provided in ndarray_reshape(); ensure that the intended cardinality of the reshaped ndarray is equal to the target\n");
	}
	ndarray* out = (ndarray*)malloc(sizeof(ndarray));
	out->data = arr->data;
	out->ndims = new_ndim;
	out->size = new_size;

	//	ref counter increment
	(*(arr->ref_count))++;
	out->ref_count =  arr->ref_count;
	
	memcpy(out->shape, new_shape, new_ndim*sizeof(size_t));
	int _strides = 1;
	for(int i = 0; i < new_ndim; i++){
		out->strides[new_ndim-i-1] = _strides;
		_strides *= new_shape[new_ndim - i - 1];
	}
	return out;
}



//	TODO: Finish 
// ndarray* ndarray_concat(ndarray** arrs, int num, int axis){
// 	if(NDARRAY_NULL(arrs[0])){
// 		perror("NULL ndarray in ndarray_concat()\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	int ndim = arrs[0]->ndims;
// 	if(axis > ndim)
// 		NDARRAY_ERROR("Concatenation axis must be <= the number of dimensions of the ndarrray in ndarray_concat()\n");
// 	size_t* shape = arrs[0]->shape;
// 	size_t output_shape[ndim];
// 	memcpy(output_shape, shape, ndim*sizeof(size_t));
//
// 	for(int i = 1; i < num; i++){
// 		if(NDARRAY_NULL(arrs[i])){
// 			NDARRAY_ERROR("NULL ndarray in ndarray_concat()\n");
// 		}
// 		if(arrs[i]->ndims != ndim){
// 			NDARRAY_ERROR("All input arrays must have the same number of dimensions in ndarray_concat()\n");
// 		}
// 		for(int j = 0; j < ndim; j++){
// 			if(j == axis) continue;
// 			if(shape[j] != arrs[i]->shape[j]){
// 				NDARRAY_ERROR("All Input dimensions except the concatenation axis must match exactly in ndarray_concat()\n");
// 			}
// 		} 
// 		output_shape[axis] += arrs[i]->shape[axis];
// 	}
// 	ndarray* output = ndarray_alloc(ndim, output_shape);
// 	return output;
// }

