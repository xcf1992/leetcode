/*
https://www.hack2hire.com/companies/stripe/coding-questions/697bdcdd9731315964cfaf6e/practice?questionId=697bdcee9731315964cfaf6f
Hotel Booking Reminder

A hotel reservation system is responsible for creating email communication schedules for its guests, based on their
booking details. You're given two JSON-like objects: reservations and emailTouchpoints.

The reservations object contains:

"guest_name": the guest's name (string)
"room_type": booked room category (string)
"check_in_day": the day of check-in (integer)
"stay_length": total number of days of the stay (integer)
The emailTouchpoints object maps timing markers to email subjects:

"start": schedule an email on the check-in day
"end": schedule an email on the check-out day (check_in_day + stay_length)
Negative integer string keys (like "-15", "-7"): schedule emails that many days before the check-out day
Return all scheduled email notifications for all guests, sorted by the sending date (earliest to latest). Each
notification should be formatted like this: "<day>: [<subject>] Booking: <guest_name> (<room_type>)"

Only include notifications where the calculated day is on or after the guest's check_in_day. If multiple notifications
fall on the same day, their order doesn't matter. Notifications on different days must be sorted chronologically.

Constraints:
1 ≤ reservations.length ≤ 1000
0 ≤ check_in_day ≤ 10^9
1 ≤ stay_length ≤ 1000
emailTouchpoints contains "start", "end", and any number of negative integer string keys
Example:

Input:
reservations = [
  {
    "guest_name": "John",
    "room_type": "Standard",
    "check_in_day": 0,
    "stay_length": 30
  },
  {
    "guest_name": "Alice",
    "room_type": "Suite",
    "check_in_day": 1,
    "stay_length": 15
  }
],
emailTouchpoints = {
  "start": "Welcome",
  "-15": "Upcoming Checkout",
  "end": "Thank You"
}

Output: ["0: [Welcome] Booking: John (Standard)",
         "1: [Upcoming Checkout] Booking: Alice (Suite)",
         "1: [Welcome] Booking: Alice (Suite)",
         "15: [Upcoming Checkout] Booking: John (Standard)",
         "16: [Thank You] Booking: Alice (Suite)",
         "30: [Thank You] Booking: John (Standard)"]

Explanation: The email sending schedule is calculated as follows:

"John" (check-in day 0, stay length 30):
Day 0: Welcome email (check-in)
Day 15: "Upcoming Checkout" reminder (15 days before checkout: 30 - 15 = 15)
Day 30: Thank You email (check-out)
"Alice" (check-in day 1, stay length 15):
Day 1: Welcome email and "Upcoming Checkout" reminder (15 days before checkout: 16 - 15 = 1)
Day 16: Thank You email
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
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <any>
using namespace std;

class Solution {
public:
    vector<string> scheduleBookingEmails(vector<map<string, any>>& reservations,
                                         map<string, string>& emailTouchpoints) {
        map<int, vector<string>> day_to_msg;
        for (auto& res : reservations) {
            string name = any_cast<string>(res["guest_name"]);
            string room = any_cast<string>(res["room_type"]);
            int begin = any_cast<int>(res["check_in_day"]);
            int endDay = begin + any_cast<int>(res["stay_length"]);
            for (auto& entry : emailTouchpoints) {
                string key = entry.first;
                string subject = entry.second;
                int day;

                if (key == "start") {
                    day = begin;
                } else if (key == "end") {
                    day = endDay;
                } else {
                    // Negative offsets are reminders before checkout.
                    day = endDay + stoi(key);
                }

                if (day < begin) {
                    continue;
                }

                string msg = to_string(day) + ": [" + subject + "] Booking: " + name + " (" + room + ")";
                day_to_msg[day].push_back(msg);
            }
        }

        vector<string> result;

        for (auto& [day, all_msg] : day_to_msg) {
            for (string& msg : all_msg) {
                result.push_back(msg);
            }
        }
        return result;
    }

    static void test1() {
        cout << "===== Test 1 =====" << endl;
        Solution solution;

        vector<map<string, any>> reservations;
        map<string, any> res1;
        res1["guest_name"] = string("John");
        res1["room_type"] = string("Standard");
        res1["check_in_day"] = 0;
        res1["stay_length"] = 30;
        reservations.push_back(res1);

        map<string, any> res2;
        res2["guest_name"] = string("Alice");
        res2["room_type"] = string("Suite");
        res2["check_in_day"] = 1;
        res2["stay_length"] = 15;
        reservations.push_back(res2);

        map<string, string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-15"] = "Upcoming Checkout";
        emailTouchpoints["end"] = "Thank You";

        vector<string> result = solution.scheduleBookingEmails(reservations, emailTouchpoints);
        cout << "[" << endl;
        for (string& msg : result) {
            cout << "    \"" << msg << "\"," << endl;
        }
        cout << "]" << endl;
        // Expected:
        // [
        //     "0: [Welcome] Booking: John (Standard)",
        //     "1: [Upcoming Checkout] Booking: Alice (Suite)",
        //     "1: [Welcome] Booking: Alice (Suite)",
        //     "15: [Upcoming Checkout] Booking: John (Standard)",
        //     "16: [Thank You] Booking: Alice (Suite)",
        //     "30: [Thank You] Booking: John (Standard)",
        // ]
    }

    static void test2() {
        cout << "\n===== Test 2 =====" << endl;
        Solution solution;

        vector<map<string, any>> reservations;
        map<string, any> res1;
        res1["guest_name"] = string("Mia");
        res1["room_type"] = string("Economy");
        res1["check_in_day"] = 0;
        res1["stay_length"] = 2;
        reservations.push_back(res1);

        map<string, string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-2"] = "First Reminder";
        emailTouchpoints["end"] = "Thank You";

        vector<string> result = solution.scheduleBookingEmails(reservations, emailTouchpoints);
        cout << "[" << endl;
        for (string& msg : result) {
            cout << "    \"" << msg << "\"," << endl;
        }
        cout << "]" << endl;
        // Expected:
        // [
        //     "0: [First Reminder] Booking: Mia (Economy)",
        //     "0: [Welcome] Booking: Mia (Economy)",
        //     "2: [Thank You] Booking: Mia (Economy)",
        // ]
    }

    static void test3() {
        cout << "\n===== Test 3 =====" << endl;
        Solution solution;

        vector<map<string, any>> reservations;
        map<string, any> res1;
        res1["guest_name"] = string("Liam");
        res1["room_type"] = string("Standard");
        res1["check_in_day"] = 10;
        res1["stay_length"] = 3;
        reservations.push_back(res1);

        map<string, any> res2;
        res2["guest_name"] = string("Zoe");
        res2["room_type"] = string("Suite");
        res2["check_in_day"] = 0;
        res2["stay_length"] = 5;
        reservations.push_back(res2);

        map<string, string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-5"] = "Upcoming Checkout";
        emailTouchpoints["-2"] = "Second Reminder";
        emailTouchpoints["end"] = "Thank You";

        vector<string> result = solution.scheduleBookingEmails(reservations, emailTouchpoints);
        cout << "[" << endl;
        for (string& msg : result) {
            cout << "    \"" << msg << "\"," << endl;
        }
        cout << "]" << endl;
        // Expected:
        // [
        //     "0: [Upcoming Checkout] Booking: Zoe (Suite)",
        //     "0: [Welcome] Booking: Zoe (Suite)",
        //     "3: [Second Reminder] Booking: Zoe (Suite)",
        //     "5: [Thank You] Booking: Zoe (Suite)",
        //     "10: [Welcome] Booking: Liam (Standard)",
        //     "11: [Second Reminder] Booking: Liam (Standard)",
        //     "13: [Thank You] Booking: Liam (Standard)",
        // ]
    }

    static void test4() {
        cout << "\n===== Test 4 =====" << endl;
        Solution solution;

        vector<map<string, any>> reservations;
        map<string, any> res1;
        res1["guest_name"] = string("Ivy");
        res1["room_type"] = string("Deluxe");
        res1["check_in_day"] = 4;
        res1["stay_length"] = 1;
        reservations.push_back(res1);

        map<string, string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-1"] = "Last Day";
        emailTouchpoints["end"] = "Thank You";

        vector<string> result = solution.scheduleBookingEmails(reservations, emailTouchpoints);
        cout << "[" << endl;
        for (string& msg : result) {
            cout << "    \"" << msg << "\"," << endl;
        }
        cout << "]" << endl;
        // Expected:
        // [
        //     "4: [Last Day] Booking: Ivy (Deluxe)",
        //     "4: [Welcome] Booking: Ivy (Deluxe)",
        //     "5: [Thank You] Booking: Ivy (Deluxe)",
        // ]
    }

    static void test5() {
        cout << "\n===== Test 5 =====" << endl;
        Solution solution;

        vector<map<string, any>> reservations;
        map<string, any> res1;
        res1["guest_name"] = string("Noah");
        res1["room_type"] = string("Single");
        res1["check_in_day"] = 0;
        res1["stay_length"] = 3;
        reservations.push_back(res1);

        map<string, string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-10"] = "Too Early";
        emailTouchpoints["end"] = "Thank You";

        vector<string> result = solution.scheduleBookingEmails(reservations, emailTouchpoints);
        cout << "[" << endl;
        for (string& msg : result) {
            cout << "    \"" << msg << "\"," << endl;
        }
        cout << "]" << endl;
        // Expected:
        // [
        //     "0: [Welcome] Booking: Noah (Single)",
        //     "3: [Thank You] Booking: Noah (Single)",
        // ]
    }

    static void test6() {
        cout << "\n===== Test 6 =====" << endl;
        Solution solution;

        vector<map<string, any>> reservations;
        map<string, any> res1;
        res1["guest_name"] = string("Emma");
        res1["room_type"] = string("Presidential");
        res1["check_in_day"] = 5;
        res1["stay_length"] = 20;
        reservations.push_back(res1);

        map<string, string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-1"] = "Final Reminder";
        emailTouchpoints["-7"] = "Week Left";
        emailTouchpoints["-15"] = "Halfway Reminder";
        emailTouchpoints["end"] = "Thank You";

        vector<string> result = solution.scheduleBookingEmails(reservations, emailTouchpoints);
        cout << "[" << endl;
        for (string& msg : result) {
            cout << "    \"" << msg << "\"," << endl;
        }
        cout << "]" << endl;
        // Expected:
        // [
        //     "5: [Welcome] Booking: Emma (Presidential)",
        //     "10: [Halfway Reminder] Booking: Emma (Presidential)",
        //     "18: [Week Left] Booking: Emma (Presidential)",
        //     "24: [Final Reminder] Booking: Emma (Presidential)",
        //     "25: [Thank You] Booking: Emma (Presidential)",
        // ]
    }

    static void test7() {
        cout << "\n===== Test 7 =====" << endl;
        Solution solution;

        vector<map<string, any>> reservations;
        map<string, any> res1;
        res1["guest_name"] = string("Ava");
        res1["room_type"] = string("Standard");
        res1["check_in_day"] = 2;
        res1["stay_length"] = 4;
        reservations.push_back(res1);

        map<string, any> res2;
        res2["guest_name"] = string("Ben");
        res2["room_type"] = string("Suite");
        res2["check_in_day"] = 2;
        res2["stay_length"] = 4;
        reservations.push_back(res2);

        map<string, any> res3;
        res3["guest_name"] = string("Kai");
        res3["room_type"] = string("Deluxe");
        res3["check_in_day"] = 1;
        res3["stay_length"] = 5;
        reservations.push_back(res3);

        map<string, string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-2"] = "Reminder";
        emailTouchpoints["end"] = "Thank You";

        vector<string> result = solution.scheduleBookingEmails(reservations, emailTouchpoints);
        cout << "[" << endl;
        for (string& msg : result) {
            cout << "    \"" << msg << "\"," << endl;
        }
        cout << "]" << endl;
        // Expected:
        // [
        //     "1: [Welcome] Booking: Kai (Deluxe)",
        //     "2: [Welcome] Booking: Ava (Standard)",
        //     "2: [Welcome] Booking: Ben (Suite)",
        //     "4: [Reminder] Booking: Ava (Standard)",
        //     "4: [Reminder] Booking: Ben (Suite)",
        //     "4: [Reminder] Booking: Kai (Deluxe)",
        //     "6: [Thank You] Booking: Ava (Standard)",
        //     "6: [Thank You] Booking: Ben (Suite)",
        //     "6: [Thank You] Booking: Kai (Deluxe)",
        // ]
    }
};

int main() {
    Solution::test1();
    Solution::test2();
    Solution::test3();
    Solution::test4();
    Solution::test5();
    Solution::test6();
    Solution::test7();
    return 0;
}

/*
Follow-up 1:
You are now given a list modifications, where each modification contains:

"guest_name": Guest's name (string)
"new_room_type": The new room category (string)
"modification_date": The date when the room change occurs (integer)
When a room change happens during an active stay:

Schedule a "[Room Change]" email on modification_date using the new room type
All emails scheduled after modification_date must use the new room type instead of the original one
Each modification generates its own "[Room Change]" email, and the room type for any notification is determined by the
most recent modification that occurred strictly before that notification's scheduled day.

Constraints:

0
0 ≤ modifications.length ≤
1000
1000
All modification entries refer to existing guests
A guest may have multiple room changes during their stay
Example:

Input:
reservations = [
  {
    "guest_name": "A",
    "room_type": "Standard",
    "check_in_day": 0,
    "stay_length": 30
  },
  {
    "guest_name": "B",
    "room_type": "Suite",
    "check_in_day": 1,
    "stay_length": 15
  }
],
emailTouchpoints = {
  "start": "Welcome",
  "-15": "Upcoming Checkout",
  "end": "Thank You"
},
modifications = [
  {
    "guest_name": "A",
    "new_room_type": "Suite",
    "modification_date": 5
  }
]

Output: ["0: [Welcome] Booking: A (Standard)",
         "1: [Upcoming Checkout] Booking: B (Suite)",
         "1: [Welcome] Booking: B (Suite)",
         "5: [Room Change] Booking: A (Suite)",
         "15: [Upcoming Checkout] Booking: A (Suite)",
         "16: [Thank You] Booking: B (Suite)",
         "30: [Thank You] Booking: A (Suite)"]

Explanation: The email sending schedule is calculated as follows:

"Guest A" (Standard → Suite on day 5):
Day 0: Welcome email with Standard (original room)
Day 5: Room Change email (room changed to Suite)
Day 15: Upcoming Checkout with Suite (room changed before this email)
Day 30: Thank You with Suite
"Guest B" (Suite, no changes):
Day 1: Welcome and Upcoming Checkout emails with Suite
Day 16: Thank You with Suite
 */
