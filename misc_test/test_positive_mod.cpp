#include <cassert>
#include <vector>
#include <iostream>
using namespace std;
#include "positive_mod.hpp"

int main(int argc, char** argv) {
	assert(positive_mod(7, 3) == 1);
	assert(positive_mod(-7, 3) == 2);
	assert(positive_mod(3, 7) == 3);
	assert(positive_mod(-3, 7) == 4);


	vector<double> numer {-5.0, -3.0, -1.0, 1.0, 3.0, 5.0};
	vector<int> q;
	vector<double> r(positive_mod(numer, 1.5, q));

	for (int (i); i < numer.size(); ++i) {
		assert(r[i] >= 0.0);
		assert(numer[i] == q[i] * 1.5 + r[i]);
	}

	vector<double> denum {1.5, 2.5, 0.7, 3.9, 2.1, 3.3};
	r = positive_mod(numer, denum, q);

	for (int (i); i < numer.size(); ++i) {
		assert(r[i] >= 0.0);
		assert(numer[i] == q[i] * denum[i] + r[i]);
	}

	return 0;
}
