#include "OpConverter.hpp"
using namespace std;

class PoolConverter : public OpConverter {
public:
    // virtual void run(MNN::OpT* dstOp, const caffe::LayerParameter& parameters, const caffe::LayerParameter& weight);
    PoolConverter() {
    }
    virtual ~PoolConverter() {
    }
    // virtual MNN::OpType opType() {
    //     return MNN::OpType_Pooling;
    // }
    // virtual MNN::OpParameter type() {
    //     return MNN::OpParameter_Pool;
    // }
};

static OpConverterRegister<PoolConverter> a("Pooling");