#pragma once
#include "bctree/BCTree.hpp"
#include <vector>



template <typename T>
auto serialize_breadth(BCTree<T> const& tree)
    -> std::vector<typename BCTree<T>::NodeHandlerConst>
{
    std::vector<typename BCTree<T>::NodeHandlerConst> serial;
    serial.push_back(tree.node(0));

    for (size_t i=0; i < serial.size(); ++i)
    {
        for (auto const child : serial[i].children()) {
            if (child.index() != tree.null) {
                serial.push_back(child);
            }
        }
    }
    return serial;
}



template <typename T>
auto serialize_breadth_mut(BCTree<T>& tree)
    -> std::vector<typename BCTree<T>::NodeHandler>
{
    std::vector<typename BCTree<T>::NodeHandler> serial;
    serial.push_back(tree.node(0));

    for (size_t i=0; i < serial.size(); ++i)
    {
        for (auto const child : serial[i].children()) {
            if (child.index() != tree.null) {
                serial.push_back(child);
            }
        }
    }
    return serial;
}
