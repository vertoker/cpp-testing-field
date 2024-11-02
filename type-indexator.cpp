// Simple way to define types as integer
// https://habr.com/ru/companies/yandex/articles/854352/

#include <iostream>

using type_index = std::uint32_t;

struct TypeIndexatorCounter final {
    [[nodiscard]] static type_index next() noexcept {
        static std::atomic<type_index> counter{};
        return counter++;
    }
};

template <typename Type>
struct TypeIndexator final {
    [[nodiscard]] static type_index value() noexcept {
        static const type_index value = ecs::TypeIndexatorCounter::next();
        return value;
    }
};

// define some custom types
struct A {};
struct B : A { int v1; };
struct C : B { int v2; C(int v2) : v2{v2} {} };

int main() {
    std::cout << TypeIndexator<A>::value() << ' ';
    std::cout << TypeIndexator<B>::value() << ' ';
    std::cout << TypeIndexator<C>::value() << ' ';
    std::cout << TypeIndexator<B>::value() << ' ';
    std::cout << TypeIndexator<A>::value() << ' ';
    std::cout << std::endl;
    // prints 0 1 2 1 0
}