/*
721. Accounts Merge
https://leetcode.com/problems/accounts-merge/

Given a list accounts, each element accounts[i] is a list of strings,
where the first element accounts[i][0] is a name,
and the rest of the elements are emails representing emails of the account.

Now, we would like to merge these accounts.
Two accounts definitely belong to the same person if there is some email that is common to both accounts.
Note that even if two accounts have the same name,
they may belong to different people as people could have the same name.
A person can have any number of accounts initially,
but all of their accounts definitely have the same name.

After merging the accounts,
return the accounts in the following format: the first element of each account is the name,
and the rest of the elements are emails in sorted order.
The accounts themselves can be returned in any order.

Example 1:
Input:
accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John",
"johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]] Output: [["John", 'john00@mail.com',
'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
Explanation:
The first and third John's are the same person as they have the common email "johnsmith@mail.com".
The second John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John',
'johnnybravo@mail.com'],
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
Note:

The length of accounts will be in the range [1, 1000].
The length of accounts[i] will be in the range [1, 10].
The length of accounts[i][j] will be in the range [1, 30].
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;

class Solution {
private:
    string find(string s, unordered_map<string, string>& parents) {
        if (parents.find(s) == parents.end() || parents[s] == s) {
            return s;
        }
        return find(parents[s], parents);
    }

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        unordered_map<string, string> owner;
        unordered_map<string, string> parents;
        for (int i = 0; i < n; ++i) {
            string root_email = find(accounts[i][1], parents);
            owner[root_email] = accounts[i][0];
            for (int j = 1; j < accounts[i].size(); ++j) {
                parents[find(accounts[i][j], parents)] = root_email;
            }
        }

        unordered_map<string, set<string>> unions;
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < accounts[i].size(); ++j) {
                unions[find(accounts[i][j], parents)].insert(accounts[i][j]);
            }
        }

        vector<vector<string>> result;
        for (pair<string, set<string>> u : unions) {
            vector<string> emails(u.second.begin(), u.second.end());
            emails.insert(emails.begin(), owner[u.first]);
            result.push_back(emails);
        }
        return result;
    }
};