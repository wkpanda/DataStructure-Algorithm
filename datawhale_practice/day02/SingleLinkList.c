#include<stdio.h>
#include<stdlib.h>

typedef struct Node* PtrNode;
typedef PtrNode List;
typedef PtrNode Position;

struct Node {
    int ele;
    Position next;
};

void InitLinkList(List L)
{
    L->ele=0;
    L->next=NULL;
}

int IsEmpty(List L)
{
    return L->next==NULL;
}

Position Find(int x,List L)
{
    Position p;
    p = L->next;
    while(p!=NULL&&p->ele!=x)
        p = p->next;
    return p;
}

Position FindPrevious(int x,List L)
{
    Position p;
    p = L->next;
    while (p->next!=NULL&&p->next->ele!=x)
    {
        p=p->next;
    }
    return p;
    
}

int IsLast(Position p,List L)
{
    return p->next == NULL;
}

void Delete(int x,List L)
{
    Position p,tmpCell;
    p = FindPrevious(x,L);
    if(!IsLast(p,L))
    {
        tmpCell = p->next;
        p->next = tmpCell->next;
        free(tmpCell);
    }
    
}

void Insert(int x,List L,Position p)
{
    Position tmpCell;
    tmpCell = malloc(sizeof(struct Node));
    if(tmpCell == NULL)
        return ;
    tmpCell->ele = x;
    tmpCell->next = p->next;
    p->next = tmpCell;
}
void PrintLinkList(List L)
{
    Position p;
    p = L->next;
    while(p!=NULL)
    {
        printf("%d ",p->ele);
        p = p->next;
    }
}
int main()
{
    List L = (List)malloc(sizeof(struct Node));
    InitLinkList(L);
    Insert(0,L,L);
    Insert(1,L,L->next);
    printf("%d\n",L->next->ele);
    printf("%d\n",L->next->next->ele);
    printf("%d\n",FindPrevious(1,L)->ele);
    Delete(1,L);
    Insert(2,L,L->next);
    PrintLinkList(L);
    return 0;
}