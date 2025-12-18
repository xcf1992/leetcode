/*
https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/description/
2115. Find All Possible Recipes from Given Supplies

You have information about n different recipes. You are given a string array recipes and a 2D string array ingredients.
The ith recipe has the name recipes[i], and you can create it if you have all the needed ingredients from
ingredients[i]. A recipe can also be an ingredient for other recipes, i.e., ingredients[i] may contain a string that is
in recipes.

You are also given a string array supplies containing all the ingredients that you initially have, and you have an
infinite supply of all of them.

Return a list of all the recipes that you can create. You may return the answer in any order.

Note that two recipes may contain each other in their ingredients.



Example 1:

Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
Output: ["bread"]
Explanation:
We can create "bread" since we have the ingredients "yeast" and "flour".
Example 2:

Input: recipes = ["bread","sandwich"], ingredients = [["yeast","flour"],["bread","meat"]], supplies =
["yeast","flour","meat"] Output: ["bread","sandwich"] Explanation: We can create "bread" since we have the ingredients
"yeast" and "flour". We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".
Example 3:

Input: recipes = ["bread","sandwich","burger"], ingredients =
[["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]], supplies = ["yeast","flour","meat"] Output:
["bread","sandwich","burger"] Explanation: We can create "bread" since we have the ingredients "yeast" and "flour". We
can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread". We can create "burger"
since we have the ingredient "meat" and can create the ingredients "bread" and "sandwich".


Constraints:

n == recipes.length == ingredients.length
1 <= n <= 100
1 <= ingredients[i].length, supplies.length <= 100
1 <= recipes[i].length, ingredients[i][j].length, supplies[k].length <= 10
recipes[i], ingredients[i][j], and supplies[k] consist only of lowercase English letters.
All the values of recipes and supplies combined are unique.
Each ingredients[i] does not contain any duplicate values.
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
#include <climits>
#include <set>

using namespace std;

class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients,
                                  vector<string>& supplies) {
        unordered_set<string> available_supplies(supplies.begin(), supplies.end());
        unordered_map<string, vector<string>> ingredient_to_recipes;
        unordered_map<string, unordered_set<string>> recipe_to_ingredients;
        int recipes_cnt = recipes.size();
        for (int i = 0; i < recipes_cnt; i++) {
            string& recipe = recipes[i];
            recipe_to_ingredients[recipe] = unordered_set<string>(ingredients[i].begin(), ingredients[i].end());
            for (const string& ingredient : ingredients[i]) {
                ingredient_to_recipes[ingredient].push_back(recipe);
            }
        }

        queue<string> bfs;
        for (const string& supply : supplies) {
            bfs.push(supply);
        }

        vector<string> rst;
        while (!bfs.empty()) {
            string cur_supply = bfs.front();
            bfs.pop();

            if (ingredient_to_recipes.find(cur_supply) == ingredient_to_recipes.end()) {
                continue;
            }

            for (const string& dependent_recipe : ingredient_to_recipes[cur_supply]) {
                recipe_to_ingredients[dependent_recipe].erase(cur_supply);
                if (recipe_to_ingredients[dependent_recipe].size() == 0) {
                    rst.push_back(dependent_recipe);
                    bfs.push(dependent_recipe);
                }
            }
        }
        return rst;
    }
};