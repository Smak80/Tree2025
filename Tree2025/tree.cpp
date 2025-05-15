#include "tree.h"
#include <stack>
using namespace std;

node* create_node(int value);
bool add_to_tree(node*& root, int value);
stack<node*> find_in_tree(node* root, int value);
bool remove_from_tree(node*& root, int value);
int get_level(node* n);
void drop_tree(node*& n);
queue<node*> bypass(node* t, bypass_type type);

stack<node*> find_max_value(node* n);
stack<node*> find_min_value(node* n);

bool add_to_tree(tree& t, int value)
{
	return add_to_tree(t.root, value);
}

node* find_in_tree(tree& t, int value)
{
	auto stack = find_in_tree(t.root, value);
	auto result = stack.top();
	return (result->value == value) ? result : nullptr;
}

bool remove_from_tree(tree& t, int value)
{
	return remove_from_tree(t.root, value);
}

void drop_tree(tree& t)
{
	drop_tree(t.root);
}

queue<node*> bypass(tree& t, bypass_type type)
{
	return queue<node*>();
}

bool add_to_tree(node*& root, int value) {
	// ������ ������?
	if (!root) {
		root = create_node(value);
		return true;
	}
	// ������ �� ������. ����, ��� �� ��� ������ �������� � ������.
	auto stack = find_in_tree(root, value);
	auto result = stack.top();

	if (result->value == value) {
		// �������� � ������ ��� ����
		result->count++;
		return false;
	}
	// ���������� ������ ���� � ����� ���������������� � ������ ���������
	if (value < result->value) result->left = create_node(value);
	else result->right = create_node(value);

	//���������� ������ ����
	while (stack.size() > 0) {
		result = stack.top();
		result->level = get_level(result);
		stack.pop();
	}

	return true;
}

stack<node*> find_in_tree(node* root, int value) {
	stack<node*> st;
	auto curr = root;
	st.push(root);
	while (curr && value != curr->value) {
		if (value < curr->value) curr = curr->left;
		else curr = curr->right;
		if (curr) st.push(curr);
	}
	return st;
}

bool remove_from_tree(node*& root, int value) {
	if (!root) return false;
	auto st = find_in_tree(root, value);
	auto rem_node = st.top();
	if (rem_node->value != value) return false;
	// ������� ����?
	if (!rem_node->level) {
		st.pop();
		if (st.size() > 0) {
			auto prev = st.top();
			if (prev->left == rem_node) prev->left = nullptr;
			else prev->right = nullptr;
		}
		else root = nullptr;
		delete rem_node;
		return true;
	}
	// ������� �� ����. ������� � �������� ������� ��������� max ��� min ������� 
	stack<node*> sub_stack;
	if (rem_node->left->level > rem_node->right->level) {
		sub_stack = find_max_value(rem_node->left);
	}
	else {
		sub_stack = find_min_value(rem_node->right);
	}
	auto leaf = sub_stack.top();
	sub_stack.pop();
	rem_node->value = leaf->value;
	rem_node->count = leaf->count;
	if (leaf->left) sub_stack.top()->right = leaf->left;
	if (leaf->right) sub_stack.top()->left = leaf->right;
	delete leaf;
	while (sub_stack.size() > 0) {
		auto curr = sub_stack.top();
		curr->level = get_level(sub_stack.top());
		sub_stack.pop();
	}
	while (st.size() > 0) {
		auto curr = st.top();
		curr->level = get_level(st.top());
		st.pop();
	}
}

stack<node*> find_max_value(node* n) {
	stack<node*> st;
	while (n) {
		st.push(n);
		n = n->right;
	}
	return st;
}

stack<node*> find_min_value(node* n) {
	stack<node*> st;
	while (n) {
		st.push(n);
		n = n->left;
	}
	return st;
}


node* create_node(int value) {
	node* n = new node;
	n->value = value;
	return n;
}

int get_level(node* n) {
	if (!n) return -1;
	auto ll = (n->left) ? n->left->level : -1;
	auto rl = (n->right) ? n->right->level : -1;
	return max(ll, rl) + 1;
}

void drop_tree(node*& n) {
	
}

queue<node*> bypass(node* t, bypass_type type) {
	queue<node*> q;
	switch (type) {
	case prefix: {

		break;
	}
	case infix: {

		break;
	}
	case postfix: {

		break;
	}
	case wide: {

		break;
	}
	}
}