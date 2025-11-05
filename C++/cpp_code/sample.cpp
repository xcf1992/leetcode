#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
using namespace std;

void duplicate(string &rock) {
    unordered_map<char, bool> line;
    for (int i = 0; i < rock.size(); i++) {
        if (line[rock[i]]) {
            rock.erase(i, 1);
            i--;
        } else {
            line[rock[i]] = true;
        }
    }
}

int gemStone(vector<string> &rocks) {
    unordered_map<char, int> gems;
    int commons = 0;
    for (int i = 0; i < rocks.size(); i++) {
        for (int j = 0; j < rocks[i].size(); j++) {
            gems[rocks[i][j]]++;
        }
    }

    for (auto it = gems.begin(); it != gems.end(); it++) {
        if (it->second == rocks.size()) {
            commons++;
        }
    }
    return commons;
}

int main() {
    int n;
    cin >> n;
    vector<string> gems;
    string st;
    for (int i = 0; i < n; i++) {
        cin >> st;
        duplicate(st);
        gems.push_back(st);
    }

    cout << gemStone(gems) << endl;
    return 0;
}