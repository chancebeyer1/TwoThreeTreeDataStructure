#pragma once
#include "TwoTreeNodes.h"
#include <vector>

template<typename K, typename V>
class TwoThreeTree
{
public:
	TwoThreeNode<K, V>* root;

	TwoThreeTree()
	{
		this->root = nullptr;
	}

	//TwoThreeNode<K, V>* find(K key)
	//{
	//	if (this->root == nullptr)
	//	{
	//		return nullptr;
	//	}
	//	else
	//	{
	//		return findR(this->root, key);
	//	}
	//}

	//TwoThreeNode<K, V>* findR(TwoThreeNode<K, V>* N, K key)
	//{
	//	if (N == nullptr) return nullptr;
	//	// Two-Node
	//	for (int i = 0; i < N->keys.size(); i++)
	//	{
	//		if (N->keys[i] == key)
	//		{
	//			return N;
	//		}
	//	}
	//	int size = N->keys.size();
	//	if (size == 1)
	//	{
	//		if (key < N->keys[0])
	//		{
	//			findR(N->pointers[0], key);
	//		}
	//		else
	//		{
	//			if (key > N->keys[0])
	//			{
	//				findR(N->pointers[1], key);
	//			}
	//		}
	//	}
	//	// Three-Node
	//	else if (size == 2)
	//	{
	//		if (key < N->keys[0])
	//		{
	//			findR(N->pointers[0], key);
	//		}
	//		else
	//		{
	//			if (key > N->keys[1])
	//			{
	//				findR(N->pointers[2], key);
	//			}
	//			// N->keys[0] < key < N->keys[1]
	//			else
	//			{
	//				findR(N->pointers[1], key);
	//			}
	//		}
	//	}
	//}


	//V get(K key)
	//{
	//	TwoThreeNode<K, V>* node = find(key);
	//	int size = node->keys.size();
	//	if (size == 1)
	//	{
	//		return node->values[0];
	//	}
	//	else
	//	{
	//		if (node->keys[0] == key)
	//		{
	//			return node->values[0];
	//		}
	//		else
	//		{
	//			return node->values[1];
	//		}
	//	}
	//}

	bool get(K key, V* value)
	{
		bool b = getR(this->root, key, value);
		if (b)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool getR(TwoThreeNode<K, V>* node, K key, V* value)
	{
		int* i = nullptr;
		bool b = node->findIn(key, i);
		if (b)
		{
			value = new V(node->values->at((int) i));
			return true;
		}
		else
		{
			if (node->pointers->at((int) i) != nullptr)
			{
				bool r = getR(node->pointers->at((int) i), key, value);
			}
			else
			{
				return false;
			}
		}
	}

	void put(K key, V value)
	{
		if (this->root == nullptr)
		{
			this->root = new TwoThreeNode<K, V>(key, value);
			return;
		}
		else
		{
			putR(this->root, key, value);
		}
	}

	void putR(TwoThreeNode<K, V>* node, K key, V value)
	{
		int* i = nullptr;
		bool f = node->findIn(key, i);
		if (f)
		{
			node->values->at((int) i) = value;
			return;
		}
		else
		{
			if (node->pointers->at((int) i) != nullptr)
			{
				putR(node->pointers->at((int) i), key, value);
				if (node->pointers->at((int) i)->isFourNode())
				{
					this->split(node, (int) i);
				}
			}
			else
			{
				node->add(key, value);
				if (node == this->root && node->isFourNode())
				{
					this->split(node, (int) i);
				}
			}
		}
	}

private:

	void split(TwoThreeNode<K, V>* parent, int i)
	{
		if (parent == this->root && parent->isFourNode())
		{
			TwoThreeNode<K, V>* newRoot = new TwoThreeNode<K, V>(parent->keys->at(1), parent->values->at(1));
			TwoThreeNode<K, V>* leftChild = new TwoThreeNode<K, V>(parent->keys->at(0), parent->values->at(0));
			TwoThreeNode<K, V>* rightChild = new TwoThreeNode<K, V>(parent->keys->at(2), parent->values->at(2));
			newRoot->pointers->at(0) = leftChild;
			newRoot->pointers->at(1) = rightChild;
			this->root = newRoot;
		}
		else
		{
			TwoThreeNode<K, V>* toBeSplit = parent->pointers->at(i);
			K middleKey = toBeSplit->keys->at(1);
			V middleValue = toBeSplit->values->at(1);
			parent->add(middleKey, middleValue);
			TwoThreeNode<K, V>* leftChild = new TwoThreeNode<K, V>(toBeSplit->keys->at(0), toBeSplit->values->at(0));
			TwoThreeNode<K, V>* rightChild = new TwoThreeNode<K, V>(toBeSplit->keys->at(2), toBeSplit->values->at(2));
			leftChild->pointers->at(0) = toBeSplit->pointers->at(0);
			leftChild->pointers->at(1) = toBeSplit->pointers->at(1);
			rightChild->pointers->at(0) = toBeSplit->pointers->at(2);
			rightChild->pointers->at(1) = toBeSplit->pointers->at(3);
			if (parent->isThreeNode())
			{
				if (i == 0)
				{
					parent->pointers->at(0) = leftChild;
					parent->pointers->at(1) = rightChild;
				}
				else
				{
					parent->pointers->at(1) = leftChild;
					parent->pointers->at(2) = rightChild;
				}
			}
			else // parent is fourNode
			{
				if (i == 0)
				{
					parent->pointers->at(0) = leftChild;
					parent->pointers->at(1) = rightChild;
				}
				else if (i == 1)
				{
					parent->pointers->at(1) = leftChild;
					parent->pointers->at(2) = rightChild;
				}
				else // i == 2
				{
					parent->pointers->at(2) = leftChild;
					parent->pointers->at(3) = rightChild;
				}
			}
		}
	}

	//for (int i = 0; i < node->keys.size(); i++)
	//{
	//	if (node->keys[i] == key)
	//	{
	//		node->values[i] = value;
	//		return nullptr;
	//	}
	//}
	//int size = node->keys.size();
	//// TWO NODE
	//if (size == 1)
	//{
	//	if (key < node->keys[0])
	//	{
	//		if (node->pointers[0] == nullptr)
	//		{
	//			node->addFront(key, value);
	//			return nullptr;
	//		}
	//		else
	//		{
	//			TwoThreeNode<K, V>* N = putR(node->pointers[0], key, value);
	//			if (N != nullptr)
	//			{
	//				split(N)
	//			}
	//		}
	//	}
	//	else // key > node->keys[0]
	//	{
	//		if (node->pointers[1] == nullptr)
	//		{
	//			node->addBack(key, value);
	//			return nullptr;
	//		}
	//		else
	//		{
	//			TwoThreeNode<K, V>* N = putR(node->pointers[1], key, value);
	//		}
	//	}
	//}
	//// THREE NODE
	//else
	//{
	//	if (key < node->keys[0])
	//	{
	//		if (node->pointers[0] == nullptr)
	//		{
	//			return node;
	//		}
	//		else
	//		{
	//			TwoThreeNode<K, V>* N = putR(node->pointers[0], key, value);

	//		}
	//	}
	//}

};