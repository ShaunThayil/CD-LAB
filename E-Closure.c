#include<stdio.h>

// 1001 is the final element of the transition diagram array 
// 0 is the e input symbol
// 0110 Null State
int transition[20][20][20];
int n_states,n_inp_smb;
int checked[20];
int stack[20],top=-1;
int e_close[20][20],e_len[20];
int delimiter = 0110;
int null = 1001;
// Printing Functions
void print_e_close(int e_close[][20],int n_states,int e_len[]){
    for(int i=0;i<n_states;i++){
        printf("State %d :",i);
        for(int j=0;j<e_len[i];j++){
            printf(" %d",e_close[i][j]);
        }
        printf("\n");
    }
}

void print_transitions(int transition[][20][20],int n_states,int n_inp_smb){
    for(int i=0;i<n_states;i++){
        printf("State %d ",i);
        for(int j=0;j<n_inp_smb;j++){
            if(transition[i][j][0] == null){
                printf("NULL   ");
                continue;
            }
            for(int k=0;transition[i][j][k] != delimiter;k++){
                printf("%d,",transition[i][j][k]);
            }
            printf("   ");
        }
        printf("\n");
    }
}

void stack_state(int stack[],int top){
    printf("\nStack State : \n");
    if(top == -1){
        printf("Stack Empty\n");
    }
    else{
    for(int i=0;i<=top;i++){
        printf("%d ",stack[i]);
    }
    printf("\n");
    }
}

void print_arr(int arr[],int x){
    for(int i=0;i<x;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}



//End Printing Functions



// Input the Transition Table
void input_transitions(int transition[][20][20],int n_states,int n_inp_smb){
    int n;
    for(int i=0;i<n_states;i++){
        for(int j=0;j<n_inp_smb;j++){
             printf("Enter The Number of States for (State,inp_smb) (%d,%d): ",i,j);
            scanf("%d",&n);
            if(n == 0){
                transition[i][j][0] = null;
                continue;
            }
            printf("\nState %d\n",i);
            printf("\n     INP SMB %d:",j);
            
            for(int k=0;k<n;k++){
                     scanf("%d",&transition[i][j][k]);
            }
            printf("\n");
            transition[i][j][n] = 0110;
        }
    }

    
}

void reset(int arr[],int n){
    for(int i=0;i<n;i++){
        arr[i] = 0;
    }
}

int check_present(int checked[],int n_states,int state){
   return checked[state];
}






void e_closure(int transition[][20][20],int n_states,int n_inp_smb){
    printf("\nInside E-Closure\n");
    int curr;
    reset(e_len,n_states);
    for(int i=0;i<n_states;i++){
        top = -1;
        stack[++top] = i;
        e_close[i][0] = i;
        e_len[i]++;
        reset(checked,n_states);
        
        printf("\nPRESENT STATE %d:-\n",i);
        printf("\nCheck State Reset!!\n");
        while(top != -1){
            curr = stack[top--];
            printf("\nCURR STATE = %d\n",curr);
            if(transition[curr][0][0] != null){
                for(int k=0; transition[curr][0][k] != delimiter;k++){
                    printf("Check Present %d :- %d",transition[curr][0][k],check_present(checked,n_states,transition[curr][0][k]));
                    if(check_present(checked,n_states,transition[curr][0][k]) == 0){
                        stack[++top] = transition[curr][0][k];
                        stack_state(stack,top);
                        
                        e_close[i][e_len[i]++] = transition[curr][0][k];
                        printf("\nSTATE %d : %d ADDED\n",curr,transition[curr][0][k]);
                    }
                    checked[curr] = 1;
                    printf("\nCHECK STATE\n");
                    print_arr(checked,n_states);
                }
            }
            
        }
        

    }

    printf("\nE - Closure :-\n");
    print_e_close(e_close,n_states,e_len);

}




void main(){
   printf("Enter The Number Of States:- ");
   scanf("%d",&n_states);

   printf("\nEnter The Number Of Input Symbols:-  ");
   scanf("%d",&n_inp_smb);

   input_transitions(transition,n_states,n_inp_smb);
   printf("\nTransition Diagram :-\n");
   print_transitions(transition,n_states,n_inp_smb);

   e_closure(transition,n_states,n_inp_smb);


}