struct Change {
    int date;
    int idx;
    std::string new_room_type;

    Change(int modificationDate, int idx, std::string newRoomType)
            : date(modificationDate), idx(idx), new_room_type(newRoomType) {
    }
};

class Solution {
public:
    std::vector<std::string> scheduleBookingEmails(std::vector<std::map<std::string, std::any>>& reservations,
                                                   std::map<std::string, std::string>& emailTouchpoints,
                                                   std::vector<std::map<std::string, std::any>>& modifications) {
        // Group room changes by guest
        std::unordered_map<std::string, std::vector<Change>> change_map;
        for (int idx = 0; idx < modifications.size(); idx++) {
            auto& change = modifications[idx];
            if (change.find("new_room_type") == change.end()) {
                continue;
            }

            std::string name = std::any_cast<std::string>(change["guest_name"]);
            change_map[name].emplace_back(std::any_cast<int>(change["modification_date"]), idx,
                                          std::any_cast<std::string>(change["new_room_type"]));
        }

        // Sort modifications for each guest by (modification_date, idx)
        for (auto& [name, changes] : change_map) {
            std::sort(changes.begin(), changes.end(), [](const Change& a, const Change& b) {
                if (a.date != b.date) {
                    return a.date < b.date;
                }
                return a.idx < b.idx;
            });
        }

        // Map guest name to their reservation for quick lookup
        std::unordered_map<std::string, std::map<std::string, std::any>*> usr_to_rsv;
        for (auto& res : reservations) {
            usr_to_rsv[std::any_cast<std::string>(res["guest_name"])] = &res;
        }

        std::map<int, std::vector<std::string>> day_to_msg;
        for (auto& res : reservations) {
            std::string name = std::any_cast<std::string>(res["guest_name"]);
            std::string origRoom = std::any_cast<std::string>(res["room_type"]);
            int begin = std::any_cast<int>(res["check_in_day"]);
            int endDay = begin + std::any_cast<int>(res["stay_length"]);
            auto& userChanges = change_map[name];

            for (auto& [key, subject] : emailTouchpoints) {
                int day;
                if (key == "start") {
                    day = begin;
                } else if (key == "end") {
                    day = endDay;
                } else {
                    day = endDay + std::stoi(key);
                }

                if (day < begin)
                    continue;

                // Room strictly before this day (modification_date < day)
                std::string roomForDay = origRoom;
                for (auto& ch : userChanges) {
                    if (ch.date < day) {
                        roomForDay = ch.new_room_type;
                    } else {
                        break;
                    }
                }

                std::string msg =
                        std::to_string(day) + ": [" + subject + "] Booking: " + name + " (" + roomForDay + ")";
                day_to_msg[day].push_back(msg);

                // If a room change happens exactly on a reminder day, also emit a reminder for the new rooms.
                if (key != "start" && key != "end") {
                    for (auto& ch : userChanges) {
                        if (ch.date == day) {
                            std::string msg2 = std::to_string(day) + ": [" + subject + "] Booking: " + name + " (" +
                                               ch.new_room_type + ")";
                            day_to_msg[day].push_back(msg2);
                        }
                    }
                }
            }
        }

        // Generate [Room Change] emails
        for (auto& change : modifications) {
            if (change.find("new_room_type") == change.end())
                continue;
            std::string name = std::any_cast<std::string>(change["guest_name"]);
            std::string newRoom = std::any_cast<std::string>(change["new_room_type"]);
            int changeDate = std::any_cast<int>(change["modification_date"]);

            if (usr_to_rsv.find(name) != usr_to_rsv.end()) {
                auto& res = *usr_to_rsv[name];
                int begin = std::any_cast<int>(res["check_in_day"]);
                int endDay = begin + std::any_cast<int>(res["stay_length"]);
                if (begin <= changeDate && changeDate <= endDay) {
                    std::string msg =
                            std::to_string(changeDate) + ": [Room Change] Booking: " + name + " (" + newRoom + ")";
                    day_to_msg[changeDate].push_back(msg);
                }
            }
        }

        std::vector<std::string> result;
        for (auto& [day, messages] : day_to_msg) {
            for (auto& msg : messages) {
                result.push_back(msg);
            }
        }
        return result;
    }

