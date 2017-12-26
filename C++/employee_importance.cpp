#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;


// Employee info
class Employee {
public:
    // It's the unique ID of each node.
    // unique id of this employee
    int id;
    // the importance value of this employee
    int importance;
    // the id of direct subordinates
    vector<int> subordinates;
};

class Solution {
private:
    int sum(vector<Employee*> employees, unordered_map<int, int> index, int id) {
        int result = employees[index[id]] -> importance;
        for (int sub : employees[index[id]] -> subordinates) {
            result += sum(employees, index, sub);
        }
        return result;
    }
public:
    int getImportance(vector<Employee*> employees, int id) {
        unordered_map<int, int> index;
        for (int i = 0; i < employees.size(); i++) {
            index[employees[i] -> id] = i;
        }

        return sum(employees, index, id);
    }
};