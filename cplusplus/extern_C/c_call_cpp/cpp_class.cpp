#include <stdio.h>
#include <iostream>
#include "cpp_class.h"

CppClass::CppClass(){};
CppClass::~CppClass(){};

void CppClass::fun(){
    std::cout<<"fun"<<std::endl;
}

void CppClass::fun(int a){
    std::cout<<"fun a"<<std::endl;
}