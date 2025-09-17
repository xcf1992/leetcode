/*
1722. Minimize Hamming Distance After Swap Operations
https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/

You are given two integer arrays,
source and target, both of length n.
You are also given an array allowedSwaps where each allowedSwaps[i] = [ai, bi]
indicates that you are allowed to swap the elements at index ai and index bi (0-indexed) of array source.
Note that you can swap elements at a specific pair of indices multiple times and in any order.

The Hamming distance of two arrays of the same length, source and target,
is the number of positions where the elements are different.
Formally, it is the number of indices i for 0 <= i <= n-1 where source[i] != target[i] (0-indexed).

Return the minimum Hamming distance of source and target after performing any amount of swap operations on array source.

Example 1:
Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
Output: 1
Explanation: source can be transformed the following way:
- Swap indices 0 and 1: source = [2,1,3,4]
- Swap indices 2 and 3: source = [2,1,4,3]
The Hamming distance of source and target is 1 as they differ in 1 position: index 3.
Example 2:
Input: source = [1,2,3,4], target = [1,3,2,4], allowedSwaps = []
Output: 2
Explanation: There are no allowed swaps.
The Hamming distance of source and target is 2 as they differ in 2 positions: index 1 and index 2.
Example 3:
Input: source = [5,1,2,4,3], target = [1,5,4,2,3], allowedSwaps = [[0,4],[4,2],[1,3],[1,4]]
Output: 0

Constraints:
n == source.length == target.length
1 <= n <= 105
1 <= source[i], target[i] <= 105
0 <= allowedSwaps.length <= 105
allowedSwaps[i].length == 2
0 <= ai, bi <= n - 1
ai != bi
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;
/*
The detail of how it swaps does not matter
If we can swap [0, 1] and [1, 2], then we can rearrange [0, 1, 2] to everything we want.
Similar question: 1202. Smallest String With Swaps
Thus, union-find would be a good fit
Steps:
Union-find all connected indexes
Count elements for each union-find group (we use Map<Integer, Map<Integer, Integer>> here)
Scan the target, try to find the element in that union-find group greedily
if found: count - 1
if not: diff + 1

*/
class UnionFind {
    public:
    vector<int> parent, rank;
    UnionFind(int n){
        rank.resize(n, 0);
        parent.resize(n);
        for(int i=0; i<n; i++){
            parent[i] = i;
        }
    }
    int find(int i){
        if(parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    void Union(int x, int y){
        int px = find(x);
        int py = find(y);

        if(px != py){
            if(rank[px] > rank[py]){
                parent[py] = px;
            }else if(rank[px] < rank[py]){
                parent[px] = py;
            }else{
                parent[py] = px;
                rank[px]++;
            }
        }
    }
};
class Solution {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        int res = 0;
        UnionFind uf(n);
        for(int i = 0; i<allowedSwaps.size(); i++){
            uf.Union(allowedSwaps[i][0], allowedSwaps[i][1]);
        }
        unordered_map<int, unordered_map<int,int>> mp;

        for(int i=0; i<n; i++){
            //parent
            int pi = uf.find(i);
            mp[pi][source[i]]++;
        }

        for(int i=0; i<n; i++){
            int num = target[i];
            //parent
            int pi = uf.find(i);
            if(mp[pi][num] <= 0){
                res++;
            }else{
                mp[pi][num]--;
            }
        }
        return res;
    }
};
