#include <string>
using namespace std;

class Solution {
public:
// 三层for循环, 第一层是双指针往两头移动, 相等则count++并继续向两头移动直到索引达到临界
// 第二层是初始索引可以从0到size-1
// 第三层是初始索引可以指向同一个数或者指向相邻的两个数
    int countSubstrings(string s) {
        int i,j;
        int n = s.size();
        int count=0;
        
        for(int k=0;k<n;k++){  
            i = k;
            j = k;
            while(i>=0&&j<n){ 
                if(s[i]==s[j]){
                    count++;
                    i--;
                    j++;            
                }
                else
                    break;
            }
        }
        for(int k=0;k<n-1;k++){  
            i = k;
            j = k+1;
            while(i>=0&&j<n){      
                if(s[i]==s[j]){
                    count++;
                    i--;
                    j++;            
                }
                else
                    break;
            }
        }

        return count;
            
    }
};