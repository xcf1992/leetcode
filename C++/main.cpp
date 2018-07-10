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
#include <set>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int num = position.size();
        if (num == 0) {
            return 0;
        }
        
        vector<pair<int, int>> car;
        for (int i = 0; i < num; i++) {
            car.push_back(make_pair(position[i], speed[i]));
        }
        sort(car.begin(), car.end(), [](pair<int, int>& a, pair<int, int>& b) {
            return a.first < b.first;
        });
        
        int result = 1;
        double arrive = (target - car[num - 1].first) / car[num - 1].second;
        for (int i = num - 2; i >= 0; i--) {
            double newArrive = (target - car[i].first) / car[i].second;
            if (newArrive > arrive) {
                arrive = newArrive;
                result += 1;
            }
        }
        return result;
    }
};

class ExamRoom {
private:
    int num;
    vector<int> seats;
public:
    ExamRoom(int N) {
        num = N;
    }
    
    int seat() {
        if (seats.size() == 0) {
            seats.push_back(0);
            return 0;
        }
        
        int pos = 0;
        int index = 0;
        int distance = seats[0];
        if (num - 1 - seats.back() > distance) {
            pos = num - 1;
            index = seats.size();
            distance = num - 1 - seats.back();
        }
        
        for (int i = 0; i < seats.size() - 1; i++) {
            if ((seats[i + 1] - seats[i]) / 2 > distance ||
                ((seats[i + 1] - seats[i]) / 2 == distance && (seats[i + 1] + seats[i]) / 2 < pos)) {
                distance = (seats[i + 1] - seats[i]) / 2;
                pos = seats[i] + distance;
                index = i + 1;
            }
        }
        
        seats.insert(seats.begin() + index, pos);
        return pos;
    }
    
    void leave(int p) {
        for (auto it = seats.begin(); it != seats.end(); it++) {
            if (*it == p) {
                seats.erase(it);
                return;
            }
        }
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({6,8});
    vector<int> vb({3,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({{0,0,1,1}, {1,0,1,0}, {1,1,0,0}});
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(4,3));
    fuxk.push_back(make_pair(2,3));
    fuxk.push_back(make_pair(2,1));
    fuxk.push_back(make_pair(5,0));
    
    //s.carFleet(10, va, vb);
    
    ExamRoom ex(4);
    ex.seat();
    ex.seat();
    ex.seat();
    ex.seat();
    ex.leave(1);
    ex.leave(3);
    ex.seat();
}
