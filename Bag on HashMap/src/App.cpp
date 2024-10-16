#include "Bag.h"
#include "BagIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>
#include <assert.h>

void testAdditional();

using namespace std;

int main() {

	testAll();
	cout << "Short tests over" << endl;
	testAllExtended();

	cout << "All test over" << endl;
	testAdditional();
	cout << "DONE";
}

void testAdditional() {
	Bag b;
	b.add(5);
	b.add(1);
	b.add(10);
	BagIterator it = b.iterator();
	it.first();
	assert(it.getCurrent() == 1);
	it.remove();
	assert(it.getCurrent() == 5);
	assert(it.remove() == 5);
	it.remove();
	assert(it.valid() == false);
}