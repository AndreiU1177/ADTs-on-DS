#include "SortedSet.h"
#include "SortedSetIterator.h"


//BC = WC = TC = Theta(1)
SortedSet::SortedSet(Relation r) {
	this->capacity = 10;
	this->length = 0;
	this->elements = new TElem[this->capacity];
	this->rel = r;
}


//BC = Theta(1) WC = Theta(log(arrSize)) TC = O(log(arrSize))
int SortedSet::searchIndex(TElem e) const
{
	//!!
	if(this->length > 0)
	{
		if (this->rel(e, this->elements[0]) && !this->rel(this->elements[0], e))
			return -1;
		if (this->rel(this->elements[this->length - 1], e) && !this->rel(e, this->elements[this->length - 1]))
			return -1;
	}
	int left = 0;
	int right = length - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		//!!
		if (elements[mid] == e)
			return mid;
		else if (this->rel(elements[mid], e))
			left = mid + 1;
		else
			right = mid - 1;
	}
	return -1;
}


//BC = Theta(1) WC = Theta(arrSize) TC = O(arrSize)
bool SortedSet::add(TComp elem) {
	if (length == capacity) {
		this->capacity *= 2;
		TElem* resized_set = new TElem[this->capacity];
		for (int i = 0; i < this->length; i++)
			resized_set[i] = this->elements[i];
		delete[] this->elements;
		this->elements = resized_set;
	}
	if (this->rel(this->elements[this->length - 1], elem) && !this->rel(elem, this->elements[this->length - 1])) {
		this->elements[this->length++] = elem;
		return true;
	}
	int index = searchIndex(elem);
	if (index != -1)
		return false;
	int i = length - 1;
	while (i >= 0 && !this->rel(this->elements[i], elem)) {
		this->elements[i + 1] = elements[i];
		i--;
	}
	this->elements[i + 1] = elem;
	length++;
	return true;
}


//BC = Theta(1) WC = Theta(arrSize) TC = O(arrSize)
bool SortedSet::remove(TComp elem) {
	if (!search(elem))
		return false;
	int index = searchIndex(elem);
	for (int i = index; i < this->length; i++)
		this->elements[i] = this->elements[i + 1];
	this->length--;
	return true;
}


//BC = Theta(1) WC = Theta(log(arrSize)) TC = O(log(arrSize))
bool SortedSet::search(TComp elem) const {
	return searchIndex(elem) != -1;
}

//BC = WC = TC = O(1)
int SortedSet::size() const {
	return this->length;
}


//BC = WC = TC = O(1)
bool SortedSet::isEmpty() const {
	return this->size() == 0;
}


//BC = WC = TC = O(1)
SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


//BC = WC = TC = O(1)
SortedSet::~SortedSet() {
	delete[] this->elements;
}


//BC = Theta(arrSize) WC = O(arrSize^2) TC = O(arrSize^2)
void SortedSet::filter(Condition cond)
{
	int i = 0;
	while (i < this->length) {
		if (!cond(this->elements[i])) {
			remove(this->elements[i]);
			i--;
		}
		i++;
	}
}

