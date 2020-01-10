# Stack Data Structure

Stack is a linear structure which follows a particular order in which the operations are preformed. The order may be LIFO(Last In First Out) or FILO(First In Last Out).

There are many real-life examples of a stack. Consider an example of plates stacked over one another in the canteen.The plate which is on the top is the first to be removed,i.e. the plate which has been placed at the bottommost position remains in the stack for the longest period of time. So, it can be simply seen to follow LIFO/FILO order.

## Features of stacks
- Dynamic data structures
- Do not have a fixed size
- Do not consume a fixed amount of memory
- Size of stack changes with each push() and pop() operation.Each push() and pop() operation increases and decreases the size of the stack by 1,respectively.
  
A stack can be visualized as follows:
![top](https://he-s3.s3.amazonaws.com/media/uploads/9a74c87.png) 

## perations:
push(x): Insert element x at the top of a stack
```c
void push(int stack[],int x,int n)
{
    if(top == n-1)
    {
        printf("Stack is full!");
    }
     else
    {
        top ++ ;
        stack[top] = x;
    }
    
}
```
pop( ): Removes an element from the top of a stack.
```c
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
```
topElement ( ): Access the top element of a stack
```c
int topElement(int stack[])
{
    return stack[top];
}
```

## Implementation by list
```c
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
```

## Implentation by LinkedList
```c
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
```

## 火车车厢重排问题
一列货运列车共有n节车厢，每节车厢将停放在不同的车站。假定n个车站的编号分别为1 ~n，货运列车按照第n站至第1站的次序经过这些车站。车厢的编号与它们的目的地相同。为了便于从列车上卸掉相应的车厢，必须重新排列车厢，使各车厢从前至后按编号1到n的次序排列。当所有的车厢都按照这种次序排列，在每个车站只需卸掉最后一节车厢即可。我们在一个转轨站里完成车厢的重排工作，在转轨站中有一个入轨、一个出轨和k个缓冲铁轨（位于入轨和出轨之间）。下图给出了一个转轨站，其中有k= 3个缓冲铁轨H1，H2和H3。开始时，n节车厢的货车从入轨处进入转轨站，转轨结束时各车厢从右到左按照编号1至编号n的次序离开转轨站（通过出轨处）。在图(a) 中，n= 9，车厢从后至前的初始次序为5，8，1，7，4，2，9，6，3。图(b) 给出了按所要求的次序重新排列后的结果。
![a](https://camo.githubusercontent.com/86edbf1123e9773856c1b48c8170d68832d2f622/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f32303139313232323231353835393937342e706e67)
### 问题分析
对于给定序列，我们可以依次从左至右遍历序列，若遇到需要输出的编号，则直接输出；否则，将其放入缓冲铁轨（堆栈）中。
从而引出以下问题：

1. 需要输出的编号怎样设置？——-初始需要输出的编号为1，此后只要输出一个（车厢）编号，则下一步需要输出的编号+1；

2. 怎么将无法直接输出的车厢编号放入缓冲铁轨？
设想给定k个缓冲铁轨（建立k个堆栈），编号为1~k。初始时每个缓冲铁轨（堆栈）都为空。当原始序列中的火车车厢编号无法直接输出时，将它压入第i个栈的条件为：
（1）此栈为空；
（2）此栈不为空，并且此栈的栈顶元素大于需要压入的车厢编号，同时，此栈的栈顶元素在所有的栈顶元素中是最小的。
3. 如何判断此栈顶元素是否是所有栈顶元素中的最小值？——已知k个栈，那么依次可以获取这k个栈的栈顶元素，定义最小栈顶元素值为min_value，最小元素所在的栈的编号为min_stack。初始时，设定min_value=n+1（即大于任何火车车厢编号）,min_stack=0。在遍历所有栈的过程中，根据入栈条件依次更新min_value和min_stack的值。

```cpp
#include<iostream>
#include<stack>

using namespace std;
void FindInStack(int &min_value,int &min_stack,stack<int> *s,int k,int n);
bool ArrangeCarriage(int c,int &min_stack,int &min_value, stack<int> *S,int k,int n); //参数n为当前需要放入的车厢索引值，s为缓冲铁轨，k为缓冲铁轨数


bool ArrangeCarriages(int *a,int n,int k)    //数组a为入站前车厢顺序,n为车厢数,k为缓冲轨道数
{
    int NowNeed = 1;        //现在需要出轨的车厢编号
    stack<int> *s;
    s = new stack<int>[k+1];
    int min_stack,min_value = n+1;  //min_stack为最小的缓冲轨道的编号,min_value是所有缓冲铁轨上的最小值,初始值为n+1,即所有车厢编号的最大值
    for(int i=1;i<=n;i++)
    {
        if(a[i]==NowNeed)   //如果第i个车厢正好是当前需要出轨的车厢,则输出
        {
            cout<<"Move car "<<a[i]<<" from input to output"<<endl;
            NowNeed++;
            while (min_value == NowNeed)
            {
                FindInStack(min_value,min_stack,s,k,n);
                NowNeed++;
            }
        }
        else
        {
            if(!ArrangeCarriage(a[i],min_stack,min_value,s,k,n))
            {
                return false;
            }
        }
        
    }
    return true;
}

//从缓冲轨道中找出需要的火车索引
//注意:min_value&min_stack都是变量的索引
void FindInStack(int &min_value,int &min_stack,stack<int> *s,int k,int n)
{
    s[min_stack].pop();
    cout<<"Move car "<<min_value<<" from holding track "<<min_stack<<" to output"<<endl;
    min_value =n+2;
    //更新最优缓冲轨道编号和当前所有缓冲轨道中的最小车厢编号
    for(int i=1;i<=k;i++)
    {
        if(!s[i].empty() && s[i].top()<min_value)
        {
            min_value = s[i].top();
            min_stack = i;
        }
    }
}

//向缓冲轨道中放置车厢
bool ArrangeCarriage(int c,int &min_stack,int &min_value, stack<int> *S,int k,int n) //参数n为当前需要放入的车厢索引值，s为缓冲铁轨，k为缓冲铁轨数
{
    int BestTrack = 0;
    int BestTop = n+1;
     for (int i = 1; i <= k; i++)           //遍历每个缓冲铁轨
    {   
        if (!S[i].empty()) {             //若缓冲铁轨不为空
            //若当前缓冲铁轨的栈顶元素大于当前要放置的车厢编号，并且其栈顶元素小于当前缓冲铁轨中的最小编号
            //则更新最优缓冲铁轨编号和缓冲铁轨中的最小车厢编号
            if (S[i].top() > c && BestTop > S[i].top()) 
            {                                             
                BestTop = S[i].top();
                BestTrack = i;
            }
        }
        else   //若当前缓冲铁轨为空，并且bestTrack值仍为初始值，即没有被改动，则更新最优缓冲铁轨编号
            if(!BestTrack)
                BestTrack = i;
    }
    //如果没有符合条件的缓冲铁轨，则不能继续放置，意味着不能完成车厢排序工作
    if (BestTrack == 0) return false;
    //若程序能继续运行，则将当前的待放置车厢入栈至最优缓冲铁轨中
    S[BestTrack].push(c);
    cout << "Move car  " << c << " from input to holding track  "<< BestTrack << endl;
    //更新当前的所有缓冲铁轨的最小值和最优的缓冲铁轨编号
    //注意min_value和min_stack都是通过引用方式访问的，即在函数中的变化会导致变量值的变化
    if (c < min_value)
    {
        min_value = c;
        min_stack = BestTrack;
    }
    return true;
}

int main()
{
    int a[] = { 0,5,8,1,7,4,2,9,6,3 };
    cout << ArrangeCarriages(a, 9, 3)<< endl;
    return 0;
}
```
输出:
```
Move car  5 from input to holding track  1
Move car  8 from input to holding track  2
Move car 1 from input to output
Move car  7 from input to holding track  2
Move car  4 from input to holding track  1
Move car 2 from input to output
Move car  9 from input to holding track  3
Move car  6 from input to holding track  2
Move car 3 from input to output
Move car 4 from holding track 1 to output
Move car 5 from holding track 1 to output
Move car 6 from holding track 2 to output
Move car 7 from holding track 2 to output
Move car 8 from holding track 2 to output
Move car 9 from holding track 3 to output
1
```