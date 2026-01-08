#   **N-Dimensional arrays in C**

NOTE: This project is currently on ice. I will come back to this in the near future



The core struct of this library is the `ndarray`; a tiny implementation of the `numpy.ndarray`. 
The eventual goal of this project is to allow me to train tiny neural networks with a minimal set of tools - tensors, autograd, optim, and some accoutrements.




##  Roadmap
1.  **`ndarray` implementation and population:**
    
    -   ~allocation, deallocation~
    -   ~ones, zero tensors~
    -   random tensors; ~uniform~ and ~normal~


2.  **`ndarray` arithmetic** 

    -   ~elementwise addition~
    -   ~elementwise subtraction~
    -   ~elementwise multiplication (hadamard)~
    -   ~elementwise division~
    -   matmul along specific dimensions. -- look into how `numpy` does this.


3.  **`ndarray` manipulation** 
    
    -   transpose 
    -   view 
    -   ~reshape~
    -   flatten
    -   inverse??


4.  **miscellaneous**

-   `OPTYPE` - eventual automatic differentiation on these tensors will require `optype` and `backward_fn` type fields


##  What I'm dealing with right now.

-   When an ndarray is created which is a view of another , i.e owns the same data as an original ndarray, calling `ndarray_free()` on one should lead to `NDARRAY_NULL()` being true for the other. Why is that not the case??
-   How do I implement `ndarray_transpose()`? 


