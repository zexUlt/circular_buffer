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
    uint16_t _size;
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

        iterator(pointer init_ptr, pointer ptr, uint16_t offset) : _init_ptr(init_ptr), _ptr(ptr), _offset(offset){}

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
            this->_offset++;
            this->_ptr = this->_init_ptr + this->_offset;
            return *this; 
        } 
        self_type& operator++(int)  // Postfix increment
        { 
            auto tmp = *this;
            ++(*this); 
            return tmp; 
        }

        bool operator==(const self_type& other) 
        {
            // std::cout << this->_offset << " " << other._offset << '\n';
            // std::cout << this->_ptr << " " << other._ptr << '\n';
            // std::cout << _init_ptr << " " << other._init_ptr << '\n'; 
            return (this->_init_ptr == other._init_ptr) && (this->_ptr == other._ptr) && (this->_offset == other._offset); 
        }
        bool operator!=(const self_type& other) { return !(*this == other); }

    private:
        pointer _ptr;
        const pointer _init_ptr;
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
        this->_size += static_cast<int>(this->_size != SIZE); // Имеются сомнения насчет этого каста, может лучше переписать через if?
    }

    void push_front(T item)
    {
        this->_tail = (SIZE + (this->_tail - 1) % SIZE) % SIZE;

        if(this->isFull){   
            this->_head = (SIZE + (this->_head - 1) % SIZE) % SIZE;
        }

        this->_data[this->_tail] = item;

        this->isFull = (this->_head == this->_tail);
        this->_size += static_cast<int>(this->_size != SIZE); // Имеются сомнения насчет этого каста, может лучше переписать через if?
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
        this->_size--;

        return val; 
    }

    void clear()
    {
        this->_head = this->_tail;
        this->isFull = false;
        this->_size = 0;
    }

    // Element access
    T front() const { return this->_data[this->_tail]; }
    T back() const { return this->_data[this->_head]; }
    T operator[](int idx)
    {
        assert(idx < this->_size);
        return this->_data[(this->_tail + idx) % SIZE];
    }
    const T operator[](int idx) const
    {
        assert(idx < this->_size);
        return this->_data[(this->_tail + idx) % SIZE];
    } 

    // Iteration
    auto begin() { return iterator(this->_data, &(this->_data[this->_tail]), 0); }
    auto end() { return iterator(this->_data, &(this->_data[this->_tail + this->_size]), this->_size); }

    // State determination
    bool empty() const { return (!this->isFull && (this->_head == this->_tail)); }
    bool full() const { return this->isFull; }
    uint16_t size() const
    {
        // uint16_t __size = SIZE;

        // if(!this->isFull){
        //     if(this->_head >= this->_tail){
        //         __size = this->_head - this->_tail; 
        //     }else{
        //         __size = SIZE + this->_head - this->_tail;
        //     }
        // }

        return _size;
    }
    constexpr uint16_t capacity() const { return SIZE; }
};
