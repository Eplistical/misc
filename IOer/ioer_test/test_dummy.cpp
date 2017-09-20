#include <limits>
#include <cstddef>
#include <iostream>
#include <string>
#include <complex>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include "ioer.hpp"

using namespace std;
using namespace ioer;

int main(int argc, char** argv){
	output_t F1("1.txt", ios::out);
	cout << sizeof(int) << endl;
	complex<int> a(100, 200);
	F1.write(a);
	F1.close();
}
