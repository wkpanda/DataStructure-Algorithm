# Linked List

A linked list is a linear data structure where each element is a separate object.
Linked list elements are not stored at contiguous location; the elements are linked using pointers.

Each node of a list is made up of two items - the data and a reference to the next node. The last node has a reference to null. The entry point into a linked list is called the head of the list. It should be noted that head is not a separate node, but the reference to the first node. If the list is empty then the head is a null reference.

![linklist](https://s3-us-west-2.amazonaws.com/ib-assessment-tests/problem_images/singly-ll.png)

## Implement of LinkedList
```c
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
```

## Doubly linked list
A doubly linked list , also known as a doubly linked list , is a type of linked list . There are two pointers in each data node, which point to direct successor and direct predecessor, respectively. Therefore, starting from any node in the doubly linked list, you can easily access its predecessor and successor nodes. Generally we construct a doubly circular linked list .
![doublylinkedlist](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5e/Doubly-linked-list.svg/610px-Doubly-linked-list.svg.png)

```c
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
```
## Circular Linked List
Circular Linked List is a variation of Linked list in which the first element points to the last element and the last element points to the first element. Both Singly Linked List and Doubly Linked List can be made into a circular linked list.
### Singly Linked List as Circular
In singly linked list, the next pointer of the last node points to the first node.
![dll1](https://www.tutorialspoint.com/data_structures_algorithms/images/singly_circular_linked_list.jpg)
Singly Linked List as Circular Linked List
### Doubly Linked List as Circular
In doubly linked list, the next pointer of the last node points to the first node and the previous pointer of the first node points to the last node making the circular in both directions.
![dll2](https://www.tutorialspoint.com/data_structures_algorithms/images/doubly_circular_linked_list.jpg)
```c
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
```
# 练习部分

## 1. 合并两个有序链表

https://leetcode-cn.com/problems/merge-two-sorted-lists/

将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

示例：

输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4

### 思路
> 分别维护两个链表的指针,对指针指向的结点数据比较
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
    if(!l1 && !l2)
            return NULL;
        if(!l1 && l2)
            return l2;
        if(l1 && !l2)
            return l1;
    //  l1 = l1->next;
    //  l2 = l2->next;
    struct ListNode* tmp = (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode*  res = tmp;
    tmp->next = NULL;
    while(l1 != NULL && l2 != NULL )
    {
        if(l1->val<=l2->val)
        {
            tmp->next= l1;
            tmp=l1;
            l1=l1->next;
        } else{
            tmp->next = l2;
            tmp = l2;
            l2=l2->next;
        }
    }
    tmp->next = l1?l1:l2;
    l1 = NULL;
    l2 =NULL;
    return res->next;
}
```
![](21&#32;合并两个有序链表.png)
## 2. 删除链表的倒数第N个节点

https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/

给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。

示例：

给定一个链表: 1->2->3->4->5, 和 n = 2.

当删除了倒数第二个节点后，链表变为 1->2->3->5.
说明：

给定的 n 保证是有效的。

进阶：

你能尝试使用一趟扫描实现吗？

### 思路
> 维护两个指针,一个从头结点开始,另一个从第n+1个结点开始,当后一个指针指向表尾时,前面的指针指向的就是倒数第n个结点
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
     struct ListNode* dummyHead = (struct ListNode *)malloc(sizeof(struct ListNode));
        dummyHead->next = head;

        struct ListNode* p = dummyHead;
        struct ListNode* q = dummyHead;
        for( int i = 0 ; i < n + 1 ; i ++ ){
            q = q->next;
        }

        while(q){
            p = p->next;
            q = q->next;
        }

        struct ListNode* delNode = p->next;
        p->next = delNode->next;
        free(delNode);

        struct ListNode* retNode = dummyHead->next;
        free(dummyHead);

        return retNode;

}
```
![](19&#32;删除链表的倒数第N个节点.png)

## 3. 旋转链表

https://leetcode-cn.com/problems/rotate-list/

给定一个链表，旋转链表，将链表每个节点向右移动k个位置，其中k是非负数。

示例 1:

输入: 1->2->3->4->5->NULL, k = 2
输出: 4->5->1->2->3->NULL

解释:
向右旋转 1 步: 5->1->2->3->4->NULL
向右旋转 2 步: 4->5->1->2->3->NULL
示例 2:

输入: 0->1->2->NULL, k = 4
输出: 2->0->1->NULL

解释:
向右旋转 1 步: 2->0->1->NULL
向右旋转 2 步: 1->2->0->NULL
向右旋转 3 步: 0->1->2->NULL
向右旋转 4 步: 2->0->1->NULL

### 思路
> 可以看做将单链表改成循环链表之后,重新选择头结点与尾结点
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* rotateRight(struct ListNode* head, int k){
    if(head == NULL) return head;
        
        int N = 1;
        struct ListNode* tail = head;
        while(tail -> next) {
            tail = tail -> next;
            N++;
        }
        tail -> next = head; // 做环
        
        k = N - k % N; // head的相对移动数
        // 对head少移动1位，得到新表尾指针的位置
        while(k - 1) {
            head = head -> next;
            k--;
        }
        tail = head; 
        head = head -> next;
        tail -> next = NULL;
        
        return head;

}
```
![](61旋转链表.png)