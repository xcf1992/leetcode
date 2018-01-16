#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int maxProfit(vector<int> &prices) {
       if ( prices.size() == 0) {
            return 0;
        }
        
        int profit1 = 0;
        int profit2 = 0;
        int min = 0;
        int max = 0;
        min = prices.at(0);
        max = prices.at(0);
        
        for ( int i = 0; i != prices.size() - 1; i++) {
            if ( prices.at(i + 1) < max) {
                int tmp = max - min;
                if (tmp > profit2) {
                    profit1 = profit2;
                    profit2 = tmp;
                }
                else if (tmp > profit1) {
                    profit1 = tmp;
                }
                
                max = prices.at(i + 1);
                min = prices.at(i + 1);
            }
            else if ( max < prices.at(i + 1)) {
                max = prices.at(i + 1);
            }
        }
        
        if ( max != min) {
            int tmp = max - min;
            if (tmp > profit2) {
                profit1 = profit2;
                profit2 = tmp;
            }
            else if (tmp > profit1) {
                profit1 = tmp;
            }
        }
        
        return profit1 + profit2;
    }

int main() {
	vector<int> prices;
	prices.push_back(1);
	prices.push_back(2);
	prices.push_back(4);
	prices.push_back(2);
	prices.push_back(5);
	prices.push_back(7);
	prices.push_back(2);
	prices.push_back(4);
	prices.push_back(9);
	prices.push_back(0);
	maxProfit(prices);
	return 0;
}