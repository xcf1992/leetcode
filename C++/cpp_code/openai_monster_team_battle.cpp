/*
https://www.hack2hire.com/companies/openai/coding-questions/69a3a99d6e73e4abccc9c106/practice?questionId=69a3aa7d6e73e4abccc9c109
Monster Team Battle

Simulate a deterministic, turn-based monster battle between two ordered teams of monsters. The system should execute the
fight step by step and produce a complete, chronological battle log that describes every event.

You are given the following definitions for Monster and Team:

class Monster {
    String name;   // Unique identifier of the monster.
    int health;   // Initial hit points.
    int attack;   // Damage inflicted when attacking.
    ...
}
class Team {
    String label;           // Team identifier, either "A" or "B".
    List<Monster> monsters; // Monsters listed in spawn order.
}
Implement the method simulateBattle(teamA, teamB) that runs the battle simulation and returns a list of event strings
according to the rules below:

The active monster of a team is the first monster in its list whose health is greater than 0.

Round Flow:

Attack: Team A's active monster attacks Team B's active monster, dealing damage equal to its attack value. Record an
"[ATTACK]" event. Apply Damage: Reduce the defender's health by the damage amount. If the defender's health becomes less
than or equal to 0, it dies immediately. Counterattack: If the defender survives, it immediately counterattacks the
original attacker using its own attack value. Record another "[ATTACK]" event. Cleanup: Whenever a monster's health
becomes less than or equal to 0, immediately log a "[DEATH]" event. The next surviving monster in that team becomes the
new active monster.

Termination: The battle ends as soon as one team has no monsters remaining with health greater than 0. At that moment,
record a "[RESULT]" event declaring the winning team.

Event Formats

Attack Event: "[ATTACK] <attacker_team>:<attacker_name> -> <defender_team>:<defender_name> | DMG=<damage> | HP:<before>
-> <after>"

Death Event: "[DEATH] <team>:<monster_name> defeated | NEXT=<next_monster_label_or_NONE>" where the value of "NEXT" is
either "<label>:<name>" or "NONE".

Result Event: "[RESULT] WINNER=<team>"

You may assume a monster of team A always starts the first attack.

Constraints:

Team size is less than 104
1 ≤ health, attack ≤ 109
Example:

Input:
["Monster", "Monster", "Team", "Team", "simulateBattle"]
[["Dragon", 10, 5], ["Goblin", 12, 3], ["A", monster1], ["B", monster2], [teamA, teamB], []]

Output:
[
  "[ATTACK] A:Dragon -> B:Goblin | DMG=5 | HP:12 -> 7",
  "[ATTACK] B:Goblin -> A:Dragon | DMG=3 | HP:10 -> 7",
  "[ATTACK] A:Dragon -> B:Goblin | DMG=5 | HP:7 -> 2",
  "[ATTACK] B:Goblin -> A:Dragon | DMG=3 | HP:7 -> 4",
  "[ATTACK] A:Dragon -> B:Goblin | DMG=5 | HP:2 -> 0",
  "[DEATH] B:Goblin defeated | NEXT=NONE",
  "[RESULT] WINNER=A"
]

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
#include <sstream>
using namespace std;

// struct Monster {
//     string name;
//     int health;
//     int attack;
//
//     Monster(string name, int health, int attack) : name(name), health(health), attack(attack) {
//     }
// };

class Team {
public:
    string label;
    vector<Monster> monsters;
    int activeIdx;

    Team(string label, vector<Monster> monsters) : label(label), monsters(monsters), activeIdx(0) {
    }

    Monster* getActive() {
        if (activeIdx < monsters.size()) {
            return &monsters[activeIdx];
        }
        return nullptr;
    }

    string advanceAndNextLabel() {
        activeIdx = activeIdx + 1;
        if (activeIdx < monsters.size()) {
            return label + ":" + monsters[activeIdx].name;
        }
        return "NONE";
    }

    bool hasAlive() {
        return activeIdx < monsters.size();
    }
};

class Solution {
public:
    vector<string> simulateBattle(Team& teamA, Team& teamB) {
        vector<string> rst;
        while (teamA.hasAlive() && teamB.hasAlive()) {
            Monster* attacker = teamA.getActive();
            Monster* defender = teamB.getActive();

            int def_hp_before = defender->health;
            defender->health = max(0, def_hp_before - attacker->attack);

            stringstream ss;
            ss << "[ATTACK] A:" << attacker->name << " -> B:" << defender->name << " | DMG=" << attacker->attack
               << " | HP:" << def_hp_before << " -> " << defender->health;
            rst.push_back(ss.str());

            if (defender->health == 0) {
                string next_monster = teamB.advanceAndNextLabel();
                stringstream ss2;
                ss2 << "[DEATH] B:" << defender->name << " defeated | NEXT=" << next_monster;
                rst.push_back(ss2.str());
                continue;
            }

            int att_hp_before = attacker->health;
            attacker->health = max(0, att_hp_before - defender->attack);

            stringstream ss3;
            ss3 << "[ATTACK] B:" << defender->name << " -> A:" << attacker->name << " | DMG=" << defender->attack
                << " | HP:" << att_hp_before << " -> " << attacker->health;
            rst.push_back(ss3.str());

            if (attacker->health == 0) {
                string next_monster = teamA.advanceAndNextLabel();
                stringstream ss4;
                ss4 << "[DEATH] A:" << attacker->name << " defeated | NEXT=" << next_monster;
                rst.push_back(ss4.str());
            }
        }

        string winner = teamA.hasAlive() ? "A" : "B";
        rst.push_back("[RESULT] WINNER=" + winner);
        return rst;
    }

    static void test1() {
        cout << "===== Test 1 =====" << endl;

        Solution solution;
        Monster monster1("Dragon", 10, 5);
        Monster monster2("Goblin", 12, 3);
        Team teamA("A", {monster1});
        Team teamB("B", {monster2});

        vector<string> log = solution.simulateBattle(teamA, teamB);
        cout << "[" << endl;
        for (const string& entry : log) {
            cout << "  \"" << entry << "\"," << endl;
        }
        cout << "]" << endl;
        // Expected:
        // [
        //   "[ATTACK] A:Dragon -> B:Goblin | DMG=5 | HP:12 -> 7",
        //   "[ATTACK] B:Goblin -> A:Dragon | DMG=3 | HP:10 -> 7",
        //   "[ATTACK] A:Dragon -> B:Goblin | DMG=5 | HP:7 -> 2",
        //   "[ATTACK] B:Goblin -> A:Dragon | DMG=3 | HP:7 -> 4",
        //   "[ATTACK] A:Dragon -> B:Goblin | DMG=5 | HP:2 -> 0",
        //   "[DEATH] B:Goblin defeated | NEXT=NONE",
        //   "[RESULT] WINNER=A"
        // ]
    }

    static void test2() {
        cout << "===== Test 2 =====" << endl;

        Solution solution;
        Monster monster1("Warrior", 5, 4);
        Monster monster2("Goblin", 3, 1);
        Monster monster3("Orc", 10, 2);
        Team teamA("A", {monster1});
        Team teamB("B", {monster2, monster3});

        vector<string> log = solution.simulateBattle(teamA, teamB);
        cout << "[" << endl;
        for (const string& entry : log) {
            cout << "  \"" << entry << "\"," << endl;
        }
        cout << "]" << endl;
        // Expected:
        // [
        //   "[ATTACK] A:Warrior -> B:Goblin | DMG=4 | HP:3 -> 0"
        //   "[DEATH] B:Goblin defeated | NEXT=B:Orc"
        //   "[ATTACK] A:Warrior -> B:Orc | DMG=4 | HP:10 -> 6"
        //   "[ATTACK] B:Orc -> A:Warrior | DMG=2 | HP:5 -> 3"
        //   "[ATTACK] A:Warrior -> B:Orc | DMG=4 | HP:6 -> 2"
        //   "[ATTACK] B:Orc -> A:Warrior | DMG=2 | HP:3 -> 1"
        //   "[ATTACK] A:Warrior -> B:Orc | DMG=4 | HP:2 -> 0"
        //   "[DEATH] B:Orc defeated | NEXT=NONE"
        //   "[RESULT] WINNER=A"
        // ]
    }

    static void test3() {
        cout << "===== Test 3 =====" << endl;

        Solution solution;
        Monster monster1("Knight", 10, 3);
        Monster monster2("Mage", 6, 5);
        Monster monster3("Goblin", 4, 2);
        Monster monster4("Troll", 15, 4);
        Monster monster5("Dragon", 8, 6);
        Team teamA("A", {monster1, monster2});
        Team teamB("B", {monster3, monster4, monster5});

        vector<string> log = solution.simulateBattle(teamA, teamB);
        cout << "[" << endl;
        for (const string& entry : log) {
            cout << "  \"" << entry << "\"," << endl;
        }
        cout << "]" << endl;
        // Expected:
        // [
        //   "[ATTACK] A:Knight -> B:Goblin | DMG=3 | HP:4 -> 1",
        //   "[ATTACK] B:Goblin -> A:Knight | DMG=2 | HP:10 -> 8",
        //   "[ATTACK] A:Knight -> B:Goblin | DMG=3 | HP:1 -> 0",
        //   "[DEATH] B:Goblin defeated | NEXT=B:Troll",
        //   "[ATTACK] A:Knight -> B:Troll | DMG=3 | HP:15 -> 12",
        //   "[ATTACK] B:Troll -> A:Knight | DMG=4 | HP:8 -> 4",
        //   "[ATTACK] A:Knight -> B:Troll | DMG=3 | HP:12 -> 9",
        //   "[ATTACK] B:Troll -> A:Knight | DMG=4 | HP:4 -> 0",
        //   "[DEATH] A:Knight defeated | NEXT=A:Mage",
        //   "[ATTACK] A:Mage -> B:Troll | DMG=5 | HP:9 -> 4",
        //   "[ATTACK] B:Troll -> A:Mage | DMG=4 | HP:6 -> 2",
        //   "[ATTACK] A:Mage -> B:Troll | DMG=5 | HP:4 -> 0",
        //   "[DEATH] B:Troll defeated | NEXT=B:Dragon",
        //   "[ATTACK] A:Mage -> B:Dragon | DMG=5 | HP:8 -> 3",
        //   "[ATTACK] B:Dragon -> A:Mage | DMG=6 | HP:2 -> 0",
        //   "[DEATH] A:Mage defeated | NEXT=NONE",
        //   "[RESULT] WINNER=B",
        // ]
    }

    static void test4() {
        cout << "===== Test 4 =====" << endl;

        Solution solution;
        Monster monster1("Dragon", 20, 5);
        Team teamA("A", {monster1});
        Team teamB("B", {});

        vector<string> log = solution.simulateBattle(teamA, teamB);
        cout << "[" << endl;
        for (const string& entry : log) {
            cout << "  \"" << entry << "\"," << endl;
        }
        cout << "]" << endl;
        // Expected:
        // [
        //   "[RESULT] WINNER=A"
        // ]
    }
};

int main() {
    Solution::test1();
    Solution::test2();
    Solution::test3();
    Solution::test4();
    return 0;
}

/*
Follow-up:
In this follow-up, the monster battle simulator is enhanced so that each monster now has types and weaknesses. These
additional attributes introduce damage multipliers that can significantly influence how battles unfold.

class Monster {
    String name;
    int health;
    int attack;

    String type; // The monster's elemental category (e.g., "Fire", "Water").
    List<String> weakness; // A list of types this monster is vulnerable to.
    ...
}
Implement the method simulateBattle(teamA, teamB) that executes the battle simulation and returns a list of event
strings based on the updated rules described below:

New Damage Rule

When an attacker hits a defender, the final damage depends on the interaction between their types:

If the defender's weakness list includes the attacker's type, the damage is doubled.
If the attacker's weakness list includes the defender's type, the damage is halved (floor division toward 0).
Otherwise, the damage remains unchanged.
All adjusted damage values must be correctly reflected in the "[ATTACK]" event logs.

Constraints:

Team size is less than 104
1 ≤ health, attack ≤ 109
type and weakness strings are non-empty and consist of alphanumeric characters.
Example:

Input:
["Monster", "Monster", "Team", "Team", "simulateBattle"]
[["FireMon", 20, 10, "Fire", ["Water"]], ["GrassMon", 15, 5, "Grass", ["Fire"]], ["A", monster1], ["B", monster2],
[teamA, teamB]]

Output:
[
  "[ATTACK] A:FireMon -> B:GrassMon | DMG=20 | HP:15 -> 0",
  "[DEATH] B:GrassMon defeated | NEXT=NONE",
  "[RESULT] WINNER=A"
]
*/

