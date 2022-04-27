#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>
#include <iterator> // used in node.h
#include <vector>

#include "dsexceptions.h"

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree {
private:
    struct Node;  // nested class defined in node.h

public:
    class Iterator;  // Exercise 2: nested class to be defined in Iterator.h

    BinarySearchTree() : root{nullptr} {
    }

    explicit BinarySearchTree(const std::vector<Comparable>& V) {

        root =  ConvertToBST(V.begin(), V.end(), nullptr) ;
    }

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{clone(rhs.root)} {
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

	// public member function named find, that returns an Iterator pointing
	// to the element in the tree that is equal to the parameter.
    Iterator find(const Comparable& x) {
        return contains(x, root);
    }

    Iterator begin() {
        if (isEmpty()) return end();
		
        return Iterator(findMin(root));
    }
    
    Iterator end() {
        return Iterator(nullptr);
    }

    /**
     * Copy assignment: copy and swap idiom
     */
    BinarySearchTree &operator=(BinarySearchTree _copy) {
        std::swap(root, _copy.root);
        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const {
        return (contains(x, root) != nullptr);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree";
        } else {
            /*inorder(root, out);*/
            preorder(root, out);
        }
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty() {
        root = makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x) {
        root = insert(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x) {
        root = remove(x, root);
    }

    /** Return total number of existing nodes
     *
     * Used for debug purposes
     */
    static int get_count_nodes() {
        return Node::count_nodes;
    }

	/** 
    * get the parent of a node containing x and return its value 
    * 
    */
    Comparable get_parent(const Comparable& x) const {
        Node* temp = contains(x, root);
		
        if (temp != nullptr && temp->parent != nullptr) {
        return temp->parent->element;
		}
		
        return Comparable{};
    }


private:
    Node *root;

    /**
     * Private member function to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x.
     */
    Node *insert(const Comparable &x, Node *t, Node *parent = nullptr) {
        if (t == nullptr) { 
			
            t = new Node{x, nullptr, nullptr, parent};

        } else if (x < t->element) {
			
            t->left = insert(x, t->left, t);
			
        } else if (t->element < x) {

            t->right = insert(x, t->right, t);

        } else {
        }
        return t;
    }
	
    /**
     * Private member function to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Return a pointer to the new root of the subtree that had root x
     */
    Node *remove(const Comparable &x, Node *t) {
        if (t == nullptr) {
            return t;  // Item not found
        }
		
        if (x < t->element) {
            t->left = remove(x, t->left);
			
        } else if (t->element < x) {
            t->right = remove(x, t->right);
			
        } else if (t->left != nullptr && t->right != nullptr) {  // Two children
            t->element = findMin(t->right)->element;
            t->right = remove(t->element, t->right);
			
        } else {
			
            Node *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            t != nullptr ? t->parent = oldNode->parent : nullptr;
            delete oldNode;
        }
        return t;
    }

    /**
     * Private member function to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    static Node *findMin(Node *t) {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }

        // Tail recursion can be easily replaced by a loop
        return findMin(t->left);  // recursive call
    }

    /**
     * Private member function to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    static Node *findMax(Node *t) {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

	
    /**
     * Private member function to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x, if x is found
     * Otherwise, return nullptr
     * If t is empty, then we can just return false. Otherwise, 
     * we make a recursive call on a subtree of t, either left or right, 
     * depending on the relationship of x to the item stored in t.
* 
     */
    Node *contains(const Comparable &x, Node *t) const {
        if (t == nullptr) {
            return t;
        } else if (x < t->element) {
            return contains(x, t->left);
        } else if (t->element < x) {
            return contains(x, t->right);
        } else {
            return t;  // Match
        }
    } // in the course book, this function returns a bool
	
    /****** NONRECURSIVE VERSION*************************
    Node *contains(const Comparable &x, Node *t) const {
        while (t != nullptr) {
            if (x < t->element) {
                t = t->left;
            } else if (t->element < x) {
                t = t->right;
            } else {
                return t;  // Match
            }
        }
        return t;  // No match
    }
    *****************************************************/

    /**
     * Private member function to make subtree empty.
     */
    Node *makeEmpty(Node *t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return nullptr;
    }

    /**
     * Private member function to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void inorder(Node *t, std::ostream &out) const {
        if (t != nullptr) {
            inorder(t->left, out);
            out << t->element << '\n';
            inorder(t->right, out);
        }
    }

	/**
	 * Private member function to print a subtree rooted at t in pre-order.
	 */
    void preorder(Node* t, std::ostream& out) const {
		
        if (t != nullptr) {
            out << t->element << '\n';
			preorder(t->left, out);
			preorder(t->right, out);
        }
    }

    /**
     * Private member function to clone subtree.
     */
    Node* clone(Node* t, Node* p = nullptr) const {
        if (t == nullptr) {
            return nullptr;
        }

        Node* temp = new Node{ t->element };

        temp->left = clone(t->left, temp);
        temp->right = clone(t->right, temp);
        temp->parent = p;

        return temp;
    }

    /*
    * A private member function that takes in two iterators of a vector and 
    * a parent node and inserts the elements of the vector into the tree.
    */
    Node* ConvertToBST(typename std::vector<Comparable>::const_iterator first, 
        typename std::vector<Comparable>::const_iterator last, Node* par) {

		// Base case
        if (first == last) {
            return nullptr;
        }

        // Find the middle element
        auto mid = std::next(first,std::distance(first,last)/2);

        // Create a node for the middle element
        Node* temp = new Node(*mid, nullptr, nullptr, par);
        
		// Recursively do the same for the left and right subtrees
        temp->left = ConvertToBST(first, mid, temp);
        temp->right = ConvertToBST(mid + 1, last, temp);

		// Return the root of the subtree
        return temp;

    }
	/*
    * A private member function named find_sucessor that returns a pointer
    * to the node storing the sucessor of the node passed in as a parameter.
    */
	static Node* find_sucessor(Node* node) {
		
		// base case
        if (node == nullptr) {
			return nullptr;
		}
        // If the node has a right child
		if (node->right != nullptr) {
			// the minmum value in the right subtree is the sucessor
			return findMin(node->right);
		}
		
		// Otherwise, the sucessor is the first ancestor of the node
		Node* temp = node->parent;
		while (temp != nullptr && node == temp->right) {
			node = temp;
			temp = temp->parent; //update parent
		}
		return temp;
	}

	/*
    * A private member function named find_predecessor that returns a pointer
	* to the node storing the predecessor of the node passed in as a parameter.
	*/
	static Node* find_predecessor(Node* node)  {
		
        // base case
		if (node == nullptr) {
			return nullptr;
		}
		// If the node has a left child
		if (node->left != nullptr) {
			// the maxmum value in the left subtree is the predecessor
			return findMax(node->left);
		}
		// Otherwise, the predecessor is the first ancestor of the node
		Node* temp = node->parent;
		while (temp != nullptr && node == temp->left) {
			node = temp;
			temp = temp->parent;
		}
		return temp;
	}

};

// Include definitions of the nested classes
#include "node.h"
#include "iterator.h"
