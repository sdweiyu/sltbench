#pragma once

#include "Descriptor.h"
#include "DoNotOptimize.h"

namespace sltbench {
  typedef void (*SLTFun)();

  //! calls Init and Run
  int __declspec(dllexport) Main(int argc, char** argv);

  //! initialize benchmark from command line options
  void __declspec(dllexport) Init(int argc, char** argv);

  //! run benchmarking tool
  int __declspec(dllexport) Run();

  /*!
      Register function for benchmarking

      \param name - function name
      \param func - function for benchmarking
  */
  Descriptor __declspec(dllexport)* RegisterBenchmark(const char* name, SLTFun func);

  /*!
      Register function for benchmarking

      \param name - function name
      \param func - function for benchmarking
      \param prepareFunc - function to prepare benchmarking
      \param cleanFunc - function to clean after benchmarking
  */
  Descriptor __declspec(dllexport)* RegisterBenchmark(const char* name, SLTFun func, SLTFun prepareFunc, SLTFun cleanFunc);
} // namespace sltbench

//
// define internal helpers
//

#define SLT_CONCATENATE_2_IMPL(s1, s2) s1##s2
#define SLT_CONCATENATE_2(s1, s2) SLT_CONCATENATE_2_IMPL(s1, s2)

#define SLT_DECLARE_DESCR_FUNCTION(func) ::sltbench::Descriptor *SLT_CONCATENATE_2(desc_##func, __LINE__)
#define SLT_REGISTER_FUNCTION(func) ::sltbench::RegisterBenchmark(#func, func)
#define SLT_REGISTER_FUNCTION_WITH_PREPARE_AND_CLEAN(func, prepareFunc, cleanFunc)                                     \
    ::sltbench::RegisterBenchmark(#func, func, prepareFunc, cleanFunc)