class Monster {
public:
    string name;
    int health;
    int attack;
    string type;
    vector<string> weakness;

    Monster(string name, int health, int attack, string type, vector<string> weakness) {
        this->name = name;
        this->health = health;
        this->attack = attack;
        this->type = type;
        this->weakness = weakness;
    }
};

class Team {
public:
    string label;
    vector<Monster> monsters;
    int activeIdx;

    Team(string label, vector<Monster> monsters) {
        this->label = label;
        this->monsters = monsters;
        this->activeIdx = 0;
    }

    Monster* getActive() {
        if (activeIdx < monsters.size()) {
            return &monsters[activeIdx];
        }
        return nullptr;
    }

    string advanceAndNextLabel() {
        activeIdx = activeIdx + 1;
        if (activeIdx < monsters.size()) {
            return label + ":" + monsters[activeIdx].name;
        }
        return "NONE";
    }

    bool hasAlive() {
        return activeIdx < monsters.size();
    }
};

class Solution {
private:
    double get_dmg_coeff(Monster& attacker, Monster& defender) {
        if (find(defender.weakness.begin(), defender.weakness.end(), attacker.type) != defender.weakness.end()) {
            return 2.0;
        }
        if (find(attacker.weakness.begin(), attacker.weakness.end(), defender.type) != attacker.weakness.end()) {
            return 0.5;
        }
        return 1.0;
    }
public:
    vector<string> simulateBattle(Team& teamA, Team& teamB) {
        vector<string> rst;
        while (teamA.hasAlive() && teamB.hasAlive()) {
            Monster* attacker = teamA.getActive();
            Monster* defender = teamB.getActive();

            int def_hp_before = defender->health;
            int real_dmg = attacker->attack * get_dmg_coeff(*attacker, *defender);
            defender->health = max(0, def_hp_before - real_dmg);

            stringstream ss;
            ss << "[ATTACK] A:" << attacker->name << " -> B:" << defender->name << " | DMG=" << real_dmg
               << " | HP:" << def_hp_before << " -> " << defender->health;
            rst.push_back(ss.str());

            if (defender->health == 0) {
                string next_monster = teamB.advanceAndNextLabel();
                stringstream ss2;
                ss2 << "[DEATH] B:" << defender->name << " defeated | NEXT=" << next_monster;
                rst.push_back(ss2.str());
                continue;
            }

            int att_hp_before = attacker->health;
            real_dmg = defender->attack * get_dmg_coeff(*defender, *attacker);
            attacker->health = max(0, att_hp_before - real_dmg);

            stringstream ss3;
            ss3 << "[ATTACK] B:" << defender->name << " -> A:" << attacker->name << " | DMG=" << real_dmg
                << " | HP:" << att_hp_before << " -> " << attacker->health;
            rst.push_back(ss3.str());

            if (attacker->health == 0) {
                string next_monster = teamA.advanceAndNextLabel();
                stringstream ss4;
                ss4 << "[DEATH] A:" << attacker->name << " defeated | NEXT=" << next_monster;
                rst.push_back(ss4.str());
            }
        }

        string winner = teamA.hasAlive() ? "A" : "B";
        rst.push_back("[RESULT] WINNER=" + winner);
        return rst;
    }

public:
    static void test1() {
        cout << "===== Test 1 =====" << endl;

        Solution solution;
        Monster monster1("FireMon", 20, 10, "Fire", {"Water"});
        Monster monster2("GrassMon", 15, 5, "Grass", {"Fire"});
        Team teamA("A", {monster1});
        Team teamB("B", {monster2});

        vector<string> log = solution.simulateBattle(teamA, teamB);
        for (const string& line : log) {
            cout << line << endl;
        }
        // Expected:
        // [
        //   "[ATTACK] A:FireMon -> B:GrassMon | DMG=20 | HP:15 -> 0",
        //   "[DEATH] B:GrassMon defeated | NEXT=NONE",
        //   "[RESULT] WINNER=A"
        // ]
    }

