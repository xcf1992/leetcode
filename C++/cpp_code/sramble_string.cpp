#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

bool isScramble(string s1, string s2) {
    if (s1.size() != s2.size()) {
        return false;
    }
    if (s1 == s2) {
        return true;
    }

    string tmp1 = s1;
    string tmp2 = s2;
    sort(tmp1.begin(), tmp1.end());
    sort(tmp2.begin(), tmp2.end());
    for (int i = 0; i != s1.size(); i++) {
        if (tmp1.at(i) != tmp2.at(i)) {
            return false;
        }
    }

    vector<bool> row(s1.size(), false);
    vector<vector<bool> > matrix(s1.size(), row);
    vector<vector<vector<bool> > > cube(s1.size(), matrix);

    for (int k = 0; k != s1.size(); k++) {
        for (int i = 0; i != s1.size() - k; i++) {
            for (int j = 0; j != s1.size() - k; j++) {
                if (k == 0) {
                    if (s1.at(i) == s2.at(j)) {
                        cube.at(i).at(j).at(k) = true;
                    }
                } else {
                    for (int l = 0; l != k; l++) {
                        if ((cube.at(i).at(j).at(l) and
                        cube.at(i + l + 1).at(j + l + 1).at(k - l - 1)
                        )
                        or
                                (cube.at(i).at(j + k - l).at(l) and cube.at(i + l + 1).at(j).at(k - l - 1))
                        )
                        {
                            cube.at(i).at(j).at(k) = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    return cube.front().front().back();
}

int main() {
    string s1 = "abb";
    string s2 = "bba";
    isScramble(s1, s2);
    return 0;
}