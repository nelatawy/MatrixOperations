#ifndef LINEAR_ALG_H
#define LINEAR_ALG_H
#include "linear_alg.c"

// LINEAR_ALG_H

//ESSENTIALS
void swap_arrays(float* arr1, float* arr2 , int length);

float** generate_identity_f(int n);

float** create_dyn_matrix(int rows,int cols);

int** generate_identity_i(int n);

void free_matrix_f(float** matrix , int rows, int cols);

void free_matrix_i(int** matrix , int rows, int cols);

float** copy_matrix(float** matrix1, int rows,int cols);
//matrix IO
float** input_matrix(int rows, int columns);

float** input_matrix_equations(int n);


void print_matrix_f(float** matrix, int rows,int cols, int len_aug);

void print_matrix_i(int** matrix, int rows,int cols, int len_aug);

//Operations
void RREF(float** array, int rows, int columns, int len_aug, int*freeTerms);

void REF(float** array, int rows, int columns, int len_aug, int*freeTerms);

int type_of_sol(float**array, int rows,int cols,int index_of_aug);

void combine_matrices(float** matrix1, int cols1, float** matrix2, int cols2, int rows);

float** mat_inverse(float** matrix, int size);

#endif 