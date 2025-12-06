#ifndef TREE_ALGORITHMS_TPP
#define TREE_ALGORITHMS_TPP

#include "../headers/tree_algorithms.h"
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
template <typename ForwardIterator>
void tree_algorithms<T>::print_sorted_ascending(ForwardIterator begin, ForwardIterator end)
{
    for (auto it = begin; it != end; ++it)
        std::cout << *it;
}

template <typename T>
template <typename ReverseIterator>
void tree_algorithms<T>::print_sorted_descending(ReverseIterator rbegin, ReverseIterator rend)
{
    for (auto rit = rbegin; rit != rend; ++rit)
        std::cout << *rit;
}

template <typename T>
template <typename ForwardIterator>
std::vector<typename tree_algorithms<T>::value_type>
tree_algorithms<T>::get_sorted_ascending(ForwardIterator begin, ForwardIterator end)
{
    std::vector<value_type> result;
    for (auto it = begin; it != end; ++it)
        result.push_back(*it);
    return result;
}

template <typename T>
template <typename ReverseIterator>
std::vector<typename tree_algorithms<T>::value_type>
tree_algorithms<T>::get_sorted_descending(ReverseIterator rbegin, ReverseIterator rend)
{
    std::vector<value_type> result;
    for (auto rit = rbegin; rit != rend; ++rit)
        result.push_back(*rit);
    return result;
}

#endif // TREE_ALGORITHMS_TPP