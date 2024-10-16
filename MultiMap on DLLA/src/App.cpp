#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"
#include <cassert>

using namespace std;

void testkeySet();

int main() {


	testAll();
	testAllExtended();
	cout << "End" << endl;
	testkeySet();
	system("pause");

}

void testkeySet() {
	MultiMap m;
	m.add(1, 100);
	m.add(2, 200);
	m.add(3, 300);
	m.add(1, 500);
	m.add(2, 600);
	m.add(4, 800);

	vector<TKey> v;
	v = m.keySet();
	assert(v.size() == 4);

	m.add(5, 12);
	v = m.keySet();
	assert(v.size() == 5);

	m.add(5, 44);
	v = m.keySet();
	assert(v.size() == 5);

	cout << "Test keySet passed" << endl;
}
