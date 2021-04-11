#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// https://blog.csdn.net/soulwyb/article/details/100876414

int main(int argc, char const* argv[]) {
    vector<int> list(10, 0);

    // 1.普通的for循环
    for (int n = 0; n < 50; ++n)
        std::cout << n << '\n';

    // 2.用于容器的for循环
    for (auto it = list.begin(); it != list.end(); ++it)
        cout << *it << '\n';

    // 3.

    // 4.升级版简易for循环
    for (auto item : list)
        cout << item << '\n';

    // 5.

    
    return 0;
}
