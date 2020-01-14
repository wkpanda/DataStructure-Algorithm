#include <iostream>
#include <algorithm>
#include <unordered_map>
#include<vector>
using namespace std;

class Solution
{
public:
    int balanceString(string s){
         vector<char> chars{'Q', 'W', 'E', 'R'};
        unordered_map<char,int> cnt;
        for(char ch:s)
            ++cnt[ch];
        int expection=s.size()/4;   //每个字母期望出现的次数
        bool balance=true;
        for(char ch:chars){
            if(cnt[ch]!=expection)
                balance=false;
            cnt[ch]-=expection; 
        }
        if(balance==true)           //不用替换就已经平衡
            return 0;
        
        int left=0,right=0,n=s.size(),ans=n;    //滑动窗口，用左右两个指针
        while(left<=right&&right<n){
            --cnt[s[right]];
            bool find=true;         //find表示是否找到可以替换的子字符串
            while(find){            //当找到可以替换的子字符串时，有可能该子字符串的前缀包含了一些无关替换的字符，所以循环检测，每次left指针右移一位
                for(char ch:chars){ //判断目前是否已经找到子字符串
                   if(cnt[ch]>0){   
                       find=false;
                       break;
                   }      
                }  
                if(find==true){         //找到了就计算子字符串长度，找不到就继续找：right++
                    ans=min(ans,right-left+1);
                    ++cnt[s[left++]];
                }
            }
            ++right;
        }
        return ans;

    }
}