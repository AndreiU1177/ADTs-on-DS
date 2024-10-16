#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

//BC = WC = AC = Theta(1)
ListIterator::ListIterator(const IndexedList& list) : list(list){
    this->current = list.head;
}

//BC = WC = AC = Theta(1)

void ListIterator::first(){
    this->current = list.head;
}

//BC = WC = AC = Theta(1)
void ListIterator::next(){
    if (!this->valid()) {
		throw std::exception("Invalid iterator");
	}
    this->current = this->current->next;
}

//BC = WC = AC = Theta(1)
bool ListIterator::valid() const{
    return this->current != nullptr;
}

//BC = WC = AC = Theta(1)
TElem ListIterator::getCurrent() const{
    if (!this->valid()) {
        throw std::exception("Invalid iterator");
    }
    return this->current->data;
}

//BC = Theta(1) WC = O(k) AC = Theta(k)
void ListIterator::jumpForward(int k)
{
    if (!this->valid()) {
        throw std::exception("Invalid iterator");
    }
    if (k < 1) {
        throw std::exception("Invalid step");
    }

    for (int i = 0; i < k; i++) {
        if (valid())
            this->current = this->current->next;
        else
            break;
    }

}