    static void test1() {
        std::cout << "===== Test 1 =====" << std::endl;
        Solution solution;

        std::vector<std::map<std::string, std::any>> reservations;
        std::map<std::string, std::any> res1;
        res1["guest_name"] = std::string("A");
        res1["room_type"] = std::string("Standard");
        res1["check_in_day"] = 0;
        res1["stay_length"] = 30;
        reservations.push_back(res1);

        std::map<std::string, std::any> res2;
        res2["guest_name"] = std::string("B");
        res2["room_type"] = std::string("Suite");
        res2["check_in_day"] = 1;
        res2["stay_length"] = 15;
        reservations.push_back(res2);

        std::map<std::string, std::string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-15"] = "Upcoming Checkout";
        emailTouchpoints["end"] = "Thank You";

        std::vector<std::map<std::string, std::any>> modifications;
        std::map<std::string, std::any> mod1;
        mod1["guest_name"] = std::string("A");
        mod1["new_room_type"] = std::string("Suite");
        mod1["modification_date"] = 5;
        modifications.push_back(mod1);

        auto res = solution.scheduleBookingEmails(reservations, emailTouchpoints, modifications);
        for (const auto& msg : res) {
            std::cout << msg << std::endl;
        }
        // Expected:
        // [
        //     "0: [Welcome] Booking: A (Standard)",
        //     "1: [Upcoming Checkout] Booking: B (Suite)",
        //     "1: [Welcome] Booking: B (Suite)",
        //     "5: [Room Change] Booking: A (Suite)",
        //     "15: [Upcoming Checkout] Booking: A (Suite)",
        //     "16: [Thank You] Booking: B (Suite)",
        //     "30: [Thank You] Booking: A (Suite)",
        // ]
    }

