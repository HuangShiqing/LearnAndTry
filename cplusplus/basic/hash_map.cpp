#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    // 初始化
    unordered_map<string, int> map;
    map["a"] = 1;
    unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};

    // 查找
    if (map.find("a") == map.end())
        cout << "not found" << endl;
    else
        cout << "found" << endl;
    if(map.count("a"))
        cout << "found" << endl;

    // 读取
    int num = map["a"];
    return 0;
}