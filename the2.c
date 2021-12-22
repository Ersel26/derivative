#include <stdio.h>
#include <stdlib.h>

int is_num(char c){
    if(c>47 && c<58){return 1;}
    else{return 0;}
}

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

char* prev_num(char *num){
    char *prev = malloc(2 * sizeof(char));
    int len=0;
    while(num[len]!='\0')
    {
        len++;
    }
    if(len==1)
    {
        prev[0] = num[0]-1;
    }
    else if(len==2)
    {
        if(num[1]!='0')
        {
            prev[0] = num[0];
            prev[1] = num[1]-1;
        }
        else if(num[1]=='0')
        {
            prev[0] = num[0]-1;
            prev[1] = '9';
        }
    }
    else if(len==3)
    {
        prev[0] = '9';
        prev[1] = '9';
    }

    return prev;
}

void queue_maker(char *s, char **queue, int len_of_s){
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

void mid_pop(char **arr, int len, int x){
    int i,j;

    for(i=x;i<len-1;i++)
    {
        arr[i] = NULL;
        arr[i] = malloc(str_len(arr[i+1]) * sizeof(char));
        for(j=0;j<str_len(arr[i+1]);j++)
        {
            arr[i][j] = arr[i+1][j];
        }
    }
    arr[i] = NULL;
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
    mid_pop(recons_queue, len-1, x-2);
    
}

void deriv(char **deriv_queue, char **recons_queue, int len, int x){
    int i,j;
    char temp_op = deriv_queue[x][0];

    if(deriv_queue[x][0]=='+' || deriv_queue[x][0]=='-')
    {
        free(deriv_queue[x]);
        deriv_queue[x] = malloc((3+str_len(deriv_queue[x-1])+str_len(deriv_queue[x-2])) * sizeof(char));

        deriv_queue[x][0] = '(';
        j=0;
        for(i=1;i<1+str_len(deriv_queue[x-2]);i++)
        {
            deriv_queue[x][i] = deriv_queue[x-2][j++];
        }
        deriv_queue[x][1+str_len(deriv_queue[x-2])] = temp_op;
        j=0;
        for(i=2+str_len(deriv_queue[x-2]);i<2+str_len(deriv_queue[x-1])+str_len(deriv_queue[x-2]);i++)
        {
            deriv_queue[x][i] = deriv_queue[x-1][j++];
        }
        deriv_queue[x][2+str_len(deriv_queue[x-1])+str_len(deriv_queue[x-2])] = ')';
    }
    else if(deriv_queue[x][0]=='*')
    {
        free(deriv_queue[x]);
        deriv_queue[x] = malloc((5 + str_len(deriv_queue[x-2]) + str_len(deriv_queue[x-1]) + str_len(recons_queue[x-2]) + str_len(recons_queue[x-1])) * sizeof(char));
        
        deriv_queue[x][0] = '(';
        j=0;
        for(i=1;i<1+str_len(deriv_queue[x-2]);i++)
        {
            deriv_queue[x][i] = deriv_queue[x-2][j++];
        }
        deriv_queue[x][1+str_len(deriv_queue[x-2])] = '*';
        j=0;
        for(i=2+str_len(deriv_queue[x-2]);i<2+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1]);i++)
        {
            deriv_queue[x][i] = recons_queue[x-1][j++];
        }
        deriv_queue[x][2+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])] = '+';
        j=0;
        for(i=3+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1]);i<3+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(recons_queue[x-2]);i++)
        {
            deriv_queue[x][i] = recons_queue[x-2][j++];
        }
        deriv_queue[x][3+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(recons_queue[x-2])] = '*';
        j=0;
        for(i=4+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(recons_queue[x-2]);i<4+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(recons_queue[x-2])+str_len(deriv_queue[x-1]);i++)
        {
            deriv_queue[x][i] = deriv_queue[x-1][j++];
        }
        deriv_queue[x][4+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(recons_queue[x-2])+str_len(deriv_queue[x-1])] = ')';
    }
    else if(deriv_queue[x][0]=='/')
    {
        free(deriv_queue[x]);
        deriv_queue[x] = malloc((4 *(str_len(deriv_queue[x-2]) + str_len(recons_queue[x-1]) + str_len(deriv_queue[x-1]) + str_len(recons_queue[x-2] + str_len(recons_queue[x-1])))) * sizeof(char));
        i=0;
        deriv_queue[x][i++] = '(';
        deriv_queue[x][i++] = '(';
        for(j=0;j<str_len(deriv_queue[x-2]);j++)
        {
            deriv_queue[x][i++] = deriv_queue[x-2][j];
        }
        deriv_queue[x][i++] = '*';
        for(j=0;j<str_len(recons_queue[x-1]);j++)
        {
            deriv_queue[x][i++] = recons_queue[x-1][j];
        }
        deriv_queue[x][i++] = '-';
        for(j=0;j<str_len(deriv_queue[x-1]);j++)
        {
            deriv_queue[x][i++] = deriv_queue[x-1][j];
        }
        deriv_queue[x][i++] = '*';
        for(j=0;j<str_len(recons_queue[x-2]);j++)
        {
            deriv_queue[x][i++] = recons_queue[x-2][j];
        }
        deriv_queue[x][i++] = ')';
        deriv_queue[x][i++] = '/';
        for(j=0;j<str_len(recons_queue[x-1]);j++)
        {
            deriv_queue[x][i++] = recons_queue[x-1][j];
        }
        deriv_queue[x][i++] = '^';
        deriv_queue[x][i++] = '2';
        deriv_queue[x][i++] = ')';
    }
    else if(deriv_queue[x][0]=='^')
    {
        free(deriv_queue[x]);
        deriv_queue[x] = malloc((5 + str_len(recons_queue[x-1]) + str_len(recons_queue[x-2]) + str_len(prev_num(recons_queue[x-1])) + str_len(deriv_queue[x-2])) * sizeof(char));

        deriv_queue[x][0] = '(';
        j=0;
        for(i=1;i<1+str_len(recons_queue[x-1]);i++)
        {
            deriv_queue[x][i] = recons_queue[x-1][j++];
        }
        deriv_queue[x][1+str_len(recons_queue[x-1])] = '*';
        j=0;
        for(i=2+str_len(recons_queue[x-1]);i<2+str_len(recons_queue[x-1])+str_len(recons_queue[x-2]);i++)
        {
            deriv_queue[x][i] = recons_queue[x-2][j++];
        }
        deriv_queue[x][2+str_len(recons_queue[x-1])+str_len(recons_queue[x-2])] = '^';
        j=0;
        for(i=3+str_len(recons_queue[x-1])+str_len(recons_queue[x-2]);i<3+str_len(recons_queue[x-1])+str_len(recons_queue[x-2])+str_len(prev_num(recons_queue[x-1]));i++)
        {
            deriv_queue[x][i] = prev_num(recons_queue[x-1])[j++];
        }
        deriv_queue[x][3+str_len(recons_queue[x-1])+str_len(recons_queue[x-2])+str_len(prev_num(recons_queue[x-1]))] = '*';
        j=0;
        for(i=4+str_len(recons_queue[x-1])+str_len(recons_queue[x-2])+str_len(prev_num(recons_queue[x-1]));i<4+str_len(recons_queue[x-1])+str_len(recons_queue[x-2])+str_len(prev_num(recons_queue[x-1]))+str_len(deriv_queue[x-2]);i++)
        {
            deriv_queue[x][i] = deriv_queue[x-2][j++];
        }
        deriv_queue[x][4+str_len(recons_queue[x-1])+str_len(recons_queue[x-2])+str_len(prev_num(recons_queue[x-1]))+str_len(deriv_queue[x-2])] = ')';
    }
    
    mid_pop(deriv_queue, len, x-2);
    mid_pop(deriv_queue, len-1, x-2);
}

