#include "bigint.hpp"
int main()
{
#ifdef TESTS_BIGINT
    BigIntTester judeg;
    judeg.run_all_tests(1000);
#endif
}