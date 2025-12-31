#include <benchmark/benchmark.h>

#include "KCLRttiCast.h"
#include "dynamicCast.h"
#include "rttiCast.h"

void BM_testDynamicCast(benchmark::State& state) {
    for (auto _ : state) {
        testDynamicCast(state.range(0));
    }
}

void BM_testRTTI(benchmark::State& state) {
    for (auto _ : state) {
        testRTTI(state.range(0));
    }
}

void BM_testKCLRttiCast(benchmark::State& state) {
    for (auto _ : state) {
        testKCLRttiCast(state.range(0));
    }
}

BENCHMARK(BM_testDynamicCast)
    ->Arg(1000000)
    ->Arg(10000)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_testRTTI)->Arg(1000000)->Arg(10000)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_testKCLRttiCast)
    ->Arg(1000000)
    ->Arg(10000)
    ->Unit(benchmark::kMillisecond);
