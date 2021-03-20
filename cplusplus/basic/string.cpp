#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int main()
{
    //初始化
    string s;                   //初始化一个空string 对象
    string s1("qwer");          //根据字符串初始化
    string s2 = "qwer";         //同上
    string s3(s1);              //s1、s2不是一个对象
    string s4 = s1;             //同上
    string s5(4, 's');          //初始化一个长度为4每个位置放s的string
    string s6 = string(4, 's'); //同上
    string s7(s1, 2);           //将s1从index=2开始到最后都赋值给s7
    //用字符串赋值和用string赋值给一个string是不一样的，看s7和s8
    char cs[] = "12345";
    string s8(cs, 3);    //复制字符串cs的前3个字符到s当中
    string s9(s1, 2, 1); //将s1从index=2开始赋值长度为1的区域给s8长度

    //访问
    char c = s1[1];//string单个访问是一个char类型字符

    // 添加
    s9.append(s1);          //直接在s9后面添加整个s1
    s9 += s1;               //同上
    s9.append(s1, 2, 1);    //在s9后面把s1从index=2开始长度为1的区域添加上
    s9 += "ss";             //在尾部添加整个字符串
    s9.append("asdf", 3);   //把字符串的前3个添加到s9后面
    s9.insert(1, "new");    //在index=1前添加字符串"new"
    s9.insert(5, "new", 2); //在index=5前添加字符串"new"中的前2个字符

    //删除
    s9.pop_back();                      //删除最后一个字符
    s9.erase(5, 2);                     //删除从index=5开始的2个字符
    s9.erase(4);                        //删除从index=4开始后的所有字符
    s9.erase(s9.begin() + 1);           //删除迭代器指向的字符
    s9.erase(s9.begin() + 1, s9.end()); //删除迭代器区间内的字符，左闭右开

    // 类型转换
    string s10 = to_string(300); //把int数字转成string
    string s11 = "10";           //把string转成int数字
    int number = stoi(s11);      //
    string s12 = "1.2";          //把string转成flot数字，略有精度变化
    float f = stof(s11);         //

    int num = s9[0] - '0';//将string中某个字符转换成int

    char *str = new char[s8.size()];//将整个string转成字符串
    strcpy(str, s8.c_str());

    //查询
    int index = s11.find('1'); //查询字符'1'在s11中出现的位置，失败返回-1。也可以查询字符串
    string s13 = s1.substr(1,2);//start,length
    return 0;
}
