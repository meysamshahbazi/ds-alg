#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <bits/stdc++.h> 
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/edit-distance/
class Solution72 {
    string m_word1, m_word2;
    int mem[501][501];
public:
    int minDistance(int idx1, int idx2) {
        if (idx1 == m_word1.size() || idx2 == m_word2.size())
            return (int) m_word1.size() - idx1 + (int) m_word2.size() - idx2;
        
        auto &ret = mem[idx1][idx2];
        if (ret != -1)
            return ret;
        
        if (m_word1[idx1] == m_word2[idx2])
            return minDistance(idx1 + 1, idx2 + 1);
        
        // option 1: delete idx letter from word 1
        int choice1 = 1 + minDistance(idx1 + 1, idx2);
        // Insert a character 
        int choice2 = 1 + minDistance(idx1, idx2 + 1);
        // replace
        int choice3 = 1 + minDistance(idx1 + 1, idx2 + 1);

        return ret = min(choice1, min(choice2, choice3));
    }
    int minDistance(string word1, string word2) {
        memset(mem, -1, sizeof(mem));
        m_word1 = word1;
        m_word2 = word2;
        return minDistance(0,0);
    }
};

// https://leetcode.com/problems/integer-break/
class Solution343 {
public:
    int integerBreak(int n) {
        
    }
};


int main()
{
    Solution72 s72;
    string word1, word2;
    word1 = "horse", word2 = "ros";
    cout << s72.minDistance(word1, word2) << endl;
    word1 = "intention", word2 = "execution";
    cout << s72.minDistance(word1, word2) << endl;
    return 0;
}
