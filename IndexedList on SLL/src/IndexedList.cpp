#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

//BC = WC = AC = Theta(1)
IndexedList::IndexedList() : head(nullptr), length(0), tail(nullptr) {
	
}

//BC = WC = AC = Theta(1)
int IndexedList::size() const {
    return this->length;
}

//BC = WC = AC = Theta(1)
bool IndexedList::isEmpty() const {
    return this->length == 0;
}
//BC = Theta(1) WC = O(n) AC = Theta(n)
TElem IndexedList::getElement(int pos) const {
    if (pos < 0 || pos >= this->length) {
        throw std::exception("Invalid position");
    }

    if (pos == this->length - 1) {
		return tail->data;
	}

    Node* current = head;
    for (int i = 0; i < pos; ++i) {
        current = current->next;
    }

    return current->data;
}

//BC = Theta(1) WC = O(n) AC = Theta(n)
TElem IndexedList::setElement(int pos, TElem e) {
    if (pos < 0 || pos >= this->length) {
        throw std::exception("Invalid position");
    }

    if (pos == this->length - 1) {
        TElem old_val = tail->data;
        tail->data = e;
        return old_val;
    }
    Node* current = head;
    for (int i = 0; i < pos; ++i) {
        current = current->next;
    }
    TElem old_val = current->data;
    current->data = e;
    return old_val;
}

//BC = Theta(1) WC = Theta(1) AC = Theta(1)
void IndexedList::addToEnd(TElem e) {
    Node* newNode = new Node(e);
    newNode->next = nullptr;

    if (isEmpty()) {
        this->head = newNode;
        this->tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    this->length++;
}

//BC = Theta(1) WC = O(n) AC = Theta(n)
void IndexedList::addToPosition(int pos, TElem e) {
    if (pos < 0 || pos > this->length) {
		throw std::exception("Invalid position");
	}
    if (pos == this->length) {
		addToEnd(e);
        return;
    }
    if (pos == 0) {
		Node* newNode = new Node(e, head);  //constructor replaces newNode->next = head
		head = newNode;
		this->length++;
		return;
	}
    Node* current = head;
    for (int i = 0; i < pos - 1; ++i) {
		current = current->next;
	}
    Node* newNode = new Node(e, current->next);
    current->next = newNode;
    this->length++;
}

//BC = Theta(1) WC = O(n) AC = Theta(n)
TElem IndexedList::remove(int pos) {
    if (pos < 0 || pos >= this->length) {
		throw std::exception("Invalid position");
	}
    if (pos == 0) {
        TElem old_val = head->data;
        Node* toDelete = head;
        head = head->next;
		delete toDelete;
		this->length--;
        if (this->length == 0) this->tail = nullptr;
		return old_val;
    }
    Node* current = head;
    for (int i = 0; i < pos - 1; ++i) {
        current = current->next;
    }
    TElem old_val = current->next->data;
    Node* toDelete = current->next;
    current->next = current->next->next;
    if (pos == this->length - 1) {
		tail = current;
	}
    delete toDelete;
	this->length--;
	return old_val;
}

//BC = Theta(1) WC = O(n) AC = Theta(n)
int IndexedList::search(TElem e) const{
    Node* current = head;
    for (int i = 0; i < this->length; ++i) {
        if (current->data == e) {
			return i;
		}
		current = current->next;
	}
    return -1;
}

//BC = WC = AC = Theta(1)
ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}

//BC = WC = AC = Theta(n)
IndexedList::~IndexedList() {
    Node* current = head;
    while (current != nullptr) {
		Node* toDelete = current;
		current = current->next;
		delete toDelete;
	}
}