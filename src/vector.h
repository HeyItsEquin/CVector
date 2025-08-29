#pragma once

#include <stdlib.h>

typedef struct {
    size_t size;
    size_t capacity;

    int* data;
} vector;

vector* v_new();

void v_pushback(vector *v, int val);
void v_push(vector *v, int val);
int v_poplast(vector *v);
int v_popfirst(vector *v);
void v_shrinktofit(vector *v);

unsigned int v_length(vector *v);