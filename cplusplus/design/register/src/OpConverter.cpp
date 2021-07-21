#include "OpConverter.hpp"

OpConverterSuit* OpConverterSuit::global = nullptr;
OpConverter* OpConverterSuit::search(const std::string& name) {
    auto iter = mTests.find(name);
    if (iter == mTests.end()) {
        std::cout<<"can not find"<<std::endl;
        // static DefaultCaffeOpConverter converter;
        // return &converter;
    }
    else{
        std::cout<<"find"<<std::endl;
    }
    return iter->second;
}

OpConverterSuit* OpConverterSuit::get() {
    if (global == nullptr)
        global = new OpConverterSuit;
    return global;
}

OpConverterSuit::~OpConverterSuit() {
    for (auto& iter : mTests) {
        delete iter.second;
    }
    mTests.clear();
}

void OpConverterSuit::insert(OpConverter* t, const char* name) {
    mTests.insert(std::make_pair(name, t));
}