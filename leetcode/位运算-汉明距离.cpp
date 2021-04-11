

class Solution {
public:
    int hammingDistance(int x, int y) {
        int xor_ = x ^ y;
        int res = 0;
        while (xor_ != 0) {
            res += xor_&1;
            xor_ = xor_ >> 1;
        }
        return res;
    }
};