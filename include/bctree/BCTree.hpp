/*

class BCTree<T>

Binary Tree,
nodes are in contiguous storage.

*/
#pragma once
#include <array>
#include <vector>


template <typename T>
class BCTree
{
public:
    using index_t = std::size_t;

    static constexpr auto null = index_t(-1);

private:
    struct NodeRelations {
        index_t parent;
        index_t child1;
        index_t child2;
    };

    std::vector<NodeRelations>  m_relations;
    std::vector<T>              m_values;

public:
    class NodeHandler;

    auto node(index_t) const -> NodeHandler;
    auto node(index_t) -> NodeHandler;
    auto size() const -> size_t;
    auto contains(NodeHandler const& node) const -> bool;

    auto insert(T&&, index_t parent) -> NodeHandler;
    auto insert(T&&, NodeHandler const& parent) -> NodeHandler;

};



////////////////////////////////////////////////////////////////////////////////
template <typename T>
class BCTree<T>::NodeHandler
{
    BCTree* m_tree;
    index_t m_index;

    friend class BCTree<T>;
    NodeHandler(BCTree* t, index_t i) noexcept;

public:
    auto tree()     const -> BCTree const&;
    auto tree()           -> BCTree&;
    auto index()    const -> index_t;
    auto value()    const -> T const&;
    auto value()          -> T&;
    auto parent()   const -> NodeHandler;
    auto children() const -> std::array<NodeHandler, 2>;

    auto insert(T&&) -> NodeHandler;

    friend bool operator==(
        BCTree::NodeHandler const& lhs,
        BCTree::NodeHandler const& rhs
    ){
        return lhs.m_tree == rhs.m_tree && lhs.m_index == rhs.m_index;
    }
};



#include "bctree/BCTree.impl.hpp"