    static void test2() {
        std::cout << "\n===== Test 2 =====" << std::endl;
        Solution solution;

        std::vector<std::map<std::string, std::any>> reservations;
        std::map<std::string, std::any> res1;
        res1["guest_name"] = std::string("C");
        res1["room_type"] = std::string("Economy");
        res1["check_in_day"] = 0;
        res1["stay_length"] = 10;
        reservations.push_back(res1);

        std::map<std::string, std::string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-3"] = "Reminder";
        emailTouchpoints["end"] = "Thank You";

        std::vector<std::map<std::string, std::any>> modifications;
        std::map<std::string, std::any> mod1;
        mod1["guest_name"] = std::string("C");
        mod1["new_room_type"] = std::string("Premium");
        mod1["modification_date"] = 7;
        modifications.push_back(mod1);

        auto res = solution.scheduleBookingEmails(reservations, emailTouchpoints, modifications);
        for (const auto& msg : res) {
            std::cout << msg << std::endl;
        }
        // Expected:
        // [
        //     "0: [Welcome] Booking: C (Economy)",
        //     "7: [Reminder] Booking: C (Economy)",
        //     "7: [Reminder] Booking: C (Premium)",
        //     "7: [Room Change] Booking: C (Premium)",
        //     "10: [Thank You] Booking: C (Premium)",
        // ]
    }

    static void test3() {
        std::cout << "\n===== Test 3 =====" << std::endl;
        Solution solution;

        std::vector<std::map<std::string, std::any>> reservations;
        std::map<std::string, std::any> res1;
        res1["guest_name"] = std::string("D");
        res1["room_type"] = std::string("Gold");
        res1["check_in_day"] = 5;
        res1["stay_length"] = 20;
        reservations.push_back(res1);

        std::map<std::string, std::string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-10"] = "Reminder";
        emailTouchpoints["end"] = "Thank You";

        std::vector<std::map<std::string, std::any>> modifications;
        std::map<std::string, std::any> mod1;
        mod1["guest_name"] = std::string("D");
        mod1["new_room_type"] = std::string("Platinum");
        mod1["modification_date"] = 15;
        modifications.push_back(mod1);

        auto res = solution.scheduleBookingEmails(reservations, emailTouchpoints, modifications);
        for (const auto& msg : res) {
            std::cout << msg << std::endl;
        }
        // Expected:
        // [
        //     "5: [Welcome] Booking: D (Gold)",
        //     "15: [Reminder] Booking: D (Gold)",
        //     "15: [Reminder] Booking: D (Platinum)",
        //     "15: [Room Change] Booking: D (Platinum)",
        //     "25: [Thank You] Booking: D (Platinum)",
        // ]
    }

