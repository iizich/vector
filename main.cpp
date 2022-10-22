#include <iostream>
#include <vector>
#include "src/vector.hpp"

int main() {
    std::vector<int> v {1,2,3,4,5,6};
    std::cout << "v.cap = " << v.capacity() << std::endl;
    std::cout << "v.size = " << v.size() << std::endl;
    v.pop_back();
    std::cout << "v.cap = " << v.capacity() << std::endl;
    std::cout << "v.size = " << v.size() << std::endl;
}