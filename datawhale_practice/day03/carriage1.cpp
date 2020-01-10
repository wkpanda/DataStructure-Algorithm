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