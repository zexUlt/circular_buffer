#include <iostream>

#include "CiricullarBuffer.hpp"


int main(int argc, char** argv)
{
    CiricullarBuffer<3, int> buf;

    std::cout << "Is empty: " << buf.empty() << '\n';
    std::cout << "Is full: " << buf.full() << '\n';
    std::cout << "Capacity: " << buf.capacity() << '\n';
    std::cout << "Size: " << buf.size() << '\n';
    
    buf.push_back(1); // 1
    std::cout << buf[0] << " " << buf[1] << " " << buf[2] << '\n';
    buf.push_back(2); // 1 2
    std::cout << buf[0] << " " << buf[1] << " " << buf[2] << '\n';
    buf.push_back(3); // 1 2 3
    std::cout << buf[0] << " " << buf[1] << " " << buf[2] << '\n';
    buf.push_back(4); // 2 3 4
    std::cout << buf[0] << " " << buf[1] << " " << buf[2] << '\n';
    buf.push_back(5); // 3 4 5
    std::cout << buf[0] << " " << buf[1] << " " << buf[2] << '\n';
    buf.push_back(6); // 4 5 6
    std::cout << buf[0] << " " << buf[1] << " " << buf[2] << '\n';
    buf.push_front(2); // 2 4 5
    std::cout << buf[0] << " " << buf[1] << " " << buf[2] << '\n';
    buf.push_front(1); // 1 2 5
    std::cout << buf[0] << " " << buf[1] << " " << buf[2] << '\n';

    std::cout << "Is empty: " << buf.empty() << '\n';
    std::cout << "Is full: " << buf.full() << '\n';
    std::cout << "Capacity: " << buf.capacity() << '\n';
    std::cout << "Size: " << buf.size() << '\n';
    
    // std::cout << *buf.begin() << " " << *(++buf.begin()) << " " << *(buf.end() - 1);
    auto it = buf.begin();

    std::cout << *it << '\n';

    ++it;

    std::cout << *it;

    std::cout << '\n';
    return 0;
}