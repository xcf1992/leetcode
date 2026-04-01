/*
given a pavement segment [start, end]
and a list of rain drops covers [[drop1_start, drop1_end], [drop2_start, drop2_end]...]
return the 1 based rain drop index that after the drop, the rain covers all the pavement area
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
    int get_rain_drop_covers_pavement(pair<double, double> pavement, vector<pair<double, double>>& rain_drops) {
        map<double, double> rain_covered_seg;
        size_t n = rain_drops.size();
        for (size_t i = 0; i < n; i++) {
            double start = rain_drops[i].first;
            double end = rain_drops[i].second;

            if (start > pavement.second || end < pavement.first) {
                continue;
            }

            auto it = rain_covered_seg.upper_bound(start);
            if (it != rain_covered_seg.begin()) {
                auto prev_it = prev(it);
                if (prev_it->second >= start) {
                    start = min(start, prev_it->first);
                    end = max(end, prev_it->second);
                    rain_covered_seg.erase(prev_it);
                }
            }

            /*
             wrong implementation
            it = rain_covered_seg.upper_bound(end);
            if (it != rain_covered_seg.begin()) {
                auto prev_it = prev(it);
                if (prev_it->first <= end && prev_it->second >= end) {
                    end = max(end, prev_it->second);
                    rain_covered_seg.erase(prev_it);
                }
            }
             */
            while (it != rain_covered_seg.end() && it->first <= end) {
                start = min(start, it->first);
                end = max(end, it->second);
                auto next_it = next(it);
                rain_covered_seg.erase(it);
                it = next_it;
            }

            rain_covered_seg[start] = end;

            if (rain_covered_seg.begin()->first <= pavement.first &&
                rain_covered_seg.begin()->second >= pavement.second) {
                return i + 1;
            }
        }
        return 0;
    }
};

void test(string name, pair<double, double> pavement, vector<pair<double, double>> drops, size_t expected) {
    Solution sol;
    size_t result = sol.get_rain_drop_covers_pavement(pavement, drops);
    bool passed = (result == expected);
    cout << (passed ? "PASS" : "FAIL") << " | " << name;
    if (!passed) {
        cout << " | expected=" << expected << " got=" << result;
    }
    cout << endl;
}

int main() {
    // === 基本功能 ===

    // 1. 一滴雨恰好覆盖整个路面
    test("single drop exact cover", {0, 10}, {{0, 10}}, 1);

    // 2. 一滴雨超出路面范围
    test("single drop exceeds pavement", {2, 8}, {{0, 15}}, 1);

    // 3. 两滴雨拼接覆盖，无重叠
    test("two drops no overlap", {0, 10}, {{0, 5}, {5, 10}}, 2);

    // 4. 两滴雨有重叠
    test("two drops with overlap", {0, 10}, {{0, 6}, {4, 10}}, 2);

    // === 无法覆盖 ===

    // 5. 中间有缺口，永远覆盖不了
    test("gap in middle never covered", {0, 10}, {{0, 4}, {6, 10}}, 0);

    // 6. 空的 rain drops
    test("no drops", {0, 10}, {}, 0);

    // 7. 所有 drop 都在 pavement 外面
    test("all drops outside pavement", {5, 10}, {{0, 3}, {12, 15}, {20, 25}}, 0);

    // === 过滤逻辑 ===

    // 8. drop 完全在 pavement 左边
    test("drop entirely left of pavement", {5, 10}, {{0, 3}, {5, 10}}, 2);

    // 9. drop 完全在 pavement 右边
    test("drop entirely right of pavement", {0, 5}, {{8, 12}, {0, 5}}, 2);

    // 10. drop 部分重叠 pavement 左侧
    test("drop partial overlap left", {5, 10}, {{3, 7}, {6, 12}}, 2);

    // 11. drop 部分重叠 pavement 右侧
    test("drop partial overlap right", {0, 5}, {{0, 3}, {2, 8}}, 2);

    // === 合并逻辑 ===

    // 12. 多滴雨从左到右逐步覆盖
    test("sequential left to right", {0, 10}, {{0, 3}, {3, 6}, {6, 10}}, 3);

    // 13. 多滴雨从右到左逐步覆盖
    test("sequential right to left", {0, 10}, {{7, 10}, {3, 8}, {0, 4}}, 3);

    // 14. 一滴大雨合并多个小区间
    test("one big drop merges many small", {0, 20}, {{0, 3}, {5, 8}, {10, 13}, {15, 18}, {2, 19}, {19, 20}}, 6);

    // 15. 中间 drop 填补缺口
    test("fill gap in middle", {0, 10}, {{0, 4}, {6, 10}, {3, 7}}, 3);

    // === 边界条件 ===

    // 16. pavement 长度为 0
    test("zero length pavement", {5, 5}, {{5, 5}}, 1);

    // 17. drop 恰好触碰边界
    test("drop touches pavement boundary", {0, 10}, {{0, 5}, {5, 10}}, 2);

    // 18. 相邻但不重叠的 drop（有缝隙）
    test("adjacent drops with tiny gap", {0, 10}, {{0, 4.9}, {5.1, 10}}, 0);

    // 19. 大量重复 drop
    test("many duplicate drops", {0, 10}, {{0, 5}, {0, 5}, {0, 5}, {5, 10}}, 4);

    // === 浮点数 ===

    // 20. 浮点数坐标
    test("floating point coordinates", {0.5, 9.5}, {{0.5, 3.7}, {3.7, 6.2}, {6.2, 9.5}}, 3);

    // 21. 很小的区间
    test("tiny intervals", {0, 1}, {{0, 0.25}, {0.25, 0.5}, {0.5, 0.75}, {0.75, 1.0}}, 4);

    // === 复杂场景 ===

    // 22. 先覆盖两端，再用一滴连接
    test("cover ends then bridge", {0, 10}, {{0, 2}, {8, 10}, {1, 9}}, 3);

    // 23. 大量无关 drop 后才覆盖
    test("many irrelevant drops before cover", {5, 10}, {{0, 1}, {20, 25}, {30, 35}, {5, 10}}, 4);

    // 24. 第一滴就覆盖
    test("first drop covers", {3, 7}, {{0, 100}}, 1);

    // 25. 逆序填充
    test("reverse order fill", {0, 12}, {{9, 12}, {6, 10}, {3, 7}, {0, 4}}, 4);

    // 26. 左侧合并触发
    test("left merge trigger", {0, 10}, {{0, 6}, {4, 10}}, 2);

    // 27. 右侧合并触发
    test("right merge trigger", {0, 10}, {{4, 10}, {0, 6}}, 2);

    // 28. 链式合并：大 drop 合并多个小 drop
    test("chain merge multiple intervals", {0, 20}, {{1, 3}, {5, 7}, {9, 11}, {13, 15}, {17, 19}, {0, 20}}, 6);

    return 0;
}
