#include <iostream>

namespace shunya::cuda::examples {

// Kernel definition
__global__ void VecAdd(float* vector_a, float* vector_b, int n) {
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = blockDim.x * gridDim.x;
  for (int i = index; i < n; i += stride) {
    vector_b[i] = vector_a[i] + vector_b[i];
  }
}

void RunVecAddExample() {
  int N = 1<<20; // 1M elements

  float *x = new float[N];
  float *y = new float[N];

  // Allocate Unified Memory – accessible from CPU or GPU
  cudaError_t allocErr;
  allocErr = cudaMallocManaged(&x, N * sizeof(float));
  if (allocErr != cudaSuccess) {
    std::cerr << "Failed to allocate memory for x: " << cudaGetErrorString(allocErr) << std::endl;
    return;
  }
  allocErr = cudaMallocManaged(&y, N * sizeof(float));
  if (allocErr != cudaSuccess) {
    std::cerr << "Failed to allocate memory for y: " << cudaGetErrorString(allocErr) << std::endl;
    return;
  }

  // initialize x and y arrays on the host
  for (int i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  // Run kernel on 1M elements on the CPU
  VecAdd<<<1, 1>>>(x, y, N);

  cudaError_t err = cudaGetLastError();
  if (err != cudaSuccess) {
    std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
    return;
  }

  // Wait for GPU to finish before accessing on host
  cudaDeviceSynchronize();

  // Check for errors (all values should be 3.0f)
  float maxError = 0.0f;
  for (int i = 0; i < N; i++)
    maxError = fmax(maxError, fabs(y[i]-3.0f));
  std::cout << "Max error: " << maxError << std::endl;

  // Free memory
  cudaFree(x);
  cudaFree(y);
}

} // namespace shunya::cuda::examples