#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class TwoSum {
private:
    unordered_map<int, bool> table;
    unordered_map<int, bool> hashtable;
    
public:
	void add(int number) {
        if (table.empty()) {
            table[number] = true;
            return;
        }
        if (table.find(number) != table.end()) {
            if (hashtable.find(number * 2) == hashtable.end()) {
                hashtable[number * 2] = true;
            }
            return;
        }
        for (auto it = table.begin(); it != table.end(); it++) {
            if (hashtable.find(number + it->first) == hashtable.end()) {
                hashtable[number + it->first] = true;
            }
        }
        table[number] = true;
        return;
	}

	bool find(int value) {
	    if (hashtable.find(value) == hashtable.end()) {
	        return false;
	    }
	    return true;
	}
};

int main() {
	TwoSum t;
	t.add(0);
	t.add(0);
	bool b = t.find(0);
	if (b) {
		cout << "true" << endl;
	}
	else {
		cout << "false" << endl;
	}
	return 0;
}