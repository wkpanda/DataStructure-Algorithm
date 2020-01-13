
//PTA02-线性结构1 两个有序链表序列的合并
//L1和L2是给定的带头结点的单链表，其结点存储的数据是递增有序的；
// 函数Merge要将L1和L2合并为一个非递减的整数序列。应直接使用原序列中的结点，
// 返回归并后的带头结点的链表头指针。

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Merge(List L1,List L2)
{
    if(L1 == NULL || L2 == NULL) return NULL;
    List l1 = L1->Next;
    List l2 = L2->Next;
    List tmp = (List)malloc(sizeof(struct Node));
    List res = tmp;
    while(l1 != NULL && l2 != NULL )
    {
        if(l1->Data<=l2->Data)
        {
            tmp->Next= l1;
            tmp=l1;
            l1=l1->Next;
        } else{
            tmp->Next = l2;
            tmp = l2;
            l2=l2->Next;
        }
    }
    tmp->Next = l1?l1:l2;
    L1->Next = NULL;
    L2->Next=NULL;
    return res;
}