    static void test2() {
        cout << "===== Test 2 =====" << endl;

        Solution solution;
        Monster monster1("FireMon", 8, 9, "Fire", {"Water"});
        Monster monster2("WaterMon", 10, 6, "Water", {});
        Team teamA("A", {monster1});
        Team teamB("B", {monster2});

        vector<string> log = solution.simulateBattle(teamA, teamB);
        for (const string& line : log) {
            cout << line << endl;
        }
        // Expected:
        // [
        //   "[ATTACK] A:FireMon -> B:WaterMon | DMG=4 | HP:10 -> 6",
        //   "[ATTACK] B:WaterMon -> A:FireMon | DMG=12 | HP:8 -> 0",
        //   "[DEATH] A:FireMon defeated | NEXT=NONE",
        //   "[RESULT] WINNER=B"
        // ]
    }

    static void test3() {
        cout << "===== Test 3 =====" << endl;

        Solution solution;
        Monster monster1("NormalA", 10, 5, "Normal", {"Fire"});
        Monster monster2("NormalB", 12, 3, "Normal", {"Water"});
        Team teamA("A", {monster1});
        Team teamB("B", {monster2});

        vector<string> log = solution.simulateBattle(teamA, teamB);
        for (const string& line : log) {
            cout << line << endl;
        }
        // Expected:
        // [
        //   "[ATTACK] A:NormalA -> B:NormalB | DMG=5 | HP:12 -> 7",
        //   "[ATTACK] B:NormalB -> A:NormalA | DMG=3 | HP:10 -> 7",
        //   "[ATTACK] A:NormalA -> B:NormalB | DMG=5 | HP:7 -> 2",
        //   "[ATTACK] B:NormalB -> A:NormalA | DMG=3 | HP:7 -> 4",
        //   "[ATTACK] A:NormalA -> B:NormalB | DMG=5 | HP:2 -> 0",
        //   "[DEATH] B:NormalB defeated | NEXT=NONE",
        //   "[RESULT] WINNER=A"
        // ]
    }

