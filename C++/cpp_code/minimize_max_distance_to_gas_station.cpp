/*
774. Minimize Max Distance to Gas Station

On a horizontal number line,
we have gas stations at positions stations[0], stations[1], ..., stations[N-1],
where N = stations.length.

Now, we add K more gas stations so that D,
the maximum distance between adjacent gas stations, is minimized.

Return the smallest possible value of D.

Example:
Input: stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K = 9
Output: 0.500000

Note:
stations.length will be an integer in range [10, 2000].
stations[i] will be an integer in range [0, 10^8].
K will be an integer in range [1, 10^6].
Answers within 10^-6 of the true value will be accepted as correct.
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
using namespace std;
/*
1、采用优先队列：采用优先队列的思路比较简单：就是每次找出gap最大的一个区间，然后新加入一个station，直到所有的k个station都被加入，
此时最大的gap即为所求。在实现上我们采用优先队列，使得每次最大的gap总是出现在队首。这种方法的空间复杂度是O(n)，时间复杂度是O(klogn)，
其中k是要加入的新station的个数，n是原有的station个数。这种方法应该没毛病，但是还是没有通过所有的数据测试。

2、采用二分查找：在网上参考了采用二分查找的实现。我们容易得知，minmaxGap的最小值left = 0，最大值right = stations[n - 1]
- stations[0]。
我们每次取mid为left和right的均值，然后计算如果minmaxGap为mid，那么最少需要添加多少个新的stations，记为count。
所以如果count > K，说明均值mid选取的过小，使得我们必须新加更多的stations才能满足要求，所以我们就更新left的值；
否则说明均值mid选取的过大，使得我们需要小于K个新的stations就可以达到要求，那么我们此时就可以寻找更小的mid，使得count增加到K。
如果我们假设stations[N - 1] - stations[0] = m，那么这种实现的空间复杂度是O(1)，时间复杂度是O(nlogm)，可以发现与k无关了。
*/
class Solution {
private:
    bool check(vector<int>& stations, int K, double mid) {
        int count = 0;
        for (int i = 0; i < stations.size() - 1; ++i) {
            count += ceil((stations[i + 1] - stations[i]) / mid) - 1;
        }
        return count <= K;
    }

public:
    double minmaxGasDist(vector<int>& stations, int K) {
        double left = 0;
        double right = stations.back() - stations.front();
        while (right - left > 1e-6) {
            double mid = left + (right - left) / 2;
            if (check(stations, K, mid)) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return left;
    }
};