
#include <iostream>
using namespace std;

int main()
{
    unsigned int a=1;
    unsigned int b=2;
    unsigned int c=0;
    //按位与
    c = (a&b);
    //按位或
    c = (a|b);
    //按位异或
    c = (a^b);

    //左移，非循环
    a<<=1;

    //把一个数打印16进制表示
    int num1=-1;
    cout<<hex<<num1<<endl;
    return 0;
}