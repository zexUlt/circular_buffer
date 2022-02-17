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
    std::cout << buf[0] << '\n';
    buf.push_back(2); // 1 2
    std::cout << buf[0] << " " << buf[1] << '\n';
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
    buf.push_front(3); // 3 1 2
    std::cout << buf[0] << " " << buf[1] << " " << buf[2] << '\n';

    std::cout << "Is empty: " << buf.empty() << '\n';
    std::cout << "Is full: " << buf.full() << '\n';
    std::cout << "Capacity: " << buf.capacity() << '\n';
    std::cout << "Size: " << buf.size() << '\n';
    
    // std::cout << *buf.begin() << " " << *(++buf.begin()) << " " << *(buf.end() - 1);
    auto it = buf.begin();
    /*
        В общем, проблема такая: неправильно сравниваются итераторы, из-за чего получается, что они никогда не будут равны
        Ниже в комментах написан вывод, который пишется из оператора сравнения итераторов
        Получается так, что, когда оффсеты равны, адреса не равны
        Потому что _head (конец очереди) стоит всегда на первом элементе при заполненном буфере
        А когда _tail (начало очереди) доходит до _head, его оффсет сбрасывается в 0 (что верно вообще)
    */
    /**
     * 0 2
     * 0x7ffee35496c0 0x7ffee35496c0
     * 0x7ffee35496c0 0x7ffee35496c0
     * **/
    std::cout << (it == buf.end()) << "\n\n";
    std::cout << *it << '\n';
    ++it;
    /**
     * 1 2
     * 0x7ffee35496c4 0x7ffee35496c0
     * 0x7ffee35496c0 0x7ffee35496c0
     * **/
    std::cout << (it == buf.end()) << "\n\n";
    std::cout << *it << '\n';
    ++it;
    /**
     * 2 2
     * 0x7ffee35496c8 0x7ffee35496c0
     * 0x7ffee35496c0 0x7ffee35496c0
     *  **/
    std::cout << (it == buf.end()) << "\n\n";
    std::cout << *it << '\n';
    ++it;
    std::cout << *buf.end() << '\n';
    /**
     * 0 2
     * 0x7ffee35496c0 0x7ffee35496c0
     * 0x7ffee35496c0 0x7ffee35496c0
     * **/
    std::cout << (it == buf.end()) << "\n\n";


    for(auto it = buf.begin(); it != buf.end(); ++it){
        std::cout << *it << " ";
    }

    std::cout << '\n';
    return 0;
}