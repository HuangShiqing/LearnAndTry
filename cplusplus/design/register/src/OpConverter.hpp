#include <map>
#include <string>
#include <vector>
#include <iostream>
class OpConverter {
    friend class OpConverterSuit;

public:
    // virtual void run(MNN::OpT* dstOp, const caffe::LayerParameter& parameters, const caffe::LayerParameter& weight) =
    // 0; virtual MNN::OpParameter type() = 0; virtual MNN::OpType opType() = 0;
    OpConverter() {}
    virtual ~OpConverter() {}

private:
};

class OpConverterSuit {
public:
    static OpConverterSuit* get();
    void insert(OpConverter* t, const char* name);

    OpConverter* search(const std::string& name);

    OpConverterSuit() {}
    ~OpConverterSuit();

private:
    static OpConverterSuit* global;
    std::map<std::string, OpConverter*> mTests;
};

template <class T>
class OpConverterRegister {
public:
    OpConverterRegister(const char* claim) {
        T* test             = new T;
        OpConverterSuit* ts = OpConverterSuit::get();
        ts->insert(test, claim);
        std::cout<<claim<<"  registered"<<std::endl;
    }
    ~OpConverterRegister() {
    }
};