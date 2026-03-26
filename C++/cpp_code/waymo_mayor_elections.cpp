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

/*
 * Problem: 2 districts each report top-N candidates. If there's a tie at the
 * Nth position, a random subset is picked. Determine if a winner can be
 * guaranteed.
 *
 * Key idea:
 *   - For each district, the minimum vote count among reported candidates is
 *     the "threshold". Any unreported candidate COULD have up to that many
 *     votes in that district (they might have tied and been randomly excluded).
 *   - known_votes[X] = sum of X's reported votes across both districts.
 *   - max_votes[X] = known_votes[X] + sum of thresholds from districts where
 *     X was NOT reported.
 *   - A candidate X is a guaranteed winner if:
 *       known_votes[X] > max_votes[Y] for ALL other candidates Y
 *     (i.e., even in X's worst case and Y's best case, X still leads)
 *   - Also consider a "phantom" candidate seen in neither district, whose
 *     max possible = threshold[0] + threshold[1].
 */

struct Solution {
public:
    string determine_winner(int N, vector<vector<pair<string, int>>>& districts) {
        vector<int> threshold(2, INT_MAX);
        int phantom_votes = 0;
        unordered_map<string, int> known_votes;
        vector<unordered_set<string>> district_to_name(2, unordered_set<string>());
        for (int i = 0; i < 2; i++) {
            for (auto& [name, cnt] : districts[i]) {
                known_votes[name] += cnt;
                threshold[i] = min(threshold[i], cnt);
                district_to_name[i].insert(name);
            }
            phantom_votes += threshold[i];
        }

        unordered_map<string, int> max_possible_votes;
        for (auto& [name, cnt] : known_votes) {
            max_possible_votes[name] = cnt;
            for (int i = 0; i < 2; i++) {
                if (district_to_name[i].find(name) == district_to_name[i].end()) {
                    max_possible_votes[name] += threshold[i];
                }
            }
        }

        // check if any known_vote cnt bigger than every max and phantom_max
        for (auto& [name, cnt] : known_votes) {
            if (cnt <= phantom_votes) {
                continue;
            }

            bool find_winner = true;
            for (auto& [other, max_cnt] : max_possible_votes) {
                if (name == other) {
                    continue;
                }

                if (cnt <= max_cnt) {
                    find_winner = false;
                    break;
                }
            }

            if (find_winner) {
                return "winner is " + name;
            }
        }
        return "cannot determine";
    }
};

// ---- Test harness ----
int passed = 0, failed = 0;

void test(string name, int N, vector<vector<pair<string, int>>> districts, string expected) {
    Solution sol;
    string result = sol.determine_winner(N, districts);
    if (result == expected) {
        cout << "  PASS: " << name << endl;
        passed++;
    } else {
        cout << "  FAIL: " << name << endl;
        cout << "    Expected: " << expected << endl;
        cout << "    Got:      " << result << endl;
        failed++;
    }
}

