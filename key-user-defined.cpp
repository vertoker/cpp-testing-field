// How to implement any user-defined key-type
// Special for any std types with std::hash usage
// (std::set and std::unordered_set, keys for std::map and std::unordered_map)
// 
// Based on
// https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key

#include <iostream>
#include <functional>

#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

// Utility hash function, create hash from any std::hash values
template <typename T, typename... Rest>
void hashCombine(std::size_t& seed, const T& v, const Rest&... rest) {
	const unsigned int magicNumber = 0x9e3779b9;
	seed ^= std::hash<T>{}(v) + magicNumber + (seed << 6) + (seed >> 2);
	(hashCombine(seed, rest), ...);
}

// define user-defined key-type
struct UserDefinedKey {
    int value1;
    float value2;
    std::string value3;

    // step 1: implement operator== into key-type

    bool operator==(const UserDefinedKey& other) const {
        return value1 == other.value1 
            && value2 == other.value2 
            && value3 == other.value3;
    }
};

// step 2: implement custom std::hash for key-type

template <>
struct std::hash<UserDefinedKey>
{
    std::size_t operator()(const UserDefinedKey& obj) const {
        size_t hash = 0;
        // use hash combine finction defined below
        hashCombine(hash, obj.value1, obj.value2, obj.value3);
        return hash;
    }
};

int main() {
    std::set<UserDefinedKey> set = {
        { 1, 2.0f, "text 1" },
        { 2, 4.0f, "text 2" }
    };

    std::unordered_set<UserDefinedKey> unordered_set = {
        { 1, 2.0f, "text 1" },
        { 2, 4.0f, "text 2" }
    };

    std::map<UserDefinedKey, int> map = {
        { { 1, 2.0f, "text 1" }, 0 },
        { { 2, 4.0f, "text 2" }, 0 }
    };

    std::unordered_map<UserDefinedKey, int> unordered_map = {
        { { 1, 2.0f, "text 1" }, 0 },
        { { 2, 4.0f, "text 2" }, 0 }
    };
}