#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

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


        T m_value{};
        DDL_node<T>* m_next{ nullptr };
        DDL_node<T>* m_previous{ nullptr };
    };

    template <typename T>
    DDL_node<T>::DDL_node(value_type value) : m_value{ value } 
    {}
    template <typename T>
    class Doubly_linked_list
    {
    public:
        void delete_node(DDL_node<T>* target);
        DDL_node<T> pop();
        void push_back(DDL_node<T>* node);
        void push_front(DDL_node<T>* node);
        void insert_before(DDL_node<T>* target, DDL_node<T>* node_to_insert);

    private:
        DDL_node<T>* m_head{ nullptr };
        DDL_node<T>* m_tail{ nullptr };
    };

    template <typename T>
    void Doubly_linked_list<T>::delete_node(DDL_node<T>* target)
    {

        // point target's previous node to target's next node
        target->m_previous->m_next = target->m_next;
        // point target's next node to  target's previous node
        target->m_next->m_previous = target->m_previous;


        bool is_tail{ target == m_tail };
        bool is_head{ target == m_head };

        // check if last node
        if (!is_tail && target != nullptr)
        {
            if (!is_head)
            {


            }
        }
    }
}
#endif