    static void test4() {
        std::cout << "\n===== Test 4 =====" << std::endl;
        Solution solution;

        std::vector<std::map<std::string, std::any>> reservations;
        std::map<std::string, std::any> res1;
        res1["guest_name"] = std::string("E");
        res1["room_type"] = std::string("Bronze");
        res1["check_in_day"] = 0;
        res1["stay_length"] = 40;
        reservations.push_back(res1);

        std::map<std::string, std::string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-30"] = "First Reminder";
        emailTouchpoints["-15"] = "Second Reminder";
        emailTouchpoints["end"] = "Thank You";

        std::vector<std::map<std::string, std::any>> modifications;
        std::map<std::string, std::any> mod1;
        mod1["guest_name"] = std::string("E");
        mod1["new_room_type"] = std::string("Silver");
        mod1["modification_date"] = 10;
        modifications.push_back(mod1);

        std::map<std::string, std::any> mod2;
        mod2["guest_name"] = std::string("E");
        mod2["new_room_type"] = std::string("Gold");
        mod2["modification_date"] = 25;
        modifications.push_back(mod2);

        auto res = solution.scheduleBookingEmails(reservations, emailTouchpoints, modifications);
        for (const auto& msg : res) {
            std::cout << msg << std::endl;
        }
        // Expected:
        // [
        //     "0: [Welcome] Booking: E (Bronze)",
        //     "10: [First Reminder] Booking: E (Bronze)",
        //     "10: [First Reminder] Booking: E (Silver)",
        //     "10: [Room Change] Booking: E (Silver)",
        //     "25: [Second Reminder] Booking: E (Silver)",
        //     "25: [Second Reminder] Booking: E (Gold)",
        //     "25: [Room Change] Booking: E (Gold)",
        //     "40: [Thank You] Booking: E (Gold)",
        // ]
    }

    static void test5() {
        std::cout << "\n===== Test 5 =====" << std::endl;
        Solution solution;

        std::vector<std::map<std::string, std::any>> reservations;

        std::map<std::string, std::any> res1;
        res1["guest_name"] = std::string("F");
        res1["room_type"] = std::string("Basic");
        res1["check_in_day"] = 0;
        res1["stay_length"] = 30;
        reservations.push_back(res1);

        std::map<std::string, std::any> res2;
        res2["guest_name"] = std::string("G");
        res2["room_type"] = std::string("Pro");
        res2["check_in_day"] = 5;
        res2["stay_length"] = 20;
        reservations.push_back(res2);

        std::map<std::string, std::any> res3;
        res3["guest_name"] = std::string("H");
        res3["room_type"] = std::string("Plus");
        res3["check_in_day"] = 10;
        res3["stay_length"] = 15;
        reservations.push_back(res3);

        std::map<std::string, std::string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-10"] = "Reminder";
        emailTouchpoints["end"] = "Thank You";

        std::vector<std::map<std::string, std::any>> modifications;

        std::map<std::string, std::any> mod1;
        mod1["guest_name"] = std::string("F");
        mod1["new_room_type"] = std::string("Premium");
        mod1["modification_date"] = 10;
        modifications.push_back(mod1);

        std::map<std::string, std::any> mod2;
        mod2["guest_name"] = std::string("G");
        mod2["new_room_type"] = std::string("Enterprise");
        mod2["modification_date"] = 10;
        modifications.push_back(mod2);

        std::map<std::string, std::any> mod3;
        mod3["guest_name"] = std::string("F");
        mod3["new_room_type"] = std::string("Ultimate");
        mod3["modification_date"] = 20;
        modifications.push_back(mod3);

        auto res = solution.scheduleBookingEmails(reservations, emailTouchpoints, modifications);
        for (const auto& msg : res) {
            std::cout << msg << std::endl;
        }
        // Expected:
        // [
        //     "0: [Welcome] Booking: F (Basic)",
        //     "5: [Welcome] Booking: G (Pro)",
        //     "10: [Room Change] Booking: F (Premium)",
        //     "10: [Room Change] Booking: G (Enterprise)",
        //     "10: [Welcome] Booking: H (Plus)",
        //     "15: [Reminder] Booking: G (Enterprise)",
        //     "15: [Reminder] Booking: H (Plus)",
        //     "20: [Reminder] Booking: F (Premium)",
        //     "20: [Reminder] Booking: F (Ultimate)",
        //     "20: [Room Change] Booking: F (Ultimate)",
        //     "25: [Thank You] Booking: G (Enterprise)",
        //     "25: [Thank You] Booking: H (Plus)",
        //     "30: [Thank You] Booking: F (Ultimate)",
        // ]
    }
};

int main() {
    Solution::test1();
    Solution::test2();
    Solution::test3();
    Solution::test4();
    Solution::test5();
    return 0;
}
/*
Follow-up 2:
In addition to the previous room change event, the modifications list can now also include stay extension events. Each
extension entry contains:

"guest_name": Guest's name (string).
"extension_days": Number of days to extend the stay (integer).
"modification_date": The date when the extension occurs (integer).
When a stay extension happens:

Schedule a "[Extended]" email on modification_date using the current room type at that moment
The booking's end date is increased by extension_days
All future notifications (e.g., upcoming, thank you) are recalculated based on the new end date
Room changes and extensions may occur in any order. Always process modifications in chronological order by their
modification_date for each guest.

Constraints:

All dates are non-negative integers
Example:

Input:
reservations = [
  {
    "guest_name": "A",
    "room_type": "Standard",
    "check_in_day": 0,
    "stay_length": 30
  },
  {
    "guest_name": "B",
    "room_type": "Suite",
    "check_in_day": 1,
    "stay_length": 15
  }
],
emailTouchpoints = {
  "start": "Welcome",
  "-15": "Upcoming Checkout",
  "end": "Thank You"
},
modifications = [
  {
    "guest_name": "A",
    "new_room_type": "Suite",
    "modification_date": 5
  },
  {
    "guest_name": "B",
    "extension_days": 15,
    "modification_date": 3
  }
]

Output: ["0: [Welcome] Booking: A (Standard)",
         "1: [Welcome] Booking: B (Suite)",
         "1: [Upcoming Checkout] Booking: B (Suite)",
         "3: [Extended] Booking: B (Suite)",
         "5: [Room Change] Booking: A (Suite)",
         "15: [Upcoming Checkout] Booking: A (Suite)",
         "16: [Upcoming Checkout] Booking: B (Suite)",
         "30: [Thank You] Booking: A (Suite)",
         "31: [Thank You] Booking: B (Suite)"]

Explanation: The email sending schedule is calculated as follows:

"Guest A" (Standard → Suite on day 5):
Day 0: Welcome with Standard
Day 5: Changed to Suite
Day 15: Upcoming Checkout with Suite
Day 30: Thank You with Suite
"Guest B" (extends by 15 days on day 3):
Day 1: Welcome and Upcoming Checkout (before extension, end = 16)
Day 3: Extended (extension pushes end from 16 → 31)
Day 16: Upcoming Checkout (15 days before new end: 31 - 15 = 16)
Day 31: Thank You (new end date)
 */
