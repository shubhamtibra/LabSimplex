#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

int eqno,varno,n1,*s,*a,*b,choice,z=0;
double **coff;
double *ob;
double M=10000.00;

int most_negative_find()
{
  int i,j,flag=-1;
  double minneg=0;
  for(i=0;i<varno;i++)
    if(minneg>coff[eqno][i])
      {
        minneg=coff[eqno][i]; flag=i;
      }
  return flag;
}

int pivot_row_find(int col)
{
  int i,j,flag=0;
  double min=1000;

  for(i=0;i<eqno;i++)
  {
  if(coff[i][col]!=0)
    {
      if(min>(coff[i][varno]/coff[i][col]) && (coff[i][varno]/coff[i][col]>0))
        {
          min=(coff[i][varno]/coff[i][col]); flag=i;
        }
    }
  }
  return flag;
}

void modify_non_pivotal(int x,int y)
{ int i,j;
  double piv=coff[x][y];
  for(i=0;i<eqno+1;i++)
    for(j=0;j<varno+1;j++)
      if(i!=x && j!=y)
        coff[i][j]= ((coff[i][j]*piv)-(coff[i][y]*coff[x][j]))/piv;
}

void modify_pivotal(int x,int y)
{ int i,j;
  double piv=coff[x][y];

  coff[x][y]= (1/piv);
  for(i=0;i<eqno+1;i++)
    if(i!=x)
      coff[i][y]/= (-1*piv);

  for(j=0;j<varno+1;j++)
    if(j!=y)
      coff[x][j]/=(piv);
}


void display_matrix()
{
  int i,j;
  for(i=0;i<eqno+1;i++)
    { for(j=0;j<varno+1;j++)
        printf("%.2lf\t",coff[i][j]);
      printf("\n");
    }
}

void read_input()
{
  int i,j;
  printf("Enter number of equations - ");
  scanf("%d",&eqno);
  printf("Enter number of variables - ");
  scanf("%d",&varno);
  n1=varno;
  a=(int*)malloc(eqno*sizeof(int));
  b=(int*)malloc(eqno*sizeof(int));

  printf("Enter the type of inequality for each equation. 1 for =, 2 for <=, 3 for >=\n");
  for(i=0;i<eqno;i++)
    {
      printf("Equation %d - ", i);
      scanf("%d",&a[i]);
    }
  for(i=0;i<eqno;i++)
    {
      if(a[i]==1)
      {} 
      if(a[i]==2)
      {}
      if(a[i]==3)
      {
        ++varno;
        b[i]=varno;
      }
    }
}

void read_coefficients()
{
  int i,j;

  for(i=0;i<eqno;i++)
    {
      printf("Enter the coefficients for equation %d\n",i+1);
      for(j=0;j<n1;j++)
      {
        printf("X%d - ",j+1);
        scanf("%lf",&coff[i][j]);
      }
      printf("\n");
    }
  for(i=0;i<eqno;i++)
    {
      if(a[i]==1||a[i]==2)i++;
      if(a[i]==3)
      {
        coff[i][b[i]-1]=-1;
      }
    }
  for(i=0;i<eqno;i++)
    {
      printf("Enter the 'b' value for equation %d - ",i+1);
      scanf("%lf",&coff[i][varno]);
    }
  printf("\nEnter the coefficient of variables for objective function\n");
  for(i=0;i<n1;i++)
    {
      printf("X%d - ",i+1);
      scanf("%lf",&ob[i]);
    }
  printf("Enter the constant value in objective function - ");
  scanf("%lf",&ob[varno]);
  printf("\nEnter 1 for Maximize, 2 for Minimize\n");
  scanf("%d",&choice);
  printf("\n********************************************\n");

  if(choice==1)
  {
   for(i=0;i<varno;i++)
      ob[i]=-ob[i];
  }
  else if(choice==2)
  {
  ob[varno]=-ob[varno];
  }
  for(j=0;j<varno+1;j++)
    {
      for(i=0;i<eqno;i++)
      {
        if( (a[i]==3) || (a[i]==1) )
          {
            ob[j]= ob[j] - (M*coff[i][j]);
          }
      }
    }
  for(i=0;i<varno+1;i++)
    coff[eqno][i]=ob[i];
}

int main()
{
  int colu,rowe;
  double opt;
  int i,j;

  read_input();
  coff=(double**)malloc((eqno+1)*sizeof(double*));
  for(i=0;i<eqno+1;i++)
    coff[i]=(double*)malloc((varno+1)*sizeof(double));
  for(i=0;i<eqno+1;i++)
    for(j=0;j<varno+1;j++)
      coff[i][j]=0;

  s=(int*)malloc(eqno*sizeof(int));
  for(i=0;i<eqno;i++)
  s[i]=0;
  ob=(double*)malloc((varno+1)*sizeof(double));

  read_coefficients();
  display_matrix();
  int index=1;
  colu=most_negative_find();

   while(colu>=0)
   {
      rowe=pivot_row_find(colu);
      printf("\nPivot element is - %.2lf at Row-%d Column-%d\n",coff[rowe][colu],rowe+1,colu+1);
      printf("\n******************************************\n");
      modify_non_pivotal(rowe,colu);
      modify_pivotal(rowe,colu);
      s[rowe]=colu+1;
      index++;
      display_matrix();
      colu=most_negative_find();
   }
  if(choice==1)
  	opt=coff[eqno][varno];
  if(choice==2)
  	opt=-coff[eqno][varno];
  
  printf("\n*******************************************\n");
  printf("\nOptimal sol is %lf \n",opt);
  printf("\nOptimal Solution found at\n");

  printf("\n**********************************************\n");
  for(i=0;i<eqno;i++)
  {
    if(s[i]>0)
    {
      printf("\nX%d=%lf\t",s[i],coff[i][varno]);
    }
  }

  return 0;
}