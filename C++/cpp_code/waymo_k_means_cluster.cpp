/*
问题一：
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
#include <stack>
#include <climits>
#include <map>
using namespace std;

struct Point {
    double row;
    double col;
};

// Euclidean distance squared (no need for sqrt when just comparing)
double distSq(const Point& a, const Point& b) {
    return (a.row - b.row) * (a.row - b.row) + (a.col - b.col) * (a.col - b.col);
}

// Returns: vector of size n, where result[i] = cluster id (0..k-1) for point i
vector<int> kmeans(const vector<Point>& points, int k, int maxIter = 100) {
    int n = points.size();
    vector<int> assignment(n, -1);

    // Step 1: Initialize centroids = first k points
    vector<Point> centroids(points.begin(), points.begin() + k);

    for (int iter = 0; iter < maxIter; iter++) {
        bool changed = false;

        // Step 2: Assign each point to nearest centroid
        for (int i = 0; i < n; i++) {
            int bestCluster = 0;
            double bestDist = distSq(points[i], centroids[0]);
            for (int c = 1; c < k; c++) {
                double d = distSq(points[i], centroids[c]);
                if (d < bestDist) {
                    bestDist = d;
                    bestCluster = c;
                }
            }

            if (assignment[i] != bestCluster) {
                assignment[i] = bestCluster;
                changed = true;
            }
        }

        // If no point changed cluster, we've converged
        if (!changed)
            break;

        // Step 3: Recompute centroids
        vector<Point> newCentroids(k, {0.0, 0.0});
        vector<int> count(k, 0);
        for (int i = 0; i < n; i++) {
            int c = assignment[i];
            newCentroids[c].row += points[i].row;
            newCentroids[c].col += points[i].col;
            count[c]++;
        }
        for (int c = 0; c < k; c++) {
            if (count[c] > 0) {
                newCentroids[c].row /= count[c];
                newCentroids[c].col /= count[c];
            } else {
                // Empty cluster — keep old centroid
                newCentroids[c] = centroids[c];
            }
        }
        centroids = newCentroids;
    }

    return assignment;
}

int main() {
    // Example: 6 points, split into k=2 clusters
    //   Cluster A (top-left area): (1,1), (1,2), (2,1)
    //   Cluster B (bottom-right area): (8,8), (9,8), (8,9)
    vector<Point> points = {{1, 1}, {1, 2}, {2, 1}, {8, 8}, {9, 8}, {8, 9}};
    int k = 2;

    vector<int> result = kmeans(points, k);

    // Print results grouped by cluster
    cout << "=== K-Means Result (k=" << k << ") ===" << endl;
    for (int c = 0; c < k; c++) {
        cout << "Cluster " << c << ": ";
        for (int i = 0; i < (int)points.size(); i++) {
            if (result[i] == c) {
                cout << "(" << points[i].row << "," << points[i].col << ") ";
            }
        }
        cout << endl;
    }

    // Example 2: more points, k=3
    cout << "\n=== Example 2 (k=3) ===" << endl;
    vector<Point> points2 = {
            {0, 0},   {1, 0},   {0, 1},    // bottom-left cluster
            {10, 10}, {11, 10}, {10, 11},  // top-right cluster
            {5, 0},   {6, 0},   {5, 1}     // middle cluster
    };
    vector<int> result2 = kmeans(points2, 3);
    for (int c = 0; c < 3; c++) {
        cout << "Cluster " << c << ": ";
        for (int i = 0; i < (int)points2.size(); i++) {
            if (result2[i] == c) {
                cout << "(" << points2[i].row << "," << points2[i].col << ") ";
            }
        }
        cout << endl;
    }

    return 0;
}
