#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>


using namespace std;

int hash_string(string str, int n) {
    long long nn = n;
    long long sum = 0;
    for (int i = 0; i < (int) str.size(); ++i)
        sum = (sum * 26 + str[i] - 'a') % nn;

    return sum % nn;
}

// hw1 p1
int hash_string2(string str, int n)
{
    long long nn = n;
    long long sum = 0;
    // 122-48+1 
    for (int i = 0; i< (int) str.size(); ++i)
        sum = (sum * 75 + str[i] - '0') % nn;

    return sum % nn;
}

// hw1 p2
int hash_fold(string str, int n)
{
    long long nn = n;
    long long sum = 0;

    for (int i = 0; i< (int) str.size(); i += 4) {
        string block = str.substr(i,4);
        sum += hash_string2(block, nn);
        sum %= nn;
    }
    return sum;
}
int hash_num(int value, int n_ = 65407) {
	long long n = n_;
	return (value % n + n) % n;
}

// hw1 p3
struct SomeObject {
	const static int INTERNAL_LIMIT = 2147483647;
	string str1, str2;
	int number;

	// Convert all 3 elements as a hash value
	int hash() {
		// Adding both can result in overflow. Use long long
		long long res = hash_string2(str1 + str2, INTERNAL_LIMIT);
		res += hash_num(number, INTERNAL_LIMIT);
		return res % INTERNAL_LIMIT;
	}
};


struct PhoneEntry
{
    const static int INTERNAL_LIMIT = 65407;
    string name; // key 
    string phone_number; // data

    int hash() {
        return hash_string(name, INTERNAL_LIMIT);
    }
    
    PhoneEntry(string name, string phone_number)
            :name(name), phone_number(phone_number) {
    }
    
    void print() {
        cout << "(" << name << ", " << phone_number << ")  ";
    }
};

class PhoneHashTable {
private:
    int table_size;
    double limit_load_factor;
    vector<vector<PhoneEntry>> table;
public:
    PhoneHashTable(int table_size = 10, double limit_load_factor = 0.75)
            :table_size(table_size), limit_load_factor(limit_load_factor) {
        table.resize(table_size);
    }
    bool get(PhoneEntry &phone) {
        int idx = phone.hash() % table_size;

        for (int i = 0; i < (int) table[idx].size(); i++) {
            if (table[idx][i].name == phone.name) {
                phone = table[idx][i];
                return true;
            }
        }
        return false;
    }
    void put(PhoneEntry phone) {
        int idx = phone.hash() % table_size;

        for (int i = 0; i < (int) table[idx].size(); i++) {
            if (table[idx][i].name == phone.name) {
                table[idx][i] = phone; // update
                return;
            }
        }
        table[idx].push_back(phone);
    }
    double getLeadFactor() {
        int num_of_used = 0;
        for (auto v : table) {
            if (!v.empty())
                num_of_used++;
        }
        return static_cast<double>(num_of_used)/table_size;
    }
    bool remove(PhoneEntry phone) {
        int idx = phone.hash() % table_size;
        for (int i = 0; i < (int) table[idx].size(); i++) {
            if (table[idx][i].name == phone.name) {
                swap(table[idx][i], table[idx].back());
                table[idx].pop_back();
                return true;
            }
        }
        return false;
    }
    // hw1 p4
    void rehashing() 
    {
        vector<vector<PhoneEntry>> table_old = table;
        table.clear();
        table_size = 2 * table_size;
        table.resize(table_size);
    
        for (auto v : table_old){
            for (auto e : v)
                put(e);
        }

    }
    void print_all() {
		for (int hash = 0; hash < table_size; ++hash) {
			if (table[hash].size() == 0)
				continue;

			cout << "Hash " << hash << ": ";
			for (int i = 0; i < (int) table[hash].size(); ++i)
				table[hash][i].print();
			cout << "\n";
		}
	}
};

