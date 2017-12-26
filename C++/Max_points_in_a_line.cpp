#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point {
     int x;
     int y;
     Point() : x(0), y(0) {}
     Point(int a, int b) : x(a), y(b) {}
};
int maxPoints(vector<Point> &points) {
        if (points.size() <= 2) {
            return points.size();
        }
        
        int maxLines = 0;
        
        for (int i = 0; i != points.size(); i++) {
            int same = 1;
            int vertical = 0;
            unordered_map<double, int> lines;
            lines.clear();
            
            for (int j = i + 1; j != points.size(); j++) {
                double slope = 0.0;
                if (points[i].x == points[j].x && points[i].y == points[j].y) {
                    same++;
					continue;
                }
                else if (points[i].x == points[j].x) {
                    slope = 0.0;
                }
                else if (points[i].y == points[j].y) {
                    vertical++;
                    continue;
                }
                else {
                    slope = (double) (points[i].y - points[j].y) / (points[i].x - points[j].x);
                }
                
                if (lines.find(slope) == lines.end()) {
					pair<double, int> fuck(slope, 1);
                    lines.insert(fuck);
                }
                else {
                    lines[slope]++;
                }
            }
            
            vertical += same;
            if (maxLines < vertical) {
                maxLines = vertical;
            }
            for (unordered_map<double, int>::iterator it = lines.begin(); it != lines.end(); it++) {
                if (maxLines < it->second + same) {
                    maxLines = it->second + same;
                }
            }
        }
        
        return maxLines;
    }

int main() {
	vector <Point> points;
	Point p1(1, 1);
	Point p2(1, 1);
	Point p3(1, 1);
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	maxPoints(points);
	return 0;
}