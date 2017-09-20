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
	output_t out(".formatted_input.in", ios::out);
    out.info("HarryPotter                     # name");
    out.info("180                             # height");
    out.info("72.4                            # weight");
    out.info("20                              # age");
    out.info("3e-9                            # random_number");
    out.close();

	input_t inp(".formatted_input.in", ios::in);
    inp.read_text();

    string name;
    int age;
    double h, w, randnum;
    inp.extract_para("name", name);
    inp.extract_para("age", age);
    inp.extract_para("height", h);
    inp.extract_para("weight", w);
    inp.extract_para("random_number", randnum);

    keyval()
        ("name", name)
        ("age", age)
        ("height", h)
        ("weight", w)
        ("random_number", randnum)
        ;

    inp.close();
}
