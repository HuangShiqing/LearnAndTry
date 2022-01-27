// 作用
// 1. 用于malloc时设定空间. size_t的取值range是目标平台下最大可能的数组尺寸. 
//    void *malloc(size_t __size). 最典型的,在x64下,int还是4,但size_t是8
// 2. 用于数组索引.
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // 1.
    size_t size = 100;
    void* p = malloc(size);

    // 2.
    for (size_t i = 0; i < 5; i++)
    {
        ;
    }
    
    return 0;
}


