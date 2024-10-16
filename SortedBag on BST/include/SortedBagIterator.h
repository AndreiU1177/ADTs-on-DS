#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;
    

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);
	//in constructor build a dynamic array with all the elements from the bag
	Node* arr;
	int currentIndex;
	int length;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
	~SortedBagIterator();
	void jumpForward(int k);
};

