#include <iostream>
using namespace std;

int main() {
  float* p1 = new float();          //申请了一个float，值为0
  float* p2 = new float(10);        //申请了一个float，值为10
  float* p3(new float());           //同p1
  float* arr_p2 = new float[10];    //申请了10个float,值为随机
  float* arr_p3 = new float[10]();  //申请了10个float,值为0
  delete p1;
  delete[] arr_p2;  //删除数组要带[]

  return 0;
}
