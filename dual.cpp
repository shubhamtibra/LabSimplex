
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
#include <cmath>

#define rep(i, n) for(int i = 0; i < (n); ++i)
using namespace std;

float d[10]={0};
float mat[10][10], b[10], temp[10][10], constants[10];
float ans[10][10], z[10];
bool artieqn[10];
int R, C;
int rank1, rank2, i, j, k, in_var, var, eqn;
int countVal=0,countVal1=0, slackVar = 0, ar = 0;
bool unbounded = false, flag = false;
bool infinite = false;
float lastRow[10][2];
float bv[10], nbv[10], obj_fun[10];

void initTemp(){
  rep(i, 10){
    rep(j, 10)
      temp[i][j] = 0;
  }
}
void print(){
  // rep(j, var + ar)
  //   cout << nbv[j] << "\t";
  // cout << endl;   
  rep(i, eqn + 1){
      cout << bv[i] << "\t";
        rep(j, var + ar + 1){
          cout << mat[i][j] << "\t";
        }
        cout << endl;
     } 

    printf("\n=========================================================================\n");
}
void copyFromTemp(){
     for(int i = 0 ; i <=eqn ; i++){
          for(int j = 0 ; j <= var; j++){
               mat[i][j] = temp[i][j];
               cout << mat[i][j] << "\t";
          }     
          cout << endl;
     }

    printf("\n=========================================================================\n");
}

void reverseMat(int x){
  rep(i, eqn){
    rep(j, var + ar + 1){
      mat[i][j] = (-1)*mat[i][j];
    }
  }

  if(x == 2)
    return;
  rep(j, var + ar + 1){
      mat[eqn][j] = (-1)*mat[eqn][j];
  }
}
void read(){
  printf("Enter the number of variables\n");
  scanf("%d",&var);
    
  printf("Enter the number of equations\n");
  scanf("%d",&eqn);
  string inequality;
  rep(i,10){
    artieqn[i] = false;
    obj_fun[i] = 0.0;
    rep(j,10){
      mat[i][j] = 0.0;
    }
  }

  rep(i ,eqn){
    artieqn[i] = false;
    printf("Enter coefficients, inequation and constant term of equation number %d seperated by spaces:\n" , i + 1);
    rep(j,var){
      cin >> mat[i][j];
    }
    cin >> inequality;
    cin >> mat[i][var];    
  }
  cout<<"Enter 1 for max and 2 for min problem"<<endl;
  cin>>obj_fun[9];
  cout<<"Enter objective function coefficients along with the constant \n"<<endl;
  rep(i,var){
    cin >> obj_fun[i];
    nbv[i] = obj_fun[i];
    mat[eqn][i] = obj_fun[i];
  }
  cin >> obj_fun[var + ar];

  printf("\n=========================================================================\n"); 
  mat[eqn][var + ar] = obj_fun[var + ar];
  reverseMat(obj_fun[9]);
}

int getMinFromLastCol(){
    int ind = -1;
    float currMin = 0;
    for(int i = 0 ; i < eqn ; i++){
          if(mat[i][var + ar] > 0)
               continue;            
          if(mat[i][var + ar] < currMin){
               currMin = mat[i][var + ar];
               ind = i;     
         }
    }
    return ind;            
}

int getPivotCol(int pivotRow){
     int ind = -1; 
     float currMin = 100000;
     for(int i = 0 ; i < var + ar; i++){
          if(abs(((mat[eqn][i] - bv[pivotRow])/mat[pivotRow][i])) < currMin){
               ind = i;
               currMin = abs(((mat[eqn][i] - bv[pivotRow])/mat[pivotRow][i]));               
          }
     }
     return ind;        
}

void solve(){        
     int pivotRow, pivotCol;
     while((pivotRow = getMinFromLastCol()) != -1){
          if((pivotCol = getPivotCol(pivotRow)) == -1){
               unbounded = true;
               return;
          }
          float tm = bv[pivotRow];
          bv[pivotRow] = nbv[pivotCol];
          nbv[pivotCol] = tm;
          for(i = 0 ; i <= eqn ; i++){
               for(j = 0 ; j <= var; j++){
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
          copyFromTemp();
          print();
     }
}

int main(){
     read();   
     solve();
     rep(i, var){
      if(mat[eqn][i] == 0)
        infinite = true;
     }

     printf("\n=========================================================================\n");
     if(infinite)
          printf("There are infinitely many solutions\n");          
     else if(unbounded)
          printf("The answer is unbounded\n");
     else          
          printf("The optimal value is %f \n", mat[eqn][var]); 

     printf("\n=========================================================================\n"); 
     return 0;
}

