#include "OpConverter.hpp"
#include <string>

int main(int argc, char const *argv[])
{
    std::string target = "Pooling";
    auto creator = OpConverterSuit::get()->search(target);
    return 0;
}
