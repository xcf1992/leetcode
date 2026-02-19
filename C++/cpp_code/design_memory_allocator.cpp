/*
https://leetcode.com/problems/design-memory-allocator/description/
2502. Design Memory Allocator

You are given an integer n representing the size of a 0-indexed memory array. All memory units are initially free.

You have a memory allocator with the following functionalities:

Allocate a block of size consecutive free memory units and assign it the id mID.
Free all memory units with the given id mID.
Note that:

Multiple blocks can be allocated to the same mID.
You should free all the memory units with mID, even if they were allocated in different blocks.
Implement the Allocator class:

Allocator(int n) Initializes an Allocator object with a memory array of size n.
int allocate(int size, int mID) Find the leftmost block of size consecutive free memory units and allocate it with the
id mID. Return the block's first index. If such a block does not exist, return -1. int freeMemory(int mID) Free all
memory units with the id mID. Return the number of memory units you have freed.


Example 1:

Input
["Allocator", "allocate", "allocate", "allocate", "freeMemory", "allocate", "allocate", "allocate", "freeMemory",
"allocate", "freeMemory"]
[[10], [1, 1], [1, 2], [1, 3], [2], [3, 4], [1, 1], [1, 1], [1], [10, 2], [7]]
Output
[null, 0, 1, 2, 1, 3, 1, 6, 3, -1, 0]

Explanation
Allocator loc = new Allocator(10); // Initialize a memory array of size 10. All memory units are initially free.
loc.allocate(1, 1); // The leftmost block's first index is 0. The memory array becomes [1,_,_,_,_,_,_,_,_,_]. We return
0. loc.allocate(1, 2); // The leftmost block's first index is 1. The memory array becomes [1,2,_,_,_,_,_,_,_,_]. We
return 1. loc.allocate(1, 3); // The leftmost block's first index is 2. The memory array becomes [1,2,3,_,_,_,_,_,_,_].
We return 2. loc.freeMemory(2); // Free all memory units with mID 2. The memory array becomes [1,_, 3,_,_,_,_,_,_,_]. We
return 1 since there is only 1 unit with mID 2. loc.allocate(3, 4); // The leftmost block's first index is 3. The memory
array becomes [1,_,3,4,4,4,_,_,_,_]. We return 3. loc.allocate(1, 1); // The leftmost block's first index is 1. The
memory array becomes [1,1,3,4,4,4,_,_,_,_]. We return 1. loc.allocate(1, 1); // The leftmost block's first index is 6.
The memory array becomes [1,1,3,4,4,4,1,_,_,_]. We return 6. loc.freeMemory(1); // Free all memory units with mID 1. The
memory array becomes [_,_,3,4,4,4,_,_,_,_]. We return 3 since there are 3 units with mID 1. loc.allocate(10, 2); // We
can not find any free block with 10 consecutive free memory units, so we return -1. loc.freeMemory(7); // Free all
memory units with mID 7. The memory array remains the same since there is no memory unit with mID 7. We return 0.


Constraints:

1 <= n, size, mID <= 1000
At most 1000 calls will be made to allocate and freeMemory.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>
#include <set>
using namespace std;
class Allocator {
    int n_;
    struct Node {
        int prefix, suffix, maxFree, len;
    };
    vector<Node> tree_;
    unordered_map<int, vector<pair<int, int>>> allocated_mem_;

    void build(int node, int lo, int hi) {
        int len = hi - lo + 1;
        tree_[node] = {len, len, len, len};
        if (lo == hi)
            return;
        int mid = (lo + hi) / 2;
        build(2 * node, lo, mid);
        build(2 * node + 1, mid + 1, hi);
    }

    Node combine(const Node& L, const Node& R) {
        Node res;
        res.len = L.len + R.len;
        res.prefix = (L.prefix == L.len) ? L.len + R.prefix : L.prefix;
        res.suffix = (R.suffix == R.len) ? R.len + L.suffix : R.suffix;
        res.maxFree = max({L.maxFree, R.maxFree, L.suffix + R.prefix});
        return res;
    }

    void update(int node, int lo, int hi, int pos, int val) {
        if (lo == hi) {
            tree_[node] = {val, val, val, 1};
            return;
        }
        int mid = (lo + hi) / 2;
        if (pos <= mid)
            update(2 * node, lo, mid, pos, val);
        else
            update(2 * node + 1, mid + 1, hi, pos, val);
        tree_[node] = combine(tree_[2 * node], tree_[2 * node + 1]);
    }

    int query(int node, int lo, int hi, int size) {
        if (tree_[node].maxFree < size)
            return -1;
        if (lo == hi)
            return lo;
        int mid = (lo + hi) / 2;
        // 1. Try left subtree first (lowest address wins)
        if (tree_[2 * node].maxFree >= size)
            return query(2 * node, lo, mid, size);
        // 2. Try the block that spans the mid boundary
        if (tree_[2 * node].suffix + tree_[2 * node + 1].prefix >= size)
            return mid - tree_[2 * node].suffix + 1;
        // 3. Must fit entirely in right subtree
        return query(2 * node + 1, mid + 1, hi, size);
    }

public:
    Allocator(int n) : n_(n), tree_(4 * n) {
        build(1, 0, n - 1);
    }

    int allocate(int size, int mID) {
        int start = query(1, 0, n_ - 1, size);
        if (start == -1)
            return -1;
        for (int i = start; i < start + size; i++)
            update(1, 0, n_ - 1, i, 0);
        allocated_mem_[mID].push_back({start, size});
        return start;
    }

    int freeMemory(int mID) {
        auto mit = allocated_mem_.find(mID);
        if (mit == allocated_mem_.end())
            return 0;
        int rst = 0;
        for (auto& [start, size] : mit->second) {
            for (int i = start; i < start + size; i++)
                update(1, 0, n_ - 1, i, 1);
            rst += size;
        }
        allocated_mem_.erase(mit);
        return rst;
    }
};
/*
The Logic Doesn't Hold — Here's Why
The idea has a subtle flaw. free_by_size_.lower_bound({size, 0}) finds the block with the smallest qualifying size, then
the smallest start among that size tier — not the smallest start across all qualifying blocks.
 */
