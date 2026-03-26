/*
给一个car lease 的预约时间list，返回需要多少车，和assign每个lease的车辆id，按free car的编号最小进行assign，follow up
车有cool down time"

用 min_heap 只能算出来需要多少车, 但是怎么正确 assign 车 id 呢
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <climits>
#include <map>
#include <cassert>
using namespace std;

class Solution {
public:
    vector<int> assign_cars(vector<vector<int>>& leases, int cooldown = 0) {
        int n = leases.size();
        vector<vector<int>> sorted_lease;
        for (int i = 0; i < n; i++) {
            sorted_lease.push_back({leases[i][0], leases[i][1], i});
        }
        sort(sorted_lease.begin(), sorted_lease.end(),
             [](vector<int>& a, vector<int>& b) { return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]); });

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> occupied_cars;
        set<int> available_car_ids;
        int next_avail_car_id = 0;
        vector<int> rst(n, -1);
        for (vector<int>& lease : sorted_lease) {
            int start = lease[0];
            int end = lease[1];
            int lease_id = lease[2];

            while (!occupied_cars.empty() && start >= occupied_cars.top().first) {
                available_car_ids.insert(occupied_cars.top().second);
                occupied_cars.pop();
            }

            if (!available_car_ids.empty()) {
                rst[lease_id] = *available_car_ids.begin();
                available_car_ids.erase(available_car_ids.begin());
            } else {
                rst[lease_id] = next_avail_car_id;
                next_avail_car_id++;
            }
            occupied_cars.push({end + cooldown, rst[lease_id]});
        }
        return rst;
    }
};

int countCars(const vector<int>& assignment) {
    int mx = -1;
    for (int id : assignment)
        mx = max(mx, id);
    return mx + 1;
}

void runTest(const string& name, vector<vector<int>> leases, int cooldown, int expectedCars,
             vector<int> expectedAssignment) {
    Solution sol;
    vector<int> result = sol.assign_cars(leases, cooldown);
    int totalCars = countCars(result);

    cout << "=== " << name << " (cooldown=" << cooldown << ") ===" << endl;
    cout << "Leases:     ";
    for (auto& l : leases)
        cout << "[" << l[0] << "," << l[1] << "] ";
    cout << endl;
    cout << "Expected:   cars=" << expectedCars << " assign=[ ";
    for (int x : expectedAssignment)
        cout << x << " ";
    cout << "]" << endl;
    cout << "Got:        cars=" << totalCars << " assign=[ ";
    for (int x : result)
        cout << x << " ";
    cout << "]" << endl;

    bool pass = (totalCars == expectedCars && result == expectedAssignment);
    cout << (pass ? "PASS" : "FAIL") << endl << endl;

    assert(pass);
}

int main() {
    // === Basic cases ===

    // Test 1: No overlap - reuse car 0 every time
    runTest("No overlap", {{0, 2}, {3, 5}, {6, 8}}, 0, 1, {0, 0, 0});

    // Test 2: All overlap - each lease needs a new car
    runTest("All overlap", {{0, 10}, {1, 5}, {2, 8}}, 0, 3, {0, 1, 2});

    // Test 3: Partial overlap
    // [0,5]->car0, [1,3]->car1, [4,7]->car1 (freed at 3, 3<4), [6,9]->car0 (freed at 5, 5<6)
    runTest("Partial overlap", {{0, 5}, {1, 3}, {4, 7}, {6, 9}}, 0, 2, {0, 1, 1, 0});

    // Test 4: Exact boundary - end == start, reuse (start >= end)
    runTest("Exact boundary", {{0, 5}, {5, 10}, {10, 15}}, 0, 1, {0, 0, 0});

    // Test 5: Single lease
    runTest("Single lease", {{0, 10}}, 0, 1, {0});

    // === Smallest ID assignment ===

    // Test 6: Car 0 frees earliest, should be reused first
    // [0,3]->car0, [0,5]->car1, [0,7]->car2, [4,8]->car0 (freed at 3)
    runTest("Smallest ID reuse", {{0, 3}, {0, 5}, {0, 7}, {4, 8}}, 0, 3, {0, 1, 2, 0});

    // Test 7: Multiple cars free at same time - pick smallest id
    // [0,5]->car0, [0,5]->car1, [0,5]->car2, [6,10]->car0
    runTest("Multiple free, pick smallest", {{0, 5}, {0, 5}, {0, 5}, {6, 10}}, 0, 3, {0, 1, 2, 0});

    // Test 8: Two free, two new leases - assign id 0 then id 1
    // [0,5]->car0, [0,5]->car1, [6,8]->car0, [6,9]->car1
    runTest("Two free two assign", {{0, 5}, {0, 5}, {6, 8}, {6, 9}}, 0, 2, {0, 1, 0, 1});

    // === Unsorted input ===

    // Test 9: Input not sorted by start time
    // Sorted: [0,3]->car0, [4,8]->car0, [5,10]->car1
    // Original indices: lease0=[5,10]->car1, lease1=[0,3]->car0, lease2=[4,8]->car0
    runTest("Unsorted input", {{5, 10}, {0, 3}, {4, 8}}, 0, 2, {1, 0, 0});

    // Test 10: Reverse sorted input
    // Sorted: [1,4]->car0, [3,6]->car1, [5,8]->car0
    // Original: lease0=[5,8]->car0, lease1=[3,6]->car1, lease2=[1,4]->car0
    runTest("Reverse sorted", {{5, 8}, {3, 6}, {1, 4}}, 0, 2, {0, 1, 0});

    // === Cooldown tests ===

    // Test 11: Cooldown prevents reuse
    // Car0 busy until 5+2=7, lease [6,10] starts at 6 < 7 -> need new car
    runTest("Cooldown prevents reuse", {{0, 5}, {6, 10}}, 2, 2, {0, 1});

    // Test 12: Cooldown allows reuse with enough gap
    // Car0 busy until 5+2=7, lease [8,12] starts at 8 >= 7 -> reuse
    runTest("Cooldown allows reuse", {{0, 5}, {8, 12}}, 2, 1, {0, 0});

    // Test 13: Cooldown boundary exact (start == end + cooldown)
    // Car0 busy until 5+2=7, lease [7,10] starts at 7 >= 7 -> reuse
    runTest("Cooldown exact boundary", {{0, 5}, {7, 10}}, 2, 1, {0, 0});

    // Test 14: Cooldown multi-car scenario
    // [0,3]->car0 (busy til 5), [0,5]->car1 (busy til 7)
    // [4,8]: 4 < 5 (car0 busy), 4 < 7 (car1 busy) -> car2
    // [6,10]: 6 >= 5 (car0 free!) -> car0
    runTest("Cooldown multi-car", {{0, 3}, {0, 5}, {4, 8}, {6, 10}}, 2, 3, {0, 1, 2, 0});

    // Test 15: Cooldown=0 same as no cooldown
    runTest("Cooldown=0 boundary", {{0, 5}, {5, 10}}, 0, 1, {0, 0});

    // Test 16: Large cooldown forces all new cars
    runTest("Large cooldown", {{0, 1}, {2, 3}, {4, 5}}, 100, 3, {0, 1, 2});

    // === Edge cases ===

    // Test 17: Same interval for all - all overlap since start < end (not >=)
    // [1,1]->car0, [1,1]->car1, [1,1]->car2
    // Note: start(1) >= end(1) is true, but they all start at same time
    // Sorted by (start, end): all identical, processed in order
    // First [1,1]: no occupied -> car0. Push (1, 0).
    // Second [1,1]: 1 >= 1 -> release car0. Available={0}. Assign car0. Push (1, 0).
    // Third [1,1]: 1 >= 1 -> release car0. Available={0}. Assign car0. Push (1, 0).
    runTest("Same zero-length interval", {{1, 1}, {1, 1}, {1, 1}}, 0, 1, {0, 0, 0});

    // Test 18: Chain reuse - car freed and immediately reused
    // [0,1]->car0, [1,3]->car0 (1>=1), [2,4]->car1, [3,5]->car0 (3>=3), [4,6]->car1 (4>=4)
    runTest("Chain reuse", {{0, 1}, {1, 3}, {2, 4}, {3, 5}, {4, 6}}, 0, 2, {0, 0, 1, 0, 1});

    cout << "All tests passed!" << endl;
    return 0;
}
