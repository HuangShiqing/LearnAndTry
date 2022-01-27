rm -rf build
mkdir build

CXX="g++"
CXXFLAGS="-std=c++11 -fPIC"
CC="gcc"
CCFLAGS=""

$CXX $CXXFLAGS cpp_class.cpp -c -o build/cpp_class.o
$CXX $CXXFLAGS cpp_class_wrapper.cpp -c -o build/cpp_class_wrapper.o
$CC $CCFLAGS main.c -c -o build/main.o

$CXX -shared build/cpp_class.o build/cpp_class_wrapper.o -o build/libcxx.so
$CC build/main.o -o build/main -Lbuild -lcxx -Wl,-rpath=build