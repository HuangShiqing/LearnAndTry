#include <unordered_map>
using namespace std;
class Solution {
public:
    unordered_map<int, int> map;
    int climbStairs(int n) {
        if(n == 1)
            return 1;
        if(n == 2)
            return 2;
        
        
        if(map.count(n)==0)
        {
            int num = climbStairs(n-1)+climbStairs(n-2);
            map[n] = num;
            return num;
        }
        else
        {
            return map[n];
        }
        
        
    }
};