#include<stdio.h>

int foo;
float new_enquiry[100][100];
int replace[1000];
int replace2[1000];

int least_value(float list[],int n)
{
    int i,column_pivot;
    float min=1000.0;
    for(i=0; i<n; i++)
    {
        if(list[i]<min)
        {
            min=list[i];
            column_pivot=i;
        }
    }
    return column_pivot;
}
float simplex_tableau(int m,int n,float enquiry[][(n+1)])
{
    foo++;

    int i,j,row_pivot,column_pivot;
    int row_foo=0;
    int col_foo=0;
    int infin=0;

    float value_max;
    float ratio_test[m];
    float greatest[n];

    for(i=0; i<n; i++)
    {
        greatest[i]=enquiry[m][i];
    }
    for(i=0; i<n; i++) //for checking the 1st stop criteria
    {
        if(enquiry[m][i]<0)
        {
            row_foo=1;
        }

    }
    if(row_foo==0)
    {
        value_max=enquiry[m][n];
        printf("Greatest value is: %f\n",value_max);
        return value_max;

    }
    column_pivot =least_value(greatest,n);

    for(i=0; i<m; i++)
    {
        if(enquiry[i][column_pivot]>0)
        {
            ratio_test[i]=enquiry[i][n]/enquiry[i][column_pivot];

            col_foo=1;
        }
        else
            ratio_test[i]=1000;
    }
    if(col_foo==0)
    {
        printf("The solutions are unbounded\n");
        return -1000 ;
    }
    row_pivot=least_value(ratio_test,m);

    if(enquiry[row_pivot][column_pivot]==0)
    {
        printf("Incorrect solution.\n");
        return 0;
    }
    new_enquiry[row_pivot][column_pivot]=1/enquiry[row_pivot][column_pivot];

    for(i=0; i<n+1; i++) // transforming the pivot row
    {
        if(i!=column_pivot)
            new_enquiry[row_pivot][i]=enquiry[row_pivot][i]*new_enquiry[row_pivot][column_pivot];
    }
    for(i=0; i<m+1; i++) // transforming the pivot col
    {
        if(i!=row_pivot)
            new_enquiry[i][column_pivot]=-enquiry[i][column_pivot]*new_enquiry[row_pivot][column_pivot];
    }
    for(i=0; i<m+1; i++) //transforming other elements
    {
        if(i==row_pivot)
            continue;
        for(j=0; j<n+1; j++)
        {
            if(j==column_pivot)
                continue;
            new_enquiry[i][j]=((enquiry[i][j]*enquiry[row_pivot][column_pivot])-(enquiry[i][column_pivot]*enquiry[row_pivot][j]))/enquiry[row_pivot][column_pivot];
        }

    }
    replace[row_pivot]=column_pivot;
    replace2[column_pivot]=row_pivot;
    printf("Z%d ==> X (entering variable)%d\n",row_pivot+1,column_pivot+1);
    printf("X%d ==> Z (leaving variable) %d\n",column_pivot+1,row_pivot+1);
    float temp[m+1][n+1];
    printf("Tableau:%d\n",foo);
    for(i=0; i<m+1; i++)
    {
        for(j=0; j<n+1; j++)
        {
            temp[i][j]=new_enquiry[i][j];
            printf("%f ",temp[i][j]);
        }
        printf("\n");
    }
    printf("********************************************\n");
    value_max=simplex_tableau(m,n,temp);

    return value_max;
}


