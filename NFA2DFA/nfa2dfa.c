// General Starts
int transition_diag[30][30][30];
char sym_char[20];
int n_states,n_sym;
//  General Ends

// n+1 th state is the dead state
// NFA2DFA
int new_dfa_table[30][30][30];
int seen[30][30];
int stack[30][30];
int top,index = 0;
int result[20][10];
int union_arr[30];
// Accept The transition Table
void input(){
    int index=0,num = -1;
    printf("Enter The Transisiton States for :-(1010 to stop & 1001 for null state)\n");
    for(int i=0;i<n_states;i++){
        for(int j=0;j<n_sym;j++){
            index = 0;
            num = -1;
            printf("(%d,%c)\n",i,sym_char[j]);
            while(num != 1010){
                scanf("%d",&num);
                transition_diag[i][j][index] = num;
                index++;
            }
            transition_diag[i][j][index] = num;
              
        }
    }
}

// Accept The input symbols from the user
void input_symbols(){    
    char c;
    printf("Enter The Input Symbols:-\n");
    // printf("Inside input_symbols()\n");
    for(int i=0;i<n_sym;i++){
        // printf("Inside input_symbols()\n");
        scanf(" %c",&c);
        if(c == 'e'){
            e_col = i;
        }
        sym_char[i] = c;
        
         }
}

// Print The Transition Table
void display(){
    int num = -1,index;
    for(int i=0;i<n_states;i++){
        for(int j=0;j<n_sym;j++){
            printf("[");
            index = 0;
            num = -1;
            do{
                num = transition_diag[i][j][index];
                if(num == 1010)
                   break;
                printf("%d,", num);
                index++;

            }while(1);

            printf("] ");
            
        }
        printf("\n");
    }
}


int check_seen(int states[],int n){
    if(index == 0){
        for(int i=0;i<n;i++){
            seen[0][i] = states[i];
        }
        seen[0][n] = 1010;
        index = 1;
        return 0;
    }
    int flag = 0,iterator;
    for(int i = 0;i < index ; i++){
         for(int iterator = 0; seen[i][iterator] != 1010; iterator++){
             for(int j = 0;j < n ; j++){
                if(seen[i][iterator] == states[j]){
                    flag = 1;
                    break;
                }
             
         }
         }
    }
         if(flag == 0){
             for(int i=0;i<n;i++){
                 seen[index][i] = states[i];
             }
             seen[index][n] = 1010;
             index++;
             return 0;
         }
         
          return 1;
}

int  union(int states[],int n){
     int index = 0;
     int flag;
     
     for(int i=0;i<n_sym;i++){

         for(index = 0; transition_diag[state[0]][i][index] != 1010;index++){
             union_arr[index] = transition_diag[state[0]][i][index];
         }
          for(int j = 1 ;j < n; j++){
              for(int l =0 ;transition_diag[state[j]][i][l] != 1010;l++){
                flag = 0;
                for(int k=0;k < index ;k++){
                    if(union_arr[k] == transition_diag[state[j]][i][l]){
                        flag = 1;
                        break;
                    }
                }

                if(flag == 1){
                    continue;
                }
                else{
                    union_arr[index++] = j;
                }
              }
          }
          }
}

void push_stack(int state){
    for(int sym=0; sym < n_sym;sym++){
        for(int j=0;new_dfa_table[state][sym][j] != 1010 ; j++){
            if(check_seen(new_dfa_table[j][sym]) == 1){
                break;
            }
            stack[top][j] = new_dfa_table[state][sym][j];

        }
    }
}
void NFA2DFA(){
    int i,j;
    for( i=0;i<n_sym;i++){
        for(j=0; transition_diag[0][i][j] != 1010 ; j++){
            new_dfa_table[0][i][j] = transition_diag[0][i][j];
        }
        new_dfa_table[0][i][j] = 1010;
    }

    int stack[20][20]={0},top = 0;
    push_stack(0);

    for(int i=)
    while(top != -1){

    }
   

if(check_seen(states,n) == 1){
                 return;
             }
}
void main(){
   

   printf("Enter The Number Of States :-\n");
   scanf("%d",&n_states);

   printf("Enter The number of input symbols:-\n");
   scanf("%d",&n_sym);
   
   printf("Number States - %d , Symbols - %d\n",n_states,n_sym);
   input_symbols();
   input();
   
   display();


}