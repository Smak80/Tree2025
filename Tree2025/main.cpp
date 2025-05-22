#include <iostream>
#include "tree.h"
using namespace std;

void show_tree(tree t, bypass_type type) {
	auto q = bypass(t, type);
	while (q.size() > 0) {
		auto curr = q.front();
		if (curr) {
			cout << curr->value << "(" << curr->count << "; " << curr->level << ")";
		}
		else {
			cout << "-";
		}
		cout << " ";
		q.pop();
	}
	cout << endl;
}

void main() {
	int sz = 12;
	int* arr = new int[sz] {8, 5, 8, 12, 2, 2, 7, 10, 8, 15, 5, 11};
	tree t;
	for (int i = 0; i < sz; i++) {
		add_to_tree(t, arr[i]);
	}
	show_tree(t, prefix);
	show_tree(t, infix);
	show_tree(t, postfix);
	show_tree(t, wide);
	remove_from_tree(t, 8);
	delete[] arr;
}