int main()
{
    int m,n,i,j;
    printf("Give the no. of constraints:\n");
    scanf("%d",&m);
    printf("Give the no. of variables:\n");
    scanf("%d",&n);
    float enquiry[m+1][n+1];
    float cof[n+1];
    int ar_var[m];
    float ph_1;
    printf("Specify the constraints:\n");
    for(i=0; i<m; i++)
    {
        printf("Specify whether it is <=, >= or = by entering 1, 2 or 3 respectively:\n");
        scanf("%d",&ar_var[i]);
        for(j=0; j<n+1; j++)
        {
            scanf("%f",&enquiry[i][j]);
        }
        replace[i]=-1;
    }
    printf("Give the objective function coefficients:\n");
    for(i=0; i<n+1; i++)
    {
        scanf("%f",&cof[i]);
        enquiry[m][i]=0;
    }
    for(i=0; i<n; i++)
        replace2[i]=-1;
    for(i=0; i<m; i++)
    {
        if(ar_var[i]==2 || ar_var[i]==3)
        {
            for(j=0; j<n+1; j++)
            {
                enquiry[m][j]=enquiry[m][j]+enquiry[i][j];
            }

        }
    }
    for(i=0; i<n+1; i++)
    {
        enquiry[m][i]=-enquiry[m][i];
    }
    printf("First Tableau:\n");
    for(i=0; i<m+1; i++)
    {
        for(j=0; j<n+1; j++)
            printf("%f ,",enquiry[i][j]);
        printf("\n");
    }
    ph_1=simplex_tableau(m,n,enquiry);
    
    if(ph_1==-1000)
        return 0;
    if(ph_1==0)
    {
        for(i=0; i<m; i++)
        {
            if(ar_var[i]==2 || ar_var[i]==3)
            {
                if(replace[i]==-1)
                {

                    printf("Can't continue to Phase-II because of %d \n ",i);
                    return 0;
                }
            }
        }
    }
    printf("Phase-II is starting: \n");
    int repc_store[m];
    int repc_altstore[n];

    int count_col=0;
    int x_var[n];
    int y_var[m];
    j=0;
    for(i=0; i<n; i++)
    {
        if(replace2[i]==-1)
        {
            count_col++;
            x_var[j]=i;
            j++;
        }

    }
    x_var[j]=n;
    for(i=0; i<m; i++)
    {
        if(replace[i]==-1)
        {
            y_var[i]=i;
        }
        else
            y_var[i]=replace[i];
    }
    float inq_new[m+1][count_col+1];
    int col_c=0;
    for(i=0; i<n; i++)
    {
        if(replace2[i]==-1)
        {
            for(j=0; j<m; j++)
            {
                inq_new[j][col_c]=new_enquiry[j][i];
            }
            col_c++;
        }

    }
    for(i=0; i<m; i++)
        inq_new[i][count_col]=new_enquiry[i][n];

    for(i=0; i<count_col+1; i++)
        inq_new[m][i]=-cof[x_var[i]];
    // inq_new[m][count_col]=cof[n];
    for(i=0; i<m; i++)
    {
        if(replace[i]!=-1)
        {
            for(j=0; j<count_col+1; j++)
            {

                inq_new[m][j]=inq_new[m][j]+inq_new[i][j]*cof[y_var[i]];
            }
        }
    }
    foo=0;
    printf("First Tableau of Phase-II\n");
    for(i=0; i<m+1; i++)
    {
        for(j=0; j<count_col+1; j++)
            printf("%f ,",inq_new[i][j]);
        printf("\n");
    }
    for(i=0; i<m; i++)
    {
        repc_store[i]=replace[i];
        replace[i]=-1;
    }
    for(j=0; j<n; j++)
    {
        repc_altstore[j]=replace2[j];
        replace2[j]=-1;
    }
    float ph_2=simplex_tableau(m,count_col,inq_new);

    for(i=0; i<m; i++)
    {
        if(replace[i]==-1)
        {
            //  printf("z_%d = %f, ",i+1,new_enquiry[i][n]);
            if(repc_store[i]!=-1)
            {
                printf("x%d = %f, ",y_var[i]+1,new_enquiry[i][count_col]);
            }

        }
        else
        {
            printf("x%d = %f, ",x_var[replace[i]]+1,new_enquiry[i][count_col]);
        }
    }

}
