#include<iostream>
#include<string>

using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int l(0),r(0),length(0),result(0);
        int size = s.size();
        while (r < size)
        {
            char tmpChar = s[r];
            for(int i=l;i<r;i++)
            {
                if (tmpChar == s[i])
                {
                    l=i+1;
                    length = r-l;
                    break;
                }                               
            }
            r++;
            length++;
            result = max(result,length);
        }
        return result;
        
    }

};

