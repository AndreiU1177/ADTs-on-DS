#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <cassert>

using namespace std;

void testAdditional();

int main() {
	testAll();
	testAllExtended();
	
	cout << "Test over" << endl;
	system("pause");
	testAdditional();
	cout << "Extra operation done!";
}

bool relation11(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAdditional() {
	SortedBag sb(relation11);
	sb.add(1);
	sb.add(3);
	sb.add(2);
	sb.add(2);
	sb.add(2);
	sb.add(5);
	SortedBagIterator it = sb.iterator();
	assert(it.getCurrent() == 1);
	it.next();
	assert(it.getCurrent() == 2);
	it.jumpForward(3);
	assert(it.getCurrent() == 3);
	it.jumpForward(2);
	assert(!it.valid());
}
