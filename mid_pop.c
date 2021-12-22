#include <stdio.h>
#include <stdlib.h>

int str_len(char *s)
{
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

int main()
{
    char **queue = malloc(5 * sizeof(char *));
    int i;

    for(i=0;i<5;i++)
    {
        queue[i] = malloc(sizeof(char));
    }
    queue[3] = realloc(queue[3], 2 * sizeof(char));

    queue[0][0] = 'a';
    queue[1][0] = 'b';
    queue[2][0] = 'c';
    queue[3][0] = 'd';queue[3][1] = 'd';
    queue[4][0] = 'e';

    mid_pop(queue, 5, 2);
    mid_pop(queue, 4, 1);

    for(i=0;i<5;i++)
    {
        printf("%s\n",queue[i]);
    }


    return 0;
}