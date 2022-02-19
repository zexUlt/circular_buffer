#pragma once

#include <iterator>
#include <cstdint>
#include <cassert>
#include <iostream>

template<uint16_t SIZE, class T>
class CircularBuffer
{
private:
    void swap(CircularBuffer<SIZE, T>& other)
    {
        other._head ^= this->_head;
        this->_head ^= other._head;
        other._head ^= this->_head;

        other._tail ^= this->_tail;
        this->_tail ^= other._tail;
        other._tail ^= this->_tail;

        other._size ^= this->_size;
        this->_size ^= other._size;
        other._size ^= this->_size;

        other.isFull ^= this->isFull;
        this->isFull ^= other.isFull;
        other.isFull ^= this->isFull;

        std::swap(this->_data, other._data);
    }
    
    bool isFull;
    uint16_t _head; 
    uint16_t _tail;
    uint16_t _size;
    T _data[SIZE];

public:
    // Basic initialization
    explicit CircularBuffer() : 
            _head(0), 
            _tail(0), 
            isFull(false), 
            _size(0) {} 

    // Initialization of underlying memory through variadic template a.k.a list initialization
    template<typename... S>
    CircularBuffer(S... data) : 
            _data{data...}, 
            _head(sizeof...(S) % SIZE), 
            _tail(0), 
            isFull(sizeof...(S) == SIZE), 
            _size(sizeof...(S))
    { 
    }
    
    // Copy-constructor
    CircularBuffer(const CircularBuffer<SIZE, T>& other) : 
            _head(other._head), 
            _tail(other._tail), 
            isFull(other.isFull),
            _size(other._size)
    {
        std::copy(other._data, other._data + SIZE, _data);
    }

    // Copy-assignment
    CircularBuffer<SIZE, T>& operator=(const CircularBuffer<SIZE, T>& other)
    {
        // Self-assignment guard
        if(*this == other){
            return *this;
        }

        CircularBuffer<SIZE, T> local_copy(other);
        this->swap(local_copy);
        
        return *this;
    }

    // Default destructor since class does not holds any heap resources
    ~CircularBuffer() = default;

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

        self_type& operator=(const self_type& other)
        {
            this->_ptr = other._ptr;
            this->_offset = other._offset;

            return *this;
        }

        reference operator*() const { return *(this->_ptr); }
        pointer operator->() const { return this->_ptr; }

        // Prefix increment
        self_type& operator++() 
        { 
            ++this->_offset;
            this->_ptr = this->_init_ptr + this->_offset;
            return *this; 
        } 
        // Postfix increment
        self_type operator++(int)  
        { 
            self_type tmp(*this);
            ++(*this); 
            return tmp; 
        }

        bool operator==(const self_type& other) 
        {
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
        this->_size += (this->_size != SIZE);
    }

    void push_front(T item)
    {
        // This calculates backward spin by modulo SIZE
        // Since C++ allows negative result of modulo operation
        this->_tail = (SIZE + (this->_tail - 1) % SIZE) % SIZE;

        if(this->isFull){   
            this->_head = (SIZE + (this->_head - 1) % SIZE) % SIZE;
        }

        this->_data[this->_tail] = item;

        this->isFull = (this->_head == this->_tail);
        this->_size += (this->_size != SIZE);
    }

    T pop_front()
    {
        // There are 3 ways of handling empty container:
        // 1. Return empty element of type T. I.e. T()
        // 2. Function will return std::optional<T>, when empty -- std::nullopt
        // 3. Like STL containers abort execution
        assert(!this->empty() && "Container is empty"); 
        
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
    T back() const { return this->_data[(SIZE + (this->_head - 1) % SIZE) % SIZE]; }
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
    auto begin() { return iterator(this->_data, &(this->_data[this->_tail]), 0); }
    auto end() { return iterator(this->_data, &(this->_data[this->_tail + this->_size]), this->_size); }

    auto data() const { return this->_data; };

    // State determination
    bool empty() const { return (!this->isFull && (this->_head == this->_tail)); }
    bool full() const { return this->isFull; }
    uint16_t size() const
    {
        return _size;
    }
    constexpr uint16_t capacity() const { return SIZE; }

    // Comparison operators
    bool operator==(const CircularBuffer<SIZE, T>& other) 
    { 
        return (
            this->_data == other._data && 
            this->_head == other._head && 
            this->_tail == other._tail &&
            this->_size == other._size
        ); 
    }

    bool operator!=(const CircularBuffer<SIZE, T>& other) { return !(*this == other); }
};
