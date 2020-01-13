#include <iostream>
#include <queue>
#include <string>
#include<unistd.h>
using namespace std;

/* 数组实现循环顺序队列 */
template <typename T>
class CSeqQueue
{
public:
    CSeqQueue(int s = 20);
    ~CSeqQueue();
    bool isEmpty();
    int size();
    bool push(T t);
    T pop();
    T front();
    int maxsize();

private:
    int begin;
    int end;
    int MaxSize;
    int Length;
    T* queue;
};

template<typename T>
CSeqQueue<T>::CSeqQueue(int s) : MaxSize(s)
{
    begin = 0;
    end = 0;
    Length = 0;
    queue = new T[MaxSize];
}
template<typename T>
CSeqQueue<T>::~CSeqQueue()
{
    delete[] queue;
}
template<typename T>
bool CSeqQueue<T>::push(T n)
{
    if (Length == MaxSize)
    {
        throw "队列已满，不能入队!";
        return false;
    }
    queue[end] = n;
    end = (end + 1) % MaxSize;
    Length++;
}
template<typename T>
T CSeqQueue<T>::pop()
{
    if (Length == 0)
    {
        throw "队列为空，不能出队！";
    }
    T data = queue[begin];
    begin = (begin + 1) % MaxSize;
    Length--;
    return data;
}
template<typename T>
T CSeqQueue<T>::front()
{
    if (Length == 0)
    {
        throw "队列为空，不能得到队首元素！";
    }
    return queue[begin];
}
template<typename T>
bool CSeqQueue<T>::isEmpty()
{
    return Length == 0;
}
template<typename T>
int CSeqQueue<T>::size()
{
    return Length ;
}
template<typename T>
int CSeqQueue<T>::maxsize()
{
    return MaxSize;
}

/* 模拟银行服务 */
// 使用顺序存储结构存储银行队列
class CSeqBankQueue: public CSeqQueue<int>
{
public:
    CSeqBankQueue(int size) : Size(size)
    {
        Callnumber = 0;
    }
    int GetCallnumber()
    {
        if (isEmpty() && Callnumber == 0)
            Callnumber = 1;
        else
            Callnumber++;
        return Callnumber;
    }

private:
    int Size;
    int Callnumber;
};
// 服务窗口
class ServiceWindow
{
public:
    CSeqBankQueue *BankQ = new CSeqBankQueue(20);
    void Serivice()
    {
        while (true)
        {
            sleep(6); // for vs
                if (!BankQ->isEmpty())
                {
                    cout << "请" << BankQ->front() << "号到" << 1 << "号窗口！" << endl;
                }
        }
    }

};

class BankQueueApp
{
public:
    void main()
    {
        int count;
        cout << "请输入队列可容纳人数：" << endl;
        cin >> count;
        bankQueue = new CSeqBankQueue(count);
        ServiceWindow* serviceWindows = new ServiceWindow;
        serviceWindows->BankQ = bankQueue;
        while (true)
        {
            cout << "请点击触摸屏获取号码：" << endl;
            int num;
            cin >> num;
            if (bankQueue != NULL && bankQueue->size() < bankQueue->maxsize())
            {
                int callnumber = bankQueue->GetCallnumber();
                cout << "您的号码是：" << callnumber << "，你前面有" << bankQueue->size() << "位，请等待" << endl;
                bankQueue->push(callnumber);
            }
            else
            {
                cout << "现在业务繁忙，请稍后再来！" << endl;
            }
        }
    }
private:
    CSeqBankQueue* bankQueue;
};

int main()
{
    BankQueueApp bankQueueApp;
    bankQueueApp.main();

    system("pause");
    return 0;
}