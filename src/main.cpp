#include "bctree/BCTree.hpp"
#include "util/echo.hpp"
#include <iostream>
#include <string>


int main()
{
    std::boolalpha(std::cout);

    {
        using NodeValueType = std::string;

        BCTree<NodeValueType> tree;

        auto root = tree.insert(tree.null, "root node");
        auto const child_1 = root.insert("child_1");
        auto const child_2 = root.emplace("child_2");

        ECHO_LN(child_2 == root.children()[1]);
        ECHO_LN(root.tree().contains(child_2));
        ECHO_LN(root.value());
        ECHO_LN(child_1.value());
        ECHO_LN(child_2.value());

        BCTree<NodeValueType> tree_2;
        auto t2_root = tree_2.emplace(tree_2.null, "t2_root");
        ECHO_LN(root.tree().contains(t2_root));
    }

    return 0;

}
