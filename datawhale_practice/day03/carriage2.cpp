//#include "stdafx.h"
#include <iostream>
#include <queue>
 
using namespace std;
 
template <class T>
void PrintfNum(T a[], const int & n);
 
bool Hold(queue<int> q[], int n,int totalQueue){
    for(int i=0;i<totalQueue;++i){
        if(q[i].empty() || (!q[i].empty() && q[i].back() < n)){
            cout << "holding track " << i << " hold car " << n  << endl;
            q[i].push(n);
            return true;// we already find a holding track, so break the loop. 
        }
    }
    return false;
}
 
void OutPut(queue<int> q[], int n, int totalQueue,int& min){
    for(int i = 0;i< totalQueue;++i){
        if(!q[i].empty() && q[i].front() == min){
            cout << "Move car " << q[i].front() << " from holding track " << i << " to output" << endl;
            q[i].pop();
            ++min;
            i = -1;// find next car from the first holding track 0
        }
    }
}
 
int main(int argc, char* argv[])
{
    const int NUM = 9;
    const int QUEUENUM = 2;
    queue<int> q[QUEUENUM];
    int min = 1;
    int a[NUM] = {5,8,1,7,4,2,9,6,3};
    PrintfNum(a,NUM);
 
    for(int i = NUM - 1; i >=0 ;--i){
        if(a[i] == min){
            cout << "Move car " << a[i] << " from input to output" << endl;
            ++min;
            //move cars from holding tracks
            OutPut(q,a[i],QUEUENUM,min);
        }else{// move cars to holding tracks
            if(!Hold(q, a[i] ,QUEUENUM)){
               cout << "Not enough holding track" << endl;
               break;
            }
        }
    }
    return 0;
}
 
template <class T>
void PrintfNum(T a[], const int & n){
    for(int i = 0; i < n; ++i){
        cout << a[i] << ",";
    }
    cout << endl;
}
