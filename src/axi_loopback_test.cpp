#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>

#define CORE_BASE_ADDR 0x44000000
#define CORE_MEM_SIZE 0x10000

#define REG_VERSION 0x0000
#define REG_ID 0x0001
#define REG_SCRATCH 0x0002
#define REG_RESET 0x0020

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

  // Print core data
  std::cout << "--| AXI FFT Core |--\n";
  std::cout << "Version: " << *(dev + REG_VERSION) << "\n";
  std::cout << "Peripheral ID: " << *(dev + REG_ID) << "\n";
  std::cout << "--------------------\n\n";

  std::cout << "Scratch Before: " << *(dev + REG_SCRATCH) << "\n";
  *(dev + REG_SCRATCH) = 0xDEADBEEF;
  std::cout << "Scratch After: " << *(dev + REG_SCRATCH) << "\n";

  // Cleanup
  munmap(devMem, CORE_MEM_SIZE);
  close(fd);
  return 0;
}