#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iterator>

namespace izich{

template<typename T>
class Iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = size_t;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
public:
    constexpr explicit Iterator() = default;
    constexpr explicit Iterator(pointer ptr) : ptr(ptr){}
public:
    reference operator*(){
        return *ptr;
    }
    Iterator& operator++(){
        ++ptr;
        return *this;
    }
    Iterator& operator--(){
        --ptr;
        return *this;
    }
    Iterator& operator+=(size_t n){
        ptr += n;
        return *this;
    }
    Iterator& operator-=(size_t n){
        ptr -= n;
        return *this;
    }
    bool operator==(Iterator other){
        return ptr == other.ptr;
    }
    bool operator!=(Iterator other){
        return ptr != other.ptr;
    }
private:
    pointer ptr;
};

} // izich

#endif // VECTOR_ITERATOR_HPP
