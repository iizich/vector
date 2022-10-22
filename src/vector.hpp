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
public:
    void reserve(size_t n){
        if(capacity_ <= n) return;
        T* new_arr = allocator_traits::allocate(allocator_, n);
        for (int i = 0; i < size_; ++i) {
            allocator_traits::construct(allocator_, new_arr, *(array_ + i));
        }
        for (int i = 0; i < size_; ++i) {
            allocator_traits::destroy(allocator_,array_ + i);
        }
        capacity_ = n;
        array_ = new_arr;
    }
    [[nodiscard]] std::size_t capacity() const noexcept {
        return capacity_;
    }
    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }
    [[nodiscard]] iterator begin() const {
        return iterator(array_);
    }
    [[nodiscard]] iterator end() const {
        return iterator(array_ + size_);
    }
    [[nodiscard]] const_iterator cbegin() const {
        return const_iterator(array_);
    }
    [[nodiscard]] const_iterator cend() const {
        return const_iterator(array_ + size_);
    }
public:
    T& operator[](const int index) {
        return array_[index];
    }
private:
    using allocator_traits = std::allocator_traits<Allocator>;
    Allocator allocator_;
    T* array_;
    size_t capacity_;
    size_t size_;
};
} // izich