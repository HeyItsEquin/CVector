# CVector
Simple vector implementation in C, not exactly memory safe.

Currently only supports vector of `int`s, will probably add support for custom data types later.

Currently implemented methods:

`void v_pushback(vector *v, int val)` Pushes `val` to the end of the vector. Reallocates memory if necessary. Sets errno on failure.

`void v_pushback(vector *v, int val)` Pushes `val` to the end of the vector. Reallocates memory if necessary.
Sets errno on failure.

`int v_poplast(vector *v)` Pops the last element of the vector and returns it. Returns 0 if the vector is empty.

`int v_popfirst(vector *v)` Pops the first element of the vector and returns it. Returns 0 if the vector is empty.
Sets errno on failure.

`void v_shrinktofit(vector *v)` Shrinks `v->capacity` to `v->size` and reallocates the memory appropriately.
Sets errno on failure