struct Change {
    int date, idx;
    std::string newRoomType;
    Change(int date, int idx, std::string newRoomType) : date(date), idx(idx), newRoomType(newRoomType) {
    }
};

struct Extension {
    int date, days;
    Extension(int date, int days) : date(date), days(days) {
    }
};

class Solution {
public:
    std::vector<std::string> scheduleBookingEmails(std::vector<std::map<std::string, std::any>>& reservations,
                                                   std::map<std::string, std::string>& emailTouchpoints,
                                                   std::vector<std::map<std::string, std::any>>& modifications) {
        // Group room changes and extensions by guest
        std::unordered_map<std::string, std::vector<Change>> usr_to_room_change;
        std::unordered_map<std::string, std::vector<Extension>> usr_to_date_extension;
        for (int idx = 0; idx < modifications.size(); idx++) {
            auto& change = modifications[idx];
            std::string name = std::any_cast<std::string>(change["guest_name"]);

            if (change.find("new_room_type") != change.end()) {
                usr_to_room_change[name].emplace_back(std::any_cast<int>(change["modification_date"]), idx,
                                                 std::any_cast<std::string>(change["new_room_type"]));
            }

            if (change.find("extension_days") != change.end()) {
                usr_to_date_extension[name].emplace_back(std::any_cast<int>(change["modification_date"]),
                                                std::any_cast<int>(change["extension_days"]));
            }
        }

        // Sort modifications for each guest by (modification_date, idx)
        for (auto& [name, changes] : usr_to_room_change) {
            std::sort(changes.begin(), changes.end(), [](const Change& a, const Change& b) {
                if (a.date != b.date)
                    return a.date < b.date;
                return a.idx < b.idx;
            });
        }
        for (auto& [name, exts] : usr_to_date_extension) {
            std::sort(exts.begin(), exts.end(), [](const Extension& a, const Extension& b) { return a.date < b.date; });
        }

        // Map guest name to their reservation for quick lookup
        std::unordered_map<std::string, std::map<std::string, std::any>*> accountMap;
        for (auto& res : reservations) {
            accountMap[std::any_cast<std::string>(res["guest_name"])] = &res;
        }

        std::map<int, std::vector<std::string>> day_to_msg;
        for (auto& res : reservations) {
            std::string name = std::any_cast<std::string>(res["guest_name"]);
            std::string origRoom = std::any_cast<std::string>(res["room_type"]);
            int begin = std::any_cast<int>(res["check_in_day"]);
            int baseEnd = begin + std::any_cast<int>(res["stay_length"]);

            auto& userRoomChanges = usr_to_room_change[name];
            auto& userExtensions = usr_to_date_extension[name];

            int currentEnd = baseEnd;
            for (auto& [key, subject] : emailTouchpoints) {
                if (key == "start") {
                    // Welcome email always at begin
                    int day = begin;
                    std::string roomForDay = origRoom;

                    std::string msg =
                            std::to_string(day) + ": [" + subject + "] Booking: " + name + " (" + roomForDay + ")";
                    day_to_msg[day].push_back(msg);
                } else if (key == "end") {
                    // Thank You email at final end date
                    int finalEnd = baseEnd;
                    for (auto& ext : userExtensions) {
                        finalEnd += ext.days;
                    }

                    std::string roomForDay = origRoom;
                    for (auto& ch : userRoomChanges) {
                        if (ch.date < finalEnd) {
                            roomForDay = ch.newRoomType;
                        }
                        else {
                            break;
                        }
                    }
                    std::string msg =
                            std::to_string(finalEnd) + ": [" + subject + "] Booking: " + name + " (" + roomForDay + ")";
                    day_to_msg[finalEnd].push_back(msg);
                } else {
                    // Reminder emails
                    int offset = std::stoi(key);
                    currentEnd = baseEnd;
                    int prevExtDate = begin;

                    for (int i = 0; i < userExtensions.size(); i++) {
                        auto& ext = userExtensions[i];
                        int extDate = ext.date;
                        int extAmount = ext.days;
                        int reminderDay = currentEnd + offset;

                        // Only schedule if reminder falls before the next extension
                        if (prevExtDate <= reminderDay && reminderDay < extDate && reminderDay >= begin) {
                            std::string roomForDay = origRoom;
                            for (auto& ch : userRoomChanges) {
                                if (ch.date < reminderDay)
                                    roomForDay = ch.newRoomType;
                                else
                                    break;
                            }
                            std::string msg = std::to_string(reminderDay) + ": [" + subject + "] Booking: " + name +
                                              " (" + roomForDay + ")";
                            day_to_msg[reminderDay].push_back(msg);

                            // Check if room change happens on this reminder day
                            for (auto& ch : userRoomChanges) {
                                if (ch.date == reminderDay) {
                                    std::string msg2 = std::to_string(reminderDay) + ": [" + subject +
                                                       "] Booking: " + name + " (" + ch.newRoomType + ")";
                                    day_to_msg[reminderDay].push_back(msg2);
                                }
                            }
                        }
                        currentEnd += extAmount;
                        prevExtDate = extDate;
                    }

                    // Final segment after all extensions
                    int reminderDay = currentEnd + offset;
                    if (reminderDay >= prevExtDate && reminderDay >= begin) {
                        std::string roomForDay = origRoom;
                        for (auto& ch : userRoomChanges) {
                            if (ch.date < reminderDay)
                                roomForDay = ch.newRoomType;
                            else
                                break;
                        }
                        std::string msg = std::to_string(reminderDay) + ": [" + subject + "] Booking: " + name + " (" +
                                          roomForDay + ")";
                        day_to_msg[reminderDay].push_back(msg);
                        // Check if room change happens on this reminder day
                        for (auto& ch : userRoomChanges) {
                            if (ch.date == reminderDay) {
                                std::string msg2 = std::to_string(reminderDay) + ": [" + subject +
                                                   "] Booking: " + name + " (" + ch.newRoomType + ")";
                                day_to_msg[reminderDay].push_back(msg2);
                            }
                        }
                    }
                }
            }
        }

        // Generate [Room Change] and [Extended] emails
        for (auto& change : modifications) {
            std::string name = std::any_cast<std::string>(change["guest_name"]);
            int changeDate = std::any_cast<int>(change["modification_date"]);
            if (accountMap.find(name) == accountMap.end())
                continue;
            auto& res = *accountMap[name];
            int begin = std::any_cast<int>(res["check_in_day"]);

            // Calculate final end date
            int finalEnd = begin + std::any_cast<int>(res["stay_length"]);
            if (usr_to_date_extension.find(name) != usr_to_date_extension.end()) {
                for (auto& ext : usr_to_date_extension[name])
                    finalEnd += ext.days;
            }
            // Only add if within booking window
            if (!(begin <= changeDate && changeDate <= finalEnd))
                continue;

            if (change.find("new_room_type") != change.end()) {
                std::string newRoom = std::any_cast<std::string>(change["new_room_type"]);
                std::string msg =
                        std::to_string(changeDate) + ": [Room Change] Booking: " + name + " (" + newRoom + ")";
                day_to_msg[changeDate].push_back(msg);
            } else if (change.find("extension_days") != change.end()) {
                std::string roomForDay = std::any_cast<std::string>(res["room_type"]);
                auto& userRoomChanges = usr_to_room_change[name];
                for (auto& ch : userRoomChanges) {
                    if (ch.date < changeDate)
                        roomForDay = ch.newRoomType;
                    else
                        break;
                }
                std::string msg =
                        std::to_string(changeDate) + ": [Extended] Booking: " + name + " (" + roomForDay + ")";
                day_to_msg[changeDate].push_back(msg);
            }
        }

        std::vector<std::string> result;
        for (auto& [day, emails] : day_to_msg) {
            for (auto& email : emails) {
                result.push_back(email);
            }
        }
        return result;
    }

