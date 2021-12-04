#include <utility>//pair
#include <tuple>//tie
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    // 初始化
    pair<int, string> map1;
    pair<int, string> map2(1, "1");
    pair<int, string> map3(map2);
    pair<int, string> map4 = make_pair(1, "1");
    pair<int, string> map5 = map4;// 拷贝构造

    // 赋值访问
    map1.first = 2;
    int a1 = map1.first;
    map1.second = "2";
    string a2 = map1.second;

    // tie解包pair
    int a3;
    string a4;
    tie(a3, a4) = map1;
    return 0;
}

