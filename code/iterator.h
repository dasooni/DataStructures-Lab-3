#pragma once

/* **********************************************************
 * Class to represent a bi-directional iterator for BSTs     *
 * Bi-directional iterators can be moved in both directions, *
 * increasing and decreasing order of items keys             *
 * ***********************************************************/

template <typename Comparable>
class BinarySearchTree<Comparable>::Iterator {
public:
    // Some properties for Iterator  -- so that Iterator can be used with STL-algorithms
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Comparable;
    using pointer           = Comparable*;  // or also value_type*
    using reference         = Comparable&;  // or also value_type&

    /* ****************************************************************** */

	// Constructor
    Iterator() : current{ nullptr } {};
	
	//Destructor
    ~Iterator() = default;
	
	Comparable& operator*() const { return current->element; }
	
	Comparable* operator->() const { return &(current->element); }

	bool operator==(const Iterator& rhs) const { return current == rhs.current; }
	
	bool operator!=(const Iterator&	rhs) const { return !(current == rhs.current);}

	Iterator& operator++() {
		current = find_sucessor(current);
		return *this;
	}
	
	Iterator operator++(int) {
		Iterator old = *this;
		++(*this);
		return old;
	}
	
	Iterator& operator--() {
		current = find_predecessor(current);
		return *this;
	}
	
	Iterator operator--(int) {
		Iterator old = *this;
		--(*this);
		return old;
	}
	

private:
	Node* current;
	
	Iterator(Node *node = nullptr) : current{ node } {};
    friend class BinarySearchTree;
	
};
