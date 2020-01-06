#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>


int n,*array = 0,j=0;
void DAInput()
{
    int i = 0,num = 0;
    scanf("%d",&n);
    //动态分配内存
    array = (int *)malloc(sizeof(int)*n);
    
    if(array == 0)
    {
        printf("error");
    }

    //动态输入数组
    for(i=2;i<=n;i++)
    {
        if(i%5==0||i%7==0)
        {
            array[j]=i;
            j++;
        }
    }
}

void DAOutpu(){
    for(int i=0;i<j;i++)
        printf("%d ",array[i]);
}

int main()
{
    DAInput();
    DAOutpu();
    
    free(array);
    return 0;
}