#include <iostream>
#include <vector>
using namespace std;

static bool cmp(int a, int b)
{
    // 比如 "3" < "31"但是 "331" > "313"，所以要将二者拼接起来进行比较
    string A = to_string(a)+to_string(b);
    string B = to_string(b)+to_string(a);
    return A<B;
}
string PrintMinNumber(vector<int> numbers) {
    
    sort(numbers.begin(),numbers.end(),cmp);
    string res;
    for(int i = 0; i < numbers.size(); i++){
        res += to_string(numbers[i]);
    }
    return res;
}