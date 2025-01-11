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

    printf("The Diagonal Matrix \n\n") ;  //printing matrix
    print_matrix_f(array,rows,columns,len_aug);
    printf("\n");

    // //elimination finished
    for(int curr_aug = 0; curr_aug < len_aug; curr_aug++){

        printf("Set %d Answers \n", curr_aug + 1);
        int type = type_of_sol(array,rows,columns,curr_aug + 1);
        bool is_unique;
        switch(type){
            case -1 :
                puts("The System Is Inconsistent (Has No Solution)\n");
                is_unique = false;
                break;
            case 0:
                is_unique = true;
                break;
            default:
                printf("The System Has Infinite Number Of Solutions!! (%d Free Variables )\nFree Terms Are : ", type);
                for (int freeTermCheckItr = 0 ; freeTermCheckItr < columns ; freeTermCheckItr++){

                    if (freeTerms[freeTermCheckItr] == 1)  printf("X%d ",freeTermCheckItr + 1);
                }
                printf("\n");
                is_unique = false;
                break;
        }
        
        //print the answers (if unique)
        if(!is_unique) continue;

        for (int resultItr = 0 ; resultItr < columns ; resultItr++) {
                float answer = (float)array[resultItr][columns + curr_aug]/array[resultItr][resultItr];
                float_equals(answer , ((int)answer) )?printf("X%d = %d\n",resultItr + 1, (int)answer):printf("X%d = %f\n",resultItr + 1, answer);   
        }
        printf("\n");
    }
    free_matrix_f(array,rows,columns+len_aug);
    return 0;  
    
}
