#include "bctree/BCTree.hpp"
#include <stdexcept>



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
auto BCTree<T>::node(index_t index) const -> NodeHandlerConst
{
    return {this, index};
}



 template <typename T>
auto BCTree<T>::node(index_t index) -> NodeHandlerMut
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
    return &node.tree() == this;
}



 template <typename T>
auto BCTree<T>::insert(index_t parent_index, T value) -> NodeHandlerMut
{
    m_values.push_back(std::move(value));

    auto const node_index = m_relations.size();
    _set_relations(node_index, parent_index);

    return NodeHandlerMut{this, node_index};
}



 template <typename T>
auto BCTree<T>::insert(NodeHandler const& parent, T value) -> NodeHandlerMut
{
    return insert(parent.m_index, std::move(value));
}



 template <typename T>
    template <typename...Args>
auto BCTree<T>::emplace(index_t parent_index, Args&&... args) -> NodeHandlerMut
{
    m_values.emplace_back(std::forward<Args>(args)...);

    auto const node_index = m_relations.size();
    _set_relations(node_index, parent_index);

    return NodeHandlerMut{this, node_index};
}



 template <typename T>
    template <typename...Args>
auto BCTree<T>::emplace(NodeHandler const& parent, Args&&... args) -> NodeHandlerMut
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

        if (parent_relations.children[0] == null)
        {
            parent_relations.children[0] = node_index;
        }
        else if (parent_relations.children[1] == null)
        {
            parent_relations.children[1] = node_index;
        }
        else {
            using namespace std::string_literals;
            throw std::logic_error{
                "inserting a node (index "s + std::to_string(node_index)
                + ") with an already full parent ("
                + std::to_string(parent_index) + ") in BCTree"
            };
        }

        m_relations.emplace_back(parent_index, null, null);
    }

    else
    {
        using namespace std::string_literals;
        throw std::logic_error{
            "inserting a node (index "s + std::to_string(node_index)
            + ") with invalid parent index (" + std::to_string(parent_index)
            + ") in BCTree"
        };
    }
}



////////////////////////////////////////////////////////////////////////////////
 template <typename T>
BCTree<T>::NodeHandlerMut::NodeHandlerMut(BCTree* t, index_t i) noexcept:
    m_index {i},
    m_tree  {t}
{}



 template <typename T>
auto BCTree<T>::NodeHandlerMut::tree() const -> BCTree const&
{
    return *m_tree;
}



 template <typename T>
auto BCTree<T>::NodeHandlerMut::index() const -> index_t
{
    return m_index;
}



 template <typename T>
auto BCTree<T>::NodeHandlerMut::tree() -> BCTree&
{
    return *m_tree;
}



 template <typename T>
auto BCTree<T>::NodeHandlerMut::value() const -> T const&
{
    return m_tree->m_values[m_index];
}



 template <typename T>
auto BCTree<T>::NodeHandlerMut::value() -> T&
{
    return m_tree->m_values[m_index];
}



 template <typename T>
auto BCTree<T>::NodeHandlerMut::parent() const -> NodeHandlerConst
{
    return static_cast<BCTree const*>(m_tree)->node(m_tree->m_relations[m_index].parent);
}



 template <typename T>
auto BCTree<T>::NodeHandlerMut::parent() -> NodeHandlerMut
{
    return m_tree->node(m_tree->m_relations[m_index].parent);
}



 template <typename T>
auto BCTree<T>::NodeHandlerMut::children() const -> std::array<NodeHandlerConst, 2>
{
    auto const& [child1, child2] = m_tree->m_relations[m_index].children;
    return {NodeHandlerConst{m_tree, child1}, NodeHandlerConst{m_tree, child2}};
}



 template <typename T>
auto BCTree<T>::NodeHandlerMut::children() -> std::array<NodeHandlerMut, 2>
{
    auto const& [child1, child2] = m_tree->m_relations[m_index].children;
    return {NodeHandlerMut{m_tree, child1}, NodeHandlerMut{m_tree, child2}};
}



 template <typename T>
auto BCTree<T>::NodeHandlerMut::insert(T value) -> NodeHandlerMut
{
    return m_tree->insert(m_index, std::move(value));
}



 template <typename T>
    template <typename...Args>
auto BCTree<T>::NodeHandlerMut::emplace(Args&&... args) -> NodeHandlerMut
{
    return m_tree->emplace(m_index, std::forward<Args>(args)...);
}



////////////////////////////////////////////////////////////////////////////////
template <typename T>
BCTree<T>::NodeHandlerConst::NodeHandlerConst(BCTree const* t, index_t i)
noexcept:
    m_index {i},
    m_tree  {t}
{
}



 template <typename T>
BCTree<T>::NodeHandlerConst::NodeHandlerConst(NodeHandlerMut const& mut)
noexcept:
    m_index {mut.index()},
    m_tree  {&mut.tree()}
{
}



template <typename T>
auto BCTree<T>::NodeHandlerConst::tree() const -> BCTree const&
{
    return *m_tree;
}



template <typename T>
auto BCTree<T>::NodeHandlerConst::index() const -> index_t
{
    return m_index;
}



 template <typename T>
auto BCTree<T>::NodeHandlerConst::value() const -> T const&
{
    return m_tree->m_values[m_index];
}



 template <typename T>
auto BCTree<T>::NodeHandlerConst::parent() const -> NodeHandlerConst
{
    return m_tree->node(m_tree->m_relations[m_index].parent);
}



 template <typename T>
auto BCTree<T>::NodeHandlerConst::children() const -> std::array<NodeHandlerConst, 2>
{
    auto const& [child1, child2] = m_tree->m_relations[m_index].children;
    return {NodeHandlerConst{m_tree, child1}, NodeHandlerConst{m_tree, child2}};
}
