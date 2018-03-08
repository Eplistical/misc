#include <cassert>
#include "sgn.hpp"

int main(int argc, char** argv) {
	for (int i(-10000); i < 10000; i += 1) {
		if (i == 0) assert(sgn(i) == 0);
		else if (i > 0) assert(sgn(i) == 1);
		else assert(sgn(i) ==-1);
	}

	for (double i(-100); i < 100; i += 0.01) {
		if (i == 0.0) assert(sgn(i) == 0);
		else if (i > 0.0) assert(sgn(i) == 1);
		else assert(sgn(i) ==-1);
	}

	return 0;
}
