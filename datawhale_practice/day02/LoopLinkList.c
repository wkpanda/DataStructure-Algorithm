#include<stdio.h>
#include<stdlib.h>

typedef struct Node* PtrNode;
typedef PtrNode List;
typedef PtrNode Position;

struct Node{
    int data;
    List Next;
};


void Insert(int x,List L,Position P)
{
    Position tmpCell;
    tmpCell = (List)malloc(sizeof(struct Node));
    tmpCell->data = x;
    tmpCell->Next = P->Next;
    P->Next = tmpCell;
}

void Delete(int x,List L)
{
    Position P = L->Next;
    while(P->Next!=NULL&&P->Next->data!=x)
        P= P->Next;
    Position tmpCell = P->Next;
    P->Next = tmpCell->Next;
    free(tmpCell);
}

void CreatCLLinkList(List L) 
{
    List rear,s;
    rear=L;//rear指针动态指向当前表尾，其初始值指向头结点 
    int flag=1;
    int x;
    printf("Please input data and enter 0 end:\n");
    while(flag)
    {
        scanf("%d",&x);
        if(x!=0)
        {
            s=(List)malloc(sizeof(struct Node));
            s->data=x;
            rear->Next=s;
            rear=s;
        }
        else
        {
            flag=0;
            rear->Next=L;//最后一个节点的next域指向头结点 
        }
    }
}

int main()
{
    List L = (List)malloc(sizeof(struct Node));
    CreatCLLinkList(L);
    Insert(6,L,L);
    printf("%d",L->Next->data);
    // printf("%d",L->Next->Next->data);
    Delete(6,L);
    printf("%d",L->Next->data);
    return 0;

}