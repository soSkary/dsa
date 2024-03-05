#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

#include <iostream>
#include <cstddef> // for std::ptrdiff_t, std::size_t
#include <vector>

namespace soskary
{
    template <typename T>
    class Ring_buffer
    {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;

        Ring_buffer();
        Ring_buffer(const Ring_buffer<T>& other);
        Ring_buffer(Ring_buffer<T>&& other);

        Ring_buffer<T> operator=(const Ring_buffer<T>& other);
        Ring_buffer<T> operator=(Ring_buffer<T>&& other);

        void ~Ring_buffer();

        iterator begin();
        iterator end();
        const_iterator cbegin();
        const_iterator cend();
        size_type size();
        size_type max_size();
        bool empty();


    private:
        T* next_element_ptr;
        T* last_element_ptr;
        std::vector<T> container;

    };

    template <typename T>
    bool operator==(const Ring_buffer<T>& a, const Ring_buffer<T>& b)
    {

    }

    template <typename T>
    bool operator!=(const Ring_buffer<T>& a, const Ring_buffer<T>& b)
    {
        return !(a == b);
    }

    template <typename T>
    Ring_buffer<T>::Ring_buffer() :
        container{ std::vector<T>(16) }, next_element_ptr{ container.data(); }, last_element_ptr{ container.data(); }
    {}

}
#endif
