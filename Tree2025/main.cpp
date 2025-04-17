#include <iostream>
#include "tree.h"
using namespace std;

void main() {
	int sz = 9;
	int* arr = new int[sz] {5, 3, 8, 0, 2, 10, 9, 4, 7};
	tree t;
	for (int i = 0; i < sz; i++) {
		add_to_tree(t, arr[i]);
	}

	delete[] arr;
}