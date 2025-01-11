#define float_equals(a,b) ( ( (a) < (b) + 1e-5)  &&  ( (a) > (b) - 1e-5) )
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//ESSENTIALS
void swap_arrays(float* arr1, float* arr2 , int length){
    for (int i = 0; i < length; i++)
    {
        float temp = arr1[i];
        arr1[i] = arr2[i];
        arr2[i] = temp;
    }
    
}

float** generate_identity_f(int n){
    float** identity = (float**)malloc(n*sizeof(float*));
    for (int i = 0; i < n; i++)
    {
        identity[i] = (float*)calloc(n,sizeof(float));
    }
    for (int i = 0; i < n; i++)identity[i][i] = 1;
    return identity;
}

int** generate_identity_i(int n){
    int** identity = (int**)malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        identity[i] = (int*)calloc(n,sizeof(int));
    }
    for (int i = 0; i < n; i++)identity[i][i] = 1;
    return identity;
}

void free_matrix_f(float** matrix , int rows, int cols){
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
    matrix = NULL;
}

void free_matrix_i(int** matrix , int rows, int cols){
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
    matrix = NULL;
}

//matrix IO
float** input_matrix(int rows, int columns){

    float** array = (float**)malloc(rows * sizeof(float*));
    for (int i = 0; i < rows; i++)
    {
        array[i] = (float*)malloc((columns) *sizeof(float));
    }
    
    printf("Enter The Elements Of The Matrix\n");
    for (int rowFill = 0 ; rowFill < rows ; rowFill++) {
        printf("Enter Elements of Row%d Seperated by a space\n",rowFill + 1);
        for (int colFill = 0; colFill < columns; colFill++)
        {
            float c;
            scanf("%f", &c);
            array[rowFill][colFill] = c;
        } 
    }
    return array;

}

float** input_matrix_equations(int n){
    float** array = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++)
    {
        array[i] = (float*)malloc((n+1) *sizeof(float));
    }
    
    printf("for aX + bY + cZ ... = d\nEnter The Coefficients for every equation\n");
    for (int rowFill = 0 ; rowFill < n ; rowFill++) {
        printf("Enter Coefficients of Row%d Seperated by a space\n",rowFill + 1);
        for (int colFill = 0; colFill <= n; colFill++)
        {
            float c;
            scanf("%f", &c);
            array[rowFill][colFill] = c;
        } 
    }
    return array;

}


void print_matrix_f(float** matrix, int rows,int cols, int len_aug){

    for (int i = 0; i < rows; i++){ //Printing The RREF
        printf("|");
        for (int j = 0; j < cols ; j++){
            (float_equals(matrix[i][j] , ((int)matrix[i][j]) ))?printf("%9d  ",(int)matrix[i][j]):printf("%9.3f  ",matrix[i][j]);
        }
        if(len_aug != 0){
            printf("|");
            for(int j = cols; j < cols + len_aug; j++) 
                (float_equals(matrix[i][j] , ((int)matrix[i][j]) ))?printf("%9d  ",(int)matrix[i][j]):printf("%9.3f  ",matrix[i][j]);
        }
        printf("|\n");
    }
}

void print_matrix_i(int** matrix, int rows,int cols, int len_aug){

    for (int i = 0; i < rows; i++){ //Printing The RREF
        printf("|");
        for (int j = 0; j < cols + len_aug ; j++){
            printf("%9d  ",matrix[i][j]);
        }
        if(len_aug != 0){
            printf("|");
            for(int j = 0; j < len_aug; j++) 
                printf("%9d  ",matrix[i][j]);
        }
        printf("|\n");
    }
}

