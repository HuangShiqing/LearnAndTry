#include "OpConverter.hpp"
using namespace std;

class ConvolutionConverter : public OpConverter {
public:
    // virtual void run(MNN::OpT* dstOp, const caffe::LayerParameter& parameters, const caffe::LayerParameter& weight) {        
    //     ......
    // }
    ConvolutionConverter() {
    }
    virtual ~ConvolutionConverter() {
    }
    // virtual MNN::OpType opType() {
    //     return MNN::OpType_Convolution;
    // }
    // virtual MNN::OpParameter type() {
    //     return MNN::OpParameter_Convolution2D;
    // }
};

static OpConverterRegister<ConvolutionConverter> a("Convolution");