// Inspired by https://youtu.be/Xx-NcqmveDc?si=D3-sfXrBgv_vfduX
// ACM means Allocations/Copies/Moves
//

#include <iostream>
#include <vector>
#include <array>

static int allocationCount = 0;
static int allocatedBytes = 0;
static int copiesCount = 0;
static int movesCount = 0;

void* operator new(size_t size) {
  std::cout << "Allocated " << size << " bytes" << std::endl;
  allocationCount++;
  allocatedBytes += size;
  return malloc(size);
}

struct Data{
public:
  int Value = 0;

  Data() = default;
  Data(int value) : Value(value) {}
};

void func1(){

}

int main () {
  std::cout << "ACM" << std::endl;

  func1();

  std::cout << "Allocations count: " << allocationCount;
  std::cout << ", with allocated bytes: " << allocatedBytes << std::endl;
  std::cout << "Copies count: " << copiesCount << std::endl;
  std::cout << "Moves count: " << movesCount << std::endl;

  return 0;
}

