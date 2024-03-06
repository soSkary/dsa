#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <cstddef> // for std::ptrdiff_t, std::size_t
#include <vector>

namespace soskary
{
    template <typename T>
    class Ring_buffer
    {
    public:
        using storage_type = std::vector<T>;
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

        Ring_buffer<T> operator=(const Ring_buffer<T>& other) const;
        Ring_buffer<T> operator=(Ring_buffer<T>&& other);

        ~Ring_buffer() = default;

        iterator begin() const              { return first_element_ptr; };
        iterator end() const                { return (last_element_ptr + 1); };
        const_iterator cbegin() const       { return first_element_ptr; };
        const_iterator cend() const         { return (last_element_ptr + 1); };
        size_type size() const              { return last_element_index - first_element_index + 1; };
        size_type max_size() const          { return std::numeric_limits<T>::max(); };
        bool empty() const                  { return first_element_index == last_element_index; };


    private:
        size_type first_element_index;
        size_type last_element_index;
        T* first_element_ptr;
        T* last_element_ptr;
        storage_type container;

    };
    // Default constructor
    template <typename T>
    Ring_buffer<T>::Ring_buffer() :
        first_element_index{ 0 }, 
        last_element_index{ 0 },
        first_element_ptr{ container.data() }, 
        last_element_ptr{ container.data() },
        container( 16 )
    {}
    // Copy constructor
    template <typename T>
    Ring_buffer<T>::Ring_buffer(const Ring_buffer<T>& other)
        : first_element_index{ other.first_element_index },
        last_element_index{ other.last_element_index },
        first_element_ptr{ container.data() + first_element_index }, 
        last_element_ptr{ container.data() + last_element_index }
    {
        std::ranges::copy(other.container.begin(), other.container.end(), std::back_inserter(container));
        container.reserve(other.container.capacity());
    }
    //Move constructor
    template <typename T>
    Ring_buffer<T>::Ring_buffer(Ring_buffer<T>&& other)
        : first_element_index{ std::move(other.first_element_index) }, 
        last_element_index{ std::move(other.last_element_index) }, 
        first_element_ptr { container.data() + first_element_index },
        last_element_ptr { container.data() + last_element_index }
    {
        std::ranges::move(other.container, std::back_inserter(container));
        container.reserve(other.container.capacity());
    }
    //Copy assignment
    template <typename T>
    Ring_buffer<T> Ring_buffer<T>::operator=(const Ring_buffer<T>& other) const
    {
        return Ring_buffer<T>{ other };
    }
}
template <typename T>
bool operator==(const soskary::Ring_buffer<T>& a, const soskary::Ring_buffer<T>& b)
{
    return std::ranges::equal(a, b);
}

template <typename T>
bool operator!=(const soskary::Ring_buffer<T>& a, const soskary::Ring_buffer<T>& b)
{
    return !(a == b);
}
#endif
