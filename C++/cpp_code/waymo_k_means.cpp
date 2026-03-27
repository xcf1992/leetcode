/*
给定一个二维数组(相当于matrix)，其中每个元素是一个坐标点 [row, col]，以及一个整数
k，表示需要分成的聚类数量。实现一个函数，将这些坐标点划分为 k 个cluster。 初始centroids可选用二维数组前 k 个点。
迭代更新每个cluster的centroid
最后返回cluster 后的结果坐标
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

/*
这道题就是让你手写一个 K-Means 聚类算法。
算法流程

初始化：取前k个点作为初始质心（centroid）
分配：每个点归入离它最近的质心所属的cluster
更新：重新计算每个cluster的质心（所有点的坐标平均值）
重复 2-3 直到质心不再变化（或达到最大迭代次数）
*/

class Solution {
private:
    double get_dist(pair<double, double>& p1, pair<double, double>& p2) {
        return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
    }

public:
    vector<int> k_means(vector<pair<double, double>> points, int k, int max_iteration = 100) {
        int n = points.size();
        vector<int> assignment(n, -1);

        vector<pair<double, double>> centroids(points.begin(), points.begin() + k);
        for (int iter = 0; iter < max_iteration; iter++) {
            bool changed = false;
            for (int i = 0; i < n; i++) {
                int best_cluster = 0;
                double best_dist = get_dist(points[i], centroids[best_cluster]);
                for (int c = 1; c < k; c++) {
                    double dist = get_dist(points[i], centroids[c]);
                    if (dist < best_dist) {
                        best_dist = dist;
                        best_cluster = c;
                    }
                }

                if (assignment[i] != best_cluster) {
                    assignment[i] = best_cluster;
                    changed = true;
                }
            }

            if (!changed) {
                break;
            }

            vector<pair<double, double>> new_centroids(k, {0.0, 0.0});
            vector<int> count(k, 0);
            for (int i = 0; i < n; i++) {
                int c = assignment[i];
                new_centroids[c].first += points[i].first;
                new_centroids[c].second += points[i].second;
                count[c] += 1;
            }

            for (int c = 0; c < k; c++) {
                if (count[c] > 0) {
                    new_centroids[c].first /= count[c];
                    new_centroids[c].second /= count[c];
                } else {
                    new_centroids[c] = centroids[c];
                }
            }

            centroids = new_centroids;
        }

        return assignment;
    }
};

// ---- Test helpers ----
int passed = 0, failed = 0;

// Check that points expected to be in the same cluster ARE in the same cluster,
// and points in different expected groups are NOT. This avoids depending on
// specific cluster ID numbers.
bool same_grouping(const vector<int>& assignment, const vector<vector<int>>& expected_groups) {
    // Build a map: for each expected group, all members should share the same assignment
    map<int, int> point_to_group;
    for (int g = 0; g < (int)expected_groups.size(); g++) {
        for (int idx : expected_groups[g]) {
            point_to_group[idx] = g;
        }
    }

    // Check: same expected group → same assignment
    for (auto& group : expected_groups) {
        for (int i = 1; i < (int)group.size(); i++) {
            if (assignment[group[i]] != assignment[group[0]])
                return false;
        }
    }

    // Check: different expected groups → different assignments
    set<int> cluster_ids;
    for (auto& group : expected_groups) {
        cluster_ids.insert(assignment[group[0]]);
    }
    return (int)cluster_ids.size() == (int)expected_groups.size();
}

void test(string name, vector<pair<double, double>> points, int k, vector<vector<int>> expected_groups) {
    Solution sol;
    vector<int> result = sol.k_means(points, k);

    // Basic validity checks
    bool valid = true;
    string err = "";

    // Check all assignments are in [0, k)
    for (int i = 0; i < (int)result.size(); i++) {
        if (result[i] < 0 || result[i] >= k) {
            valid = false;
            err = "assignment out of range";
            break;
        }
    }

    // Check grouping matches expected
    if (valid && !same_grouping(result, expected_groups)) {
        valid = false;
        err = "wrong grouping";
    }

    if (valid) {
        cout << "  PASS: " << name << endl;
        passed++;
    } else {
        cout << "  FAIL: " << name << " (" << err << ")" << endl;
        cout << "    Assignments: ";
        for (int a : result)
            cout << a << " ";
        cout << endl;
        failed++;
    }
}

// For cases where we just check validity (no obvious expected grouping)
void test_valid(string name, vector<pair<double, double>> points, int k) {
    Solution sol;
    vector<int> result = sol.k_means(points, k);

    bool valid = true;
    string err = "";

    if ((int)result.size() != (int)points.size()) {
        valid = false;
        err = "wrong result size";
    }

    for (int i = 0; valid && i < (int)result.size(); i++) {
        if (result[i] < 0 || result[i] >= k) {
            valid = false;
            err = "assignment out of range";
        }
    }

    // Check at least 1 cluster is used (sanity)
    set<int> used;
    for (int a : result)
        used.insert(a);

    if (valid) {
        cout << "  PASS: " << name << " (used " << used.size() << "/" << k << " clusters)" << endl;
        passed++;
    } else {
        cout << "  FAIL: " << name << " (" << err << ")" << endl;
        failed++;
    }
}

