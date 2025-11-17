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