class Allocator {
private:
    unordered_map<int, vector<pair<int, int>>> allocated_mem_;
    set<pair<int, int>> free_by_pos_;
    set<pair<int, int>> free_by_size_;

public:
    Allocator(int n) {
        free_by_pos_.insert({0, n});
        free_by_size_.insert({n, 0});
    }

    int allocate(int size, int mID) {
        auto it = free_by_size_.lower_bound({size, 0});
        if (it == free_by_size_.end()) {
            return -1;
        }

        int block_size = it->first;
        int start_pos = it->second;

        free_by_size_.erase(it);
        free_by_pos_.erase({start_pos, block_size});

        if (block_size > size) {
            free_by_size_.insert({block_size - size, start_pos + size});
            free_by_pos_.insert({start_pos + size, block_size - size});
        }
        allocated_mem_[mID].push_back({start_pos, size});
        return start_pos;
    }

    int freeMemory(int mID) {
        if (allocated_mem_.find(mID) == allocated_mem_.end()) {
            return 0;
        }

        int rst = 0;
        for (int i = 0; i < allocated_mem_[mID].size(); i++) {
            int cur_start = allocated_mem_[mID][i].first;
            int cur_size = allocated_mem_[mID][i].second;
            rst += cur_size;

            auto it = free_by_pos_.lower_bound({cur_start, cur_size});
            if (it != free_by_pos_.end() && it->first == cur_start + cur_size) {
                cur_size += it->second;
                free_by_size_.erase({it->second, it->first});
                free_by_pos_.erase(it);
            }

            it = free_by_pos_.lower_bound({cur_start, cur_size});
            if (it != free_by_pos_.begin()) {
                auto prev_it = prev(it);
                if (prev_it->first + prev_it->second == cur_start) {
                    cur_start = prev_it->first;
                    cur_size += prev_it->second;
                    free_by_size_.erase({prev_it->second, prev_it->first});
                    free_by_pos_.erase(prev_it);
                }
            }

            free_by_pos_.insert({cur_start, cur_size});
            free_by_size_.insert({cur_size, cur_start});
        }

        allocated_mem_.erase(mID);
        return rst;
    }
};

class Allocator {
public:
    Allocator(int n) {
        allocated_mem_.clear();
        available_mem_.insert({0, n});
    }

    int allocate(int size, int mID) {
        for (auto it = available_mem_.begin(); it != available_mem_.end(); ++it) {
            if (it->second < size) {
                continue;
            }

            int start_idx = it->first;
            int avail_size = it->second;
            allocated_mem_[mID].push_back({start_idx, size});
            available_mem_.erase(it);
            if (avail_size > size) {
                available_mem_.insert({start_idx + size, avail_size - size});
            }
            return start_idx;
        }
        return -1;
    }

    int freeMemory(int mID) {
        if (allocated_mem_.find(mID) == allocated_mem_.end()) {
            return 0;
        }

        int rst = 0;
        for (int i = 0; i < allocated_mem_[mID].size(); i++) {
            int start_idx = allocated_mem_[mID][i].first;
            int allocated_size = allocated_mem_[mID][i].second;
            auto avail_it = available_mem_.insert({start_idx, allocated_size}).first;
            if (avail_it != available_mem_.begin()) {
                auto prev_avail_it = prev(avail_it);
                if (prev_avail_it->first + prev_avail_it->second == start_idx) {
                    prev_avail_it->second += allocated_size;
                    available_mem_.erase(avail_it);
                    avail_it = prev_avail_it;
                }
            }

            if (next(avail_it) != available_mem_.end()) {
                auto next_avail_it = next(avail_it);
                if (start_idx + allocated_size == next_avail_it->first) {
                    avail_it->second += next_avail_it->second;
                    available_mem_.erase(next_avail_it);
                }
            }

            rst += allocated_size;
        }
        allocated_mem_.erase(mID);
        return rst;
    }

private:
    unordered_map<int, vector<pair<int, int>>> allocated_mem_;
    map<int, int> available_mem_;
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->freeMemory(mID);
 */
