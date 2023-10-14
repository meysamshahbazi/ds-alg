#include<iostream>
#include<cstring>	// memset
using namespace std;

class trie
{
private:
    static const int MAX_CHAR = 26;
    trie* child[MAX_CHAR];
    bool isLeaf{};

public:
    trie() 
    {
        memset(child, 0, sizeof(child));
    }

    void insert_recur(string str, int idx = 0)
    {
        if (idx == (int) str.size())
            isLeaf = true;
        else {
            int cur = str[idx] -'a';
            if(child[cur] == 0)
                child[cur] = new trie();
            child[cur]->insert_recur(str, idx + 1);
        }
    }
    // hw1 p1
    void insert(string str)
    {
        trie* root = this;
        for (int idx = 0; idx < (int) str.size(); idx++) {
            int cur = str[idx] - 'a';
            if (root->child[cur] == 0)
                root->child[cur] = new trie();
            root = root->child[cur];
        }
        root->isLeaf = true;
    }
    bool word_exist_recur(string str, int idx = 0)
    {
        if (idx == (int) str.size())
            return isLeaf;
        
        int cur = str[idx] - 'a';
        if (!child[cur])
            return false;
        
        return child[cur]->word_exist_recur(str, idx +1);
    }
    // hw1 p2
    bool word_exist(string str)
    {
        trie* root = this;
        for (int idx = 0; idx < (int)str.size(); idx++) {
            int cur = str[idx] - 'a';
            if(!root->child[cur])
                return false;
            root = root->child[cur];
        }
        return root->isLeaf;
    }
    bool prefix_exist(string str, int idx = 0)
    {
        if (idx == (int) str.size())
            return true;
        
        int cur = str[idx] - 'a';
        if (!child[cur])
            return false;
        
        return child[cur]->prefix_exist(str, idx +1);
    }
};


int main()
{
    trie root;

	root.insert("abcd");
	root.insert("xyz");
	root.insert("abf");
	root.insert("xn");
	root.insert("ab");
	root.insert("bcd");

	cout << root.word_exist("xyz") << "\n";
	cout << root.word_exist("xy") << "\n";
	cout << root.prefix_exist("xy") << "\n";

    return 0;
}