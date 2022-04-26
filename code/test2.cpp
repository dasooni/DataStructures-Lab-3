
#include <iostream>
#include <vector>
#include <cassert>

#include "BinarySearchTree.h"

#define TEST_CONSTRUCTOR_FROM_VECTOR

/* *********************************************
 * Test 2: Constructor from sorted vector
 ********************************************* */

void test2() {
#ifdef TEST_CONSTRUCTOR_FROM_VECTOR

    /*********************************************************************/
    std::cout << "\nPHASE 0: constructor from sorted vector & get_parent\n";
    /*********************************************************************/
    {
        BinarySearchTree<int> t{std::vector<int>{2, 4, 6, 8, 10}};

        assert(BinarySearchTree<int>::get_count_nodes() == 5);

        // Display the tree
        /*std::cout << "Tree: \n";
        t.printTree();
        std::cout << '\n';*/

        assert(t.get_parent(6) == 0);  // root
        assert(t.get_parent(2) == 4);
        assert(t.get_parent(4) == 6);
        assert(t.get_parent(8) == 10);
        assert(t.get_parent(10) == 6);
    }

    assert(BinarySearchTree<int>::get_count_nodes() == 0);

    /********************************************************************************/
    std::cout << "\nPHASE 1: constructor from sorted vector & remove & get_parent\n";
    /********************************************************************************/
    {
        BinarySearchTree<int> t{std::vector<int>{2, 4, 6, 8, 10, 12, 14, 16}};

        assert(BinarySearchTree<int>::get_count_nodes() == 8);

        // Display the tree
        /*std::cout << "Tree: \n";
        t.printTree();
        std::cout << '\n';*/

        assert(t.get_parent(10) == 0);  // root
        assert(t.get_parent(2) == 4);
        assert(t.get_parent(4) == 6);
        assert(t.get_parent(8) == 6);
        assert(t.get_parent(6) == 10);
        assert(t.get_parent(12) == 14);
        assert(t.get_parent(16) == 14);
        assert(t.get_parent(14) == 10);

        t.remove(6);
        t.remove(10);
        t.remove(4);

        assert(BinarySearchTree<int>::get_count_nodes() == 5);

        assert(t.get_parent(12) == 0);  // root
        assert(t.get_parent(2) == 8);
        assert(t.get_parent(14) == 12);
        assert(t.get_parent(16) == 14);
        assert(t.get_parent(8) == 12);
    }

    assert(BinarySearchTree<int>::get_count_nodes() == 0);

    std::cout << "Success!!\n";
#endif
}
