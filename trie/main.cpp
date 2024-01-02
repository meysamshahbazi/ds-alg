#include<iostream>
#include<cstring>	// memset
#include<vector>
#include <algorithm>
#include<map>
#include <bits/stdc++.h>

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
    // hw1 p1
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
    // https://leetcode.com/problems/replace-words/
    string first_word_prefix(const string &str)
    {
        for (int n = 1; n <= (int) str.size(); n++)
            if(word_exist(str.substr(0,n)))
                return str.substr(0,n);
        
        return str;
    }

    string replaceWords(vector<string>& dictionary, string sentence) 
    {
        insert(dictionary);
        stringstream ss(sentence);
        string s;
        string res;
        while (getline(ss, s, ' ')) {
            // store token string in the vector
            res += first_word_prefix(s)+" ";
        }

        return res;
    }
    void get_all_strings(vector<string> &res, string sub="")
    {
        if(isLeaf){
            res.push_back(sub);            
        }
        for(int i = 0; i < MAX_CHAR; i++) {
            if(child[i]){
                child[i]->get_all_strings(res, sub + (char)(i+'a'));
            }
        }
    }
    void auto_complete(const string &str, vector<string>& res)
    {
        trie* root = this;
        for (int idx = 0; idx < (int)str.size(); idx++) {
            int cur = str[idx] - 'a';
            if(!root->child[cur])
                return;
            root = root->child[cur];
        }
        root->get_all_strings(res,str);
    }
    // https://leetcode.com/problems/implement-magic-dictionary
    bool word_exist_with_1_change2(string searchWord)
    {
        trie* root = this;
        for (int idx = 0; idx < (int)searchWord.size(); idx++) {
            int cur = searchWord[idx] - 'a';
            if(!root->child[cur]) {
                for(int i = 0; i < MAX_CHAR; i++) {// check if remining part of str exist as suffix!
                    if(root->child[i] && root->child[i]->word_exist(searchWord.substr(idx+1,searchWord.length()-idx-1)))
                        return true;
                }
                return false;
            }
            root = root->child[cur];
        }

        return false;
    }
    bool word_exist_with_1_change(string searchWord)
    {
        trie* root = this;
        for (int idx = 0; idx < (int)searchWord.size(); idx++) {
            for(char c = 'a'; c <= 'z'; c++) {
                if (searchWord[idx] != c) {
                    string changedWord = searchWord;
                    changedWord[idx] = c;
                    if (word_exist(changedWord))
                        return true;
                }
            }
        }

        return false;
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


// https://leetcode.com/problems/design-add-and-search-words-data-structure/

// https://leetcode.com/problems/implement-trie-prefix-tree/

// https://leetcode.com/problems/word-search-ii/


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
    // 
    trie hw1p2;
    vector<string> vec = {"xyz", "xyzea", "a", "bc"};
    hw1p2.insert(vec);
    cout<<hw1p2.first_word_prefix("x")<<endl;
    cout<<hw1p2.first_word_prefix("xyzabc")<<endl;
    trie leetcode;
    vector<string> dictionary = {"cat","bat","rat"};
    cout<<leetcode.replaceWords(dictionary,"the cattle was rattled by the battery")<<endl;
    dictionary = {"a","b","c"};
    cout<<leetcode.replaceWords(dictionary,"aadsfasf absbs bbab cadsfafs")<<endl;
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
    // hw2 p1
    cout<<"--------------\n";
    vector<string> res;
    root.get_all_strings(res);
    for(auto r:res)
        cout<<r<<"\n";
{
    trie tree;
    cout<<"--------------\n";
	tree.insert("abcd");
	tree.insert("xyz");
	tree.insert("a");
	tree.insert("ab");
	tree.insert("xyzw");
	tree.insert("bcd");
    tree.insert("abx");
    tree.insert("abyz");

	vector<string> res;
	tree.get_all_strings(res);
	for (int i = 0; i < (int) res.size(); ++i)
		cout << res[i] << "\n";

    cout<<"--------------\n";
    vector<string> res2;
    tree.auto_complete("ab",res2);
    for (int i = 0; i < (int) res2.size(); ++i)
		cout << res2[i] << "\n";
}
    cout<<"--------------\n";
    trie hw2p3;
    hw2p3.insert("hello");
    hw2p3.insert("leetcode");
    hw2p3.insert("hallo");
    cout<<hw2p3.word_exist_with_1_change("hello")<<endl;
    cout<<hw2p3.word_exist_with_1_change("hhllo")<<endl;
    cout<<hw2p3.word_exist_with_1_change("hell")<<endl;
    cout<<hw2p3.word_exist_with_1_change("leetcoded")<<endl;
    // cout<<hw2p3.word_exist_with_1_change("hello")<<endl;
    // cout<<hw2p3.word_exist_with_1_change("hexlo")<<endl;
    // cout<<hw2p3.word_exist_with_1_change("xello")<<endl;
    // cout<<hw2p3.word_exist_with_1_change("xyllo")<<endl;

    return 0;
}