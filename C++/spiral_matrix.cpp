#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<int> spiralOrder(vector<vector<int> > &matrix) {
        vector <int> result;
        result.clear();
        
        if (matrix.empty()) {
            return result;
        }
            
        int row = matrix.size();
        int column = matrix.front().size();
        int num = 0;
        int direction = 1; /*1 = right; 2 = down; 3 = left; 4 = up*/
        int tx = 0;
		int bx = 0;
		int ly = 0;
        int ry = 0;
        int i = 0;
        int j = 0;

        while (num < row * column) {
			cout << num << endl;
            switch (direction) {
                case 1:
                while (j != column - ry) {
                    result.push_back(matrix.at(i).at(j));
                    j++;
                    num++;
                }
                tx++;
                i = i + 1;
                j = j - 1;
                direction = 2;
                break;
                    
                case 2:
                while (i != row - bx) {
                    result.push_back(matrix.at(i).at(j));
                    i++;
                    num++;
                }
                ry++;
                i = i - 1;
                j = j - 1;
                direction = 3;
                break;
                        
                case 3:
                while (j >= ly) {
                    result.push_back(matrix.at(i).at(j));
                    j--;
                    num++;
                }
                bx++;
                i = i - 1;
                j = j + 1;
                direction = 4;
                break;
                    
                case 4:
                while (i >= tx) {
                   result.push_back(matrix.at(i).at(j));
                   i--;
                   num++;
                }
                ly++;
                i = i + 1;
                j = j + 1;
                direction = 1;
                break;
            }
        }
            
        return result;
    }

int main() {
	vector<int> row1;
	row1.push_back(1);
	vector<int> row2;
	row2.push_back(4);
	row2.push_back(5);
	row2.push_back(6);
	vector<int> row3;
	row3.push_back(7);
	row3.push_back(8);
	row3.push_back(9);

	vector<vector<int>> matrix;
	matrix.push_back(row1);
	spiralOrder(matrix);
	return 0;
}