    static void test1() {
        std::cout << "===== Test 1 =====" << std::endl;
        Solution solution;
        std::vector<std::map<std::string, std::any>> reservations;
        std::map<std::string, std::any> res1;
        res1["guest_name"] = std::string("A");
        res1["room_type"] = std::string("Standard");
        res1["check_in_day"] = 0;
        res1["stay_length"] = 30;
        reservations.push_back(res1);
        std::map<std::string, std::any> res2;
        res2["guest_name"] = std::string("B");
        res2["room_type"] = std::string("Suite");
        res2["check_in_day"] = 1;
        res2["stay_length"] = 15;
        reservations.push_back(res2);

        std::map<std::string, std::string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-15"] = "Upcoming Checkout";
        emailTouchpoints["end"] = "Thank You";

        std::vector<std::map<std::string, std::any>> modifications;
        std::map<std::string, std::any> mod1;
        mod1["guest_name"] = std::string("A");
        mod1["new_room_type"] = std::string("Suite");
        mod1["modification_date"] = 5;
        modifications.push_back(mod1);
        std::map<std::string, std::any> mod2;
        mod2["guest_name"] = std::string("B");
        mod2["extension_days"] = 15;
        mod2["modification_date"] = 3;
        modifications.push_back(mod2);

        auto res = solution.scheduleBookingEmails(reservations, emailTouchpoints, modifications);
        for (auto& email : res) {
            std::cout << email << std::endl;
        }
        // Expected:
        // [
        //     "0: [Welcome] Booking: A (Standard)",
        //     "1: [Welcome] Booking: B (Suite)",
        //     "1: [Upcoming Checkout] Booking: B (Suite)",
        //     "3: [Extended] Booking: B (Suite)",
        //     "5: [Room Change] Booking: A (Suite)",
        //     "15: [Upcoming Checkout] Booking: A (Suite)",
        //     "16: [Upcoming Checkout] Booking: B (Suite)",
        //     "30: [Thank You] Booking: A (Suite)",
        //     "31: [Thank You] Booking: B (Suite)",
        // ]
    }

    static void test2() {
        std::cout << "\n===== Test 2 =====" << std::endl;
        Solution solution;
        std::vector<std::map<std::string, std::any>> reservations;
        std::map<std::string, std::any> res1;
        res1["guest_name"] = std::string("C");
        res1["room_type"] = std::string("Economy");
        res1["check_in_day"] = 0;
        res1["stay_length"] = 20;
        reservations.push_back(res1);

        std::map<std::string, std::string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-10"] = "Reminder";
        emailTouchpoints["end"] = "Thank You";

        std::vector<std::map<std::string, std::any>> modifications;
        std::map<std::string, std::any> mod1;
        mod1["guest_name"] = std::string("C");
        mod1["extension_days"] = 10;
        mod1["modification_date"] = 10;
        modifications.push_back(mod1);

        auto res = solution.scheduleBookingEmails(reservations, emailTouchpoints, modifications);
        for (auto& email : res) {
            std::cout << email << std::endl;
        }
        // Expected:
        // [
        //     "0: [Welcome] Booking: C (Economy)",
        //     "10: [Extended] Booking: C (Economy)",
        //     "20: [Reminder] Booking: C (Economy)",
        //     "30: [Thank You] Booking: C (Economy)",
        // ]
    }

