#define MaxSize         1000//储存数据元素的最大个数
typedef struct SNode *Stack;
struct Snode
{
    int Data[MaxSize];
    int Top;
};

//入栈
void push(Stack Ptrs,int item)
{
    if (Ptrs->Top == MaxSize-1)
    {
        printf("堆栈满");
        return;
    }
    else
    {
        Ptrs->Data[++(Ptrs->Top)] = item;
        return;
    }  
}

//出栈
void pop(Stack Ptrs)
{
    if(Ptrs->Top==-1)
    {
        printf("栈是空的");
    }
    else
    {
        return Ptrs->Data[Ptrs->Top--];
    }
    
}