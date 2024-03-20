#include "iostream"
#include "vector.h"

int main() {
    auto my_vec = Vector<int>();

    my_vec.push(1);
    my_vec.push(2);
    my_vec.push(3);
    my_vec.push(4);
    my_vec.push(5);

    std::cout << *my_vec.pop_back()
              << *my_vec.pop_back()
              << *my_vec.pop_back()
              << *my_vec.pop_back()
              << *my_vec.pop_back()
              << std::endl;

    return 0;
}
