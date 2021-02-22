#include "bctree/BCTree.hpp"



////////////////////////////////////////////////////////////////////////////////
 template <typename T>
auto BCTree<T>::node(index_t index) const -> NodeHandler
{
    return {this, index};
}



 template <typename T>
auto BCTree<T>::node(index_t index) -> NodeHandler
{
    return {this, index};
}



 template <typename T>
auto BCTree<T>::size() const -> size_t
{
    return m_values.size();
}



 template <typename T>
auto BCTree<T>::contains(NodeHandler const& node) -> bool
{
    return node.m_tree == this;
}



 template <typename T>
auto BCTree<T>::insert(T&& value, index_t parent_index) -> NodeHandler
{
    m_values.push_back(std::forward<T>(value));

    auto const node_index = m_values.size()-1;

    if (node_index == 0)
    {
        m_relations.push_back({null, null, null});
    }

    else if (parent_index < m_values.size())
    {
        auto& relations = m_relations[parent_index];

        if (relations.child1 == null) {
            relations.child1 = node_index;
        }
        else if (relations.child2 == null) {
            relations.child2 = node_index;
        }
        else {
            throw 0;
        }

        m_relations.push_back({parent_index, null, null});
    }
    else
    {
        throw 0;
    }

    return NodeHandler{this, node_index};
}



 template <typename T>
auto BCTree<T>::insert(T&& value, NodeHandler const& parent) -> NodeHandler
{
    return insert(std::forward<T>(value), parent.m_index);
}



////////////////////////////////////////////////////////////////////////////////
 template <typename T>
BCTree<T>::NodeHandler::NodeHandler(BCTree* t, index_t i) noexcept:
    m_tree  {t},
    m_index {i}
{}



 template <typename T>
auto BCTree<T>::NodeHandler::tree() const -> BCTree const&
{
    return *m_tree;
}



 template <typename T>
auto BCTree<T>::NodeHandler::tree() -> BCTree&
{
    return *m_tree;
}



 template <typename T>
auto BCTree<T>::NodeHandler::index() const -> index_t
{
    return m_index;
}



 template <typename T>
auto BCTree<T>::NodeHandler::value() const -> T const&
{
    return m_tree->m_values[m_index];
}



 template <typename T>
auto BCTree<T>::NodeHandler::value() -> T&
{
    return m_tree->m_values[m_index];
}



 template <typename T>
auto BCTree<T>::NodeHandler::parent() const -> NodeHandler
{
    return m_tree->node(m_tree->m_relations[m_index].parent);
}



 template <typename T>
auto BCTree<T>::NodeHandler::children() const -> std::array<NodeHandler, 2>
{
    auto const& [parent, child1, child2] = m_tree->m_relations[m_index];
    return {NodeHandler{m_tree, child1}, NodeHandler{m_tree, child2}};
}



 template <typename T>
auto BCTree<T>::NodeHandler::insert(T&& value) -> NodeHandler
{
    return m_tree->insert(std::forward<T>(value), m_index);
}
