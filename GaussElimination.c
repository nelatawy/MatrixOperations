#include <stdio.h>
#define float_equals(a,b) ( ( (a) < (b) + 1e-6)  &&  ( (a) > (b) - 1e-6) )



int main() {
    // use this for user input matrix
    int n;
    printf("Enter The Number Of Unkouwns : ");
    scanf("%d", &n);
    float array[n][n+1];
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
    // float array [n][n + 1] = {{1,3,4,6},{2,3,6,3},{5,3,2,2}}; // use this for code defined matrix
    int length = sizeof(array[0])/sizeof(array[0][0]) - 1;// the minus one is because last elements is from the augmented matrix
    int freeTerms[length];
    for (int i = 0; i < length; i++) freeTerms[i]  = 0;
    
    int rowItr= 0 ; int columnItr = 0;
    while(rowItr < length  && columnItr < length) {
        if (array[rowItr][columnItr] == 0 && rowItr < length - 1) { 
            //Swapping two rows to put the pivot in place and the 2nd condition checks if it's the last element so it skips to not swap with sth outside of the array
            int nonZeroItr = rowItr + 1;

            while (array[nonZeroItr][columnItr] == 0 ){
                if (nonZeroItr == length - 1) {
                    break;
                }
                 nonZeroItr++;
            }
            //Swap Two Rows
            if (!float_equals(array[nonZeroItr][columnItr],0)) {
                // it's not a simple comparison because float 0 isn't equal to exactly 0
                int newPivotRowIndex = nonZeroItr;
                float arrayTemp [length] ;

                for (int itr1 = 0 ; itr1 <= length ; itr1++) {
                    arrayTemp[itr1] = array[rowItr][itr1];
                }

                for (int itr2 = 0 ; itr2 <= length ; itr2++) {
                    array[rowItr][itr2] = array[newPivotRowIndex][itr2];
                }

                for (int itr3 = 0 ; itr3 <= length ; itr3++) {
                    array[newPivotRowIndex][itr3] = arrayTemp[itr3];
                }
            } 
            else {
                freeTerms[columnItr] = 1; //adds the free terms while i'm working
                columnItr++; //i will only proceed if there is no zero to not divide by zero
                continue;
            }
        }
        //Now lets eliminate using this pivot to get RREF
        for (int elimItr = 0; elimItr < length ; elimItr++){
            if (array[rowItr][columnItr] == 0) break;
            if (elimItr == rowItr) continue;

            float b = array[elimItr][columnItr];
            float a = array[rowItr][columnItr];
            float factor = -b/a ;
            for (int i = 0; i <= length; i++)
            {
                array[elimItr][i] += array[rowItr][i] * factor;
            }
        }
    rowItr++;
    columnItr++;//it means that it was a successful elimination procoess so i increment both
    }

    printf("The Diagonal Matrix : \n\n")  ;  
    for (int i = 0; i < length; i++){ //Printing The RREF
        printf("|");
        for (int j = 0; j <= length ; j++){
            (float_equals(array[i][j] , ((int)array[i][j]) ))?printf("%9d  ",(int)array[i][j]):printf("%9.3f  ",array[i][j]);
        }
        printf("|\n");
    }
    printf("\n");

    //elimination finished
    //Check for inconsistency and infinite number of solutions
    if (float_equals(array[length - 1][length - 1],0)) {
        if (float_equals(array[length-1][length],0)) {
            printf("The System Has Infinite Number Of Solutions!!\nFree Terms Are : ");
            for (int freeTermCheckItr = 0 ; freeTermCheckItr < length ; freeTermCheckItr++){

                if (freeTerms[freeTermCheckItr] == 1)  printf("X%d ",freeTermCheckItr + 1);
            }
            printf("\n");
            return 0;
        }
        else{
            printf("The System Is Inconsistent (Has No Solution)\n");
            return 0;
        }
    }
    //print the answers (if unique)
    for (int resultItr = 0 ; resultItr < length ; resultItr++) {
            float answer = (float)array[resultItr][length]/array[resultItr][resultItr];
            float_equals(answer , ((int)answer) )?printf("X%d = %d\n",resultItr + 1, (int)answer):printf("X%d = %f\n",resultItr + 1, answer);;    
    }

 return 0;  
    
}