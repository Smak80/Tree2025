#include "tree.h"

node* create_node(int value);
bool add_to_tree(node*& root, int value);
node* find_in_tree(node* root, int value, bool return_last_node = false);

bool add_to_tree(tree& t, int value)
{
	return add_to_tree(t.root, value);
}

node* find_in_tree(tree& t, int value)
{
	return find_in_tree(t.root, value);
}

bool add_to_tree(node*& root, int value) {
	// Дерево пустое?
	if (!root) {
		root = create_node(value);
		return true;
	}
	// Дерево не пустое. Ищем, нет ли уже такого элемента в дереве.
	auto result = find_in_tree(root, value, true);
	if (result->value == value) {
		// Значение в дереве уже было
		result->count++;
		return false;
	}
	if (value < result->value) result->left = create_node(value);
	else result->right = create_node(value);
	return true;
}

node* find_in_tree(node* root, int value, bool return_last_node) {
	auto curr = root;
	node* prev = nullptr;
	while (curr) {
		if (value == curr->value) return curr;
		prev = curr;
		if (value < curr->value) curr = curr->left;
		else curr = curr->right;
	}
	return (return_last_node && !curr) ? prev : curr;
}

node* create_node(int value) {
	node* n = new node;
	n->value = value;
	return n;
}
