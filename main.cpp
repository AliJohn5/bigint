#include "bigdata.hpp"
int main()
{
#ifdef TESTS_BIGINT
    BigIntTester judegInt;
    //judegInt.run_all_tests(1000);
#endif

#ifdef TESTS_BIGDBL
    BigDblTester judegDbl;
    judegDbl.run_all_tests(1000);
#endif
}