#include<iostream>
#include <vector>
#include<cassert>

using namespace std;

int hash_string(string str, int n)
{
    long long nn = n;
    long long sum = 0;
    for (int i = 0; i< (int) str.size(); ++i)
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

    int hash()
    {
        return hash_string(name, INTERNAL_LIMIT);
    }
    PhoneEntry(string name, string phone_number)
        :name(name), phone_number(phone_number)
    {
    }
    
    void print()
    {
        cout << "(" << name << ", " << phone_number << ")  ";
    }
};

class PhoneHashTable
{
private:
    int table_size;
    double limit_load_factor;
    vector<vector<PhoneEntry>> table;
public:
    PhoneHashTable(int table_size = 10, double limit_load_factor = 0.75)
    :table_size(table_size), limit_load_factor(limit_load_factor)
    {
        table.resize(table_size);
    }
    bool get(PhoneEntry &phone)
    {
        int idx = phone.hash() % table_size;

        for (int i = 0; i < (int) table[idx].size(); i++) {
            if(table[idx][i].name ==phone.name) {
                phone = table[idx][i];
                return true;
            }
        }
        return false;
    }
    void put(PhoneEntry phone) 
    {
        int idx = phone.hash() % table_size;

        for (int i = 0; i < (int) table[idx].size(); i++) {
            if(table[idx][i].name == phone.name){
                table[idx][i] = phone;// update
                return;
            }
        }
        table[idx].push_back(phone);
    }
    double getLeadFactor() 
    {
        int num_of_used = 0;
        for(auto v:table){
            if (!v.empty())
                num_of_used++;
        }
        return static_cast<double>(num_of_used)/table_size;
    }
    bool remove(PhoneEntry phone)
    {
        int idx = phone.hash() % table_size;
        for (int i = 0; i < (int) table[idx].size(); i++) {
            if(table[idx][i].name ==phone.name) {
                swap(table[idx][i],table[idx].back());
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
        table_size = 2*table_size;
        table.resize(table_size);
    
        for(auto v: table_old){
            for (auto e:v)
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
    PhoneHashTableProbe(int table_size) :table_size(table_size)
    {
        table.resize(table_size);
        deleted = new PhoneEntry("","");
    }
    bool put(PhoneEntry phone)
    {
        int idx = phone.hash() % table_size;
        for(int step = 0; step<table_size; ++step) {
            if(table[idx] == deleted || !table[idx]) {
                table[idx] = new PhoneEntry(phone.name, phone.phone_number);
                return true;
            }
            else if (table[idx]->name == phone.name) {
                table[idx]->phone_number = phone.phone_number;
                return true;
            }
            idx = (idx +1) % table_size;
        }
        return false;
    }
    bool remove(PhoneEntry phone)
    {
        int idx = phone.hash() % table_size;

        for (int step = 0; step < table_size; ++step) {
            if (!table[idx])
                break;
            if(table[idx] != deleted && table[idx]->name == phone.name) {
                delete table[idx];
                table[idx] = deleted;
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }

    bool get(PhoneEntry &phone)
    {
        int idx = phone.hash() % table_size;

        for (int step = 0; step < table_size; ++step) {
            if (!table[idx])
                break;
            if(table[idx] != deleted && table[idx]->name == phone.name) {
                phone.phone_number = table[idx]->phone_number;
                return true;
            }
            idx = (idx +1) % table_size;
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

    

    return 0;
}
