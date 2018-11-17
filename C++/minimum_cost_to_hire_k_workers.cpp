/*
 There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].
 
 Now we want to hire exactly K workers to form a paid group.  When hiring a group of K workers, we must pay them according to the following rules:
 
 Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
 Every worker in the paid group must be paid at least their minimum wage expectation.
 Return the least amount of money needed to form a paid group satisfying the above conditions.
 
 
 
 Example 1:
 
 Input: quality = [10,20,5], wage = [70,50,30], K = 2
 Output: 105.00000
 Explanation: We pay 70 to 0-th worker and 35 to 2-th worker.
 Example 2:
 
 Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
 Output: 30.66667
 Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers seperately.
 
 
 Note:
 
 1 <= K <= N <= 10000, where N = quality.length = wage.length
 1 <= quality[i] <= 10000
 1 <= wage[i] <= 10000
 Answers within 10^-5 of the correct answer will be considered correct.
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

/*
"1. Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group."
So for any two workers in the paid group,
we have wage[i] : wage[j] = quality[i] : quality[j]
So we have wage[i] : quality[i] = wage[j] : quality[j]
We pay wage to every worker in the group with the same ratio compared to his own quality.

"2. Every worker in the paid group must be paid at least their minimum wage expectation."
For every worker, he has an expected ratio of wage compared to his quality.

So to minimize the total wage, we want a small ratio.
So we sort all workers with their expected ratio, and pick up K first worker.
Now we have a minimum possible ratio for K worker and we their total quality.

As we pick up next worker with bigger ratio, we increase the ratio for whole group.
Meanwhile we remove a worker with highest quality so that we keep K workers in the group.
We calculate the current ratio * total quality = total wage for this group.

We redo the process and we can find the minimum total wage.
Because workers are sorted by ratio of wage/quality.
For every ratio, we find the minimum possible total quality of K workers.

Time Complexity
O(NlogN) for sort.
O(NlogK) for priority queue.
*/
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        vector<pair<double, double>> workers;
        for (int i = 0; i < quality.size(); i++) {
            workers.push_back({(double) wage[i] / quality[i], (double) quality[i]});
        }
        sort(workers.begin(), workers.end(), [](pair<double, double>& a, pair<double, double>& b) {
            return a.first < b.first;
        });
        
        double result = __DBL_MAX__;
        double qsum = 0.0;
        priority_queue<double> pq;
        for (pair<double, double>& worker : workers) {
            qsum += worker.second;
            pq.push(worker.second);
            if (pq.size() > K) {
                qsum -= pq.top();
                pq.pop();
            }
            if (pq.size() == K) {
                result = min(result, qsum * worker.first);
            }
        }
        return result;
    }
};
