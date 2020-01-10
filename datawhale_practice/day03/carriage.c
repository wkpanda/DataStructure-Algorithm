#include<stdio.h>
#include<stdlib.h>

int top = -1;   //-1表示栈为空
int stack[9]={5,8,1,7,4,2,9,6,3};
int stack_buffer[9][3]={0};
void push(int stack[],int x,int n)
{
    if(top == n-1)  //如果条件成立说明栈以及满了
    {
        printf("Stack is full!");
    }
    else
    {
        top ++ ;
        stack[top] = x;
    }
    
}

void pop(int stack[])
{
    if(top == -1)       //栈为空
    {
        printf("Stack is empty!");
    }
    else
    {
        top --;
    }
    
}

int topElement(int stack[])
{
    return stack[top];
}

int IsProgressiveIncrease(int s[])
{
    for(int i=8;i>0;i--)
    {
        if (s[i]>s[i-1])
        {
            continue;
        }
        return 0;        
    }
    return 1;
}

int main()
{
    while (!IsProgressiveIncrease(stack))
    {
        int i=8;
        push(stack_buffer[][1],stack[i],8)
        while(stack[i]>)
    }
    

    return 0;
}