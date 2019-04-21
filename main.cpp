#include <iostream>
#include "exceptions.h"

void f1 ();
void f2 ();
void f3 ();

int main () {
	try {
		std::cout << "try f1 ()\n";
		f1 ();
	}
	catch (my_exception* ex) {
		ex->what ();
		ex->free_list ();
	}
	return 0;
}

void f1 () {
	try {
		std::cout << "try f2 ()\n";
		f2 ();
	}
	catch (my_exception* ex) {
		THROW (FILE_OPEN_ERROR, "Can't open file", ex);
	}
}

void f2 () {
	try {
		std::cout << "try f3 ()\n";
		f3 ();
	}
	catch (my_exception* ex) {
		THROW (SEGMENTATION_FAULT, "ops", ex);
	}
}

void f3 () {
	FTHROW (TIME_LIMIT, "hurry up!");
}

