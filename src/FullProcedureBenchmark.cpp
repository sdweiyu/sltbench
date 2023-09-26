#include "FullProcedureBenchmark.h"

using namespace std::chrono;

namespace sltbench
{

FullProcedureBenchmark::FullProcedureBenchmark(const char *name, SLTFun function, SLTFun prepareFunc, SLTFun cleanFunc)
    : IBenchmark(name, /*supports_multicall*/ true), function_(function), prepareFunc_(prepareFunc),
      cleanFunc_(cleanFunc)
{
}

nanoseconds FullProcedureBenchmark::Measure(size_t calls_count)
{
    const auto start_tp = high_resolution_clock::now();
    for (size_t i = 0; i < calls_count; ++i)
        function_();
    const auto final_tp = high_resolution_clock::now();
    return final_tp > start_tp ? duration_cast<nanoseconds>(final_tp - start_tp) : nanoseconds(0);
    ;
}

void FullProcedureBenchmark::Prepare()
{
    prepareFunc_();
    measured_ = false;
}

void FullProcedureBenchmark::Finalize()
{
    cleanFunc_();
}

bool FullProcedureBenchmark::HasArgsToProcess()
{
    return !measured_;
}

void FullProcedureBenchmark::OnArgProcessed()
{
    measured_ = true;
}

std::string FullProcedureBenchmark::CurrentArgAsString()
{
    return {};
}

} // namespace sltbench
