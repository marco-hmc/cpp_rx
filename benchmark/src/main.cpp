#include <iostream>

#include "KCLRttiCast.h"
#include "dynamicCast.h"
#include "rttiCast.h"
#include "utils.h"

int main() {
    std::cout << "  Dynamic cast test" << std::endl;
    myUtils::measure_time(testDynamicCast, 1000000);
    std::cout << "  ----------------------" << std::endl;

    std::cout << "  Rtti test" << std::endl;
    myUtils::measure_time(testRTTI, 1000000);
    std::cout << "  ----------------------" << std::endl;

    std::cout << "  KCLRtti test" << std::endl;
    myUtils::measure_time(testKCLRttiCast, 1000000);
    std::cout << "  ----------------------" << std::endl;
    return 0;
}