    static void test4() {
        cout << "===== Test 4 =====" << endl;

        Solution solution;
        Monster monster1("Archer", 12, 6, "Grass", {"Fire"});
        Monster monster2("Mage", 20, 4, "Water", {"Grass"});
        Monster monster3("FireSprite", 10, 4, "Fire", {"Water"});
        Monster monster4("StoneGolem", 18, 5, "Normal", {});
        Team teamA("A", {monster1, monster2});
        Team teamB("B", {monster3, monster4});

        vector<string> log = solution.simulateBattle(teamA, teamB);
        for (const string& line : log) {
            cout << line << endl;
        }
        // Expected:
        // [
        //   "[ATTACK] A:Archer -> B:FireSprite | DMG=3 | HP:10 -> 7",
        //   "[ATTACK] B:FireSprite -> A:Archer | DMG=8 | HP:12 -> 4",
        //   "[ATTACK] A:Archer -> B:FireSprite | DMG=3 | HP:7 -> 4",
        //   "[ATTACK] B:FireSprite -> A:Archer | DMG=8 | HP:4 -> 0",
        //   "[DEATH] A:Archer defeated | NEXT=A:Mage",
        //   "[ATTACK] A:Mage -> B:FireSprite | DMG=8 | HP:4 -> 0",
        //   "[DEATH] B:FireSprite defeated | NEXT=B:StoneGolem",
        //   "[ATTACK] A:Mage -> B:StoneGolem | DMG=4 | HP:18 -> 14",
        //   "[ATTACK] B:StoneGolem -> A:Mage | DMG=5 | HP:20 -> 15",
        //   "[ATTACK] A:Mage -> B:StoneGolem | DMG=4 | HP:14 -> 10",
        //   "[ATTACK] B:StoneGolem -> A:Mage | DMG=5 | HP:15 -> 10",
        //   "[ATTACK] A:Mage -> B:StoneGolem | DMG=4 | HP:10 -> 6",
        //   "[ATTACK] B:StoneGolem -> A:Mage | DMG=5 | HP:10 -> 5",
        //   "[ATTACK] A:Mage -> B:StoneGolem | DMG=4 | HP:6 -> 2",
        //   "[ATTACK] B:StoneGolem -> A:Mage | DMG=5 | HP:5 -> 0",
        //   "[DEATH] A:Mage defeated | NEXT=NONE",
        //   "[RESULT] WINNER=B"
        // ]
    }

