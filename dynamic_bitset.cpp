// Dynamic bitset
// Modified version of:
// https://github.com/syoyo/dynamic_bitset/blob/master/dynamic_bitset.hh
// https://github.com/martinstarkov/ecs/blob/main/include/ecs/ecs.h


// Start copy here

#include <vector>
#include <cassert>

class dynamic_bitset {
public:
    dynamic_bitset() = default;
    dynamic_bitset(std::size_t new_size, bool value = false) 
        { resize(new_size, value); }
    ~dynamic_bitset() = default;
    
    dynamic_bitset(dynamic_bitset&&) = default;
    dynamic_bitset& operator=(dynamic_bitset&&) = default;
    
    dynamic_bitset(const dynamic_bitset&) = default;
    dynamic_bitset& operator=(const dynamic_bitset&) = default;

    void set(const std::size_t& bit_index, const bool& value = true) {
        std::size_t byte_index = bit_index / 8;
		std::uint8_t offset = static_cast<std::uint8_t>(bit_index % 8);
		std::uint8_t bitfield = static_cast<std::uint8_t>(BIT_LEFT >> offset);

		assert(bit_index < bit_size_ && "Bit index out of range");
		assert(byte_index < data_.size() && "Byte index out of range");

		if (value) // merge source and answer bytes with OR
		    data_[byte_index] |= bitfield;
		else // merge source and inverse answer bytes with AND
            data_[byte_index] &= (~bitfield);
    }

    bool get(const std::size_t& bit_index) {
        std::size_t byte_index = bit_index / 8;
		std::size_t offset = bit_index % 8;
        
		assert(bit_index < bit_size_ && "Bit index out of range");
		assert(byte_index < data_.size() && "Byte index out of range");

		uint8_t answer = (data_[byte_index] << offset) & BIT_LEFT;
		return answer;
    }

    [[nodiscard]] bool operator[](const std::size_t& bit_index) const {
        std::size_t byte_index = bit_index / 8;
		std::size_t offset = bit_index % 8;
        
		assert(bit_index < bit_size_ && "Bit index out of range");
		assert(byte_index < data_.size() && "Byte index out of range");

		uint8_t answer = (data_[byte_index] << offset) & BIT_LEFT;
		return answer; // take first bit

        // also you can remove all bits except bit field and compare as byte
        // return (data[byte_index] & bitfield) == bitfield;
    }

    bool operator==(const dynamic_bitset& other) const
        { return bit_size_ == other.bit_size_ && data_ == other.data_; }
    
    [[nodiscard]] std::size_t size() const { return bit_size_; }
    [[nodiscard]] std::size_t capacity() const { return data_.capacity(); }
    [[nodiscard]] std::vector<uint8_t> data() const { return data_; }

    void reserve(std::size_t new_capacity) {
        std::size_t byte_count = GetByteCount(new_capacity);
        data_.reserve(byte_count);
    }

    void resize(std::size_t new_size, bool value = false) {
        std::size_t byte_count = GetByteCount(new_size);
        bit_size_ = new_size;
        data_.resize(byte_count, value);
    }

    void clear() { bit_size_ = 0; data_.clear(); }
    void shrink_to_fit() { data_.shrink_to_fit(); }

private:
    [[nodiscard]] std::size_t GetByteCount(std::size_t bit_count) {
        std::size_t byte_count = 1;
        if (bit_count >= 8) {
            assert(1 + (bit_count - 1) / 8 > 0 && "Byte count must be always > 0");
            byte_count = 1 + (bit_count - 1) / 8;
        }
        return byte_count;
    }

    std::size_t bit_size_;
    std::vector<uint8_t> data_;

    static const uint8_t BIT_LEFT = 128; // 10000000
    static const uint8_t BIT_RIGHT = 1; // 00000001
};

// End copy here


#include <iostream>

int main() {
    int size = 12;
    dynamic_bitset bitset(size);

    for (auto i = 0; i < size; i++)
        std::cout << bitset[i];
    std::cout << std::endl;

    bitset.set(0);
    bitset.set(2);
    bitset.set(4);
    bitset.set(6);
    bitset.set(8);
    bitset.set(10);
    //bitset.set(12);

    for (auto i = 0; i < size; i++)
        std::cout << bitset[i];
    std::cout << std::endl;

    bitset.resize(16);

    for (auto i = 0; i < 16; i++)
        std::cout << bitset[i];
    std::cout << std::endl;
}