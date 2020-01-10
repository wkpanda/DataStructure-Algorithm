#include<stdio.h>
#include<stdlib.h>

typedef struct Node* PtrNode;
typedef PtrNode Stack;
typedef PtrNode Position;

struct Node{
    int data;
    Position next;
};

Stack StackInit(Stack s) //创建或清空（初始化）
{
	if (s == NULL) //创建
	{
		s = (Stack)malloc(sizeof(struct Node));
		s->next = NULL;
	}
	else //清空
		while(s->next != NULL)
			pop(s);
	printf("初始化成功");
	return s;
}

void push(Stack L,int x)
{
    Position tmpCell = (Stack)malloc(sizeof(struct Node));
    tmpCell->data = x;
    tmpCell->next = L->next;
    L->next = tmpCell;
}

void pop(Stack L)
{
    if(!L->next)
    {
        printf("栈是空的");
        return;
    }
    else
    {
        Position tmpCell = L->next;
        L->next = tmpCell->next;
        free(tmpCell);
    } 
}

int top(Stack L)
{
    if(!L->next)
    {
        printf("栈是空的");
    }
    else
    {
        return L->next->data;
    } 
}

int main()
{
    Stack s = NULL;
    s = StackInit(s);
    for (int i = 0; i < 5; i++)
    {
        push(s,i);
    }
    printf("\n%d",top(s));
    pop(s);
    printf("\n%d",top(s));
    return 0;    
}