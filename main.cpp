#include "src/vector.hpp"
#include <iostream>

int main(){
    izich::vector<int> v {1,2,3,4,5};
    auto it = v.begin();
    it += 3;
    std::cout << *it;
    return 0;
}
