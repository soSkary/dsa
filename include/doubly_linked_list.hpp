#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP
#include <stdexcept>

namespace soskary
{

    template <typename T>
    class DDL_node
    {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;

        DDL_node(value_type value);
        void insert_at(DDL_node<value_type> node, size_type index);
        void remove(DDL_node<T> node);
        void removeAt(size_type index);
        void append(DDL_node<T> node);
        void prepend(DDL_node<T> node);
        DDL_node<value_type> at(size_type index);
        value_type m_value{1};
        DDL_node<value_type>* m_next{ nullptr };
        DDL_node<value_type>* m_previous{ nullptr };
        DDL_node<value_type>* m_head{ this };
        DDL_node<value_type>* m_tail{ this };
        

    private:
        size_type m_length{ 0 };
    };

    template <typename T>
    DDL_node<T>::DDL_node(value_type value) : m_value{ value }
    {}

    template <typename T>
    void DDL_node<T>::insert_at(DDL_node<T> node, DDL_node<T>::size_type index)
    {
        if (index == 0)
        {
            prepend(node);
        }
        else if (index == m_length)
        {
            append(node);
        }
        else
        {
            DDL_node<T> nodeBeforeInsertion{ this.at(index - 1) };

            // set the new node to point to correct nodes in list
            node.m_previous = &nodeBeforeInsertion;
            node.m_next = nodeBeforeInsertion.m_next;

            //set the previous and next of the old nodes
            node.m_previous->m_next = &node;
            node.m_next->m_previous = &node;

            ++m_length;
        }
    }

    template <typename T>
    void DDL_node<T>::remove(DDL_node<T> node)
    {
        // check if it is the head we are removing
        if (&node != m_head)
        {
            node.m_next->m_previous = node.m_previous;
        }
        else
        {
            node.m_next->m_previous = nullptr;
            m_head = m_next;
        }
        // check if it is the tail we are removing
        if (&node != m_tail)
        {
            node.m_previous->m_next = node.m_next;
        }
        else
        {
            node.m_previous->m_next = nullptr;
            m_head = m_previous;
        }
        node.m_length = 0;
        node.m_head = nullptr;
        node.m_tail = nullptr;
        node.m_next = nullptr;
        node.m_previous = nullptr;
    }
    template <typename T>
    void DDL_node<T>::removeAt(DDL_node<T>::size_type index)
    {
        remove(this->at(index));
    }

    template <typename T>
    void DDL_node<T>::append(DDL_node<T> node)
    {
        m_tail->m_next = &node;
        node.m_previous = m_tail;
        m_tail = &node;
        ++m_length;
    }

    template <typename T>
    void DDL_node<T>::prepend(DDL_node<T> node)
    {
        m_head->m_previous = &node;
        node.m_next = m_head;
        m_head = &node;
        ++m_length;
    }

    template <typename T>
    DDL_node<T> DDL_node<T>::at(DDL_node<T>::size_type index)
    {
        // if index out of bounds, throw an exception
        if (index >= m_length)
        {
            throw std::out_of_range{ "DDL_node.at() index out of range\n" };
        }

        DDL_node<T>* target{ m_head };
        // walk the list
        for (DDL_node<T>::size_type i; i < index; ++i)
        {
            target = target->m_next;
        }
        return *target;
    }

}
#endif
