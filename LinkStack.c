#include<stdio.h>
#include<stdlib.h>

typedef struct SNode *Stack;
struct SNode{
    int Data;
    struct SNode *Next;
};

Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next=NULL;
    return S;
}

int IsEmpty(Stack S)
{
    return (S->Next==NULL);
}

void push(int item,Stack S)
{
    struct SNode *TmpCell;
    TmpCell = (struct SNode*)malloc(sizeof(struct SNode));
    TmpCell->Data = item;
    TmpCell->Next = S->Next;
    S->Next=TmpCell;
}

int pop(Stack S)
{
    if(S->Next==NULL)
    {
        printf("堆栈为空");
        return NULL;
    }
    else
    {
        int res = S->Next->Data；
        struct SNode *TmpCell;
        TmpCell = S->Next;
        S->Next =TmpCell->Next;
        free(TmpCell);
        return res;        
    }    
}