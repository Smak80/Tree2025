#include <iostream>
#include "tree.h"
using namespace std;

void main() {
	int sz = 8;
	int* arr = new int[sz] {8, 5, 12, 2, 7, 10, 15, 11};
	tree t;
	for (int i = 0; i < sz; i++) {
		add_to_tree(t, arr[i]);
	}
	remove_from_tree(t, 8);
	delete[] arr;
}