class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        vector<int> values(n, 0);
        for (int num : nums) {
            values[num] += num;
        }
        
        int pick = 0;
        int skip = 0;
        for (int value : values) {
            int temp = pick;
            pick = skip + value;
            skip = max(temp, skip);
        }
        return max(pick, skip);
    }
};
