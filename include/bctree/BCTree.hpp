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
    class NodeHandlerMut;
    class NodeHandlerConst;

    auto node(index_t) const -> NodeHandlerConst;
    auto node(index_t) -> NodeHandlerMut;
    auto size() const -> size_t;
    auto contains(NodeHandler const& node) const -> bool;

    auto insert(index_t parent, T) -> NodeHandlerMut;
    auto insert(NodeHandler const& parent, T) -> NodeHandlerMut;

    template <typename...Args>
    auto emplace(index_t parent, Args&&...) -> NodeHandlerMut;

    template <typename...Args>
    auto emplace(NodeHandler const& parent, Args&&...) -> NodeHandlerMut;

private:
    void _set_relations(index_t, index_t);

};



////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct BCTree<T>::NodeHandler
{
    virtual auto tree()     const -> BCTree const& = 0;
    virtual auto index()    const -> index_t = 0;
    virtual auto value()    const -> T const& = 0;
    virtual auto parent()   const -> NodeHandlerConst = 0;
    virtual auto children() const -> std::array<NodeHandlerConst, 2> = 0;

    friend bool operator==(
        BCTree::NodeHandler const& lhs,
        BCTree::NodeHandler const& rhs
    ){
        return &lhs.tree() == &rhs.tree() && lhs.index() == rhs.index();
    }
};



template <typename T>
class BCTree<T>::NodeHandlerMut : public BCTree<T>::NodeHandler
{
    index_t m_index;
    BCTree* m_tree;

    friend class BCTree<T>;
    NodeHandlerMut(BCTree* t, index_t i) noexcept;

public:
    auto tree()     const -> BCTree const& override;
    auto tree()           -> BCTree&;
    auto index()    const -> index_t override;
    auto value()    const -> T const& override;
    auto value()          -> T&;
    auto parent()   const -> NodeHandlerConst override;
    auto parent()         -> NodeHandlerMut;
    auto children() const -> std::array<NodeHandlerConst, 2> override;
    auto children()       -> std::array<NodeHandlerMut, 2>;

    auto insert(T) -> NodeHandlerMut;

    template <typename...Args>
    auto emplace(Args&&...) -> NodeHandlerMut;
};



template <typename T>
class BCTree<T>::NodeHandlerConst : public BCTree<T>::NodeHandler
{
    index_t         m_index;
    BCTree const*   m_tree;

    friend class BCTree<T>;
    NodeHandlerConst(BCTree const* t, index_t i) noexcept;

public:
    NodeHandlerConst(NodeHandlerMut const&) noexcept;
    
    auto tree()     const -> BCTree const& override;
    auto index()    const -> index_t override;
    auto value()    const -> T const& override;
    auto parent()   const -> NodeHandlerConst override;
    auto children() const -> std::array<NodeHandlerConst, 2> override;
};



#include "bctree/BCTree.impl.hpp"
