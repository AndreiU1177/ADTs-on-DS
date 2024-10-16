#include "SortedSetIterator.h"
#include <exception>

using namespace std;


//BC = WC = TC = Theta(1)
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m), currentIndex(0)
{
	
}


//BC = WC = TC = Theta(1)
void SortedSetIterator::first() {
	this->currentIndex = 0;
}


//BC = WC = TC = Theta(1)
void SortedSetIterator::next() {
	if (this->currentIndex == this->multime.size())
		throw exception();
	this->currentIndex++;
}


//BC = WC = TC = Theta(1)
TElem SortedSetIterator::getCurrent()
{
	if (this->currentIndex == this->multime.size())
		throw exception();
	return this->multime.elements[currentIndex];
}


//BC = WC = TC = Theta(1)
bool SortedSetIterator::valid() const {
	return this->multime.size() > this->currentIndex;
}

