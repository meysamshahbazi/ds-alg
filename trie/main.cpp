#include<iostream>
#include<cstring>	// memset
#include<vector>
#include <algorithm>
#include<map>

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
    void insert(const vector<string> &vec)
    {
        for (auto &v:vec)
            insert(v);
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
    string first_word_prefix(const string &str)
    {
        for (int n = 1; n <= (int) str.size(); n++)
            if(word_exist(str.substr(0,n)))
                return str.substr(0,n);
        
        return str;
    }
    bool suffix_exist(string str)
    {

    }
};

class trieHw1p3
{
private:
    trie tr;
public:
    void insert(string str)
    {
        reverse(str.begin(),str.end());
        cout<<str<<endl;
        tr.insert(str);
    }
    bool suffix_exist(string str)
    {
        reverse(str.begin(),str.end());
        return tr.prefix_exist(str);
    }
};


class TrieMap
{
private:
    map<char,TrieMap*> child;
    bool isLeaf{};
public:
    TrieMap() 
    {
    }
    void insert(string str)
    {
        TrieMap* root = this;
        for (int idx = 0; idx < (int) str.size(); idx++) {
            char cur = str[idx];
            if (!root->child.count(cur))
                root->child[cur] = new TrieMap();

            root = root->child[cur];
        }
        root->isLeaf = true;
    }
    bool word_exist(string str)
    {
        TrieMap* root = this;
        for (int idx = 0; idx < (int)str.size(); idx++) {
            char cur = str[idx];
            if(!root->child.count(cur))
                return false;
            root = root->child[cur];
        }
        return root->isLeaf;
    }
    bool prefix_exist(string str, int idx = 0)
    {
        if (idx == (int) str.size())
            return true;
        
        char cur = str[idx];
        if (!child.count(cur))
            return false;
        
        return child[cur]->prefix_exist(str, idx +1);
    }
};


class TriePath
{
private:
    map<string,TriePath*> child;
    bool isLeaf{};
public:
    TriePath() 
    {
    }
    // void insert(string str)
    void insert(const vector<string> &path)
    {
        TriePath* root = this;
        for (int idx = 0; idx < (int) path.size(); idx++) {
            string cur = path[idx];
            if (!root->child.count(cur))
                root->child[cur] = new TriePath();

            root = root->child[cur];
        }
        root->isLeaf = true;
    }

    // bool prefix_exist(string str, int idx = 0)
    bool subpath_exist(const vector<string> &path, int idx = 0)
    {
        if (idx == (int) path.size())
            return true;
        
        string cur = path[idx];
        if (!child.count(cur))
            return false;
        
        return child[cur]->subpath_exist(path, idx +1);
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

    // hw1 p2
    trie hw1p2;
    vector<string> vec = {"xyz", "xyzea", "a", "bc"};
    hw1p2.insert(vec);
    cout<<hw1p2.first_word_prefix("x")<<endl;
    cout<<hw1p2.first_word_prefix("xyzabc")<<endl;
    // hw1 p3
    {
    cout<<"--------------\n";
    trieHw1p3 root;
    root.insert("abcd");
	root.insert("xyz");
	root.insert("abf");
	root.insert("xn");
	root.insert("ab");
	root.insert("bcd");

	cout << root.suffix_exist("cd") << "\n";
	cout << root.suffix_exist("cc") << "\n"; 
    }
    {
    cout<<"--------------\n";
    // hw1 p4
    TrieMap root;

	root.insert("abcd");
	root.insert("xyz");
	root.insert("abf");
	root.insert("xn");
	root.insert("ab");
	root.insert("bcd");

	cout << root.word_exist("xyz") << "\n";
	cout << root.word_exist("xy") << "\n";
	cout << root.prefix_exist("xy") << "\n";
    }
    {
    // hw1 p5
    cout<<"--------------\n";
    TriePath tree;

	vector<string> path;

	path = {"home", "software", "eclipse"};
	tree.insert(path);

	path = {"home", "software", "eclipse", "bin"};
	tree.insert(path);

	path = {"home", "installed", "gnu"};
	tree.insert(path);

	path = {"user", "mostafa", "tmp"};
	tree.insert(path);

	path = {"user", "mostafa", "tmp"};
	cout << tree.subpath_exist(path) << "\n"; // 1

	path = {"user", "mostafa"};
	cout << tree.subpath_exist(path) << "\n"; // 1

	path = {"user", "mostafa", "private"};
	cout << tree.subpath_exist(path) << "\n"; // 0
    }

    return 0;
}