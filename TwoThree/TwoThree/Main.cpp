#include "TwoThreeTree.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv) {

	TwoThreeTree<int, double>* t = new TwoThreeTree<int, double>();
	t->put(1, 1.1);
	t->put(2, 2.2);
	t->put(3, 3.3);
	t->put(4, 4.4);
	t->put(5, 5.5);
	t->put(6, 6.6);
	t->put(7, 7.7);

	double* value = nullptr;
	bool g = t->get(4, value);

	std::cout << t->root->values->at(0) << "\n";
	std::cout << t->root->keys->at(0) << "\n";
	std::cout << value << "\n";

}