    static void test5() {
        cout << "===== Test 5 =====" << endl;

        Solution solution;
        Monster monster1("Blaze", 14, 7, "Fire", {"Water"});
        Monster monster2("Aqua", 10, 5, "Water", {"Electric"});
        Monster monster3("Leaf", 12, 6, "Grass", {"Fire"});
        Monster monster4("Sprout", 13, 4, "Grass", {"Fire"});
        Monster monster5("Spark", 9, 7, "Electric", {"Grass"});
        Monster monster6("Wave", 16, 3, "Water", {"Electric"});
        Monster monster7("Rock", 18, 15, "Normal", {"Water"});
        Team teamA("A", {monster1, monster2, monster3});
        Team teamB("B", {monster4, monster5, monster6, monster7});

        vector<string> log = solution.simulateBattle(teamA, teamB);
        for (const string& line : log) {
            cout << line << endl;
        }
        // Expected:
        // [
        //   "[ATTACK] A:Blaze -> B:Sprout | DMG=14 | HP:13 -> 0",
        //   "[DEATH] B:Sprout defeated | NEXT=B:Spark",
        //   "[ATTACK] A:Blaze -> B:Spark | DMG=7 | HP:9 -> 2",
        //   "[ATTACK] B:Spark -> A:Blaze | DMG=7 | HP:14 -> 7",
        //   "[ATTACK] A:Blaze -> B:Spark | DMG=7 | HP:2 -> 0",
        //   "[DEATH] B:Spark defeated | NEXT=B:Wave",
        //   "[ATTACK] A:Blaze -> B:Wave | DMG=3 | HP:16 -> 13",
        //   "[ATTACK] B:Wave -> A:Blaze | DMG=6 | HP:7 -> 1",
        //   "[ATTACK] A:Blaze -> B:Wave | DMG=3 | HP:13 -> 10",
        //   "[ATTACK] B:Wave -> A:Blaze | DMG=6 | HP:1 -> 0",
        //   "[DEATH] A:Blaze defeated | NEXT=A:Aqua",
        //   "[ATTACK] A:Aqua -> B:Wave | DMG=5 | HP:10 -> 5",
        //   "[ATTACK] B:Wave -> A:Aqua | DMG=3 | HP:10 -> 7",
        //   "[ATTACK] A:Aqua -> B:Wave | DMG=5 | HP:5 -> 0",
        //   "[DEATH] B:Wave defeated | NEXT=B:Rock",
        //   "[ATTACK] A:Aqua -> B:Rock | DMG=10 | HP:18 -> 8",
        //   "[ATTACK] B:Rock -> A:Aqua | DMG=7 | HP:7 -> 0",
        //   "[DEATH] A:Aqua defeated | NEXT=A:Leaf",
        //   "[ATTACK] A:Leaf -> B:Rock | DMG=6 | HP:8 -> 2",
        //   "[ATTACK] B:Rock -> A:Leaf | DMG=15 | HP:12 -> 0",
        //   "[DEATH] A:Leaf defeated | NEXT=NONE",
        //   "[RESULT] WINNER=B"
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