#pragma once
#include <iterator>

namespace izich {

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
    bool operator==(Iterator other){
        return ptr == other.ptr;
    }
    bool operator!=(Iterator other){
        return ptr != other.ptr;
    }
private:
    pointer ptr;
};

template<typename T, typename Allocator = std::allocator<T>>
class vector {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using allocator_type = Allocator;
    using difference_type = std::ptrdiff_t;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::pointer;
    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;
public:
    constexpr explicit vector() : capacity_(0), size_(0) {}
    constexpr vector(std::initializer_list<T> il) : size_(il.size()), capacity_(il.size() * 2) {
        array_ = allocator_traits::allocate(allocator_, capacity_);
        size_t index = 0;
        for (auto it = il.begin(); it != il.end(); ++it, ++index) {
            allocator_traits::construct(allocator_, array_ + index, *it);
        }
    }
    iterator begin(){
        return iterator(array_);
    }
    iterator end(){
        return iterator(array_ + size_);
    }
    const_iterator cbegin(){
        return const_iterator(array_);
    }
    const_iterator cend(){
        return const_iterator(array_ + size_);
    }
public:
    T& operator[](const int index) {
        return array_[index];
    }
private:
    T* array_;
    Allocator allocator_;
    using allocator_traits = std::allocator_traits<Allocator>;
    size_t capacity_;
    size_t size_;
};
} // izich