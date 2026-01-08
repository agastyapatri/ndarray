#ifndef NDARRAY_H
#define NDARRAY_H
#include <stdatomic.h>
#include <stddef.h>

#ifndef MAX_DIMS
#define MAX_DIMS 8
#endif


/************************************************************
 * NDARRAY ALLOCATION AND POPULATION
************************************************************/

/*
	The core n dimensional array 
	@param int ndims - the number of indices requried to access the elements of the array;
	@param size_t size - the number of elements in the data buffer;
	@param size_t shape - the shape array of the struct. MAX_DIMS is by default set to 8. 
	@param size_t strides - the strides array of the struct. MAX_DIMS is by default set to 8. 
	@param double* data - the raw data buffer. 
*/
typedef struct ndarray {
	int ndims;
	int* ref_count;
	size_t size;
	size_t shape[MAX_DIMS];
	size_t strides[MAX_DIMS];
	double* data;
} ndarray;


/*
	Returns true if either the target ndarray or its data buffer are NULL.
 */
bool NDARRAY_NULL(const ndarray* arr);

/*
	Returns true if the shapes and the dimensionality of two ndarrays are equal.
 */
bool NDARRAY_EQUAL_SHAPE(const ndarray* inp1, const ndarray* inp2);

void NDARRAY_ERROR(char* msg);

ndarray* ndarray_alloc(const int NDIMS, const size_t* SHAPE); ndarray* ndarray_ones(const int NDIMS, const size_t* SHAPE);
ndarray* ndarray_zeroes(const int NDIMS, const size_t* SHAPE);
void ndarray_print(const ndarray* arr);
void ndarray_print_shape(const ndarray* arr);
void ndarray_free(ndarray* arr);

/*
	Calculates the index offset into the flat data buffer of a ndarray.
	Note that the number of indices provided MUST be equal to the ndims of the target ndarray
*/
size_t offset(const ndarray* arr, const size_t* idxs);


/*
	Generates a ndarray of elements randomly selected between the limits [left, right]
 */
ndarray* ndarray_random_uniform(const int NDIMS, const size_t* SHAPE, const double left, const double right);


/*
	Generates a ndarray of elements randomly selected from the random normal distribution with mean mu and standard deviation sigma.
 */
ndarray* ndarray_random_normal(const int NDIMS, const size_t* SHAPE, const double mu, const double sigma);




/************************************************************
 * NDARRAY ARITHMETIC
************************************************************/

//	Elementwise addition
void ndarray_add(ndarray* inp1, ndarray* inp2, ndarray* outs);
//	Elementwise subtraction
void ndarray_sub(ndarray* inp1, ndarray* inp2, ndarray* outs);
//	Elementwise multiplication
void ndarray_hadamard(ndarray* inp1, ndarray* inp2, ndarray* outs);

//	Mapping any single variable scalar function across a ndarray
void ndarray_map(ndarray* arr, double (*function)(double x));


//	Mapping arithmetic functions to an output ndarray 
void ndarray_map_arithmetic(ndarray* inp1, ndarray* inp2, ndarray* output, double (*function)(double x, double y));


//	Scales the elements of the ndarray by a scalar value
void ndarray_scale(ndarray* arr, double scalar);


/************************************************************
 * TODO: NDARRAY MANIPULATION
************************************************************/

/*	
	Returns a ndarray with a view of the original data. Note that both the reshaped and the original ndarrays now own the data. 
 */
ndarray* ndarray_reshape(ndarray* arr, int new_ndim, size_t* new_shape);


/*	
	Swaps the axes of a 
 */
ndarray* ndarray_transpose(ndarray* arr, int* axes);
void ndarray_view();
void ndarray_flatten();



/************************************************************
 * TODO: ADVANCED NDARRAY GENERATION; HSTACK, VSTACK, LINSPACE, ARANGE.
************************************************************/
/*
	Horizontally stacking a set of ndarrays. 
	From NumPy:
	"This is equivalent to concatentation along the second axis, except for 1D arrays, where the concatentation happens along the first axis"


	This function is essentially a reimplementation of numpy.hstack. I've found this function to be very useful when dealing with image data, 
	Where images sometimes need to be stacked along the channel axis, for example.
*/
ndarray* ndarray_hstack(ndarray** arrs, int num);
ndarray* ndarray_vstack(ndarray** arrs, int num);
/*
	Concatentating a sequence of ndarrays about any axis.
*/
ndarray* ndarray_concat(ndarray** arrs, int num, int axis);



#endif
