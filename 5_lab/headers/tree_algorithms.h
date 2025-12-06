#ifndef TREE_ALGORITHMS_H
#define TREE_ALGORITHMS_H

#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class tree_algorithms
{
public:
    using value_type = T;

    template <typename ForwardIterator>
    void print_sorted_ascending(ForwardIterator begin, ForwardIterator end);

    template <typename ReverseIterator>
    void print_sorted_descending(ReverseIterator rbegin, ReverseIterator rend);

    template <typename ForwardIterator>
    std::vector<value_type> get_sorted_ascending(ForwardIterator begin, ForwardIterator end);

    template <typename ReverseIterator>
    std::vector<value_type> get_sorted_descending(ReverseIterator rbegin, ReverseIterator rend);
};

#include "../source/tree_algorithms.tpp"

#endif // TREE_ALGORITHMS_H