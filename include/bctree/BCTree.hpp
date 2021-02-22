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
        index_t               parent;
        std::array<index_t,2> children;
        NodeRelations(index_t, index_t, index_t) noexcept;
    };

    std::vector<NodeRelations>  m_relations;
    std::vector<T>              m_values;

public:
    class NodeHandler;

    auto node(index_t) const -> NodeHandler;
    auto node(index_t) -> NodeHandler;
    auto size() const -> size_t;
    auto contains(NodeHandler const& node) const -> bool;

    auto insert(index_t parent, T) -> NodeHandler;
    auto insert(NodeHandler const& parent, T) -> NodeHandler;

    template <typename...Args>
    auto emplace(index_t parent, Args&&...) -> NodeHandler;

    template <typename...Args>
    auto emplace(NodeHandler const& parent, Args&&...) -> NodeHandler;

private:
    void _set_relations(index_t, index_t);

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

    auto insert(T) -> NodeHandler;

    template <typename...Args>
    auto emplace(Args&&...) -> NodeHandler;

    friend bool operator==(
        BCTree::NodeHandler const& lhs,
        BCTree::NodeHandler const& rhs
    ){
        return lhs.m_tree == rhs.m_tree && lhs.m_index == rhs.m_index;
    }
};



#include "bctree/BCTree.impl.hpp"
