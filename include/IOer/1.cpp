#include <vector>
#include <iostream>
#include "ioer.hpp"

using namespace std;

vector<double>& operator+=(vector<double>& v, int k) {
	for (double& vi : v) {
		vi += k;
	}
	return v;
}

int main(int argc, char** argv) {

	vector<double> v {1,2,3,4,5};
	ioer::info(v);
	v += 2;
	ioer::info(v);

    ioer::output_t xx("xx");
    xx.info(123);
    xx.info(198327);
    xx.newline();
    xx << "slfjslfdsjld" << "slfkj" << std::endl;

	return 0;
}
