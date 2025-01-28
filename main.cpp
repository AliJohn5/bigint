#include "bigint.hpp"

int main()
{

    digit dig = 2;
    dig = dig * 3;
    std::cout << dig << '\n';

#ifdef TESTS_BIGINT
    BigInt test;
    test.testProduct(100000);
    test.testSum(100000);
    test.testSum2(100000);
    test.testMinus(100000);
    test.testDivideBy2(100000);
    test.testDivide(100000);
    test.testMod(100000);

#endif

    BigInt a = 1000000;
    std::cout << a << '\n';

    a = "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    for (size_t i = 0; i < 1000; i++)
    {
        a.num += '0';
    }

    std::cout << a << '\n';
    BigInt v = "999999999999999999999999999999999999999999999999999999999999";
    for (size_t i = 0; i < 1000; i++)
    {
        v.num += '0';
    }
    BigInt res = a * v;
    // freopen("out.txt","w",stdout);
    std::cout << res << std::endl;
    return 0;

    // ERROR: a = 1000000000000000000000000000000000000000;

    BigInt b = a * a;
    std::cout << b << '\n';

    std::cout << "Enter BigInt: ";
    std::cin >> b;
    std::cout << b << '\n';
    std::cout << "isOdd: " << b.isOdd() << '\n';

    a = "0";
    b = "1";
    BigInt c = a * b;
    if (c == 0)
        std::cout << c << '\n';
    else
    {
        std::cout << "ERROR in zero" << '\n';
        exit(-1);
    }

    std::cout << "every thing is OK" << '\n';

    return 0;
}

/*
1231
1233-
-------


*/