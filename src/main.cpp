#include "bctree/BCTree.hpp"
#include "util/echo.hpp"
#include <iostream>
#include <string>


int main()
{
    std::boolalpha(std::cout);

    using NodeValueType = std::string;

    BCTree<NodeValueType> tree;

    auto root = tree.insert("root", tree.null);
    auto const child_1 = root.insert("child_1");
    auto const child_2 = root.insert("child_2");

    ECHO_LN(child_2 == root.children()[1]);
    ECHO_LN(root.tree().contains(child_2));

    BCTree<NodeValueType> tree_2;
    auto t2_root = tree_2.insert("t2_root", tree_2.null);
    ECHO_LN(root.tree().contains(t2_root));

}
