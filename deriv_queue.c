#include <stdio.h>
#include <stdlib.h>

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

"""
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
        deriv_queue[x][2+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])] = '-';
        j=0;
        for(i=3+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1]);i<3+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(deriv_queue[x-1]);i++)
        {
            deriv_queue[x][i] = deriv_queue[x-1][j++];
        }
        deriv_queue[x][3+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(deriv_queue[x-1])] = '*';
        j=0;
        for(i=4+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(deriv_queue[x-1]);i<4+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(deriv_queue[x-1])+str_len(recons_queue[x-2]);i++)
        {
            deriv_queue[x][i] = recons_queue[x-2][j++];
        }
        deriv_queue[x][4+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(deriv_queue[x-1])+str_len(recons_queue[x-2])] = ')';
        deriv_queue[x][5+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(deriv_queue[x-1])+str_len(recons_queue[x-2])] = '/';
        j=0;
        for(i=6+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(deriv_queue[x-1])+str_len(recons_queue[x-2]);i<6+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(deriv_queue[x-1])+str_len(recons_queue[x-2])+str_len(recons_queue[x-1]);i++)
        {
            deriv_queue[x][i] = recons_queue[x-1][j++];
        }
        deriv_queue[x][6+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(deriv_queue[x-1])+str_len(recons_queue[x-2])+str_len(recons_queue[x-1])] = '^';
        deriv_queue[x][7+str_len(deriv_queue[x-2])+str_len(recons_queue[x-1])+str_len(deriv_queue[x-1])+str_len(recons_queue[x-2])+str_len(recons_queue[x-1])] = '2';
"""

int main()
{
    
    return 0;
}