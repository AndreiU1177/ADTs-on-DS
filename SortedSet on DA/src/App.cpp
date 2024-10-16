#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
	testAll();
	testAllExtended();
	testAdditional();

	cout << "Test end" << endl;
	system("pause");
}

bool r3(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

bool conditionBiggerThanTen(TComp e) {
	return e > 10;
}

void testAdditional() {
	std::cout << "Test additional...\n";
	SortedSet s(r3);
	s.add(13);
	s.add(5);
	s.add(6);
	s.add(19);
	s.add(119);
	s.add(9);
	s.filter(conditionBiggerThanTen);
	assert(s.size() == 3);
	SortedSetIterator it = s.iterator();
	it.first();
	TComp e = it.getCurrent();
	assert(e == 13);
	it.next();
	e = it.getCurrent();
	assert(e == 19);
	it.next();
	e = it.getCurrent();
	assert(e == 119);
}