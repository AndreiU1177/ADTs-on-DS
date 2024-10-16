#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


//BC = Theta(1), WC = Theta(length), TC = O(length)
BagIterator::BagIterator(Bag& c): bag(c)
{
	currentNode = nullptr;
	currentPos = 0;
	while(currentPos < bag.capacity && bag.hashTable[currentPos] == nullptr)
		currentPos++;
	if(currentPos < bag.capacity)
		currentNode = bag.hashTable[currentPos];
}

//BC = Theta(1), WC = Theta(length), TC = O(length)
void BagIterator::first() {
	currentNode = nullptr;
	currentPos = 0;
	while (currentPos < bag.capacity && bag.hashTable[currentPos] == nullptr)
		currentPos++;
	if (currentPos < bag.capacity)
		currentNode = bag.hashTable[currentPos];
}

//BC = Theta(1), WC = Theta(length), TC = O(length)
void BagIterator::next() {
	if (!valid())
		throw exception();
	if (currentNode->next != nullptr)
		currentNode = currentNode->next;
	else {
		currentPos++;
		while (currentPos < bag.capacity && bag.hashTable[currentPos] == nullptr)
			currentPos++;
		if (currentPos < bag.capacity)
			currentNode = bag.hashTable[currentPos];
		else
			currentNode = nullptr;
	}
}

//BC = WC = TC = Theta(1)
bool BagIterator::valid() const {
	return currentNode != nullptr;
}

//BC = WC = TC = Theta(1)
TElem BagIterator::getCurrent() const
{
	if (!valid())
		throw exception();
	return currentNode->data;
}


TElem BagIterator::remove() {
	if (!valid())
		throw exception();
	TElem toRemove = this->getCurrent();
	this->next();
	this->bag.remove(toRemove);
	return toRemove;
}
