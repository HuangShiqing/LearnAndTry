// enum和enum class的区别 https://blog.csdn.net/sanoseiichirou/article/details/50180533
// 这篇写的太好了, 我就不赘述了, 一句话, c++里不要用enum, 用enum class

// c的写法
typedef enum {
    cpu,
    gpu
}device_c;

// 一. 默认的底层数据类型是int, 也可以手动指定任何整形(除了wchar_t)作为底层数据类型。
enum device {
    cpu,
    gpu
};

enum class device2 {
    cpu, 
    gpu
};
enum class device3: unsigned char {
    cpu, 
    gpu
};

// 二. 访问要通过域名
device cpu = device::cpu;//传统的enum好像也可以通过域名访问
device2 cpu2 = device2::cpu;

// 三. 与整形之间不会发生隐式类型转换，但是可以强转
int res = static_cast<int>(device2::cpu);//OK
device2 col = static_cast<device2>(0);//OK
