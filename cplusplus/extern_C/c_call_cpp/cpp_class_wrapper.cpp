#include <vector>//CppClass这个类依赖的但是C又不能用的头文件内容都要在这个cpp里include
#include "cpp_class_wrapper.h"
#include "cpp_class.h"

void* wrapper_fun_init(){
    return new CppClass();
}

void wrapper_fun_delete(void* p){
    delete static_cast<CppClass*>(p);
}

void wrapper_fun(void* p){
    static_cast<CppClass*>(p)->fun();
}
void wrapper_fun_a(void* p){
    static_cast<CppClass*>(p)->fun(1);
}