#include <stdio.h>
#include <stdlib.h>

int is_num(char c){
    if(c>47 && c<58){return 1;}
    else{return 0;}
}

void queue_maker(char *s, char **queue, int len_of_s, char kind){
    int i,j,queue_index=0,stack_index=0;
    char *op_stack = malloc(len_of_s * sizeof(char));

    i=0;
    while(s[i]!='\0')
    {
        if(s[i]=='(')
        {
            op_stack[stack_index++]=s[i];
        }
        else if(s[i]==')')
        {
            while(op_stack[stack_index-1]!='(')
            {
                queue[queue_index++][0]=op_stack[--stack_index];
            }
            stack_index--;
        }
        else if(s[i]=='+' || s[i]=='-')
        {
            while(op_stack[stack_index-1]=='+' || op_stack[stack_index-1]=='-' || op_stack[stack_index-1]=='*' || op_stack[stack_index-1]=='/' || op_stack[stack_index-1]=='^')
            {
                queue[queue_index++][0]=op_stack[--stack_index];
            }
            op_stack[stack_index++]=s[i];
        }
        else if(s[i]=='*' || s[i]=='/')
        {
            while(op_stack[stack_index-1]=='*' || op_stack[stack_index-1]=='/' || op_stack[stack_index-1]=='^')
            {
                queue[queue_index++][0]=op_stack[--stack_index];
            }
            op_stack[stack_index++]=s[i];
        }
        else if(s[i]=='^')
        {
            op_stack[stack_index++]=s[i];
        }
        else
        {
            if(s[i]=='t' || (s[i]=='s' && s[i+1]=='i'))
            {
                queue[queue_index++][0]=s[i]-32;
                i+=2;
            }
            else if(s[i]=='l' || s[i]=='s' || s[i]=='c')
            {
                queue[queue_index++][0]=s[i];
                i++;
            }
            else if(is_num(s[i]))
            {
                j=0;
                while(is_num(s[i]))
                {
                    queue[queue_index][j]=s[i];
                    i++;j++;
                }
                i--;
                queue_index++;
            }
            else
            {
                queue[queue_index++][0]=s[i];
            }
        }
        i++;
    }
    
    while(stack_index>=0)
    {
        queue[queue_index++][0]=op_stack[--stack_index];
    }
}


int main(){
    char s[100] = "(X^2+1)*tan-ln^2/X";
    char **queue_of_s = (char **)malloc(20 * sizeof(char *));
    int i;

    for(i=0;i<20;i++)
    {
        *(queue_of_s+i) = (char *)malloc(3 * sizeof(char));
    }

    queue_maker(s, queue_of_s, 3);
    
    i=0;
    while(queue_of_s[i][0]!='\0')
    {
        printf("%c",queue_of_s[i++][0]);
    }
    printf("\n");

    return 0;
}