#include <stdio.h>
#include "ndarray.h"
#include "ndarray_math.h"

#define NDIMS 3
const size_t SHAPE[NDIMS] = {3,3,3};
const size_t SHAPE2[NDIMS] = {5,3,3};

#define ndarray_null(arg) (arg->data == NULL) ? 1 : 0

int main(){
	ndarray* x = ndarray_linspace(1234, 2341, 234);
	ndarray_print(x);








	ndarray_free(x);
	// ndarray_free(output2);
	return 0;
}
