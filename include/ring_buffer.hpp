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

        iterator begin() const              { return front_ptr; };
        iterator end() const                { return (back_ptr + 1); };
        const_iterator cbegin() const       { return front_ptr; };
        const_iterator cend() const         { return (back_ptr + 1); };
        size_type size() const;
        size_type max_size() const          { return std::numeric_limits<T>::max(); };
        bool empty() const                  { return size() == 0; };

        void reserve(size_type new_capacity);

        void push_back(value_type element);
        void push_front(value_type element);
        // void insert(value_type element, size_type index);        // Needs to be implemented
        // value_type pop_back();                                   // Needs to be implemented
        // value_type pop_front();                                  // Needs to be implemented
        // value_type erase(iterator position);                     // Needs to be implemented

    private:
        size_type front_index;
        size_type back_index;
        T* front_ptr;
        T* back_ptr;
        storage_type container;

        bool full()                 { return size() == container.size(); };
        void double_the_capacity()  { (size() < 2)? reserve(2) : reserve(size() * 2)};

    };
    // Default constructor
    template <typename T>
    Ring_buffer<T>::Ring_buffer() :
        front_index{ 0 }, 
        back_index{ 0 },
        front_ptr{ container.data() }, 
        back_ptr{ container.data() },
        container( 16 )
    {}
    // Copy constructor
    template <typename T>
    Ring_buffer<T>::Ring_buffer(const Ring_buffer<T>& other)
        : front_index{ other.front_index },
        back_index{ other.back_index },
        front_ptr{ container.data() + front_index }, 
        back_ptr{ container.data() + back_index }
    {
        std::ranges::copy(other.container.begin(), other.container.end(), std::back_inserter(container));
        container.reserve(other.container.capacity());
    }
    //Move constructor
    template <typename T>
    Ring_buffer<T>::Ring_buffer(Ring_buffer<T>&& other)
        : front_index{ std::move(other.front_index) }, 
        back_index{ std::move(other.back_index) }, 
        front_ptr { container.data() + front_index },
        back_ptr { container.data() + back_index }
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

    template <typename T>
    Ring_buffer<T>::size_type Ring_buffer<T>::size() const
    {
        // size if buffer has looped
        if (front_index > back_index)
        {
            return container.size() - front_index + back_index + 1;
        }
        return back_index + 1 - front_index;
    }

    template <typename T>
    void Ring_buffer<T>::push_back(value_type element)
    {
        // if current buffer is full, double the capacity
        if (full())
        {
            double_the_capacity();
        }
        // move back index up by one, loop when needed
        ++back_index;
        if (back_index >= container.size())
            back_index = 0;
        back_ptr = container.data() + back_index;
        &back_ptr = element;
    }

    template <typename T>
    void Ring_buffer<T>::push_front(value_type element)
    {
        // if current buffer is full, double the capacity
        if (full())
        {
            double_the_capacity();
        }
        // move front index down by one, loop when needed
        if (front_index == 0)
        {
            front_index = container.size() - 1;
        }
        else
        {
            --front_index;
        }
        front_ptr = container.data() + front_index;
        &front_index = element;
    }

    template <typename T>
    void Ring_buffer<T>::reserve(size_type new_capacity)
    {
        if (new_capacity <= container.capacity())
        {
            return;
        }
        container.resize(new_capacity);
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
