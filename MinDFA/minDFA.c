#include<stdio.h>
/*
For the table:-
2 -> Invalid cell
0 -> Unmarked cell
1 -> Marked Cell
3 -> Already Combined
*/
int n_states,n_inp_smb;  // Number of States & Input Symbol
int transition[20][20];  // Transition Table
int final_states[10],n_final;  //Final State Array
int non_final_states[10],n_non_final; // Non Final State Array
int combined_states[10][10],n_unmarked; //Store the combined states
int final_len[15];

// Print Matrix
void print_mat(int mat[][20],int x,int y){
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}

// Print Array
void print_arr(int arr[],int x){
    for(int i=0;i<x;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}


//Accept Transition Table and set of final states from the user
void input_transitions(){ 
    
    printf("Enter The Number Of States :- ");
    scanf("%d",&n_states);
    
    printf("Enter The Number of Input Symbols :- ");
    scanf("%d",&n_inp_smb);

    printf("\nEnter The Transition Table :- \n");
    for(int i=0;i<n_states;i++){
        printf("State %d ",i);
        for(int j=0;j<n_inp_smb;j++){
            printf("\n    InSymb %d : ",j);
            scanf("%d",&transition[i][j]);
            //printf(" %d",transition[i][j]);
            }
    }

    printf("\nEnter Number of Final States:-");
    scanf("%d",&n_final);

    printf("Enter the Final States:- \n");
    for(int i=0;i<n_final;i++){
        scanf("%d",&final_states[i]);
    }
    
    int flag,index = 0;
    n_non_final = n_states - n_final;
    for(int i=0;i<n_states;i++){
        flag = 0;
        for(int j=0;j<n_final;j++){
            if(i == final_states[j]){
                flag = 1;
                break;
            }
        }

        if(flag == 0){
            non_final_states[index++] = i;
        }
    }
    printf("\nFinal States Are:-\n");
    print_arr(final_states,n_final);

     printf("\nNon -Final States Are:-\n");
    print_arr(non_final_states,n_non_final);
    
}

//Initialize the minTable
void init_minTable(int minTable[][20],int n_states){
    for(int i=0;i<n_states;i++){
        for(int j=0;j<n_states;j++){
            minTable[i][j] = 2;
        }
    }
    // for(int i=0;i<n_states;i++){
    //     for(int j=0;j<n_states;j++){
    //         if(j<i){
    //             minTable[i][j] = 0;
    //         }
    //         else{
    //             minTable[i][j] = 2;
    //         }
    //     }
    // }

     for(int i=0;i<n_states;i++){
        for(int j=0;j<i;j++){
            
                minTable[i][j] = 0;
            }
     }

}

// Marks the cells which are a pair of final and non final states
void mark_non_final_pairs(int minTable[][20]){
      for(int i=0;i<n_final;i++){
          for(int j=0;j<n_non_final;j++){
              if(minTable[final_states[i]][non_final_states[j]] == 0){
                  minTable[final_states[i]][non_final_states[j]] = 1;
              }
              else{
                  minTable[non_final_states[j]][final_states[i]] = 1;
              }
          }
      }
}

int checkMark(int minTable[][10],int x, int y){
    int trans_x,trans_y;
    for(int i=0;i<n_inp_smb;i++){
        trans_x = transition[x][i];
        trans_y = transition[y][i];
        printf("\n X-> %d Y -> %d Trans_X -> %d Trans_Y -> %d minTable[trans_x][trans_y] = %d  minTable[trans_y][trans_x] = %d\n",x,y,trans_x,trans_y,minTable[trans_x][trans_y],minTable[trans_y][trans_x]);
        if(minTable[trans_x][trans_y] == 1 || minTable[trans_y][trans_x] == 1){
            printf("Return 1");
            return 1;
        }
    }
    return 0;
}

void mark_unmarked(int minTable[][10]){
    int flag;
    while(1){
    flag = 0;
    for(int i=1;i<n_states;i++){
        for(int j=0;j<i;j++){
             printf("\nX->%d Y->%d\n",i,j);
            if(checkMark(minTable,i,j) == 1 && minTable[i][j] == 0){
                printf("\nMarked (%d,%d)",i,j);
                minTable[i][j] = 1;
                flag = 1;
                
            }
        }
    }
    if(flag == 0){
        break;
    }
    }
}

int check_present(int state,int location,int len){
    for(int i=0;i<len;i++){
        if(combined_states[location][i] == state){
            return 1;
        }
    }
    return 0;
}

void combine_next(int minTable[][n_states],int s1,int s2,int location,int next_pointer){
    for(int j=0;j<n_states;j++){
        if(check_present(j,location,next_pointer) == 0){
            if(minTable[s1][j] == 0){
                combined_states[location][next_pointer++] = j;
                minTable[s1][j] = 3;
            }
            if(minTable[j][s1] == 0){
                combined_states[location][next_pointer++] = j;
                minTable[j][s1] = 3;
            }

            if(minTable[s2][j] == 0){
                combined_states[location][next_pointer++] = j;
                minTable[s2][j] = 3;
            }

            if(minTable[j][s2] == 0){
                combined_states[location][next_pointer++] = j;
                minTable[j][s2] = 3;
            }
        }
            }
    final_len[location] = next_pointer;
    }


void combine_unmarked(int minTable[][n_states]){
   int index = 0;
  
   int len;
   for(int i=0;i<n_states;i++){
       len = 0;
       for(int j=0;j<i;j++){
           if(minTable[i][j] == 0){
               combined_states[index][0] = i;
               combined_states[index++][1] = j;
               minTable[i][j] = 3;
               len = 2;

               combine_next(minTable,i,j,index,len);
               index++;
           }
       }
   }
   
}

void min_DFA(){
    int minTable[n_states][n_states];

    init_minTable(minTable,n_states);
    printf("\nInit_minTable:-\n");
    print_mat(minTable,n_states,n_states);
   
//    printf("\nTesting\n");
//    for(int i=0;i<n_states;i++){
//        printf("%d ",minTable[5][i]);
//    }
    mark_non_final_pairs(minTable);
    printf("\nMinTable after marking non_final_pairs :-\n");
    print_mat(minTable,n_states,n_states);

    mark_unmarked(minTable);
    printf("\nMinTable After Marking Unmarked Pairs\n");
    print_mat(minTable,n_states,n_states);

    combine_unmarked(minTable);
}

void main(){

    input_transitions();
    printf("\nTransition Table:-\n");
    print_mat(transition,n_states,n_inp_smb);
    min_DFA();
}