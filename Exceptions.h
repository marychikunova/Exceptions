#include <iostream>
#include <fstream>
#include <string>

#define FTHROW(err_code, str)\
	throw new my_exception (__FILE__, __LINE__, err_code, str, nullptr);

#define THROW(err_code, str, ptr)\
	throw new my_exception (__FILE__, __LINE__, err_code, str, ptr);

std::fstream log ("log.txt");

enum Error {
	SEGMENTATION_FAULT,
	MEMORY_ERROR,
	TIME_LIMIT,
	FILE_OPEN_ERROR,
	NO_ERROR,
};

class my_exception {
	private:
		std::string file;
		int line;

		Error err_code;
		std::string str;
		my_exception *old;

	public:
		my_exception () {};
		my_exception (std::string f, int l, Error e, std::string s, my_exception *o) {
			file = f;
			line = l;
			err_code = e;
			str = s;
			old = o;
		}

		void what ();
		void free_list ();
};

void my_exception::what () {
	log << "Exception caught:\n";
	log << "file\t[" << file << "]\n";
	log << "line\t[" << line << "]\n";
	log << "error code \t[" << err_code << "]\n";
	log << "Additional info: " << str << "\n";

	if (old) {
		log << "Previous exception:\n\n";
		old->what ();
	}
	else
		log.close ();
}

void my_exception::free_list () {
	if (old)
		old->free_list ();

	delete this;
}
