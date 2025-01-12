def print_matrix(matrix,rows,cols,len_aug) :
    for i in range(0,rows):
        print("|", end="")
        for j in range(0,cols) :
            print(f"  {matrix[i][j] : 9.0f}   " , end = "") if matrix[i][j] == int(matrix[i][j]) else print(f"  {matrix[i][j] : 9.3f}   " , end = "") 
        if len_aug != 0 :
            print("|",end="")
        for j in range(0,len_aug) :
            print(f"  {matrix[i][cols + j] : 9.0f}   " , end = "") if matrix[i][cols + j] == int(matrix[i][cols + j]) else print(f"  {matrix[i][cols + j] : 9.3f}   " , end = "") 
        print("|",end="\n")

def generate_identity(n) :
    matrix_prnt = [[0 for i in range(n)]for j in range(n)]
    for i in range(0,n):
        matrix_prnt[i][i] = 1
    return matrix_prnt

def find_last_occurance(array,target) :
    index = -1
    for i in range (0,len(array)) :
        if array[i] == target :
            index = i
    return index

def RREF(matrix,len_aug,freeTerms) :
    rows = len(matrix)
    cols = len(matrix[0]) - len_aug
    if freeTerms != None :
        freeTerms = [1 for i in range(cols)]
    rowItr = 0
    columnItr = 0
    while rowItr < rows and columnItr < cols :
        if matrix[rowItr][columnItr] == 0 :
            nonZeroItr = rowItr

            while matrix[nonZeroItr][columnItr] == 0 and nonZeroItr < rows - 1:
                nonZeroItr += 1
            if matrix[nonZeroItr][columnItr] != 0 :
                matrix[rowItr], matrix[nonZeroItr] = matrix[nonZeroItr],matrix[rowItr]
            else :
                columnItr += 1
                continue
        
        #elimination process
        for elimItr in range(0,rows) :
            if elimItr == rowItr :
                continue
            factor = -matrix[elimItr][columnItr] / matrix[rowItr][columnItr]
            for i in range(0,cols + len_aug) :
                matrix[elimItr][i] += matrix[rowItr][i] * factor 
        if freeTerms != None :
            freeTerms[columnItr] = 1       
        rowItr += 1
        columnItr += 1
    min_length = min(cols,rows)
    #making main diagonal elements equal 1
    for i in range (0,min_length) :
        for j in range(0,cols) :
            if matrix[i][j] != 0 :
                for k in range(0,len_aug) : 
                    matrix[i][cols + k] /= matrix[i][j]
                matrix[i][j] = 1
                break

def REF(matrix,len_aug,freeTerms) :
    rows = len(matrix)
    cols = len(matrix[0]) - len_aug
    if freeTerms != None :
        freeTerms = [1 for i in range(0,cols)]
    rowItr = 0
    columnItr = 0
    while rowItr < rows and columnItr < cols :
        if matrix[rowItr][columnItr] == 0 :
            nonZeroItr = rowItr

            while matrix[nonZeroItr][columnItr] == 0 and nonZeroItr < rows - 1:
                nonZeroItr += 1
            if matrix[nonZeroItr][columnItr] != 0 :
                matrix[rowItr], matrix[nonZeroItr] = matrix[nonZeroItr],matrix[rowItr]
            else :
                columnItr += 1
                continue
        
        #elimination process
        for elimItr in range(rowItr + 1,rows) :
            factor = -matrix[elimItr][columnItr] / matrix[rowItr][columnItr]
            for i in range(0,cols + len_aug) :
                matrix[elimItr][i] += matrix[rowItr][i] * factor 
        
        if freeTerms != None :
            freeTerms[columnItr] = 1        
        rowItr += 1
        columnItr += 1






matrix = [[1,2,3,4,5],[2.1,3.0,4.0,5.2,6.2]]
freeTerms = []
RREF(matrix,1,freeTerms)
print_matrix(matrix,2,4,1)
print(freeTerms)

