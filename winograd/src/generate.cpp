#include <fstream>
using namespace std;

class WinogradGenerater {
public:
    // If dividedInG, make A, B not frac, else make A, G not frac
    WinogradGenerater(int computeUnit, int kernelSize, float interp = 0.5f, bool dividedInG = true);
    ~WinogradGenerater() = default;

    // std::shared_ptr<Tensor> A() const {
    //     return mA;
    // }
    // std::shared_ptr<Tensor> B() const {
    //     return mB;
    // }
    // std::shared_ptr<Tensor> G() const {
    //     return mG;
    // }

    // std::shared_ptr<Tensor> allocTransformWeight(const Tensor* originWeight, int unitCi = 4, int unitCo = 4, bool alloc = true);
    // void transformWeight(const Tensor* dest, const Tensor* source);

private:
    // std::shared_ptr<Tensor> mA;
    // std::shared_ptr<Tensor> mG;
    // std::shared_ptr<Tensor> mB;
    int mUnit;
    int mKernelSize;
};


WinogradGenerater::WinogradGenerater(int computeUnit, int kernelSize, float interp, bool dividedInG) {
    MNN_ASSERT(computeUnit > 0 && kernelSize > 0);
    mUnit       = computeUnit;
    mKernelSize = kernelSize;

    int n     = computeUnit;
    int r     = kernelSize;
    int alpha = n + r - 1;
    mG.reset(Matrix::create(r, alpha));
    mB.reset(Matrix::create(alpha, alpha));
    mA.reset(Matrix::create(n, alpha));

    std::shared_ptr<Tensor> polyBuffer(Matrix::create(alpha, 1));

    auto a   = polyBuffer->host<float>();
    a[0]     = 0.0f;
    int sign = 1;
    for (int i = 0; i < alpha - 1; ++i) {
        int value = 1 + i / 2;
        a[i + 1]  = sign * value * interp;
        sign *= -1;
    }
    // Matrix::print(polyBuffer.get());
    {
        auto A = computeA(a, alpha, n);
        Matrix::transpose(mA.get(), A.get());
    }
    auto fdiag = computeFDiag(a, alpha);
    // Matrix::print(fdiag.get());
    {
        auto A = computeA(a, alpha, r);
        Matrix::transpose(mG.get(), A.get());
        if (dividedInG) {
            Matrix::divPerLine(mG.get(), mG.get(), fdiag.get());
        }
    }
    {
        auto B = computeB(a, alpha);
        if (dividedInG) {
            Matrix::transpose(mB.get(), B.get());
            Matrix::mulPerLine(B.get(), mB.get(), fdiag.get());
            Matrix::transpose(mB.get(), B.get());
        } else {
            mB = B;
        }
    }
}

int main(int argc, char const *argv[])
{
    int unit       = atoi(argv[1]);
    int kernelSize = atoi(argv[2]);
    auto alpha     = unit + kernelSize - 1;
    float interp   = 0.5f;
    if (argc > 3) {
        interp = atof(argv[3]);
    }    
    WinogradGenerater generater(unit, kernelSize, interp);
    return 0;
}
