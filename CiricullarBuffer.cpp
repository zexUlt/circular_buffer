#include "CiricullarBuffer.hpp"

/** CONTAINER MODIFICATION PART BEGIN **/

template<uint16_t SIZE, class T>
void CiricullarBuffer<SIZE, T>::push_back(T item)
{
    this->_data[this->_head] = item;

    if(this->isFull){
        this->_tail = (this->_tail + 1) % SIZE;
    }

    this->_head = (this->_head + 1) % SIZE;

    this->isFull = (this->_head == this->_tail);
}

template<uint16_t SIZE, class T>
void CiricullarBuffer<SIZE, T>::push_front(T item)
{
    this->_tail = (this->_tail - 1) % SIZE;
    
    if(this->isFull){   
        this->_head = (this->_head - 1) % SIZE;
    }

    this->_data[this->_tail] = item;

    this->isFull = (this->_head == this->_tail);
}

template<uint16_t SIZE, class T>
T CiricullarBuffer<SIZE, T>::pop_front()
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

template<uint16_t SIZE, class T>
void CiricullarBuffer<SIZE, T>::clear()
{
    this->_head = this->_tail;
    this->isFull = false;
}

/** CONTAINER MODIFICATION PART END **/

/** GETTERS PART BEGIN **/

template<uint16_t SIZE, class T>
T CiricullarBuffer<SIZE, T>::front() const
{
    
}

template<uint16_t SIZE, class T>
T CiricullarBuffer<SIZE, T>::back() const
{
    return this->_data[this->_head];
}

/** GETTERS PART END **/

/** ITERATION PART BEGIN **/

template<uint16_t SIZE, class T>
typename CiricullarBuffer<SIZE, T>::Iterator CiricullarBuffer<SIZE, T>::begin() const
{
    return CiricullarBuffer<SIZE, T>::Iterator(&(this->_data[this->_tail]));
}

template<uint16_t SIZE, class T>
typename CiricullarBuffer<SIZE, T>::Iterator CiricullarBuffer<SIZE, T>::end() const
{
    return CiricullarBuffer<SIZE, T>::Iterator(&(this->_data[this->_head]));
}

/** ITERATION PART END **/

/** STATE DETERMINATION PART BEGIN **/

template<uint16_t SIZE, class T>
bool CiricullarBuffer<SIZE, T>::empty() const
{
    return (!this->isFull && (this->_head == this->_tail));
}

template<uint16_t SIZE, class T>
bool CiricullarBuffer<SIZE, T>::full() const
{
    return this->isFull;
}

template<uint16_t SIZE, class T>
uint16_t CiricullarBuffer<SIZE, T>::size() const
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

template<uint16_t SIZE, class T>
constexpr uint16_t CiricullarBuffer<SIZE, T>::capacity() const
{
    return SIZE;
}

/** STATE DETERMINATION PART END **/