    static void test3() {
        std::cout << "\n===== Test 3 =====" << std::endl;
        Solution solution;
        std::vector<std::map<std::string, std::any>> reservations;
        std::map<std::string, std::any> res1;
        res1["guest_name"] = std::string("D");
        res1["room_type"] = std::string("Gold");
        res1["check_in_day"] = 5;
        res1["stay_length"] = 20;
        reservations.push_back(res1);

        std::map<std::string, std::string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-10"] = "Reminder";
        emailTouchpoints["end"] = "Thank You";

        std::vector<std::map<std::string, std::any>> modifications;
        std::map<std::string, std::any> mod1;
        mod1["guest_name"] = std::string("D");
        mod1["new_room_type"] = std::string("Platinum");
        mod1["modification_date"] = 15;
        modifications.push_back(mod1);

        auto res = solution.scheduleBookingEmails(reservations, emailTouchpoints, modifications);
        for (auto& email : res) {
            std::cout << email << std::endl;
        }
        // Expected:
        // [
        //     "5: [Welcome] Booking: D (Gold)",
        //     "15: [Reminder] Booking: D (Gold)",
        //     "15: [Reminder] Booking: D (Platinum)",
        //     "15: [Room Change] Booking: D (Platinum)",
        //     "25: [Thank You] Booking: D (Platinum)",
        // ]
    }

    static void test4() {
        std::cout << "\n===== Test 4 =====" << std::endl;
        Solution solution;
        std::vector<std::map<std::string, std::any>> reservations;
        std::map<std::string, std::any> res1;
        res1["guest_name"] = std::string("E");
        res1["room_type"] = std::string("Bronze");
        res1["check_in_day"] = 0;
        res1["stay_length"] = 10;
        reservations.push_back(res1);

        std::map<std::string, std::string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-5"] = "First Reminder";
        emailTouchpoints["-2"] = "Second Reminder";
        emailTouchpoints["end"] = "Thank You";

        std::vector<std::map<std::string, std::any>> modifications;
        std::map<std::string, std::any> mod1;
        mod1["guest_name"] = std::string("E");
        mod1["extension_days"] = 10;
        mod1["modification_date"] = 5;
        modifications.push_back(mod1);
        std::map<std::string, std::any> mod2;
        mod2["guest_name"] = std::string("E");
        mod2["extension_days"] = 5;
        mod2["modification_date"] = 15;
        modifications.push_back(mod2);

        auto res = solution.scheduleBookingEmails(reservations, emailTouchpoints, modifications);
        for (auto& email : res) {
            std::cout << email << std::endl;
        }
        // Expected:
        // [
        //     "0: [Welcome] Booking: E (Bronze)",
        //     "5: [Extended] Booking: E (Bronze)",
        //     "15: [Extended] Booking: E (Bronze)",
        //     "20: [First Reminder] Booking: E (Bronze)",
        //     "23: [Second Reminder] Booking: E (Bronze)",
        //     "25: [Thank You] Booking: E (Bronze)",
        // ]
    }

    static void test5() {
        std::cout << "\n===== Test 5 =====" << std::endl;
        Solution solution;
        std::vector<std::map<std::string, std::any>> reservations;
        std::map<std::string, std::any> res1;
        res1["guest_name"] = std::string("F");
        res1["room_type"] = std::string("Basic");
        res1["check_in_day"] = 0;
        res1["stay_length"] = 20;
        reservations.push_back(res1);
        std::map<std::string, std::any> res2;
        res2["guest_name"] = std::string("G");
        res2["room_type"] = std::string("Pro");
        res2["check_in_day"] = 5;
        res2["stay_length"] = 15;
        reservations.push_back(res2);

        std::map<std::string, std::string> emailTouchpoints;
        emailTouchpoints["start"] = "Welcome";
        emailTouchpoints["-7"] = "Week Reminder";
        emailTouchpoints["-1"] = "Final Reminder";
        emailTouchpoints["end"] = "Thank You";

        std::vector<std::map<std::string, std::any>> modifications;
        std::map<std::string, std::any> mod1;
        mod1["guest_name"] = std::string("F");
        mod1["new_room_type"] = std::string("Premium");
        mod1["modification_date"] = 10;
        modifications.push_back(mod1);
        std::map<std::string, std::any> mod2;
        mod2["guest_name"] = std::string("F");
        mod2["extension_days"] = 10;
        mod2["modification_date"] = 13;
        modifications.push_back(mod2);

        auto res = solution.scheduleBookingEmails(reservations, emailTouchpoints, modifications);
        for (auto& email : res) {
            std::cout << email << std::endl;
        }
        // Expected:
        // [
        //     "0: [Welcome] Booking: F (Basic)",
        //     "5: [Welcome] Booking: G (Pro)",
        //     "10: [Room Change] Booking: F (Premium)",
        //     "13: [Extended] Booking: F (Premium)",
        //     "13: [Week Reminder] Booking: G (Pro)",
        //     "19: [Final Reminder] Booking: G (Pro)",
        //     "20: [Thank You] Booking: G (Pro)",
        //     "23: [Week Reminder] Booking: F (Premium)",
        //     "29: [Final Reminder] Booking: F (Premium)",
        //     "30: [Thank You] Booking: F (Premium)",
        // ]
    }
};

int main() {
    Solution::test1();
    Solution::test2();
    Solution::test3();
    Solution::test4();
    Solution::test5();
    return 0;
}