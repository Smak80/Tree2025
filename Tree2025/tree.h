#include <queue>
using namespace std;

enum bypass_type{ prefix, infix, postfix, wide };

#pragma once
struct node {
	int value; // Хранимое значение
	int count = 1; // Количество одинаковых значений
	int level = 0; // Макс. высота поддеревьев + 1
	node* left = nullptr;  // указатель на левое поддерево
	node* right = nullptr; // указатель на правое поддерево
};

struct tree {
	node* root = nullptr; // указатель на корень дерева
	int height = 0; // высота дерева
	int count = 0;  // счётчик узлов
};

/// <summary>
/// Добавление элемента в дерево
/// </summary>
/// <param name="t">Дерево, в которое нужно добавить новое значени</param>
/// <param name="value">Значение, добавляемое в дерево</param>
/// <returns>true, если в дерево добавлен новый узел и false, если увеличен счетчик
/// одинаковых элементов в одном из существующих узлов
/// </returns>
bool add_to_tree(tree& t, int value);

/// <summary>
/// Поиск значения в дереве
/// </summary>
/// <param name="t">Дерево, в котором осуществляется поиск значения</param>
/// <param name="value">Искомое значение</param>
/// <returns>Указатель на узел дерева с соответствующим значением, 
/// если оно найдено в дереве и nullptr - в противном случае</returns>
node* find_in_tree(tree& t, int value);

/// <summary>
/// Удаление узла с заданным значением из дерева
/// </summary>
/// <param name="t">Дерево, из которого требуется удалить значение</param>
/// <param name="value">Удаляемое из дерева значение</param>
/// <returns>true, если значение было удалено и false, если значения в дереве не было</returns>
bool remove_from_tree(tree& t, int value);

/// <summary>
/// Удаление всего дерева из памяти
/// </summary>
/// <param name="t">Дерево, которое требуется удалить</param>
void drop_tree(tree& t);

/// <summary>
/// Обход узлов дерева различными способами
/// </summary>
/// <param name="t">дерево, которое нужно обойти</param>
/// <param name="type">тип обхода</param>
/// <returns>очередь, содержащая последовательность вершин дерева</returns>
queue<node*> bypass(tree t, bypass_type type = prefix);
