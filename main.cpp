#include "bigint.hpp"
int main()
{
#ifdef TESTS_BIGINT
    BigIntTester::run_all_tests();
#endif
    BigInt a("123456789");
    BigInt b("987654321");
    std::cout << "Product: " << a * b << "\n"; // 121932631112635269

    BigInt c(100);
    c /= 3;
    std::cout << "Division: " << c << "\n"; // 33

    BigInt d = BigInt(17) % BigInt(5);
    std::cout << "Modulo: " << d << "\n"; // 2

}