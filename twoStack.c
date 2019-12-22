
//用一个数组实现两个堆栈，要求最大地利用数组空间，使数组只要有空间，入栈操作就可以成功

#define MaxSize 1000

#include <stdio.h>
#include<stdlib.h>

struct DStack
{
    int Data[MaxSize];
    int Top1;       //堆栈１的栈顶指针
    int Top2;       //堆栈２的栈顶指针
}Ｓ;

S.Top1 = -1;
S.Top2 = MaxSize;

void push(struct DStack *Ptrs,int item,int tag )
{
    //ｔａｇ用来区分放在哪个堆栈，取值为１，２
    if(Ptrs->Top2-Ptrs->Top1 == 1) 
    {
        printf("堆栈满");
        return;
    }
    if(tag ==1 )
    {
        Ptrs->Data[++(Ptrs->Top1)]=item;
    }
    else
    {
        Ptrs->Data[--(Ptrs->Top2)] = item;
    }
    
}

int pop(struct DStack *Ptrs,int item,int tag)
{
    if(tag==1)
    {
        if(Ptrs->Top1==-1)
        {
            printf("堆栈１为空");
            return NULL;
        }
        else
        {
            return Ptrs->Data[(Ptrs->Top1)--];
        }
    }
    else
    {
        if(Ptrs->Top2==MaxSize)
        {
            printf("堆栈２为空");
            return NULL;
        }
        else
        {
            return Ptrs->Data[(Ptrs->Top2)++];
        }
        
    }
    
}

