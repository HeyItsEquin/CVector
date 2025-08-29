#include "vector.h"
#include <errno.h>
#include <string.h>

#define VLAST(v) v->size/sizeof(int)

#define V_MALLOC_FAIL 0x1
#define V_REALLOC_FAIL 0x2
#define V_COPY_FAIL 0x3

vector *v_new() {
    vector* v = malloc(sizeof(vector));
    v->size = 0;
    v->capacity = sizeof(int);

    v->data = (int*)malloc(v->capacity);
    if (!v->data) {
        errno = V_MALLOC_FAIL;
        return v;
    }

    return v;
}

void v_pushback(vector *v, int val) {
    if (v->size + sizeof(int) > v->capacity) {
        size_t new_capacity = v->capacity ? v->capacity * 2 : sizeof(int) * 2;

        if (new_capacity < v->size + sizeof(int))
            new_capacity = v->size + sizeof(int);
        
        int* new_mem = (int*)realloc(v->data, new_capacity);
        
        if (!new_mem) {
            return;
        }

        v->data = new_mem;
        v->capacity = new_capacity;
    }

    v->data[VLAST(v)] = val;
    v->size += sizeof(val);
}

void v_push(vector *v, int val) {
    if (v->size + sizeof(int) > v->capacity) {
        size_t new_capacity = v->capacity ? v->capacity * 2 : sizeof(int) * 2;

        if (new_capacity < v->size + sizeof(int))
            new_capacity = v->size + sizeof(int);

        int* new_mem = (int*) realloc(v->data, new_capacity);

        if (!new_mem) {
            return;
        }

        v->data = new_mem;
        v->capacity = new_capacity;
    }

    memcpy(&v->data[1], v->data, v->size);
    if (!v->data) {
        errno = V_COPY_FAIL;
        return;
    }

    v->data[0] = val;
    v->size += sizeof(int);
}

int v_poplast(vector *v) {
    if (v->size == 0)
        return 0;

    int res = v->data[VLAST(v)];

    v->data[VLAST(v)-1] = 0;
    v->size -= sizeof(int);

    return res;
}

int v_popfirst(vector *v) {
    if (v->size == 0)
        return 0;

    int res = v->data[0];

    v->data[0] = 0;
    memcpy(v->data, &v->data[1], v->size-sizeof(int));
    if (!v->data) {
        errno = V_COPY_FAIL;
        return -1;
    }

    v->size -= sizeof(int);

    return res;
}

void v_shrinktofit(vector *v) {
    if (v->size == v->capacity)
        return;

    int* new_mem = realloc(v->data, v->size);
    if (!new_mem) {
        errno = V_REALLOC_FAIL;
        return;
    }

    v->data = new_mem;
    v->capacity = v->size;
}

unsigned int v_length(vector *v) {
    return v->size/sizeof(int);
}