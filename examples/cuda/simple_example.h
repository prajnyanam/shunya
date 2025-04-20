#pragma once

#include <cuda_runtime.h>

namespace shunya::cuda::examples {

void VecAdd(float* vector_a, float* vector_b, int n);

void RunVecAddExample();

}  // namespace shunya::cuda::examples