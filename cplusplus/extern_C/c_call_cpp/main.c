// https://zhuanlan.zhihu.com/p/31295798
// https://zhuanlan.zhihu.com/p/123269132
// https://blog.csdn.net/fengfengdiandia/article/details/82704375
// [C通过wrapper调用C++库](https://blog.csdn.net/shaosunrise/article/details/81176880)
#include "cpp_class_wrapper.h"

int main(int argc, char const *argv[]) {
    void* p = wrapper_fun_init();
    wrapper_fun(p);
    wrapper_fun_a(p);
    wrapper_fun_delete(p);
    return 0;
}
