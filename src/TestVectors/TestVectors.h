#ifndef TEST_VECTOR_H
#define TEST_VECTOR_H

#include "stdint.h"
#include <map>
#include <string>

struct TestVector {
  std::string name;
  uint32_t nfft;
  const float *input;
  const float *output;
};

extern const std::map<uint32_t, TestVector> vectors;

#endif // TEST_VECTOR_H