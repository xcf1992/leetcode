#include <unordered_map>

vector<pair<int, int> > optimalUtilization(int maxTravelDist,
							        vector<pair<int, int> > forwardRouteList,
							        vector<pair<int, int> > returnRouteList)
{
    int n1 = forwardRouteList.size();
    int n2 = returnRouteList.size();
    if (n1 == 0 or n2 == 0) {
        return {};
    }

    sort(forwardRouteList.begin(), forwardRouteList.end(), [](pair<int, int>& a, pair<int, int>& b) {
       return a.second < b.second;
    });
    sort(returnRouteList.begin(), returnRouteList.end(), [](pair<int, int>& a, pair<int, int>& b) {
       return a.second < b.second;
    });

    int left = 0;
    int right = n2 - 1;
    int curMax = -1;
    unordered_map<int, vector<pair<int, int> > > memo;
    while (left < n1 and right >= 0) {
        int curVal = forwardRouteList[left].second + returnRouteList[right].second;
        if (curVal > maxTravelDist) {
            right -= 1;
            continue;
        }

        if (curVal > curMax) {
            curMax = curVal;
        }
        int r = right;
        while (r >= 0 and returnRouteList[r].second == returnRouteList[right].second) {
            memo[curVal].push_back({forwardRouteList[left].first, returnRouteList[r].first});
            r -= 1;
        }
        left += 1;
    }

    if (curMax == -1) {
        return {};
    }
    return memo[curMax];
}
// FUNCTION SIGNATURE ENDS