int main() {
    cout << "=== Basic cases ===" << endl;

    // Test 1: The example from the problem
    // A=10 in D1, B=9+6=15, C=5 in D2
    // threshold D1=9, D2=5, phantom=14
    // A could have 5 hidden in D2 → max=15, ties with B's known=15
    test("Problem example", 2, {{{"A", 10}, {"B", 9}}, {{"B", 6}, {"C", 5}}}, "cannot determine");

    // Test 2: Clear winner — one candidate dominates both districts
    // A: 100+50=150, B: max=9+3=12, C: max=9+3=12, phantom=9+3=12
    test("Clear winner in both districts", 2, {{{"A", 100}, {"B", 9}}, {{"A", 50}, {"C", 3}}}, "winner is A");

    // Test 3: Only one candidate per district, no overlap
    // A known=10, max=10+8=18. B known=8, max=8+10=18. phantom=18
    test("N=1, no overlap", 1, {{{"A", 10}}, {{"B", 8}}}, "cannot determine");

    // Test 4: Same candidate wins both districts with identical votes
    // A: 5+5=10, B: max=5+5=10, phantom=5+5=10
    test("Tied thresholds", 2, {{{"A", 5}, {"B", 5}}, {{"A", 5}, {"C", 5}}}, "cannot determine");

    cout << "\n=== Edge cases ===" << endl;

    // Test 5: One candidate appears in both, huge lead
    // A: 1000+1000=2000, B: max=1+1=2, phantom=1+1=2
    test("Massive lead", 2, {{{"A", 1000}, {"B", 1}}, {{"A", 1000}, {"C", 1}}}, "winner is A");

    // Test 6: Winner appears in only one district but still dominates
    // A known=100 (D1 only), max=100 (appears in D1, not D2, +threshold_D2=3)=103? No.
    // Wait: A not in D2, so max_A = 100+3 = 103
    // B: known=50+3=53, in both districts, max=53
    // C: known=3, in D2 only, max=3+50=53
    // phantom = 50+3 = 53
    // A's known=100 > 103? No, 100 < 103 is A's own max, but we check A's KNOWN vs others' MAX
    // A's known=100 > B's max=53? Yes. > C's max=53? Yes. > phantom=53? Yes.
    // Actually: the code checks cnt (known) >= phantom first. 100 >= 53. Then 100 > 53 for all others.
    test("Winner in one district only", 2, {{{"A", 100}, {"B", 50}}, {{"B", 3}, {"C", 3}}}, "winner is A");

    // Test 7: Phantom candidate could win
    // A known=5, B known=5. threshold=[5,5], phantom=10
    // A's known=5 < phantom=10 → skip. B same. Nobody wins.
    test("Phantom blocks winner", 1, {{{"A", 5}}, {{"B", 5}}}, "cannot determine");

    // Test 8: Three candidates reported per district (N=3)
    // A:20+15=35, B:18, C:15, D:12, E:10
    // threshold D1=15, D2=10
    // B: known=18, not in D2, max=18+10=28
    // C: known=15, not in D2, max=15+10=25
    // D: known=12, not in D1, max=12+15=27
    // E: known=10, not in D1, max=10+15=25
    // phantom = 15+10 = 25
    // A known=35 > 28? Yes. > 25? Yes. > 27? Yes. > 25? Yes. > phantom=25? Yes.
    test("N=3, clear winner", 3, {{{"A", 20}, {"B", 18}, {"C", 15}}, {{"A", 15}, {"D", 12}, {"E", 10}}}, "winner is A");

    // Test 9: Barely wins — known just beats max of all others
    // A: 10+11=21, B: 10 in D1, not in D2, max=10+11=21
    // A known=21 > B max=21? No (<=). Cannot determine.
    test("Off by one — tie with max", 2, {{{"A", 10}, {"B", 10}}, {{"A", 11}, {"C", 11}}}, "cannot determine");

    // Test 10: Barely wins — known strictly beats max of all others
    // A: 10+12=22, B: 10 not in D2, max=10+12=22. Still tied.
    // Need: A: 10+13=23, B max=10+13=23. Still tied!
    // Let's make it work: A in both, others not
    // A:20+20=40, B:19 in D1 only, max=19+20=39, C:20 in D2 only, max=20+20=40
    // A known=40 > B max=39? Yes. > C max=40? No.
    // Fix: A:20+21=41, B:19 D1 only max=19+21=40, C:20 D2 only max=20+20=40
    // phantom=20+20=40. A known=41 > 40? Yes for all.
    test("Barely wins — strict inequality", 2, {{{"A", 20}, {"B", 19}}, {{"A", 21}, {"C", 20}}}, "winner is A");

    cout << "\n=== Tricky cases ===" << endl;

    // Test 11: All candidates same votes
    test("All tied", 2, {{{"A", 10}, {"B", 10}}, {{"C", 10}, {"D", 10}}}, "cannot determine");

    // Test 12: One district has much higher votes than the other
    // A:1000, B:999+1=1000. threshold=[999,1], phantom=1000
    // A not in D2, max=1000+1=1001
    // B in both, max=1000
    // B known=1000 > A max=1001? No.
    test("Lopsided districts", 2, {{{"A", 1000}, {"B", 999}}, {{"B", 1}, {"C", 1}}}, "cannot determine");

    // Test 13: Candidate in both districts, others only in one
    // A:50+50=100, B:49 D1 only max=49+50=99, C:50 D2 only max=50+49=99
    // phantom=49+50=99. A known=100 > 99? Yes!
    test("Appears in both, others in one", 2, {{{"A", 50}, {"B", 49}}, {{"A", 50}, {"C", 50}}}, "winner is A");

    // Test 14: N=1 with same candidate in both — clear win
    // A:100+100=200, phantom=100+100=200. known=200 >= phantom=200.
    // But 200 > 200 fails (<=). Cannot determine?
    // Actually phantom could have 200, ties with A. So correct: cannot determine.
    test("N=1, same candidate both, phantom ties", 1, {{{"A", 100}}, {{"A", 100}}}, "cannot determine");

    // Test 15: N=1, candidate in both with unequal votes
    // A: 100+1=101. phantom=100+1=101. Same issue, cannot determine.
    // Need known > phantom. A:100+100=200, phantom must be < 200.
    // phantom = min(D1) + min(D2) = 100+100=200. Tied again.
    // For N=1, only 1 candidate per district, threshold = that candidate's votes.
    // If A is in both: phantom = A_d1 + A_d2 = A's known. Always ties.
    test("N=1, same candidate both, always ties phantom", 1, {{{"A", 50}}, {{"A", 200}}}, "cannot determine");

    // Test 16: Large N, many candidates, one dominates
    test("Large N, dominant winner", 3, {{{"A", 100}, {"B", 5}, {"C", 3}}, {{"A", 100}, {"D", 4}, {"E", 2}}},
         "winner is A");

    cout << "\n=== Results ===" << endl;
    cout << passed << " passed, " << failed << " failed out of " << (passed + failed) << " tests." << endl;

    return 0;
}