#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <bits/stdc++.h> 
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/longest-palindromic-substring/
class Solution5 {
    // 1 <= s.length <= 1000
    string str;
    char mem[1001][1001];
public:
    int dp(int start, int end) {
        if (start >= end)
            return 1;
        
        auto &ret = mem[start][end];
        if (ret != -1)
            return ret;
        
        if (str[start] == str[end]) {
            return dp(start + 1, end -1);
        }
        return 0;
    }
    string longestPalindrome(string s) {
        memset(mem, -1, sizeof(mem));
        str = s;
        // for(int i = 0; i < (int) str.size(); i++) 
        //     for(int j = (int) str.size() - 1; j >=0 ; j--) 
        int start = 0;
        int end = (int) str.size() - 1;
        while (end >= start) {
            if (dp(start, end) == 1)
                return str.substr(start, end + 1);
            if (dp(start, end - 1) == 1)
                return str.substr(start, end);
            if (dp(start + 1, end) == 1)
                return str.substr(start + 1, end + 1);

            start++;
            end--;
        }
        return "";
    }
};



int main()
{
    Solution5 s5;
    cout<<s5.longestPalindrome("babad")<<endl;
    cout<<s5.longestPalindrome("cbbd")<<endl;
    return 0;
}