#include <stdio.h>
#include <stdlib.h>
#include "linear_alg.h"


int main() {
    // use this for user input matrix
    int size,len_aug;
    puts("Please enter the size (n) for nxn matrix");
    scanf("%d", &size);
    len_aug = size;


    float** array = input_matrix(size, size);

    //You can swap the code between startpoint and endpoint by the following line
    // float** inverse = mat_inverse(array,size);

    //start point
    float** identity = generate_identity_f(3);
    combine_matrices(array,size,identity,size,size);

    int freeTerms[size];
    int countFreeTerms = 0;

    
    RREF(array,size,size, len_aug,freeTerms);
    for (int i = 0; i < size; i++) countFreeTerms += freeTerms[i];
    if (countFreeTerms != 0) return 0;

    printf("\nThe Inverse Matrix :\n") ;  //printing matrix

    // //elimination finished
    float** inverse = create_dyn_matrix(size,size);

    for(int curr_aug = 0; curr_aug < len_aug; curr_aug++){

        for (int resultItr = 0 ; resultItr < size ; resultItr++) {
                float answer = (float)array[resultItr][size + curr_aug]/array[resultItr][resultItr];
                inverse[resultItr][curr_aug] = answer;   
        }
        printf("\n");
    }
    //end point

    print_matrix_f(inverse,size,size,0);
    free_matrix_f(inverse,size,size);
    free_matrix_f(identity,size,size);
    free_matrix_f(array,size,size + len_aug);
    return 0;  
    
}
