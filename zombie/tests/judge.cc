// #include "testlib.h"
#include "validate.h"
#include <cmath>

using namespace std;

constexpr double EPS = 1e-7;

bool doubleCompare(double expected, double result, double eps) {
    if (abs(expected - result) < eps) return true;
    double minv = min(expected * (1.0 - eps),
                                expected * (1.0 + eps));
    double maxv = max(expected * (1.0 - eps),
                                expected * (1.0 + eps));
    return result >= minv && result <= maxv;
}

int main(int argc, char * argv[])
{
    cerr << "initing io" << endl;
    init_io(argc, argv);
    cerr << "inited io" << endl;

    int n = 0;
    double j = 0, p = 0;

    while (judge_ans >> j)
    {
        n++;
        cerr << n << endl;
        if (author_out >> p, author_out.fail())
        {
            wrong_answer("invalid value in n=%d", n);
        }

        if (!doubleCompare(j, p, EPS))
        {            
            wrong_answer("n=%d, expected: '%.7f', found: '%.7f', error = '%.7f'",
                n, j, p, abs(j - p));
        }
    }

    if (n == 1)
        judge_message("found '%.7f', expected '%.7f', error '%.7f'", p, j, abs(j - p));

    accept();
}
