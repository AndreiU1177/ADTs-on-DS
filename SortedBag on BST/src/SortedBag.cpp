#include "SortedBag.h"
#include "SortedBagIterator.h"


//BC = WC = TC = Theta(1)
SortedBag::SortedBag(Relation r) {
	relation = r;
	root = nullptr;
	length = 0;
}

//BC = Theta(1), WC = Theta(heigth), TC = Theta(height)
void SortedBag::add(TComp e) {
	if (root == nullptr) {
		root = new Node(e);
		length++;
		return;
	}
	Node* current = root;
	while (true) {
		if (relation(e, current->value) && !relation(current->value, e)) {
			if (current->leftChild == nullptr) {
				current->leftChild = new Node(e);
				current->leftChild->parent = current;
				length++;
				return;
			}
			else {
				current = current->leftChild;
			}
		}
		else if (relation(current->value, e) && !relation(e, current->value)) {
			if (current->rightChild == nullptr) {
				current->rightChild = new Node(e);
				current->rightChild->parent = current;
				length++;
				return;
			}
			else {
				current = current->rightChild;
			}
		}
		else if (relation(e, current->value) && relation(current->value, e)) {
			current->frequency++;
			length++;
			return;
		}
	}
}

//BC = Theta(1), WC = Theta(height), TC = O(height)
bool SortedBag::remove(TComp e) {
	Node* current = root;

	while (current != nullptr) {
		if (relation(e, current->value) && relation(current->value, e)) {
			if (current->frequency > 1) {
				current->frequency--;
				length--;
				return true;
			}
			else {
				// Node has zero or one child
				if (current->leftChild == nullptr || current->rightChild == nullptr) {
					Node* child = (current->leftChild != nullptr) ? current->leftChild : current->rightChild;

					if (current->parent == nullptr) {
						// Current is root
						root = child;
					}
					else if (current->parent->leftChild == current) {
						current->parent->leftChild = child;
					}
					else {
						current->parent->rightChild = child;
					}

					if (child != nullptr) {
						child->parent = current->parent;
					}

					delete current;
					length--;
					return true;
				}
				else {
					// Node has two children: find the minimum in the right subtree
					Node* minimum = current->rightChild;
					while (minimum->leftChild != nullptr) {
						minimum = minimum->leftChild;
					}

					current->value = minimum->value;
					current->frequency = minimum->frequency;

					// Remove minimum since we moved him to current 
					Node* minParent = minimum->parent;
					Node* minRightChild = minimum->rightChild;

					if (minParent->leftChild == minimum) {  //enters here if we descended left at least once
						minParent->leftChild = minRightChild;
					}
					else {  //enters here if we went only right once and we couldn't descend left
						minParent->rightChild = minRightChild;
					}

					if (minRightChild != nullptr) {
						minRightChild->parent = minParent;
					}

					delete minimum;
					length--;
					return true;
				}
			}
		}
		else if (relation(e, current->value)) {
			current = current->leftChild;
		}
		else {
			current = current->rightChild;
		}
	}
	return false;
}


//BC = Theta(1), WC = Theta(height), TC = O(height)
bool SortedBag::search(TComp elem) const {
	Node* current = root;
	while (current != nullptr) {
		if (relation(elem, current->value) && relation(current->value, elem)) {
			return true;
		}
		else if (relation(elem, current->value)) {
			current = current->leftChild;
		}
		else {
			current = current->rightChild;
		}
	}
	return false;
}


//BC = Theta(1), WC = Theta(height), TC = O(height)
int SortedBag::nrOccurrences(TComp elem) const {
	Node* current = root;
	while (current != nullptr) {
		if (relation(elem, current->value) && relation(current->value, elem)) {
			return current->frequency;
		}
		else if (relation(elem, current->value)) {
			current = current->leftChild;
		}
		else {
			current = current->rightChild;
		}
	}
	return 0;
}


//BC = WC = TC = Theta(1)
int SortedBag::size() const {
	return length;
}

//BC = WC = TC = Theta(1)
bool SortedBag::isEmpty() const {
	return length == 0;
}

//BC = WC = TC = Theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

//BC = Theta(length), WC = Theta(height*length), TC = O(height*length)
SortedBag::~SortedBag() {
	while (root != nullptr) {
		remove(root->value);
	}
}
