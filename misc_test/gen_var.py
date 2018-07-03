from hashlib import md5

def hs(s):
    m = md5()
    m.update(s.encode())
    return m.hexdigest()

Ts = (
        "char",
        "int",
        "float",
        "uint64_t",
        "double",
        "long",
        )

Cs = (
        "vector",
        "forward_list",
        "list",
        "deque",
        "vector",
        )

txt = ""
aaa = ""
bbb = ""

for T in Ts:
    txt += """
    %s _%s = numeric_limits<%s>::max();
"""[1:] % (T, hs(T), T)

    aaa += """
    _%s,
"""[1:] % (hs(T))
    
    bbb += """
    ("_%s", _%s)
"""[1:] % (hs(T), hs(T))


for i, C in enumerate(Cs):
    txt += """
    %s<%s> _%s = {numeric_limits<%s>::max(), numeric_limits<%s>::min(), (numeric_limits<%s>::max(), numeric_limits<%s>::min()) / 2};
"""[1:] % (C, Ts[i], hs(C+Ts[i]), Ts[i], Ts[i], Ts[i], Ts[i])

    aaa += """
    _%s,
"""[1:] % (hs(Ts[i]))

    bbb += """
    ("_%s", _%s)
"""[1:] % (hs(T), hs(T))


txt += """
    string _str = "string";
    complex<double> _cplx(1.0, 4.0);
"""[1:]

aaa += """
    _str,
    _cplx
"""[1:]

bbb += """
    ("_str", _str)
    ("_cplx", _cplx)
"""[1:]



content1 = """
#include <limits>
#include <cstddef>
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
    output_t STDOUT;
    output_t F1("1.txt", ios::out);
    output_t F2("2.txt", ios::out);

%s

    STDOUT.info(
%s
    );

    F1.info(
%s
    );

    F2.tabout(
%s
    );

    F2.close();
    return 0;
}
"""[1:] % (txt, aaa, aaa, aaa, )



content2 = """
#include <limits>
#include <cstddef>
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
    output_t STDOUT;
    output_t F1("1.txt", ios::out);
    output_t F2("2.txt", ios::out);
    output_t F3("2.txt", ios::out);

%s

    STDOUT.keyval(false, false)
%s
    ;

    F1.keyval(false, true)
%s
    ;

    F2.keyval(true, false)
%s
    ;

    F3.keyval(true, true)
%s
    ;

    F2.close();
    return 0;
}
"""[1:] % (txt, bbb, bbb, bbb, bbb, )

print(content2)
