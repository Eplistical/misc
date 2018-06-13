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
	h5file_t h5f("1.hdf5", ios::out);
	vector<double> v {1,2,3,4,5};
	vector<int> w {6,7,8,9,10};
	h5f.create_dataset("testd", v);
	h5f.create_dataset("testi", w);

	h5f.create_attr("testd", "das1", 1);
	h5f.create_attr("testd", "das2", 2.5);
	h5f.create_attr("testd", "das3", "kasdfhs");
	h5f.create_attr("testd", "das4", 'c');

	h5f.close();

	h5file_t h5g("1.hdf5", ios::in);
	vector<double> vr;
	vector<int> wr;
	h5g.read_dataset("testd", vr);
	h5g.read_dataset("testi", wr);
	int das1;
	double das2;
	string das3;
	char das4;
	h5g.read_attr("testd", "das1", das1);
	h5g.read_attr("testd", "das2", das2);
	h5g.read_attr("testd", "das3", das3);
	h5g.read_attr("testd", "das4", das4);
	info(vr);
	info(wr);
	info(das1);
	info(das2);
	info(das3);
	info(das4);

	return 0;
}