int main() {
    cout << "=== Basic cases ===" << endl;

    // Test 1: Two obvious clusters, k=2
    test("Two clear clusters", {{0, 0}, {1, 0}, {0, 1}, {10, 10}, {11, 10}, {10, 11}}, 2, {{0, 1, 2}, {3, 4, 5}});

    // Test 2: Three obvious clusters, k=3
    test("Three clear clusters", {{0, 0}, {1, 0}, {0, 1}, {10, 10}, {11, 10}, {10, 11}, {5, 0}, {6, 0}, {5, 1}}, 3,
         {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});

    // Test 3: k=1, everything in one cluster
    test("k=1, single cluster", {{0, 0}, {5, 5}, {10, 10}}, 1, {{0, 1, 2}});

    // Test 4: k equals n, each point its own cluster
    test("k=n, each point is a cluster", {{0, 0}, {10, 10}, {20, 20}}, 3, {{0}, {1}, {2}});

    cout << "\n=== Edge cases ===" << endl;

    // Test 5: All points identical
    // All should be in the same cluster (or at least valid)
    test_valid("All identical points", {{5, 5}, {5, 5}, {5, 5}, {5, 5}}, 2);

    // Test 6: Points on a line, k=2
    test("Collinear points, k=2", {{0, 0}, {1, 0}, {2, 0}, {100, 0}, {101, 0}, {102, 0}}, 2, {{0, 1, 2}, {3, 4, 5}});

    // Test 7: Two points, k=2
    test("Minimum: 2 points, k=2", {{0, 0}, {10, 10}}, 2, {{0}, {1}});

    // Test 8: Negative coordinates
    test("Negative coordinates", {{-10, -10}, {-9, -10}, {-10, -9}, {10, 10}, {11, 10}, {10, 11}}, 2,
         {{0, 1, 2}, {3, 4, 5}});

    // Test 9: Floating point coordinates
    test("Floating point coordinates", {{0.1, 0.2}, {0.15, 0.25}, {0.12, 0.18}, {9.9, 9.8}, {9.85, 9.75}, {9.88, 9.82}},
         2, {{0, 1, 2}, {3, 4, 5}});

    cout << "\n=== Convergence / iteration cases ===" << endl;

    // Test 10: Clusters that need multiple iterations
    // Initial centroids are first 2 points: (0,0) and (1,0)
    // But real clusters are {0,1,2} near origin and {3,4,5} far away
    // Should still converge correctly
    test("Needs multiple iterations", {{0, 0}, {1, 0}, {2, 0}, {50, 50}, {51, 50}, {50, 51}}, 2,
         {{0, 1, 2}, {3, 4, 5}});

    // Test 11: Already converged on first pass
    // First 2 points are perfect centroids for their groups
    test("Converges immediately", {{0, 0}, {100, 100}, {1, 1}, {99, 99}}, 2, {{0, 2}, {1, 3}});

    // Test 12: Large well-separated clusters
    test("Large separated clusters",
         {{0, 0},
          {1, 1},
          {2, 2},
          {0, 1},
          {1, 0},
          {2, 1},
          {1, 2},
          {0, 2},
          {2, 0},
          {100, 100},
          {101, 101},
          {102, 102},
          {100, 101},
          {101, 100},
          {102, 101}},
         2, {{0, 1, 2, 3, 4, 5, 6, 7, 8}, {9, 10, 11, 12, 13, 14}});

    cout << "\n=== Geometry cases ===" << endl;

    // Test 13: Square corners, k=2
    // Initial centroids (0,0) and (10,0) → splits left vs right
    test("Square corners, left vs right", {{0, 0}, {10, 0}, {0, 100}, {10, 100}}, 2, {{0, 2}, {1, 3}});

    // Test 14: Initial centroids (0,0) and (1,0) both near origin
    // K-means splits based on those seeds, not inner/outer
    // Just check validity since exact grouping depends on convergence
    test_valid("Inner/outer points, centroid-sensitive",
               {{0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {100, 0}, {0, 100}, {-100, 0}, {0, -100}}, 2);

    // Test 15: Diagonal clusters
    test("Diagonal clusters", {{0, 0}, {1, 1}, {2, 2}, {10, 0}, {11, 1}, {12, 2}}, 2, {{0, 1, 2}, {3, 4, 5}});

    // Test 16: k=4, four quadrants
    test("Four quadrant clusters", {{-10, -10}, {-9, -9}, {10, -10}, {9, -9}, {-10, 10}, {-9, 9}, {10, 10}, {9, 9}}, 4,
         {{0, 1}, {2, 3}, {4, 5}, {6, 7}});

    cout << "\n=== Stress / validity ===" << endl;

    // Test 17: Many points, just check validity
    {
        vector<pair<double, double>> pts;
        for (int i = 0; i < 100; i++) {
            pts.push_back({(double)(i % 10), (double)(i / 10)});
        }
        test_valid("100 grid points, k=5", pts, 5);
    }

    // Test 18: k with max_iteration=1 (just one round)
    {
        Solution sol;
        vector<pair<double, double>> pts = {{0, 0}, {1, 0}, {100, 100}, {101, 100}};
        auto result = sol.k_means(pts, 2, 1);
        bool valid = result.size() == 4;
        for (int a : result)
            if (a < 0 || a >= 2)
                valid = false;
        cout << (valid ? "  PASS" : "  FAIL") << ": max_iteration=1, still valid" << endl;
        if (valid)
            passed++;
        else
            failed++;
    }

    cout << "\n=== Results ===" << endl;
    cout << passed << " passed, " << failed << " failed out of " << (passed + failed) << " tests." << endl;

    return 0;
}