class PhoneHashTableLL
{
private:
    struct LinkedHashEntry
    {
        PhoneEntry item;
        LinkedHashEntry* next{};
        LinkedHashEntry(PhoneEntry item)
        : item(item) {}
    };
    int table_size;
    vector<LinkedHashEntry*> table { };
public:
    PhoneHashTableLL(int table_size) :table_size(table_size)
    {
        table.resize(table_size);
    }
    void put(PhoneEntry phone) 
    {
        int idx = phone.hash() % table_size;

        if(!table[idx]) {
            LinkedHashEntry* tail = new LinkedHashEntry(phone);
            table[idx] = tail;
            return;
        }
        for(LinkedHashEntry* cur = table[idx]; cur; cur = cur->next){
            if(cur->item.name == phone.name) {
                cur->item = phone;
                return;
            }
            if(!cur->next) {
                LinkedHashEntry* tail = new LinkedHashEntry(phone);
                cur->next = tail;
                return;
            }
        }
    }
    void print_all() {
		for (int hash = 0; hash < table_size; ++hash) {
			if (!table[hash])
				continue;

			cout << "Hash " << hash << ": ";
            for(LinkedHashEntry* cur = table[hash]; cur; cur = cur->next)
				cur->item.print();
			cout << "\n";
            
		}
	}
};

