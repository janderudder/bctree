#include "bctree/BCTree.hpp"



////////////////////////////////////////////////////////////////////////////////
 template <typename T>
BCTree<T>::NodeRelations::NodeRelations(index_t p, index_t c1, index_t c2)
noexcept:
    parent   {p},
    children {c1, c2}
 {
 }



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
auto BCTree<T>::contains(NodeHandler const& node) const -> bool
{
    return node.m_tree == this;
}



 template <typename T>
auto BCTree<T>::insert(index_t parent_index, T value) -> NodeHandler
{
    m_values.push_back(std::move(value));

    auto const node_index = m_relations.size();
    _set_relations(node_index, parent_index);

    return NodeHandler{this, node_index};
}



 template <typename T>
auto BCTree<T>::insert(NodeHandler const& parent, T value) -> NodeHandler
{
    return insert(parent.m_index, std::move(value));
}



 template <typename T>
    template <typename...Args>
auto BCTree<T>::emplace(index_t parent_index, Args&&... args) -> NodeHandler
{
    m_values.emplace_back(std::forward<Args>(args)...);

    auto const node_index = m_relations.size();
    _set_relations(node_index, parent_index);

    return NodeHandler{this, node_index};
}



 template <typename T>
    template <typename...Args>
auto BCTree<T>::emplace(NodeHandler const& parent, Args&&... args) -> NodeHandler
{
    return emplace(parent.m_index, std::forward<Args>(args)...);
}



 template <typename T>
void BCTree<T>::_set_relations(index_t node_index, index_t parent_index)
{
    if (node_index == 0)
    {
        m_relations.emplace_back(null, null, null);
    }

    else if (parent_index < m_relations.size())
    {
        auto& parent_relations = m_relations[parent_index];

        if (parent_relations.children[0] == null) {
            parent_relations.children[0] = node_index;
        }
        else if (parent_relations.children[1] == null) {
            parent_relations.children[1] = node_index;
        }
        else {
            throw 0;
        }

        m_relations.emplace_back(parent_index, null, null);
    }
    else
    {
        throw 0;
    }
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
    auto const& [child1, child2] = m_tree->m_relations[m_index].children;
    return {NodeHandler{m_tree, child1}, NodeHandler{m_tree, child2}};
}



 template <typename T>
auto BCTree<T>::NodeHandler::insert(T value) -> NodeHandler
{
    return m_tree->insert(m_index, std::move(value));
}



 template <typename T>
    template <typename...Args>
auto BCTree<T>::NodeHandler::emplace(Args&&... args) -> NodeHandler
{
    return m_tree->emplace(m_index, std::forward<Args>(args)...);
}
