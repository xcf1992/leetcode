/*
638. Shopping Offers

In LeetCode Store, there are some kinds of items to sell.
Each item has a price.

However, there are some special offers,
and a special offer consists of one or more different kinds of items with a sale price.

You are given the each item's price,
a set of special offers,
and the number we need to buy for each item.
The job is to output the lowest price you have to pay for exactly certain items as given,
where you could make optimal use of the special offers.

Each special offer is represented in the form of an array,
the last number represents the price you need to pay for this special offer,
other numbers represents how many specific items you could get if you buy this offer.

You could use any of special offers as many times as you want.

Example 1:
Input: [2,5], [[3,0,5],[1,2,10]], [3,2]
Output: 14
Explanation:
There are two kinds of items, A and B. Their prices are $2 and $5 respectively.
In special offer 1, you can pay $5 for 3A and 0B
In special offer 2, you can pay $10 for 1A and 2B.
You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.
Example 2:
Input: [2,3,4], [[1,1,0,4],[2,2,1,9]], [1,2,1]
Output: 11
Explanation:
The price of A is $2, and $3 for B, $4 for C.
You may pay $4 for 1A and 1B, and $9 for 2A ,2B and 1C.
You need to buy 1A ,2B and 1C, so you may pay $4 for 1A and 1B (special offer #1), and $3 for 1B, $4 for 1C.
You cannot add more items, though only $9 for 2A ,2B and 1C.

Note:
There are at most 6 kinds of items, 100 special offers.
For each item, you need to buy at most 6 of them.
You are not allowed to buy more items than you want, even if that would lower the overall price.
*/
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
#include <map>
#include <numeric>
using namespace std;

class Solution { // dfs with memo
private:
    unordered_map<string, int> memo;

    string generateKey(vector<int>& needs) {
        string result = "";
        for (int num : needs) {
            result += "_" + to_string(num);
        }
        return result;
    }
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        if (accumulate(needs.begin(), needs.end(), 0) == 0) {
            return 0;
        }

        string key = generateKey(needs);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }

        memo[key] = INT_MAX;
        for (int index = 0; index < special.size(); index++) {
            vector<int> offer = special[index];
            bool pick = true;
            for (int i = 0; i < needs.size(); i++) {
                if (offer[i] > needs[i]) {
                    pick = false;
                    break;
                }
            }

            if (!pick) {
                continue;
            }

            vector<int> left = needs;
            for (int i = 0; i < offer.size() - 1; i++) {
                left[i] -= offer[i];
            }
            memo[key] = min(memo[key], offer.back() + shoppingOffers(price, special, left));
        }

        int cost = 0;
        for (int i = 0; i < needs.size(); ++i) {
            cost += needs[i] * price[i];
        }
        memo[key] = min(memo[key], cost);
        return memo[key];
    }
};

class Solution1 { // pure dfs
private:
    void pickSpecial(vector<int>& price, vector<vector<int>>& special, int start, vector<int>& needs,
                     vector<int>& bought, int currentFee, int& result) {
        for (int index = start; index < special.size(); index++) {
            vector<int> offer = special[index];
            bool pick = true;
            for (int i = 0; i < needs.size(); i++) {
                if (bought[i] + offer[i] > needs[i]) {
                    pick = false;
                    break;
                }
            }

            if (!pick) {
                continue;
            }

            for (int i = 0; i < offer.size() - 1; i++) {
                bought[i] += offer[i];
            }
            currentFee += offer.back();
            pickSpecial(price, special, index, needs, bought, currentFee, result);
            currentFee -= offer.back();
            for (int i = 0; i < offer.size() - 1; i++) {
                bought[i] -= offer[i];
            }
        }

        for (int i = 0; i < needs.size(); ++i) {
            currentFee += (needs[i] - bought[i]) * price[i];
        }
        result = min(result, currentFee);
    }
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        int result = INT_MAX;
        int currentFee = 0;
        int start = 0;
        vector<int> bought(needs.size(), 0);
        pickSpecial(price, special, start, needs, bought, currentFee, result);
        return result;
    }
};
