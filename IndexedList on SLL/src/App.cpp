#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include "IndexedList.h"
#include "ListIterator.h"
#include <cassert>

using namespace std;

void testAdditional();

int main(){
    testAll();
    testAllExtended();
    cout<<"Finished LI Tests!"<<endl;
    testAdditional();
}

void testAdditional() {
    IndexedList list = IndexedList();
    for (int i = 1; i < 10; i++) {
        list.addToEnd(i);
    }
    ListIterator it = list.iterator();
    assert(it.getCurrent() == 1);
    it.jumpForward(2);
    assert(it.getCurrent() == 3);
    it.next();
    it.jumpForward(4);
    assert(it.getCurrent() == 8);
    it.jumpForward(3);
    assert(!it.valid());
    cout << "jumpForward test done!";
}