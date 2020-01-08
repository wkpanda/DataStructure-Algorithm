#include<stdio.h>
#include<stdlib.h>

typedef struct Node* PtrNode;
typedef PtrNode Position;
typedef PtrNode List;

struct  Node{
    int ele;
    Position Pre;
    Position Next;
};

List InitLinkList(List L)
{
    L = (List)malloc(sizeof(List)); //创建链表第一个结点
    L->ele=0;
    L->Next=NULL;
    L->Pre = NULL;
}

void Insert(int x,List L,Position P)
{
    List tmpCell;
    tmpCell = (List)malloc(sizeof(struct Node));
    if(tmpCell == NULL)
        return;
    tmpCell->ele = x;
    tmpCell->Next = P->Next;
    if(tmpCell->Next != NULL)
    {
        tmpCell->Next->Pre = tmpCell;
    }

    tmpCell->Pre = P;
    P->Next = tmpCell;
 

}

Position FindPrevious(int x,List L)
{
    Position p;
    p = L->Next;
    while (p->Next!=NULL&&p->Next->ele!=x)
    {
        p=p->Next;
    }
    return p;
    
}
Position Find(int x,List L)
{
    Position P;
    P = L->Next;
    while(P!=NULL && P->ele != x)
        P= P->Next;
    return P;
}

int IsLast(Position P,List L)
{
    return P->Next == NULL;
}

void Delete(int x,List L)
{
    Position p,tmpCell;
    p = FindPrevious(x,L);
    if(!IsLast(p,L))
    {
        tmpCell = p->Next;
        p->Next = tmpCell->Next;
        tmpCell->Next->Pre = p;
        free(tmpCell);
    }
    
}

int main()
{
    List L = (List)malloc(sizeof(struct Node));
    InitLinkList(L);
    Insert(0,L,L);
    Insert(1,L,L->Next);
    printf("%d\n",L->Next->ele);
    printf("%d\n",L->Next->Next->ele);
    return 0;
}