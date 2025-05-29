#include "tree.h"
#include <stack>
using namespace std;

node* create_node(int value);
bool add_to_tree(node*& root, int value);
stack<node*> find_in_tree(node* root, int value);
bool remove_from_tree(node*& root, int value);
int get_level(node* n);
void drop_tree(node*& n);
void bypass(queue<node*>& q, node* t, bypass_type type);

void small_rotate_left(node*& n);
void small_rotate_right(node*& n);
void large_rotate_left(node*& n);
void large_rotate_right(node*& n);
bool balance(node*& n);
void balance_stack(node*& root, stack<node*> stack);

stack<node*> find_max_value(node* n);
stack<node*> find_min_value(node* n);

bool add_to_tree(tree& t, int value)
{
	auto res = add_to_tree(t.root, value);
	if (res) {
		t.count++;
		t.height = get_level(t.root) + 1;
	}
	return res;
}

node* find_in_tree(tree& t, int value)
{
	auto stack = find_in_tree(t.root, value);
	auto result = stack.top();
	return (result->value == value) ? result : nullptr;
}

bool remove_from_tree(tree& t, int value)
{
	auto res = remove_from_tree(t.root, value);
	if (res) {
		t.count--;
		t.height = get_level(t.root) + 1;
	}
	return res;
}

void drop_tree(tree& t)
{
	drop_tree(t.root);
	t.count = 0;
	t.height = 0;
}

queue<node*> bypass(tree t, bypass_type type)
{
	queue<node*> q;
	bypass(q, t.root, type);
	return q;
}

bool add_to_tree(node*& root, int value) {
	// Дерево пустое?
	if (!root) {
		root = create_node(value);
		return true;
	}
	// Дерево не пустое. Ищем, нет ли уже такого элемента в дереве.
	auto stack = find_in_tree(root, value);
	auto result = stack.top();

	if (result->value == value) {
		// Значение в дереве уже было
		result->count++;
		return false;
	}
	// Добавление нового узла с ранее несуществовавшим в дереве значением
	if (value < result->value) result->left = create_node(value);
	else result->right = create_node(value);

	balance_stack(root, stack);
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
	// Удаляем лист?
	if (!rem_node->level) {
		st.pop();
		if (st.size() > 0) {
			auto prev = st.top();
			if (prev->left == rem_node) prev->left = nullptr;
			else prev->right = nullptr;
		}
		else root = nullptr;
		delete rem_node;
		balance_stack(root, st);
		return true;
	}
	// Удаляем не лист. Находим в наиболее высоком поддереве max или min элемент 
	stack<node*> sub_stack;
	bool left_subtree = rem_node->left->level > rem_node->right->level;
	if (left_subtree) {
		sub_stack = find_max_value(rem_node->left);
	}
	else {
		sub_stack = find_min_value(rem_node->right);
	}
	auto leaf = sub_stack.top();
	sub_stack.pop();
	rem_node->value = leaf->value;
	rem_node->count = leaf->count;

	if (sub_stack.size() > 0) {
		if (left_subtree)
			sub_stack.top()->right = leaf->left;
		else 
			sub_stack.top()->left = leaf->right;
	}
	else {
		if (left_subtree) 
			rem_node->left = leaf->left;
		else
			rem_node->right = leaf->right;
	}
	delete leaf;
	/*while (sub_stack.size() > 0) {
		auto curr = sub_stack.top();
		balance(curr);
		curr->level = get_level(sub_stack.top());
		sub_stack.pop();
	}
	while (st.size() > 0) {
		auto curr = st.top();
		balance(curr);
		curr->level = get_level(st.top());
		st.pop();
	}*/
	balance_stack(root, sub_stack);
	balance_stack(root, st);
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
	queue<node*> nodes;
	bypass(nodes, n, postfix);
	while (nodes.size() > 0) {
		auto del = nodes.front();
		nodes.pop();
		delete del;
	}
	n = nullptr;
}

void bypass(queue<node*>& q, node* t, bypass_type type) {
	if (!t) return;
	switch (type) {
	case prefix: {
		q.push(t);
		bypass(q, t->left, type);
		bypass(q, t->right, type);
		break;
	}
	case infix: {
		bypass(q, t->left, type);
		q.push(t);
		bypass(q, t->right, type);
		break;
	}
	case postfix: {
		bypass(q, t->left, type);
		bypass(q, t->right, type);
		q.push(t);
		break;
	}
	case wide: {
		queue<node*> tmp;
		tmp.push(t);
		q.push(t);
		auto cnt = (1 << t->level) - 1; 
		for (int i = 0; i < cnt; i++) { // Перебираем эл-ты до предпоследнего уровня
			auto curr = tmp.front();
			tmp.push(curr ? curr->left : nullptr);
			tmp.push(curr ? curr->right : nullptr);
			q.push(curr ? curr->left : nullptr);
			q.push(curr ? curr->right : nullptr);
			tmp.pop();
		}
		break;
	}
	}
}

void small_rotate_left(node*& n)
{
	node* old_root = n;
	n = n->right;
	old_root->right = n->left;
	n->left = old_root; 
	old_root->level = get_level(old_root);
	n->level = get_level(n);
}

void small_rotate_right(node*& n)
{
	auto old_root = n;
	n = n->left;
	old_root->left = n->right;
	n->right = old_root;
	old_root->level = get_level(old_root);
	n->level = get_level(n);
}

void large_rotate_left(node*& n)
{
	small_rotate_right(n->right);
	small_rotate_left(n);
}

void large_rotate_right(node*& n)
{
	small_rotate_left(n->left);
	small_rotate_right(n);
}

bool balance(node*& n)
{
	auto ll = get_level(n->left);
	auto rl = get_level(n->right);
	if (abs(ll - rl) >= 2) { // требуется балансировка
		if (ll > rl) { // правый поворот
			auto lll = get_level(n->left->left);
			auto lrl = get_level(n->left->right);
			if (lll >= lrl) small_rotate_right(n);
			else large_rotate_right(n);
		}
		else { // левый поворот
			auto rll = get_level(n->right->left);
			auto rrl = get_level(n->right->right);
			if (rrl >= rll) small_rotate_left(n);
			else large_rotate_left(n);
		}
		return true;
	}
	return false;
}

void balance_stack(node*& root, stack<node*> stack) {
	//Обновление структуры дерева вверх по стеку
	while (stack.size() > 0) {
		auto result = stack.top();
		auto balanced = balance(result);
		result->level = get_level(result);
		stack.pop();
		if (balanced) {
			if (stack.size() == 0) {
				root = result;
			}
			else {
				if (stack.top()->value > result->value) {
					stack.top()->left = result;
				}
				else {
					stack.top()->right = result;
				}
			}
		}
	}
}