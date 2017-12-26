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
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<int> superUglyNumbers;
        superUglyNumbers.push_back(1);
        int numPrimes = primes.size();
        vector<int> idxs(numPrimes, 0);

        while(superUglyNumbers.size() < n) {
            int nextSuperUglyNumber = superUglyNumbers[idxs[0]] * primes[0];
            
            for(int i = 0; i < numPrimes; i++) {
                nextSuperUglyNumber = min(nextSuperUglyNumber, superUglyNumbers[idxs[i]] * primes[i]);
            }
            for(int i = 0; i < numPrimes; i++) {
                if(nextSuperUglyNumber == superUglyNumbers[idxs[i]] * primes[i]) {
                    idxs[i]++;
                }
            }

            superUglyNumbers.push_back(nextSuperUglyNumber);
        }
        
        return superUglyNumbers[n-1];
    }
};

int main() {
    Solution s;
    int x[] ={7,19,29,37,41,47,53,59,61,79,83,89,101,103,109,127,131,137,139,157,167,179,181,199,211,229,233,239,241,251};
    vector<int> a(x, x + sizeof x / sizeof x[0]);
    cout << s.nthSuperUglyNumber(100000, a);
    return 0;
}