/*
 *  This program solves Type 1 LPP problems using Simplex Method.
 */
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>

using namespace std;

//-----------------------------------------------------------------
//           Initialising some parameters             
//-----------------------------------------------------------------
float d[10]={0};
float mat[10][10], b[10], temp[10][10], constants[10];
float ans[10][10], z[10];
int R, C;
int rank1, rank2, i, j, k, in_var, var, eqn;
int countVal=0,countVal1=0, slackVar = 0;
bool unbounded = false;
bool infinite = false;
int table_no = 1;

//-----------------------------------------------------------------
//           Function to read inputs from user and 
//           parse the equations to store data in 
//           appropriate matrices           
//-----------------------------------------------------------------
void parse(){
    string inequality;  
    printf("Enter the number of variables\n");
    scanf("%d",&var);
    
    printf("Enter number of equations\n");
    scanf("%d",&eqn);

    for(i = 0 ; i < eqn ; i++)
    {
        printf("Enter coefficients, inequation sign and constant term of equation no %d seperated by spaces:\n" , i + 1);
        for(j = 0 ; j < var ; j++)
        {
            scanf("%f",&mat[i][j]);
        }
        cin >> inequality;
        if (inequality.at(0) == '<')
        {
             slackVar++;
             scanf("%f", &mat[i][j]);
        }
    }
    cout <<"Enter the coefficients of the " << var;
    cout <<" variables in the objective function Z in order followed by the constant d" << endl;
    for(int j = 0; j <= var ; j++){
          scanf("%f", &mat[eqn][j]);
          if(j != var)
               mat[eqn][j] = (-1)*mat[eqn][j];
    }
}

//-----------------------------------------------------------------
//       Function to find the minimum element in the last row          
//-----------------------------------------------------------------
int getMinFromLastRow(){
    int ind = -1;
    float currMin = 0;
    for(int i = 0 ; i < var ; i++){
          if(mat[eqn][i] > 0)
               continue;  
          if(mat[eqn][i] == 0){
               infinite = true;
               return -1;
          }           
          if(mat[eqn][i] < currMin){
               currMin = mat[eqn][i];
               ind = i;     
         }
    }
    return ind;            
}

//-----------------------------------------------------------------
//           Function to find the row which has the minimum 
//           positive ratio between b(i) and a(i,u)            
//-----------------------------------------------------------------
int getPivotRow(int pivotCol){
     int ind = -1; 
     float currMin = 100000;
     for(int i = 0 ; i < eqn; i++){
          if(mat[i][pivotCol] <= 0)
               continue;
          if((mat[i][var]/mat[i][pivotCol]) < currMin){
               ind = i;
               currMin = (mat[i][var]/mat[i][pivotCol]);               
          }
     }
     return ind;        
}

//-----------------------------------------------------------------
//               Utility Function to copy matrices
//-----------------------------------------------------------------
void makeNewTableau(){

  cout << "======================================================" <<endl;
  cout << "Table " <<::table_no++ << endl << endl;
  for(int i = 0 ; i <=eqn ; i++){
    for(int j = 0 ; j <= var; j++){
        mat[i][j] = temp[i][j];
        cout << mat[i][j] << "\t";
    }     
    cout << endl;
  }
  cout << "======================================================" <<endl;   
}


//-----------------------------------------------------------------
//     Framework to update simplex tableau and find the optimum            
//-----------------------------------------------------------------

void find_optimum(){  
  cout << "======================================================" <<endl;
  cout << " Initial Simplex Table " << endl << endl;
     for(int i = 0 ; i <= eqn ; i++){
          for(int j = 0 ; j <= var; j++){
               cout << mat[i][j] << "\t";
           }
           cout << endl; 
     }          
  cout << "======================================================" <<endl;


     int pivotRow, pivotCol;
     while((pivotCol = getMinFromLastRow()) != -1){
          if((pivotRow = getPivotRow(pivotCol)) == -1){
               unbounded = true;
               return;
          }
          for(int i = 0 ; i <= eqn ; i++){
               for(int j = 0 ; j <= var; j++){
                    if(i == pivotRow && j == pivotCol)
                         temp[i][j] = 1/mat[i][j];
                    else if(i == pivotRow)     
                         temp[i][j] = (mat[i][j])/mat[pivotRow][pivotCol];          
                    else if(j == pivotCol)
                         temp[i][j] = ((-1)*mat[i][j])/mat[pivotRow][pivotCol];
                    else{
                        temp[i][j] = ((mat[pivotRow][pivotCol]*mat[i][j]) - (mat[pivotRow][j]*mat[i][pivotCol]))/mat[pivotRow][pivotCol]; 
                    }
               }
          }
          makeNewTableau();
     }
}


//-----------------------------------------------------------------
//           Main body of the program            
//-----------------------------------------------------------------
int main(){
    parse();   
    find_optimum();

    cout <<"======================================================" <<endl;
    if(infinite)
        printf("There are infinitely many solutions\n");          
    else if(unbounded)
        printf("The problem is unbounded\n");
    else          
        printf("The Maximum value of Z is %f \n", mat[eqn][var]); 

    cout <<"======================================================" <<endl; 
    return 0;
}

