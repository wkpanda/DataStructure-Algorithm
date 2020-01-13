#include <iostream>
#define MAXSIZE 10000010

using namespace std;
struct Node
{
    int Data;
    int Next;
}  Node[MAXSIZE];

int List[MAXSIZE];

int main() {
    int First,n,k;  //输入第一个节点的地址以及节点数，翻转位置
    cin>>First>>n>>k;
    int Address,Data,Next;
    for(int i=0;i<n;i++)
    {
        cin>>Address>>Data>>Next;
        Node[Address].Data=Data;
        Node[Address].Next=Next;
    }
    int p = First,sum=0;
    while(p!=-1)    //排序并用sum记录有效节点的数量即在链表中的数量
    {
        List[sum++]=p;
        p=Node[p].Next;
    }
    for(int i=0;i<k;i++)
    {
        for(int j=3;j>=i;j--)
        {

            if(j-1-i >= 0)
            {
                int tmpNextAddr = Node[List[j]].Next;
                Node[List[j]].Next = Node[List[j-1]].Next;
                Node[List[j-1]].Next = tmpNextAddr;
            }
            if(j-2-i >= 0)
                Node[List[j-2]].Next = List[j];
            if(j-1-i >= 0)
            {
                int tmp = List[j];
                List[j] = List[j-1];
                List[j-1] = tmp;
            }

        }
    }
    for(int i=0;i<sum;i++)
    {
        printf("%.5d %.5d %.5d\n",List[i],Node[List[i]].Data,Node[List[i]].Next);
    }

}