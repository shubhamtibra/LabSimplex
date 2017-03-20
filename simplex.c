#include<stdio.h>

// global variables used throughout the code
int iChangeX[1000], iChangeZ[1000];
float revisedMatrix[100][100];

// returns the index of the element with minimum value
int Min(float tempArray[],int n)
{
  float min = 1000.0;
  int i, pivotC = 0;

  for(i = 0; i < n; i++)
      if(tempArray[i] < min)
	{
	  min = tempArray[i];
	  pivotC = i;
	}

 return pivotC;
}

// Simplex Tableau
float Tableau(int m, int n, float augMatrix[][(n+1)])
{
   float maximumV;
   float minRat[m];
   float maximumS[n];

   int i, j, pivotR, pivotC;
   int fRow = 0;
   int fCol = 0;

   for(i = 0; i < n; i++)
	  maximumS[i] = augMatrix[m][i];

   for(i = 0; i < n; i++)
       if(augMatrix[m][i] < 0) fRow = 1;

   if(fRow == 0)
    {
      maximumV = augMatrix[m][n];
      printf("The optimum maximum value is: %f\n", maximumV);
      return maximumV;
    }

   pivotC = Min(maximumS, n);

   for(i = 0; i < m; i++)
    {
      if(augMatrix[i][pivotC] > 0)
	{
      minRat[i] = augMatrix[i][n]/augMatrix[i][pivotC];
      fCol = 1;
	}
    else minRat[i] = 1000;
    }

   if(fCol == 0)
     {
       printf("The LPP is unbounded.\n");
       return 0 ;
     }

   pivotR = Min(minRat, m);

   if(augMatrix[pivotR][pivotC] == 0)
     {
       printf("The solution is incorrect.\n");
       return 0;
     }

   revisedMatrix[pivotR][pivotC] = 1/augMatrix[pivotR][pivotC];

   for(i = 0; i < n + 1; i++) // transforming the pivot row
       if(i != pivotC)
	 revisedMatrix[pivotR][i] = augMatrix[pivotR][i] * revisedMatrix[pivotR][pivotC];

   for(i = 0; i < m + 1; i++) // transforming the pivot col
     {
       if(i != pivotR)
          revisedMatrix[i][pivotC] = -augMatrix[i][pivotC]*revisedMatrix[pivotR][pivotC];
     }

   for(i = 0; i < m+1; i++)//transforming other elements
    {
       if(i == pivotR)
	      continue;
       for(j = 0; j < n+1; j++)
        {
	   if(j == pivotC)
	     continue;
	   revisedMatrix[i][j] = ((augMatrix[i][j]*augMatrix[pivotR][pivotC])-(augMatrix[i][pivotC]*augMatrix[pivotR][j]))/augMatrix[pivotR][pivotC];
        }
     }

   iChangeX[pivotR] = pivotC;
   iChangeZ[pivotC] = pivotR;

   float temp[m+1][n+1];

   for(i = 0; i < m+1; i++)
       for(j = 0; j < n+1; j++)
         temp[i][j] = revisedMatrix[i][j];

   maximumV = Tableau(m, n, temp);

   return maximumV;
}

int main()
{
   float maximumV;
   int m, n, i, j;

   printf("Please give the number of constraints:\n");
   scanf("%d", &m);

   printf("Please give the number of variables:\n");
   scanf("%d", &n);

   float augMatrix[m+1][n+1];
   float maximumS[n+1];
   float minRat[m];

   printf("Enter the Augmented Matrix:\n");
   for(i = 0; i < m; i++)
    {
    for(j = 0; j < n+1; j++)
    {
        printf("Enter a[%d][%d]: ", i, j);
        scanf("%f", &augMatrix[i][j]);
    }
    iChangeX[i] = -1;
    iChangeZ[i] = -1;
    }

   printf("Enter coefficients of the objective functions:\n");
   for(i = 0; i < n+1; i++)
    {
      if(i != n)
        {
        scanf("%f", &maximumS[i]);
        maximumS[i] = -maximumS[i];
       	}
	  else scanf("%f", &maximumS[i]);
	  augMatrix[m][i] = maximumS[i];
    }

   maximumV = Tableau(m, n, augMatrix);

   printf("The optimal solution is as follows:\n");
   for(i = 0; i < m; i++)
    {
      if(iChangeX[i] == -1) printf("z_%d = %f, ",i + 1, revisedMatrix[i][n]);
      else printf("x_%d = %f, ", iChangeX[i] + 1, revisedMatrix[i][n]);
    }

   for(i=0;i<n;i++)
    {
      if(iChangeZ[i] == -1) printf("x_%d = 0, ", i+1);
	  else printf("z_%d = 0, ", iChangeZ[i] + 1);
    }
}
