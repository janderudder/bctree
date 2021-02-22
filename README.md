# bctree


```cpp
class BCTree<T> // Binary Contiguous Tree
```


This project is home to a relatively simple but powerful data-structure: a Binary Tree.

This particular implementation keeps the nodes in a contiguous array allocated on the heap.

It provides a `NodeHandler` nested class as an interface to manipulate individual nodes.


## Usage

A tree of strings.
```cpp
BCTree<std::string> tree;
```

Insert root node. Must provide a null index as parent.
```cpp
tree.insert("", tree.null);
```

Insert a new node. Must provide index of the parent node, here root.
```cpp
tree.insert("child_1", 0);
```

It's simpler if we get a handler for the root node.
```cpp
auto root = tree.node(0);
tree.insert("child_1", root);
```

Even simpler, get the handler when the node is created.
```cpp
auto root = tree.insert("", tree.null);
```

Using a node handler to insert an immediate child.
```cpp
root.insert("child_1");
auto child_2 = root.insert("child_2");
```

Retrieve handlers to immediate children.
```cpp
auto const root_children = root.children();
```

To know if a node is in a particular tree, we may test the following:
```cpp
auto const& the_tree = root.tree();

if (the_tree.contains(child_2)) {
    // `child_2` and `root` nodes are in the same tree
}
```

Equality comparison of handlers is possible too. It tests that the two handlers refer to the same index in the same tree.
```cpp
for (auto const child : root.children())
{
    if (child == child_2) {
        // this instance of `child` is `child_2`
    }
}
```



## Extending the project

This implementation could, seemingly, be easily generalized to support a Tree with an arbitrary number of children.

The underlying storage for node values and relationships could be configurable via a template parameter of the BCTree class, letting the user decide the type, or at least pass an allocator of their choosing. Or it could be altogether extracted and abstracted away from the class, to provide maximum flexibility.
