#include <stdio.h>
#include <stdlib.h>
#include "linear_alg.h"


int main() {
    // use this for user input matrix
    int rows,columns,len_aug;
    puts("Please enter the number of equations");
    scanf("%d", &rows);
    puts("Please enter the number of unknowns");
    scanf("%d", &columns);
    puts("please enter the number of augmented columns");
    scanf("%d", &len_aug);


    float** array = input_matrix(rows, columns + len_aug);
    int freeTerms[columns];

    RREF(array,rows,columns, len_aug,freeTerms);


    printf("The Diagonal Matrix : \n\n") ;  //printing matrix
    print_matrix_f(array,rows,columns,len_aug);
    printf("\n");

    // //elimination finished
    int type = type_of_sol(array,rows,columns,1);
    switch(type){
        case -1 :
            puts("The System Is Inconsistent (Has No Solution)");
            return 0;
        case 0:
            break;
        default:
            printf("The System Has Infinite Number Of Solutions!! (%d Free Variables )\nFree Terms Are : ", type);
            for (int freeTermCheckItr = 0 ; freeTermCheckItr < columns ; freeTermCheckItr++){

                if (freeTerms[freeTermCheckItr] == 1)  printf("X%d ",freeTermCheckItr + 1);
            }
            return 0;
    }
    
    //print the answers (if unique)
    int aug_index = len_aug;
    for (int resultItr = 0 ; resultItr < columns ; resultItr++) {
            float answer = (float)array[resultItr][columns + aug_index - 1]/array[resultItr][resultItr];
            float_equals(answer , ((int)answer) )?printf("X%d = %d\n",resultItr + 1, (int)answer):printf("X%d = %f\n",resultItr + 1, answer);;    
    }
    
    free_matrix_f(array,rows,columns+len_aug);
    return 0;  
    
}
