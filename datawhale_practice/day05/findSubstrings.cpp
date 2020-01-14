class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        map<string,int> mp;
        vector<int> wstart;
        vector<int> ans;
        if(s.size()==0||words.size()==0) return ans;
        //建立单词->单词个数的映射
        for(int i=0;i<(int)words.size();i++)
            mp[words[i]]++;
        //分割出所有候选单词
        int wlen=(int)words[0].length();
        for(int i=0;i+wlen<=(int)s.size();i++){
            string ss=s.substr(i,wlen);
            int id=mp[ss];
            if(id) wstart.push_back(i);
        }
        //滑动窗口
        int wnum=(int)words.size();
        for(int i=0;i+wnum<=(int)wstart.size();i++){
            map<string,int> window;
            int cnt=0;
            for(int j=i;j<(int)wstart.size()&&wstart[j]<=wstart[i]+cnt*wlen&&cnt<wnum;j++)
                if(wstart[j]==wstart[i]+cnt*wlen) {
                    ++window[s.substr(wstart[j],wlen)];
                    ++cnt;
                }
            bool valid=true;
            for(auto it=mp.begin();it!=mp.end();it++)
                if(window[it->first]!=it->second) {valid=false; break;}
            if(valid) ans.push_back(wstart[i]);
        }
        return ans;
    }
};
