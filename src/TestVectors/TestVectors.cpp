#include "TestVectors.h"

#include "vectors/cosine_10.h"
#include "vectors/cosine_3.h"

const std::map<uint32_t, TestVector> vectors = {{3,
                                                 {
                                                     "Cosine, 8 Point",
                                                     3,
                                                     &cosine_3_input[0],
                                                     &cosine_3_output[0],
                                                 }},
                                                {10,
                                                 {
                                                     "Cosine, 1024 Point",
                                                     10,
                                                     &cosine_10_input[0],
                                                     &cosine_10_output[0],
                                                 }}};