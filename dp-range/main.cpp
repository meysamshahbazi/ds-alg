#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <bits/stdc++.h> 
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/longest-palindromic-substring/
class Solution5 {
    string str;
    char mem[1001][1001];
public:
    int dp(int start, int len) {
        auto &ret = mem[start][len];
        if (ret != -1)
            return ret;

        if (len <= 1)
            return ret = 1;

        if (str[start] == str[start + len - 1]) {
            return ret = dp(start + 1, len - 2);
        }
        return ret = 0;
    }
    string longestPalindrome(string s) {
        memset(mem, -1, sizeof(mem));
        str = s; 
        for (int len = (int) str.size() ; len >= 0; len--)
            for (int start = 0; start <= str.size() - len ; start++)
                if (dp(start, len) == 1)
                    return str.substr(start, len);

        return "";
    }
};



int main()
{
    Solution5 s5;
    cout<<s5.longestPalindrome("0123babad")<<endl;
    cout<<s5.longestPalindrome("cbbd")<<endl;
    cout<<s5.longestPalindrome("a")<<endl;
    cout<<s5.longestPalindrome("ac")<<endl;
    string str = "0123456789";
    // cout<<str.substr(0,4);
    return 0;
}