/*
https://leetcode.com/problems/design-movie-rental-system/description/
1912. Design Movie Rental System

You have a movie renting company consisting of n shops. You want to implement a renting system that supports searching
for, booking, and returning movies. The system should also support generating a report of the currently rented movies.

Each movie is given as a 2D integer array entries where entries[i] = [shopi, moviei, pricei] indicates that there is a
copy of movie moviei at shop shopi with a rental price of pricei. Each shop carries at most one copy of a movie moviei.

The system should support the following functions:

Search: Finds the cheapest 5 shops that have an unrented copy of a given movie. The shops should be sorted by price in
ascending order, and in case of a tie, the one with the smaller shopi should appear first. If there are less than 5
matching shops, then all of them should be returned. If no shop has an unrented copy, then an empty list should be
returned. Rent: Rents an unrented copy of a given movie from a given shop. Drop: Drops off a previously rented copy of a
given movie at a given shop. Report: Returns the cheapest 5 rented movies (possibly of the same movie ID) as a 2D list
res where res[j] = [shopj, moviej] describes that the jth cheapest rented movie moviej was rented from the shop shopj.
The movies in res should be sorted by price in ascending order, and in case of a tie, the one with the smaller shopj
should appear first, and if there is still tie, the one with the smaller moviej should appear first. If there are fewer
than 5 rented movies, then all of them should be returned. If no movies are currently being rented, then an empty list
should be returned. Implement the MovieRentingSystem class:

MovieRentingSystem(int n, int[][] entries) Initializes the MovieRentingSystem object with n shops and the movies in
entries. List<Integer> search(int movie) Returns a list of shops that have an unrented copy of the given movie as
described above. void rent(int shop, int movie) Rents the given movie from the given shop. void drop(int shop, int
movie) Drops off a previously rented movie at the given shop. List<List<Integer>> report() Returns a list of cheapest
rented movies as described above. Note: The test cases will be generated such that rent will only be called if the shop
has an unrented copy of the movie, and drop will only be called if the shop had previously rented out the movie.



Example 1:

Input
["MovieRentingSystem", "search", "rent", "rent", "report", "drop", "search"]
[[3, [[0, 1, 5], [0, 2, 6], [0, 3, 7], [1, 1, 4], [1, 2, 7], [2, 1, 5]]], [1], [0, 1], [1, 2], [], [1, 2], [2]]
Output
[null, [1, 0, 2], null, null, [[0, 1], [1, 2]], null, [0, 1]]

Explanation
MovieRentingSystem movieRentingSystem = new MovieRentingSystem(3, [[0, 1, 5], [0, 2, 6], [0, 3, 7], [1, 1, 4], [1, 2,
7], [2, 1, 5]]); movieRentingSystem.search(1);  // return [1, 0, 2], Movies of ID 1 are unrented at shops 1, 0, and 2.
Shop 1 is cheapest; shop 0 and 2 are the same price, so order by shop number. movieRentingSystem.rent(0, 1); // Rent
movie 1 from shop 0. Unrented movies at shop 0 are now [2,3]. movieRentingSystem.rent(1, 2); // Rent movie 2 from
shop 1. Unrented movies at shop 1 are now [1]. movieRentingSystem.report();   // return [[0, 1], [1, 2]]. Movie 1 from
shop 0 is cheapest, followed by movie 2 from shop 1. movieRentingSystem.drop(1, 2); // Drop off movie 2 at shop 1.
Unrented movies at shop 1 are now [1,2]. movieRentingSystem.search(2);  // return [0, 1]. Movies of ID 2 are unrented at
shops 0 and 1. Shop 0 is cheapest, followed by shop 1.


Constraints:

1 <= n <= 3 * 105
1 <= entries.length <= 105
0 <= shopi < n
1 <= moviei, pricei <= 104
Each shop carries at most one copy of a movie moviei.
At most 105 calls in total will be made to search, rent, drop and report.
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

struct Movie {
    int shop;
    int movie;
    int price;
    bool operator<(const Movie& other) const {
        if (price != other.price) {
            return price < other.price;
        }

        if (shop != other.shop) {
            return shop < other.shop;
        }

        return movie < other.movie;
    }
};

class MovieRentingSystem {
    unordered_map<long long, Movie> all_movies_;
    unordered_map<int, set<Movie>> available_movies_;
    set<Movie> rented_movies_;

    long long key(int shop, int movie) {
        return ((long long)shop << 32) ^ movie;
    }

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (auto& e : entries) {
            int shop = e[0], movie = e[1], price = e[2];
            Movie node{shop, movie, price};
            all_movies_[key(shop, movie)] = node;
            available_movies_[movie].insert(node);
        }
    }

    vector<int> search(int movie) {
        vector<int> res;
        if (available_movies_.count(movie) == 0) {
            return res;
        }

        auto& s = available_movies_[movie];
        int count = 0;
        for (auto it = s.begin(); it != s.end() && count < 5; ++it, ++count) {
            res.push_back(it->shop);
        }
        return res;
    }

    void rent(int shop, int movie) {
        long long k = key(shop, movie);
        Movie node = all_movies_[k];
        available_movies_[movie].erase(node);
        rented_movies_.insert(node);
    }

    void drop(int shop, int movie) {
        long long k = key(shop, movie);
        Movie node = all_movies_[k];
        rented_movies_.erase(node);
        available_movies_[movie].insert(node);
    }

    vector<vector<int>> report() {
        vector<vector<int>> res;
        int count = 0;
        for (auto it = rented_movies_.begin(); it != rented_movies_.end() && count < 5; ++it, ++count) {
            res.push_back({it->shop, it->movie});
        }
        return res;
    }
};

class Movie {
public:
    int idx_;
    int price_;
    int shop_idx_;

    Movie() : idx_(-1), price_(-1), shop_idx_(-1) {
    }
    Movie(int idx, int price, int shop_id) : idx_(idx), price_(price), shop_idx_(shop_id) {
    }
};

class Shop {
public:
    int idx_;
    unordered_map<int, Movie> rented_movies_;
    unordered_map<int, Movie> unrented_movies_;

    Shop() : idx_(-1) {
    }
    Shop(int idx) : idx_(idx) {
    }
};

class MovieRentingSystem {
private:
    vector<Shop> shops_;

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        shops_.clear();
        for (int i = 0; i < n; i++) {
            shops_.push_back(Shop(i));
        }

        for (vector<int>& entry : entries) {
            int shop = entry[0];
            int movie = entry[1];
            int price = entry[2];
            shops_[shop].unrented_movies_.insert({movie, Movie(movie, price, shop)});
        }
    }

    vector<int> search(int movie) {
        vector<pair<int, int>> price_shop_of_movie;
        for (int i = 0; i < shops_.size(); i++) {
            if (shops_[i].unrented_movies_.find(movie) != shops_[i].unrented_movies_.end()) {
                price_shop_of_movie.push_back({shops_[i].unrented_movies_[movie].price_, i});
            }
        }

        sort(price_shop_of_movie.begin(), price_shop_of_movie.end(), [](pair<int, int>& a, pair<int, int>& b) {
            return a.first < b.first || (a.first == b.first && a.second < b.second);
        });

        int cnt = min(5, (int)price_shop_of_movie.size());
        vector<int> rst(cnt, 0);
        for (int i = 0; i < cnt; i++) {
            rst[i] = price_shop_of_movie[i].second;
        }
        return rst;
    }

    void rent(int shop, int movie) {
        if (shop < 0 || shop >= shops_.size()) {
            return;
        }

        Shop& cur_shop = shops_[shop];
        if (cur_shop.unrented_movies_.find(movie) == cur_shop.unrented_movies_.end()) {
            return;
        }

        cur_shop.rented_movies_[movie] = cur_shop.unrented_movies_[movie];
        cur_shop.unrented_movies_.erase(movie);
    }

    void drop(int shop, int movie) {
        if (shop < 0 || shop >= shops_.size()) {
            return;
        }

        Shop& cur_shop = shops_[shop];
        if (cur_shop.rented_movies_.find(movie) == cur_shop.rented_movies_.end()) {
            return;
        }

        cur_shop.unrented_movies_[movie] = cur_shop.rented_movies_[movie];
        cur_shop.rented_movies_.erase(movie);
    }

    vector<vector<int>> report() {
        vector<vector<int>> rented_movies;
        for (int i = 0; i < shops_.size(); i++) {
            for (auto it = shops_[i].rented_movies_.begin(); it != shops_[i].rented_movies_.end(); ++it) {
                Movie& cur_movie = it->second;
                rented_movies.push_back({cur_movie.price_, cur_movie.shop_idx_, cur_movie.idx_});
            }
        }

        sort(rented_movies.begin(), rented_movies.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]) || (a[0] == b[0] && a[1] == b[1] && a[2] < b[2]);
        });

        int cnt = min(5, (int)rented_movies.size());
        vector<vector<int>> rst(cnt);
        for (int i = 0; i < cnt; i++) {
            rst[i] = vector<int>({rented_movies[i][1], rented_movies[i][2]});
        }
        return rst;
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */
