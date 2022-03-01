#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<class T>
class Test {
private:
	T obj;
public:
	Test(T obj) : obj(obj) {}
	
	bool operator<(const Test& other) { return obj < other.obj; }

	string asString() { return to_string(obj); }
};


int main() {

	Test<string> test1("c");
	Test<string> test2("b");

	if (test1 < test2)
		cout << "test1 is less" << endl;

	return 0;
}
