#include "iostream"
#include "optional"
#include "assert.h"

#include "vector.h"

int main() {
    auto first_vec = Vector<int>();

    first_vec.push(1);
    first_vec.push(2);
    first_vec.push(3);
    first_vec.push(4);
    first_vec.push(5);

    assert(first_vec.pop() == 5);
    assert(first_vec.pop() == 4);

    std::cout << "Validated push and pop" << std::endl;

    assert(first_vec.length() == 3);
    assert(first_vec.capacity() == 8);

    std::cout << "Validated length and capacity" << std::endl;

    Vector<int> second_vec(std::move(first_vec));

    assert(second_vec[0] == 1);
    assert(second_vec[1] == 2);
    assert(second_vec[2] == 3);
    assert(second_vec.length() == 3);
    assert(second_vec.capacity() == 8);

    std::cout << "Validated move ctor" << std::endl;

    assert(!second_vec.is_empty());
    second_vec.clear();
    assert(second_vec.is_empty());

    std::cout << "Validated is_empty" << std::endl;

    assert(second_vec.pop() == std::nullopt);

    std::cout << "Validated safety of pop";

    auto third_vec = Vector(3, 4);

    assert(third_vec[0] == 4);
    assert(third_vec[1] == 4);
    assert(third_vec[2] == 4);
    assert(third_vec.length() == 3);
    assert(third_vec.capacity() == 8);

    std::cout << "Validated length-and-value ctor" << std::endl;

    return 0;
}
