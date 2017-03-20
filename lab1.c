#include<stdio.h>
#include<math.h>

int numOfCombinations = 0, numOfBsoln = 0;

void readAugMatrix(float (*A)[101], int m, int n){

    printf("\nEnter the elements of augmented matrix row-wise:\n\n");

    int i, j;
    for(i = 1; i <= m; i++)
        for(j=1; j<=n+1; j++)
        {
            printf("A[%d][%d] : ", i,j);
            scanf("%f",&A[i][j]);
        }
}

void combinationUtil(int arr[], int (*combinations)[100], int data[], int start, int end, int index, int r);

void makeCombination(int arr[], int (*combinations)[100], int n, int r)
{
    int data[r];
    combinationUtil(arr, combinations, data, 0, n-1, 0, r);
}

void combinationUtil(int arr[], int (*combinations)[100], int data[], int start, int end,
                     int index, int r)
{

    if (index == r)
    {
        int j;
        for (j = 0; j<r; j++)
            combinations[numOfCombinations][j] = data[j];
        numOfCombinations++;
        return;
    }
    int i;
    for (i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, combinations, data, i+1, end, index+1, r);
    }
}

void gaussElimination(float (*A)[101], float x[], int n)
{

    int i, j, k;
    float sum = 0.0, c;

    for(j=1; j<=n; j++)
    {
        for(i=1; i<=n; i++)
        {
            if(i>j)
            {
                c = A[i][j]/A[j][j];
                for(k=1; k<=n+1; k++)
                {
                    A[i][k]=A[i][k]-c*A[j][k];
                }
            }
        }
    }
    x[n]=A[n][n+1]/A[n][n];

    for(i=n-1; i>=1; i--)
    {
        sum=0;
        for(j=i+1; j<=n; j++)
        {
            sum = sum + A[i][j]*x[j];
        }
        x[i]=(A[i][n+1]-sum)/A[i][i];
    }
}


int main()
{
    int m, n, combinations[10001][100], columnIndices[100];
    float augMatrix[100][101], bSolutions[100], sqMatrix[100][101], allBSoln[1001][100];

    printf("\nEnter the number of equations (m) and variables (n) respectively: \n");
    scanf("%d%d", &m, &n);

    int i = 0;
    for (i = 0; i < n; i++)
        columnIndices[i] = i + 1;

    readAugMatrix(augMatrix, m, n);

    makeCombination(columnIndices, combinations, n, m);

    printf("The basic solutions of the problem are:\n\n");

    int j, k, l, r, feasible;
    for(i = 0; i < numOfCombinations; i++){
        for(j = 0; j < m; j++){
            for(k = 1; k <= m; k++){
                sqMatrix[k][j+1] = augMatrix[k][combinations[i][j]];
            }
        }
        for (r = 1; r <=m; r++)
        sqMatrix[r][m+1] = augMatrix[r][n+1];

        gaussElimination(sqMatrix, bSolutions, m);

        int temp = 0;
        for(feasible = 1; feasible <= m; feasible++)
            if (!isfinite(bSolutions[feasible])){
                feasible = 0;
                break;
            }
        if(feasible == 0) continue;
        else{
            for(l = 1; l <= n; l++){
            if (l == combinations[i][temp]){
                allBSoln[numOfBsoln][l] = bSolutions[temp+1];
                printf("x_%d = %f, ", l, bSolutions[temp+1]);
                temp++;
            }
            else{
                printf("x_%d = 0.0, ", l);
                allBSoln[numOfBsoln][l] = 0;
            }
        }
        numOfBsoln++;
        printf("\n");
        }

    }

    printf("Total number of basic solutions is %d\n", numOfBsoln);
    return(0);
}
