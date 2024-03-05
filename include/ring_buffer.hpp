#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

#include <iostream>

namespace soskary
{
    template <typename T>
    class Ring_buffer
    {
    public:
        Ring_buffer();
    private:

    };



    template <typename T>
    Ring_buffer<T>::Ring_buffer()
    {
        std::cout << "Created a Ring_buffer of type " << typeid(T).name() << '\n';
    }

}
#endif
