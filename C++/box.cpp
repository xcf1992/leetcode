#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Box {
public:
	int height;
	int length;
	int width;

	Box (int h, int l, int w) {
		height = h;
		length = l;
		width = w;
	}
};

bool bigger(Box b1, Box b2) {
	return b1.height > b2.height && b1.length > b2.length && b1.width > b2.width;
}

void calculate(vector<Box> &boxes, vector<int> &bStack, vector<int> &occupied, int &max_height) {
	bool oneMore = false;
	for (int i = 0; i < boxes.size() && !oneMore; i++) {
		if (occupied[i] == 0 && bigger(boxes[i], boxes[bStack.back()])) {
			oneMore = true;
			bStack.push_back(i);
			occupied[i] = 1;
			calculate(boxes, bStack, occupied, max_height);
			oneMore = false;
		}
	}

	int height = 0;
	for (int i = 0; i < bStack.size(); i++) {
		height += boxes[bStack[i]].height;
	}
	max_height = max(height, max_height);

	occupied[bStack.back()] = 0;
	bStack.pop_back();

	return;
}

int boxStack(vector<Box> &boxes) {
	int max_height = 0;
	vector<int> bStack;
	vector<int> occupied(boxes.size(), 0);

	for (int i = 0; i < boxes.size(); i++) {
		bStack.push_back(i);
		occupied[i] = 1;
		calculate(boxes, bStack, occupied, max_height);
	}
	
	return max_height;
}

int main() {
	Box b1(1, 7, 4);
	Box b2(2, 6, 9);
	Box b3(4, 9, 6);
	Box b4(10, 12, 8);
	Box b5(6, 2, 5);
	Box b6(3, 8, 5);
	Box b7(5, 7, 7);
	Box b8(2, 10, 16);
	Box b9(12, 15, 9);

	vector<Box> boxes;
	boxes.push_back(b1);
	boxes.push_back(b2);
	boxes.push_back(b3);
	boxes.push_back(b4);
	boxes.push_back(b5);
	boxes.push_back(b6);
	boxes.push_back(b7);
	boxes.push_back(b8);
	boxes.push_back(b9);

	cout << boxStack(boxes) << endl;
	return 0;
}