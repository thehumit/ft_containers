#include <map>
#include <iostream>
#include "rbtree.hpp"

int main()
{
    red_black_tree<int>::red_black_node node(1, BLACK);
    red_black_tree<int>::red_black_node node1(4, BLACK);
    red_black_tree<int> tree(&node, &node1);
    // tree._root =

    tree.insert(1);
    tree.insert(10);
    tree.insert(20);
    tree.insert(0);
    tree._root->print_node(tree._root);
}
