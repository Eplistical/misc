/**
 * This is an example to show features of ioer::output_t class
 *
 */

#include <string>
#include <vector>
#include <complex>
#include <deque>
#include "ioer.hpp"
using namespace std;

int main(int argc, char** argv) 
{
	// constructors
	ioer::output_t F1("F1.out");
	ioer::output_t F2;

	// open
	F2.open("F2.dat");

	double d = 0.02;
	int i = 5;
	string s("Hello, world");
	vector<double> v {4, 5, 8.9, 2.3};
	complex<int> c(4, 9);
	deque<float> q {3.2, 8.6, 0.2};

	// formatted output
	ioer::info(d, " - ", i, " - ", s, " - ", v, " - ", c, " - ", q, " --end");		// to screen
	F1.info(d, i, s, v, c, q, "a random string");	// to file

	// formatted table output
	ioer::tabout(d, i, s, "a random string");		// to screen
	F1.tabout_nonewline(v, c, q);					// to file

	// binary file output
	F2.write(d, i, s, v, c, q, "a random string");	// to file only

	// key-value pair output
	F1.set_dlm(":"); 	// delimiter
	F1.keyval() 		// output_t.keyval(bool _keyfirst = true, bool _nonewline = false)
		("double", d)
		("int", i)
		("string", s)
		("vector", v)
		("complex", c)
		("deque", q)
		;

	// manullay close file. 
	F2.close();
	// otherwise will be closed automatically later
	
	return 0;
}