int main()
{
    char *s = malloc(sizeof(char));
    char x;
    char **deriv_queue, **recons_queue;
    char *result;
    int i=0,j,input_len;
    int result_len;

    while(1)
    {
        x = getchar();
        if(x==' ' || x=='\n')
        {
            continue;
        }
        else if(x==EOF)
        {
            break;
        }
        else
        {
            s[i++] = x;
            s = realloc(s, (i+1) * sizeof(char));
        }
    }
    input_len = i;
    
    deriv_queue = (char **)malloc(input_len * sizeof(char *));
    recons_queue = (char **)malloc(input_len * sizeof(char *));

    for(i=0;i<input_len+1;i++)
    {
        *(deriv_queue+i) = (char *)malloc(7 * sizeof(char));
        *(recons_queue+i) = (char *)malloc(3 * sizeof(char));
    }

    queue_maker(s, deriv_queue, input_len);
    queue_maker(s, recons_queue, input_len);
    
    for(i=0;i<input_len;i++)
    {
        if(is_op(deriv_queue[i][0]))
        {
            continue;
        }
        else if(deriv_queue[i][0]=='T')
        {
            deriv_queue[i][0] = '(';
            deriv_queue[i][1] = 'T';
            deriv_queue[i][2] = '^';
            deriv_queue[i][3] = '2';
            deriv_queue[i][4] = '+';
            deriv_queue[i][5] = '1';
            deriv_queue[i][6] = ')';
        }
        else if(deriv_queue[i][0]=='l')
        {
            deriv_queue[i][0] = '(';
            deriv_queue[i][1] = '1';
            deriv_queue[i][2] = '/';
            deriv_queue[i][3] = 'X';
            deriv_queue[i][4] = ')';
        }
        else if(deriv_queue[i][0]=='S')
        {
            deriv_queue[i][0] = 'C';
        }
        else if(deriv_queue[i][0]=='s')
        {
            deriv_queue[i][0] = 'c';
        }
        else if(deriv_queue[i][0]=='c')
        {
            deriv_queue[i][0] = 's';
        }
        else if(deriv_queue[i][0]=='X')
        {
            deriv_queue[i][0] = '1';
        }
        else if(is_num(deriv_queue[i][0]))
        {
            deriv_queue[i] = NULL;
            deriv_queue[i] = malloc(sizeof(char));
            deriv_queue[i][0] = '0';
        }
    }
    i=0;
    while(deriv_queue[i])
    {
        if(is_op(deriv_queue[i][0]))
        {
            deriv(deriv_queue, recons_queue, input_len, i);
            recons(recons_queue, input_len, i);
            input_len-=2;
            i=0;
        }
        else
        {
            i++;
        }
    }
    result_len = str_len(deriv_queue[0]);
    result = malloc(result_len * sizeof(char));
    j=0;
    for(i=0;i<str_len(deriv_queue[0]);i++)
    {
        if(deriv_queue[0][i]=='T')
        {
            result_len+=2;
            result = realloc(result, result_len * sizeof(char));
            result[j++] = 't';
            result[j++] = 'a';
            result[j++] = 'n';
        }
        else if(deriv_queue[0][i]=='S')
        {
            result_len+=2;
            result = realloc(result, result_len * sizeof(char));
            result[j++] = 's';
            result[j++] = 'i';
            result[j++] = 'n';
        }
        else if(deriv_queue[0][i]=='C')
        {
            result_len+=2;
            result = realloc(result, result_len * sizeof(char));
            result[j++] = 'c';
            result[j++] = 'o';
            result[j++] = 's';
        }
        else if(deriv_queue[0][i]=='l')
        {
            result_len++;
            result = realloc(result, result_len * sizeof(char));
            result[j++] = 'l';
            result[j++] = 'n';
        }
        else if(deriv_queue[0][i]=='s')
        {
            result_len++;
            result = realloc(result, result_len * sizeof(char));
            result[j++] = 's';
            result[j++] = 'h';
        }
        else if(deriv_queue[0][i]=='c')
        {
            result_len++;
            result = realloc(result, result_len * sizeof(char));
            result[j++] = 'c';
            result[j++] = 'h';
        }
        else
        {
            result[j++] = deriv_queue[0][i];
        }
    }
    
    for(i=0;i<result_len;i++)
    {
        printf("%c",result[i]);
    }

    return 0;
}