// #include <vector>//CppClass这个类依赖的但是C又不能用的头文件内容不能在这个h里include
// 设计这个wrapper时函数参数不要用C不能用的内容, 比如vector
#ifdef __cplusplus
extern "C"
{
#endif

void* wrapper_fun_init();
void wrapper_fun_delete(void* p);
void wrapper_fun(void* p);
void wrapper_fun_a(void* p);

#ifdef __cplusplus
}
#endif