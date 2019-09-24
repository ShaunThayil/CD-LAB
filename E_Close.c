#include<stdio.h>

// 1001 is the final element of the transition diagram array 
// 0 is the e input symbol
// 0110 Null State
int transitions[20][20][20];
int n_states,n_inp_smb;
int checked[20];
int stack[20],top=-1;
int e_close[20][20],e_len[20];

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



// Input the Transition Table
void input_transitions(int transition_diag[][][20],int n_states,int n_inp_smb){
    int n;
    for(int i=0;i<n_states;i++){
        for(int j=0;j<n_inp_smb;j++){
             printf("Enter The Number of States for (State,inp_smb) (%d,%d)",i,j);
            scanf("%d",&n);
            printf("\nState %d\n",i);
            printf("\n     INP SMB %d:\n",j);
            for(int k=0;k<n;k++){
                     scanf("%d",&transition[i][j][k]);
            }

            transition[i][j][n] = 1010;
        }
    }

    
}

void reset_1D(int arr[],int n){
    for(int i=0;i<n;i++){
        arr[i] = 0;
    }
}

int check_present(int checked[],int n_states,int state){
   for(int i=0;i<n_states,i++){
       if(checked[i] == state){
           return 1;
       }
   }
   
   return 0;
}






void e_closure(int transition[][][20],int n_states,int n_inp_smb){
    int curr;
    reset(e_len,n_states);
    for(int i=0;i<n_states;i++){
        top = -1;
        stack[++top] = i;
        e_close[i][0] = i;
        e_len[i]++;
        reset(checked,n_states);
        while(top != -1){
            curr = stack[top--];
            if(transition[curr][0] != 0110){
                for(int k=0;k != 1010;k++){
                    if(check_present(checked,n_states,transition[i][0][k]) == 0){
                        stack[++top] = transition[i][0][k];
                        checked[transition[i][0][k]] = 1;
                        e_close[i][e_len[i]++] = transition[i][0][k];
                    }
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

   e_closure(transition,n_states,n_inp_smb);


}