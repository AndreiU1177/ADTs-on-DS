#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


int Bag::hashFunction(TElem e) const
{
	return abs(e) % this->capacity;
}


//BC = WC = TC = Theta(newCapacity)
void Bag::resize()
{
	int newCapacity = capacity * 2;
	Node** newHashTable = new Node*[newCapacity];
	for (int i = 0; i < newCapacity; i++)
		newHashTable[i] = nullptr;
	for (int i = 0; i < capacity; i++) {
		Node* current = hashTable[i];
		while (current != nullptr) {
			Node* next = current->next;
			int position = abs(current->data) % newCapacity;
			current->next = newHashTable[position];
			newHashTable[position] = current;
			current = next;
		}
	}
	delete[] hashTable;
	hashTable = newHashTable;
	capacity = newCapacity;
	loadFactor = (double)length / capacity;
}

//BC = WC = TC = Theta(1)
Bag::Bag() {
	capacity = 16;
	length = 0;
	loadFactor = 0;
	hashTable = new Node*[capacity];
	for (int i = 0; i < capacity; i++)
		hashTable[i] = nullptr;
}

//BC = Theta(1), WC = O(newCapacity), TC = Theta(1) amortized
void Bag::add(TElem elem) {
	if(loadFactor > MAX_LOAD_FACTOR)
		resize();
	int position = hashFunction(elem);
	Node* newNode = new Node(elem);
	newNode->next = hashTable[position];
	hashTable[position] = newNode;
	length++;
	loadFactor = (double)length / capacity;
}

//BC = Theta(1), WC = O(length), TC = Theta(1) on average
bool Bag::remove(TElem elem) {
	int position = hashFunction(elem);
	Node* current = hashTable[position];
	Node* previous = nullptr;
	while (current != nullptr && current->data != elem) {
		previous = current;
		current = current->next;
	}
	if (current == nullptr)
		return false;
	if (previous == nullptr)
		hashTable[position] = current->next;
	else
		previous->next = current->next;
	delete current;
	length--;
	loadFactor = (double)length / capacity;
	return true;
}

//BC = Theta(1), WC = O(length), TC = Theta(1) on average
bool Bag::search(TElem elem) const {
	int position = hashFunction(elem);
	Node* current = hashTable[position];
	while (current != nullptr && current->data != elem)
		current = current->next;
	if (current == nullptr)
		return false;
	return true;
}

//BC = Theta(1), WC = O(length), TC = Theta(1) on average
int Bag::nrOccurrences(TElem elem) const {
	int position = hashFunction(elem);
	Node* current = hashTable[position];
	int count = 0;
	while (current != nullptr) {
		if (current->data == elem)
			count++;
		current = current->next;
	}
	return count;
}

//BC = WC = TC = Theta(1)
int Bag::size() const {
	return length;
}

//BC = WC = TC = Theta(1)
bool Bag::isEmpty() const {
	return length == 0;
}

BagIterator Bag::iterator() {
	return BagIterator(*this);
}

//BC = WC = TC = Theta(length)
Bag::~Bag() {
	for (int i = 0; i < capacity; i++)
	{
		Node* current = hashTable[i];
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] hashTable;
}

