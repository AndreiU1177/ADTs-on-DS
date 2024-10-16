#include "MultiMapIterator.h"
#include "MultiMap.h"

//BC = WC = TC = O(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	this->currentPos = col.head;
}

//BC = WC = TC = O(1)
TElem MultiMapIterator::getCurrent() const{
	if(currentPos == -1)
		throw std::exception();
	return col.elements[currentPos].info;
}

//BC = WC = TC = O(1)
bool MultiMapIterator::valid() const {
	if (currentPos == -1)
		return false;
	return true;
}

//BC = WC = TC = O(1)
void MultiMapIterator::next() {
	if (currentPos == -1)
		throw std::exception();
	this->currentPos = col.elements[currentPos].next;
}

//BC = WC = TC = O(1)
void MultiMapIterator::first() {
	this->currentPos = col.head;
}

