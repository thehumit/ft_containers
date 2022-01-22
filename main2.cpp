#include <map>
#include <iostream>
#include <cstdlib>
#include "rbtree.hpp"


int main()
{
    // red_black_tree<int>::red_black_node node(1, BLACK);
    // red_black_tree<int>::red_black_node node1(4, BLACK);
    red_black_tree<int> tree;
    // tree._root =
    // tree.insert(4);
    for (size_t i = 0; i < 5; i++)
    {
        tree.insert(3);
    }
    std::cout << tree.is_red_black_tree() << "\n";
    tree._root->print_node(tree._root);
    // std::map<int, int> _map;
    // _map.insert(std::make_pair(1, 1));
    // _map.insert(std::make_pair(2, 1));
    // std::cout << _map[2] << "\n";
}
