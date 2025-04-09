
#ifndef HARDworKING
#define HARDworKING
#include <string>
class Error {
public:
	virtual std::string what() const {
		return std::string("Unknown error");
	}
};

class ErrorUnknownOperation : public Error {
	std::string funname;
public:
	ErrorUnknownOperation(const char* s) : funname(s) {}
	ErrorUnknownOperation(char s) : funname(1, s) {}
	std::string what() const {
		return std::string("Unknown Operation name: ")
			+ funname;
	}
};

class ErrorBracketsClose : public Error {
	std::string str;
	int index;
public:
	ErrorBracketsClose(const char* s, int position) :
		str(s), index(position) {}

	std::string what() const {
		return std::string("Error with brackets. There are no ( for ) in '")
			+ str
			+ std::string("' at position ")
			+ std::to_string(index + 1);
	}
};

class ErrorBracketsOpen : public Error {
	std::string str;
	int index;
public:
	ErrorBracketsOpen(const char* s, int position) :
		str(s), index(position) {}

	std::string what() const {
		return std::string("Error with brackets. There are no ) for ( in '")
			+ str
			+ std::string("' at position ")
			+ std::to_string(index + 1);
	}
};

class ErrorPostfix : public Error {
	std::string str;
	int index;
public:
	ErrorPostfix(const char* s, int position) :
		str(s), index(position) {}

	std::string what() const {
		return std::string("Error in postfix string '")
			+ str
			+ std::string("' at position ")
			+ std::to_string(index + 1);
	}
};

class ErrorNumber : public Error {
	std::string str;
	int index;
public:
	ErrorNumber(const char* s, int position) :
		str(s), index(position) {}

	std::string what() const {
		return std::string("No number after value: ")
			+ str
			+ std::string("' at position ")
			+ std::to_string(index + 1);
	}
};
#endif // HARDworKING
