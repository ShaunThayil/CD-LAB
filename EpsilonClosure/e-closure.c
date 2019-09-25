#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int transition_diag[30][30][30];
char sym_char[20];
int n_states,n_sym;
int e_col;   //column with 
int seen[30],seen_index = 0;
int e_closure[30][30];
void input(){
    int index=0,num = -1;
    printf("Enter The Transisiton States for :-(1010 to stop)\n");
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

void reset_seen(){
    for(int i=0;i<n_states;i++)
         seen[i] = 0;
}
void epsilon_closure_noob(){
    int stack[30],top,state;
    for(int i = 0 ; i < n_states ; i++){
        top = 0;
        stack[++top] = i;
        index = 0;
        reset_seen();

        while(top > 0){
            state = i;
            e_closure[i][index] = i;
            seen[seen_index++] = i;
            if(transition_diag[i][])
   
        }

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