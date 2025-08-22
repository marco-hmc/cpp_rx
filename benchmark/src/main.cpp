#include <iostream>

#include "KCLRttiCast.h"
#include "dynamicCast.h"
#include "rttiCast.h"
#include "utils.h"

int main() {
    std::cout << "  DynamicCast spend: "
              << myUtils::measure_time(testDynamicCast, 1000000) << std::endl;
    std::cout << "  ----------------------" << std::endl;

    std::cout << "  RttiCast spend: "
              << myUtils::measure_time(testRTTI, 1000000) << std::endl;
    std::cout << "  ----------------------" << std::endl;

    std::cout << "  KCLRttiCast spend: "
              << myUtils::measure_time(testKCLRttiCast, 1000000) << std::endl;
    std::cout << "  ----------------------" << std::endl;
    return 0;
}
