#pragma once

#include <iterator>
#include <cstdint>
#include <cassert>
#include <iostream>

template<uint16_t SIZE, class T>
class CiricullarBuffer
{
private:
    T _data[SIZE]; // Buffer itself
    uint16_t _head; 
    uint16_t _tail;
    bool isFull;

public:
    explicit CiricullarBuffer() : _head(0), _tail(0), isFull(false)
    {
        
    }

    /** ITERATOR DEFINITION BEGIN **/
    struct iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using self_type         = iterator;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        iterator(pointer ptr, uint16_t offset) : _ptr(ptr), _offset(offset){}

        self_type& operator=(self_type& other)
        {
            this->_ptr = other._ptr;
            this->_offset = other._offset;

            return *this;
        }

        reference operator*() const { return *(this->_ptr); }
        pointer operator->() const { return this->_ptr; }

        self_type& operator++() // Prefix increment
        { 
            this->_ptr++;
            this->_offset = (this->_offset + 1) % SIZE; 
            return *this; 
        } 
        self_type& operator++(int)  // Postfix increment
        { 
            auto tmp = *this;
            ++(*this); 
            return tmp; 
        }

        bool operator==(const self_type& other) { return (this->_ptr == other._ptr) && (this->_offset == other._offset); }
        bool operator!=(const self_type& other) { return !(*this == other); }

    private:
        pointer _ptr;
        uint16_t _offset;
    };
    /** ITERATOR DEFINITION END **/

    // Container modification
    void push_back(T item) 
    {
        this->_data[this->_head] = item;

        if(this->isFull){
            this->_tail = (this->_tail + 1) % SIZE;
        }

        this->_head = (this->_head + 1) % SIZE;

        this->isFull = (this->_head == this->_tail);
    }

    void push_front(T item)
    {
        this->_tail = (SIZE + (this->_tail - 1) % SIZE);
    
        if(this->isFull){   
            this->_head = (SIZE + (this->_head - 1) % SIZE);
        }

        this->_data[this->_tail] = item;

        this->isFull = (this->_head == this->_tail);
    }

    T pop_front()
    {
       if(this->empty()){
        return T();
        }
        
        // Get data and pop element from buffer (move tail)
        auto val = this->_data[this->_tail];
        this->isFull = false;
        this->_tail = (this->_tail + 1) % SIZE;

        return val; 
    }

    void clear()
    {
        this->_head = this->_tail;
        this->isFull = false;
    }

    // Element access
    T front() const { return this->_data[this->_tail]; }
    T back() const { return this->_data[this->_head]; }
    T operator[](int idx)
    {
        assert(idx < SIZE);
        return this->_data[(this->_tail + idx) % SIZE];
    }
    const T operator[](int idx) const
    {
        assert(idx < SIZE);
        return this->_data[(this->_tail + idx) % SIZE];
    } 

    // Iteration
    auto begin() {return iterator(&(this->_data[this->_tail]), 0); }
    auto end() { return iterator(&(this->_data[this->_head]), this->size()); }

    // State determination
    bool empty() const { return (!this->isFull && (this->_head == this->_tail)); }
    bool full() const { return this->isFull; }
    uint16_t size() const
    {
        uint16_t __size = SIZE;

        if(!this->isFull){
            if(this->_head >= this->_tail){
                __size = this->_head - this->_tail; 
            }else{
                __size = SIZE + this->_head - this->_tail;
            }
        }

        return __size;
    }
    constexpr uint16_t capacity() const { return SIZE; }
};
