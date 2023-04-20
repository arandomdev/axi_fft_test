#include "TestVectors/TestVectors.h"
#include <chrono>
#include <fcntl.h>
#include <fmt/core.h>
#include <iostream>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <vector>

#define CORE_BASE_ADDR 0x44000000
#define CORE_MEM_SIZE 0x10000

#define REG_VERSION 0x0000
#define REG_PERI_ID 0x0001
#define REG_SCRATCH 0x0002
#define REG_IDENT 0x0003
#define REG_NFFT 0x0004
#define REG_FFT_CONFIG 0x0010
#define REG_STATUS 0x0011
#define REG_RESET 0x0020
#define REG_INPUT_TRIG 0x0021
#define REG_CONFIG_TRIG 0x0022
#define REG_INPUT_START 0x0040

#define ITERATIONS (1 << 16)

int main() {
  int fd = open("/dev/mem", O_RDWR);
  if (fd < 1) {
    std::cout << "Unable to open mem file." << std::endl;
    return -1;
  }

  void *devMem = mmap(NULL, CORE_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
                      fd, CORE_BASE_ADDR);
  auto dev = (uint32_t *)devMem;

  // Reset Core
  *(dev + REG_RESET) = 0;
  *(dev + REG_RESET) = 1;

  // Get core configuration
  uint32_t nfft = *(dev + REG_NFFT);
  uint32_t pointSize = 1 << nfft;
  uint32_t nElements = pointSize * 2;
  uint32_t regOutputStart = REG_INPUT_START + nElements;

  // Print Data
  std::cout << "--| AXI FFT Core |--\n";
  std::cout << fmt::format("Version: {:x}\n", *(dev + REG_VERSION));
  std::cout << fmt::format("Peripheral ID: {:x}\n", *(dev + REG_PERI_ID));
  std::cout << fmt::format("Identity: {:x}\n", *(dev + REG_IDENT));
  std::cout << fmt::format("NFFT: {}\n", nfft);
  std::cout << fmt::format("Point Size: {}\n", pointSize);
  std::cout << "--------------------\n\n";

  // Get test vector
  if (vectors.find(nfft) == vectors.end()) {
    std::cout << "No test vector available to for NFFT\n\n";
  }
  const TestVector &vec = vectors.at(nfft);

  // Set config
  std::cout << "Setting config (No norm, forward)\n\n";
  *(dev + REG_FFT_CONFIG) = 0b00001;
  *(dev + REG_CONFIG_TRIG) = 1;

  std::cout << fmt::format("Performing {} iterations\n", ITERATIONS);

  std::vector<float> output(nElements);
  const auto start = std::chrono::system_clock::now();

  // Load test vector
  for (uint32_t i = 0; i < nElements; i++) {
    *(dev + REG_INPUT_START + i) =
        *reinterpret_cast<const uint32_t *>(vec.input + i);
  }

  for (uint32_t it = 0; it < ITERATIONS; it++) {
    // Trigger and wait
    *(dev + REG_INPUT_TRIG) = 1; // Any write to register
    while (!(*(dev + REG_STATUS) & 0x1)) {
    }
  }

  // Offload data
  for (uint32_t i = 0; i < nElements; i++) {
    output[i] = *reinterpret_cast<float *>((dev + regOutputStart + i));
  }
  const auto end = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> timeDelta = end - start;
  std::cout << fmt::format("Took: {}ms\n", timeDelta.count());

  // Cleanup
  munmap((void *)dev, CORE_MEM_SIZE);
  close(fd);
  return 0;
}