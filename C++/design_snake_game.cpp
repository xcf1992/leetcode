/*
353. Design Snake Game
Design a Snake game that is played on a device with screen size = width x height.
Play the game online if you are not familiar with the game.

The snake is initially positioned at the top left corner (0,0) with length = 1 unit.

You are given a list of food's positions in row-column order.
When a snake eats the food, its length and the game's score both increase by 1.

Each food appears one by one on the screen.
For example, the second food will not appear until the first food was eaten by the snake.

When a food does appear on the screen,
it is guaranteed that it will not appear on a block occupied by the snake.

Example:

Given width = 3, height = 2, and food = [[1,2],[0,1]].

Snake snake = new Snake(width, height, food);

Initially the snake appears at position (0,0) and the food at (1,2).

|S| | |
| | |F|

snake.move("R"); -> Returns 0

| |S| |
| | |F|

snake.move("D"); -> Returns 0

| | | |
| |S|F|

snake.move("R"); -> Returns 1 (Snake eats the first food and right after that, the second food appears at (0,1) )

| |F| |
| |S|S|

snake.move("U"); -> Returns 1

| |F|S|
| | |S|

snake.move("L"); -> Returns 2 (Snake eats the second food)

| |S|S|
| | |S|

snake.move("U"); -> Returns -1 (Game over because snake collides with border)
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

class SnakeGame {
private:
    vector<int> snake;
    unordered_set<int> visited;
    int W;
    int H;
    int score;
    vector<vector<int>> f;
public:
    /** Initialize your data structure here.
     @param width - screen width
     @param height - screen height
     @param food - A list of food positions
     E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0].*/
    SnakeGame(int width, int height, vector<vector<int>> food) {
        W = width;
        H = height;
        score = 0;
        snake.push_back(0);
        visited.insert(0);
        f = food;
    }

    /** Moves the snake.
     @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
     @return The game's score after the move. Return -1 if game over.
     Game over when snake crosses the screen boundary or bites its body.*/
    int move(string direction) {
        int curH = snake.front() / W;
        int curW = snake.front() % W;

        if (direction == "U") {
            curH -= 1;
        }
        else if (direction == "D") {
            curH += 1;
        }
        else if (direction == "L") {
            curW -= 1;
        }
        else {
            curW += 1;
        }

        if (curW < 0 || curH < 0 || curW >= W || curH >= H) {
            return -1;
        }

        int tail = snake.back();
        visited.erase(snake.back());
        snake.pop_back();
        int next = curH * W + curW;
        if (visited.find(next) != visited.end()) {
            return -1;
        }

        snake.insert(snake.begin(), next);
        visited.insert(next);
        if (score < f.size() && curH == f[score][0] && curW == f[score][1]) {
            score += 1;
            snake.push_back(tail);
            visited.insert(tail);
        }
        return score;
    }
};
/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame obj = new SnakeGame(width, height, food);
 * int param_1 = obj.move(direction);
*/
