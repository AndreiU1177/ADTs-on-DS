#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

//BC = WC = TC = Theta(bagLength)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	arr = new Node[b.length];
	int i = 0;
	Node* current = bag.root;
	Node* prev = nullptr;

	while (current != nullptr) {
		if (prev == current->parent) {  //last step we descended
			if (current->leftChild != nullptr) {  //can we go further left?
				prev = current;
				current = current->leftChild;
			}
			else {  //cannot go left, so we append current and try to go right
				int freq = current->frequency;
				while (freq > 0) {
					arr[i].value = current->value;
					i++;
					freq--;
				}
				prev = current;
				current = (current->rightChild != nullptr) ? current->rightChild : current->parent;  //go right if possible, else go up
			}
		}
		else if (prev == current->leftChild) {  //last step we went up from a left node => we can't go left so we append current to arr and try to go right
			int freq = current->frequency;
			while (freq > 0) {
				arr[i].value = current->value;
				i++;
				freq--;
			}
			prev = current;
			current = (current->rightChild != nullptr) ? current->rightChild : current->parent;  //go right if possible, else go up
		}
		else if (prev == current->rightChild) {  //last step we went up from a right node => we keep going up since we visited left branch, curr node and his right branch
			prev = current;
			current = current->parent;
		}
	}
	length = i;
	this->currentIndex = 0;
}

SortedBagIterator::~SortedBagIterator()
{
	delete arr;
}

//BC = WC = TC = Theta(1)
TComp SortedBagIterator::getCurrent() {
	if(!valid())
		throw exception();
	return arr[currentIndex].value;
}

//BC = WC = TC = Theta(1)
bool SortedBagIterator::valid() {
	return currentIndex < length;
}

//BC = WC = TC = Theta(1)
void SortedBagIterator::next() {
	if (!valid())
		throw exception();
	//increment the current index if frequency is 1, else decrement the frequency
	currentIndex++;
}

//BC = WC = TC = Theta(1)
void SortedBagIterator::first() {
	currentIndex = 0;
}

void SortedBagIterator::jumpForward(int k)
{
	if (!valid() || k <= 0)
		throw exception();
	currentIndex += k;
}

