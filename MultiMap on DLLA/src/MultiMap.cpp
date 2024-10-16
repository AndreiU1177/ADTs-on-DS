#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//BC = WC = TC = O(n)
MultiMap::MultiMap() {
	capacity = 10;
	elements = new Node[capacity];
	head = -1;
	firstEmpty = 0;
	for (int i = 0; i < capacity - 1; i++)
		elements[i].next = i + 1;
	elements[capacity - 1].next = -1;
	for (int i = 0; i < capacity; i++)
		elements[i].prev = i - 1;
	length = 0;
	tail = -1;
}

//BC = Theta(1), WC = Theta(n), TC = O(1) amortized
void MultiMap::add(TKey c, TValue v) {
	if (firstEmpty == -1) {
		Node* newElements = new Node[2 * capacity];
		for (int i = 0; i < capacity; i++)
			newElements[i] = elements[i];
		for (int i = capacity; i < 2 * capacity - 1; i++)
			newElements[i].next = i + 1;
		newElements[capacity - 1].next = capacity;
		newElements[2 * capacity - 1].next = -1;
		for (int i = capacity; i < 2 * capacity; i++)
			newElements[i].prev = i - 1;
		delete[] elements;
		elements = newElements;
		firstEmpty = capacity;
		capacity *= 2;
	}
	if (head == -1) {
		head = firstEmpty;
		tail = firstEmpty;
		firstEmpty = elements[firstEmpty].next;
		elements[head].info.first = c;
		elements[head].info.second = v;
		elements[head].next = -1;
		elements[head].prev = -1;
	}
	else {
		elements[tail].next = firstEmpty;
		elements[firstEmpty].prev = tail;
		tail = firstEmpty;
		firstEmpty = elements[firstEmpty].next;
		elements[tail].info.first = c;
		elements[tail].info.second = v;
		elements[tail].next = -1;
	}
	length++;
}

//BC = Theta(1), WC = Theta(n), TC = O(n)
bool MultiMap::remove(TKey c, TValue v) {
	int current = head;
	while (current != -1 && (elements[current].info.first != c || elements[current].info.second != v))
		current = elements[current].next;
	if (current == -1)
		return false;
	if (current == head) {
		head = elements[current].next;
		if (head != -1)
			elements[head].prev = -1;
	}
	else {
		elements[elements[current].prev].next = elements[current].next;
		if (elements[current].next != -1)
			elements[elements[current].next].prev = elements[current].prev;
	}
	elements[current].next = firstEmpty;
	firstEmpty = current;
	length--;
	return true;
}

//BC = WC = TC = O(n)
vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> values;
	int current = head;
	while (current != -1) {
		if (elements[current].info.first == c)
			values.push_back(elements[current].info.second);
		current = elements[current].next;
	}
	return values;
}

//BC = WC = TC = O(1)
int MultiMap::size() const {
	return length;
}

//BC = WC = TC = O(1)
bool MultiMap::isEmpty() const {
	return length == 0;
}

//BC = WC = TC = O(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

//BC = WC = TC = O(1)
MultiMap::~MultiMap() {
	delete[] elements;
}


//BC = Theta(n), WC = Theta(n*m), TC = O(n*m)
vector<TKey> MultiMap::keySet() const
{
	vector<TKey> keys;
	int current = head;
	while (current != -1) {
		TKey currKey = elements[current].info.first;
		bool found = false;
		for (int i = 0; i < keys.size(); i++)
			if (keys[i] == currKey) {
				found = true;
				break;
			}
		if (!found)
			keys.push_back(currKey);
		current = elements[current].next;
	}
	return keys;
}