class PhoneHashTableProbe
{
private:
    int table_size;
    vector<PhoneEntry*> table;
    PhoneEntry* deleted{};
public:
    PhoneHashTableProbe(int table_size) 
            : table_size(table_size) {
        table.resize(table_size);
        deleted = new PhoneEntry("","");
    }
    bool put(PhoneEntry phone) {
        int idx = phone.hash() % table_size;
        for (int step = 0; step < table_size; ++step) {
            if (table[idx] == deleted || !table[idx]) {
                table[idx] = new PhoneEntry(phone.name, phone.phone_number);
                return true;
            }
            else if (table[idx]->name == phone.name) {
                table[idx]->phone_number = phone.phone_number;
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }
    bool remove(PhoneEntry phone) {
        int idx = phone.hash() % table_size;

        for (int step = 0; step < table_size; ++step) {
            if (!table[idx])
                break;
            if (table[idx] != deleted && table[idx]->name == phone.name) {
                delete table[idx];
                table[idx] = deleted;
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }

    bool get(PhoneEntry &phone) {
        int idx = phone.hash() % table_size;

        for (int step = 0; step < table_size; ++step) {
            if (!table[idx])
                break;
            if (table[idx] != deleted && table[idx]->name == phone.name) {
                phone.phone_number = table[idx]->phone_number;
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }

    void print_all()
    {
        for( int hash = 0; hash < table_size; ++hash) {
            cout<<hash<<": ";
            if (table[hash] == deleted)
                cout<< "X";
            else if (!table[hash])
                cout<< "E";
            else 
                table[hash]->print();
            cout<<endl;
        }
        cout<<"-------------------------\n";
    }
};

int count_unique_substrings(const string &str)
{
    unordered_set<string> set;
    for (int i = 0; i<str.size(); i++) {
        for (int n = 1; i + n <= str.size(); n++)
            set.insert(str.substr(i,n));
    }
    int sum = 0;
    for (auto s: set)
        sum++;

    return set.size();
}

int count_substrings_match(const string &str1, const string &str2)
{
    unordered_set<string> set1;
    for (int i = 0; i<str1.size(); i++) {
        for (int n = 1; i + n <= str1.size(); n++)
            set1.insert(str1.substr(i,n));
    }

    unordered_set<string> set2;
    for (int i = 0; i<str2.size(); i++) {
        for (int n = 1; i + n <= str2.size(); n++)
            set2.insert(str2.substr(i,n));
    }
    int res = 0;
    for (auto s:set1) {
        if (set2.count(s))
            res++;
    }
    return res;
}


int sum_string(string str)
{
    long long sum = 0;
    for (int i = 0; i< (int) str.size(); ++i)
        sum += ( str[i] - 'a') ;

    return sum;
}

int count_anagram_substrings(const string &str)
{
    int sum = 0;

    for (int n = 1; n <= str.size(); n++){
        unordered_set<int> set;
        for (int i = 0; i+n <= str.size(); i++) {
            set.insert(sum_string(str.substr(i,n)));
        }
        sum += set.size();
    }   

    return sum;   
}

struct Node{
    int data;
    Node * next;

    Node(int data):data(data){} 

};
class LinkedList
{
private:
    Node *head {nullptr};
    Node *tail {nullptr};
public:
    void print()
    {
        Node* cur = head;
        while (cur) {
            cout<<cur->data<<" ";
            cur = cur->next;
        }
        cout<<endl; 
    }
    void insert_end(int value)
    {
        Node * node = new Node(value);
        node->next = nullptr;
        if (head == nullptr) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
    }
    void create_cycle()
    {
        for (int i = 0; i < 4; i++)
            insert_end(i);
        
        Node* now = tail;

        for (int i = 0; i < 3; i++)
            insert_end(i + 14);

        tail->next = now;
    }
    void remove_cylce()
    {
        unordered_set<Node*> set;
        
        Node* cur = head;
        while (cur) {
            set.insert(cur);
            if (set.count(cur->next))
                cur->next = nullptr;
            
            cur = cur->next;
        }
         
    }
};


class PhoneHashTable {
private:
	int table_size;
	vector<PhoneEntry*> table;
	// to mark a cell as deleted
	PhoneEntry *deleted { };
public:
	PhoneHashTable(int table_size) :
			table_size(table_size) {
		table.resize(table_size);
		deleted = new PhoneEntry("", "");
	} //  needs a destructor

	void put(PhoneEntry phone) {
		/*
		 * When to stop?
		 * One might stop when he performs table_size steps
		 * my impression: we better stop when we cycle back to same index
		 *
		 * Computionally, we can see that we can fail to add in both cases
		 * ALTHOUGHT there are still free elements!
		 * This never happens in linear probing
		 *
		 * If we failed to add: then do rehashing and try again
		 * 	which will typically works well (or do rehashing again)		 *
		 */

		int idx = phone.hash() % table_size;
		int step = 0, original_idx = idx;

		do {
			if (table[idx] == deleted || !table[idx]) {
				table[idx] = new PhoneEntry(phone.name, phone.phone_number);
				return;
			} else if (table[idx]->name == phone.name) {
				table[idx]->phone_number == phone.phone_number;
				return;	// update
			}
			++step;
			idx = (original_idx + step * step) % table_size;
		} while (idx != original_idx);	// catch that we repeated

		// If we failed: rehash to increase size, then add this element
		rehashing();
		put(phone);
	}

	bool remove(PhoneEntry phone) {
		int idx = phone.hash() % table_size;
		int step = 0, original_idx = idx;

		do {
			if (!table[idx])
				break;
			if (table[idx] != deleted && table[idx]->name == phone.name) {
				delete table[idx];
				table[idx] = deleted;
				return true;
			}
			++step;
			idx = (original_idx + step * step) % table_size;
		} while (idx != original_idx);	// catch that we repeated
		return false;
	}

	bool get(PhoneEntry &phone) {
		int idx = phone.hash() % table_size;
		int step = 0, original_idx = idx;

		do {
			if (!table[idx])
				break;
			if (table[idx] != deleted && table[idx]->name == phone.name) {
				phone.phone_number = table[idx]->phone_number;
				return true;
			}
			++step;
			idx = (original_idx + step * step) % table_size;
		} while (idx != original_idx);	// catch that we repeated
		return false;
	}

	void rehashing() {
		cout<<"Rehashing\n";
		PhoneHashTable new_table(2 * table_size);

		for (int hash = 0; hash < table_size; ++hash) {
			if (table[hash] == deleted || !table[hash])
				continue;

			new_table.put(*table[hash]);
		}
		// Copy & delete
		table_size *= 2;
		table = new_table.table;
	}

	void print_all() {
		for (int hash = 0; hash < table_size; ++hash) {
			cout << hash << " ";
			if (table[hash] == deleted)
				cout << " X ";
			else if (!table[hash])
				cout << " E ";
			else
				table[hash]->print();
			cout << "\n";
		}
		cout << "******************\n";
	}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// https://leetcode.com/problems/linked-list-cycle/
class Solution141 {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode*> set;
        
        ListNode* cur = head;
        while (cur) {
            set.insert(cur);
            if (set.count(cur->next))
                return true;
            
            cur = cur->next;
        }
        return false;
    }
};

// https://leetcode.com/problems/linked-list-cycle-ii/
class Solution142 {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode*> set;
        
        ListNode* cur = head;
        while (cur) {
            set.insert(cur);
            if (set.count(cur->next))
                return cur->next;
            
            cur = cur->next;
        }
        return nullptr;
    }
};

// https://leetcode.com/problems/find-all-anagrams-in-a-string/
class Solution438 {
public:
    vector<int> findAnagrams(string s, string p) {
        
    }
};

int main()
{
    PhoneHashTable table(3);
	table.put(PhoneEntry("mostafa", "604-401-120"));
	table.put(PhoneEntry("mostafa", "604-401-777"));	// update
	table.put(PhoneEntry("ali", "604-401-343"));
	table.put(PhoneEntry("ziad", "604-401-17"));
	table.put(PhoneEntry("hany", "604-401-758"));
	table.put(PhoneEntry("belal", "604-401-550"));
	table.put(PhoneEntry("john", "604-401-223"));

	PhoneEntry e("mostafa", "");
	if (table.get(e))
		cout << e.phone_number << "\n";	// 604-401-777

	table.print_all();
	// Hash 0: (ali, 604-401-343)  (hany, 604-401-758)  (john, 604-401-223)
	// Hash 1: (mostafa, 604-401-777)  (ziad, 604-401-17)
	// Hash 2: (belal, 604-401-550)

	cout << table.remove(PhoneEntry("smith", "")) << "\n"; // 0
	cout << table.remove(PhoneEntry("hany", "")) << "\n";  // 1
	cout << table.remove(PhoneEntry("belal", "")) << "\n";  // 1
	table.print_all();
	// Hash 0: (ali, 604-401-343)  (john, 604-401-223)
	// Hash 1: (mostafa, 604-401-777)  (ziad, 604-401-17)

    // hw1 p5
    PhoneHashTableLL tablell(3);
	tablell.put(PhoneEntry("mostafa", "604-401-120"));
	tablell.put(PhoneEntry("mostafa", "604-401-777"));	// update
	tablell.put(PhoneEntry("ali", "604-401-343"));
	tablell.put(PhoneEntry("ziad", "604-401-17"));
	tablell.put(PhoneEntry("hany", "604-401-758"));
	tablell.put(PhoneEntry("belal", "604-401-550"));
	tablell.put(PhoneEntry("john", "604-401-223"));

	tablell.print_all();

    cout<<"***************************\n";
    PhoneHashTableProbe tablepr(11);
	tablepr.put(PhoneEntry("mostafa", "604-401-120"));
	tablepr.put(PhoneEntry("mostafa", "604-401-777"));
	tablepr.put(PhoneEntry("ali", "604-401-343"));
	tablepr.put(PhoneEntry("ziad", "604-401-17"));
	tablepr.put(PhoneEntry("hany", "604-401-758"));
	tablepr.put(PhoneEntry("belal", "604-401-550"));
	tablepr.put(PhoneEntry("john", "604-401-223"));
    tablepr.print_all();

    cout << tablepr.remove(PhoneEntry("smith", "")) << "\n"; // 0
	cout << tablepr.remove(PhoneEntry("hany", "")) << "\n";  // 1
	cout << tablepr.remove(PhoneEntry("john", "")) << "\n";  // 1
	tablepr.print_all();

    PhoneEntry pe("belal", "");
	if (tablepr.get(pe))
		cout << pe.phone_number << "\n";	// 604-401-550

	tablepr.put(PhoneEntry("hany", "604-401-555"));
	tablepr.print_all();

    // hw2 p1 
    string str_hw2_p1;
    str_hw2_p1 = "aaaaa";
    cout<<str_hw2_p1<<": "<<count_unique_substrings(str_hw2_p1)<<endl;
    str_hw2_p1 = "aaaba";
    cout<<str_hw2_p1<<": "<<count_unique_substrings(str_hw2_p1)<<endl;
    str_hw2_p1 = "abcdef";
    cout<<str_hw2_p1<<": "<<count_unique_substrings(str_hw2_p1)<<endl;
    // hw2 p2

    cout<<count_substrings_match("aaab","aa")<<endl;
    cout<<count_substrings_match("aaab","ab")<<endl;
    cout<<count_substrings_match("aaaaa","xy")<<endl;
    cout<<count_substrings_match("aaaaa","aaaaa")<<endl;
    // hw2 p3
    cout<<"---------------------------------\n";
    cout<<count_anagram_substrings("aaaaa")<<endl;
    cout<<count_anagram_substrings("abcba")<<endl;
    cout<<count_anagram_substrings("aabade")<<endl;
    // hw2 p4
    cout<<"---------------------------------\n";
    LinkedList lst;
    lst.create_cycle();
    lst.remove_cylce();
    lst.print();
    return 0;
}
