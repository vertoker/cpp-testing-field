// Inspired by https://youtu.be/Xx-NcqmveDc?si=D3-sfXrBgv_vfduX
// ACM means Allocations/Copies/Moves

#include <iostream>
#include <vector>
#include <array>

#define COUT_ACM true

static int allocationCount = 0;
static int allocatedBytes = 0;
static int copiesCount = 0;
static int movesCount = 0;

void* operator new(size_t size) {
  if (COUT_ACM)
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

  Data(const Data& other) : Value(other.Value) {
    if (COUT_ACM)
      std::cout << "Copied Data" << std::endl;
    copiesCount++;
  }

  Data(Data&& other) : Value(other.Value) {
    if (COUT_ACM)
      std::cout << "Moved Data" << std::endl;
    movesCount++;
  }
};

void func1() {
  std::vector<Data> vector{};

  for (size_t i = 0; i < 5; i++) {
    vector.push_back(Data(i));
  }
}

void func2() {
  std::vector<Data> vector{};

  for (size_t i = 0; i < 5; i++) {
    vector.emplace_back(i);
  }
}

void func3() {
  std::vector<Data> vector{};
  vector.reserve(5);

  for (size_t i = 0; i < 5; i++) {
    vector.emplace_back(i);
  }
}

void func4() {
  std::array<Data, 5> array{
    Data(0), Data(1), Data(2), Data(3), Data(4)
  };
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

