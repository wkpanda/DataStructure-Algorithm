#include<stdio.h>
#include<stdlib.h>

int top = -1;   //-1表示栈为空

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

int main()
{
    int stack[3];
    push(stack,5,3);
    push(stack,6,3);
    push(stack,7,3);
    push(stack,8,3);

    printf("%d\n",topElement(stack));
    pop(stack);
    printf("%d\n",topElement(stack));

    return 0;
}