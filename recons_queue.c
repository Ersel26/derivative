#include <stdio.h>
#include <stdlib.h>

int is_op(char c){
    if(c=='+' || c=='-' || c=='*' || c=='/' || c=='^'){return 1;}
    else{return 0;}
}

int str_len(char *s){
    int i=0;
    while(s[i]!='\0')
    {
        i++;
    }
    return i;
}

void mid_pop(char **arr, int len, int x){
    int i,j;

    for(i=x;i<len-1;i++)
    {
        free(arr[i]);
        arr[i] = malloc(str_len(arr[i+1]) * sizeof(char));
        for(j=0;j<str_len(arr[i+1]);j++)
        {
            arr[i][j] = arr[i+1][j];
        }
    }
    free(arr[i]);
    arr[i] = malloc(0 * sizeof(char));
    
}

void recons(char **recons_queue, int len, int x){
    int i,j;
    char temp_op = recons_queue[x][0];
    
    free(recons_queue[x]);
    recons_queue[x] = malloc((3+str_len(recons_queue[x-1])+str_len(recons_queue[x-2])) * sizeof(char));

    recons_queue[x][0] = '(';
    j=0;
    for(i=1;i<1+str_len(recons_queue[x-2]);i++)
    {
        recons_queue[x][i] = recons_queue[x-2][j++];
    }
    recons_queue[x][1+str_len(recons_queue[x-2])] = temp_op;
    j=0;
    for(i=2+str_len(recons_queue[x-2]);i<2+str_len(recons_queue[x-1])+str_len(recons_queue[x-2]);i++)
    {
        recons_queue[x][i] = recons_queue[x-1][j++];
    }
    recons_queue[x][2+str_len(recons_queue[x-1])+str_len(recons_queue[x-2])] = ')';

    mid_pop(recons_queue, len, x-2);
    mid_pop(recons_queue, len, x-2);
}

int main()
{
    char s[] = "X2^1+T*l2^X/-";
    char **recons_queue = malloc(15 * sizeof(char *));
    int i,j;

    for(i=0;i<15;i++)
    {
        *(recons_queue+i) = malloc(5 * sizeof(char));
    }
    for(i=0;i<15;i++)
    {
        recons_queue[i][0]=s[i];
    }

    i = 0;
    while(i<15)
    {
        if(is_op(recons_queue[i][0]))
        {
            recons(recons_queue, 15, i);
            i=0;
        }
        else
        {
            i++;
        }
    }
    
    for(i=0;i<15;i++)
    {
        for(j=0;j<str_len(recons_queue[i]);j++)
        {
            printf("%c",recons_queue[i][j]);
        }
        printf("\n");
    }

    
    
    return 0;
}