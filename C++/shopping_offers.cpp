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

class Solution {
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
            if (pick) {
                for (int i = 0; i < offer.size() - 1; i++) {
                    bought[i] += offer[i];
                }
                currentFee += offer.back();
                pickSpecial(price, special, index, needs, bought, currentFee, result);
                for (int i = 0; i < offer.size() - 1; i++) {
                    bought[i] -= offer[i];
                }
                currentFee -= offer.back();
            }
        }

        for (int i = 0; i < needs.size(); i++) {
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