//Operations
void RREF(float** array, int rows, int columns, int len_aug, int*freeTerms){

    if(freeTerms != NULL)
    for(int i = 0; i < rows; i++) freeTerms[i]  = 0;
    
    int rowItr= 0 ; int columnItr = 0;

    while(rowItr < rows  && columnItr < columns) {
        if (array[rowItr][columnItr] == 0) { 
            //Swapping two rows to put the pivot in place and the 2nd condition checks if it's the last element so it skips to not swap with sth outside of the array
            int nonZeroItr = rowItr;
            while (array[nonZeroItr][columnItr] == 0 && nonZeroItr != rows - 1){
                 nonZeroItr++;
            }
            //Swap Two Rows
            if (!float_equals(array[nonZeroItr][columnItr],0)) {
                swap_arrays(array[rowItr], array[nonZeroItr], columns + len_aug);
            } 
            else {
                if(freeTerms != NULL)freeTerms[columnItr] = 1; 
                columnItr++; //i will only proceed if there is no zero to not divide by zero
                continue;
            }
        }
        
        //Now lets eliminate using this pivot to get RREF
        for (int elimItr = 0; elimItr < rows ; elimItr++){
            // if (array[rowItr][columnItr] == 0) {freeTerms[columnItr] = 1; break;};
            if (elimItr == rowItr) continue;

            float b = array[elimItr][columnItr];
            float a = array[rowItr][columnItr];
            float factor = -b/a ;
            for (int i = 0; i < columns + len_aug; i++)
            {
                array[elimItr][i] += array[rowItr][i] * factor;
            }
        }
    rowItr++;
    columnItr++;//it means that it was a successful elimination procoess so i increment both
    }

    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if(!float_equals(array[i][j],0)){ // i have met a pivot
                for(int k = 0; k < len_aug;k++) array[i][columns + k] /= array[i][j];
                array[i][j] = 1;
                break;
            }
        }
        
        
    }
    
}

void REF(float** array, int rows, int columns, int len_aug, int*freeTerms){

    if(freeTerms != NULL)
    for(int i = 0; i < rows; i++) freeTerms[i]  = 0;
    
    int rowItr= 0 ; int columnItr = 0;

    while(rowItr < rows  && columnItr < columns) {
        if (array[rowItr][columnItr] == 0) { 
            //Swapping two rows to put the pivot in place and the 2nd condition checks if it's the last element so it skips to not swap with sth outside of the array
            int nonZeroItr = rowItr;
            while (array[nonZeroItr][columnItr] == 0 && nonZeroItr != rows - 1){
                 nonZeroItr++;
            }
            //Swap Two Rows
            if (!float_equals(array[nonZeroItr][columnItr],0)) {
                swap_arrays(array[rowItr], array[nonZeroItr], columns);
            } 
            else {
                if(freeTerms != NULL)freeTerms[columnItr] = 1; 
                columnItr++; //i will only proceed if there is no zero to not divide by zero
                continue;
            }
        }
        
        //Now lets eliminate using this pivot to get RREF
        for (int elimItr = rowItr + 1; elimItr < rows ; elimItr++){

            float b = array[elimItr][columnItr];
            float a = array[rowItr][columnItr];
            float factor = -b/a ;
            for (int i = 0; i < columns + len_aug; i++)
            {
                array[elimItr][i] += array[rowItr][i] * factor;
            }
        }
    rowItr++;
    columnItr++;//it means that it was a successful elimination procoess so i increment both
    }
}

int type_of_sol(float**array, int rows,int cols,int index_of_aug){
    //returns 0 if unique , number of free terms if infinite or -1 if inconsistent
    int freeTermTracker = cols; //keeping track of pivots
    for (int i = 0; i < rows; i++)
    {
        bool is_unique = 0;
        for (int j = 0; j < cols; j++)
        {
            if (!float_equals(array[i][j],0)) { is_unique = true; break;}
            
        }
        if(is_unique) {
            freeTermTracker--;//i decrement for each time i meet a pivot
            continue;
        }
        else if(!float_equals(array[i][cols + index_of_aug - 1],0)) return -1;//inconsistent
    }
    return freeTermTracker;
    
}

float** combine_matrices(float** matrix1, int cols1, float** matrix2, int cols2, int rows){

    float* temp;
    float** new_matrix;
    for (int i = 0; i < rows; i++)
    {
        temp = (float*)realloc(matrix1[i], (cols1 + cols2) * sizeof(float));
        if(temp == NULL){
            perror("error allocating memory while combining");
            free_matrix_f(matrix1,rows,cols1);
            free_matrix_f(matrix2,rows,cols2);
            exit(1);
        }
        matrix1[i] = temp;
        temp = NULL;
        for (int j = cols1; j < cols1 + cols2; j++)
        {
            matrix1[i][j] = matrix2[i][j - cols1];
        }
    }
    free_matrix_f(matrix2,rows,cols2);
    new_matrix = matrix1;
    matrix1 = NULL;

    return new_matrix;
    
}

// float** get