#include "bigdata.hpp"

int main()
{
    BigInt2 nn = "2";
    unsigned int nn2 = 77232917;
    std::cout << "##########1\n";

    BigInt2 nn3 = nn ^ nn2;

    std::cout << "##########2\n";

    std::cout
        << nn3 << '\n';
    return 0;
    //! 0) tests:

    // BigInt a("2"), b("100000");
    // std::cout << (a ^ b) << '\n';
    // exit(-1);

    /*
        if you don't want tests, comment this two lines
        from "bigdata.hpp":

            #define TESTS_BIGINT -> //#define TESTS_BIGINT
            #define TESTS_BIGDBL -> //#define TESTS_BIGDBL

        and comment j1, j2 from this code:

        BigIntTester j1;        ->  //BigIntTester j1;
        BigDblTester j2;        ->  //BigDblTester j2;
        srand(time(0));         ->  //srand(time(0));
        j1.run_all_tests(1000); ->  //j1.run_all_tests(1000);
        j2.run_all_tests(1000); ->  //j2.run_all_tests(1000);
    */
    BigIntTester j1;
    BigDblTester j2;
    srand(time(0));
    j1.run_all_tests(10000);
    j2.run_all_tests(10000);

    //! 1) BigInt
    BigInt a_int = "102315613215465413545313415313513";
    BigInt b_int = "1231534310215123154654654354153453435";
    BigInt c_int;

    std::cout << "enter first Big int number: ";
    std::cin >> a_int;

    std::cout << "enter second Big int number: ";
    std::cin >> b_int;
    std::cout << '\n';

    // a + b
    std::cout << "int a + b = ";
    c_int = a_int + b_int;
    std::cout << c_int << '\n';
    std::cout << '\n';

    // a - b
    std::cout << "int a - b = ";
    c_int = a_int - b_int;
    std::cout << c_int << '\n';
    std::cout << '\n';

    // a * b
    std::cout << "int a * b = ";
    c_int = a_int * b_int;
    std::cout << c_int << '\n';
    std::cout << '\n';

    // a / b
    std::cout << "int a / b = ";
    std::cout << a_int / b_int << '\n';
    std::cout << '\n';

    // a % b
    std::cout << "int a % b = ";
    c_int = a_int % b_int;
    std::cout << c_int << '\n';
    std::cout << '\n';

    // a ^ b = pow(a,b)
    std::cout << "int a ^ b = ";
    c_int = a_int ^ b_int;
    std::cout << c_int << '\n';
    std::cout << '\n';

    //! 2) BigDbl
    BigDbl a_dbl = "102315613215465.413545313415313513";
    BigDbl b_dbl = "123153431021.5123154654654354153453435";
    BigDbl c_dbl;

    std::cout << "enter first Big double number: ";
    std::cin >> a_dbl;

    std::cout << "enter second Big double number: ";
    std::cin >> b_dbl;
    std::cout << '\n';

    // a + b
    std::cout << "double a + b = ";
    c_dbl = a_dbl + b_dbl;
    std::cout << c_dbl << '\n';
    std::cout << '\n';

    // a - b
    std::cout << "double a - b = ";
    c_dbl = a_dbl - b_dbl;
    std::cout << c_dbl << '\n';
    std::cout << '\n';

    // a * b
    std::cout << "double a * b = ";
    c_dbl = a_dbl * b_dbl;
    std::cout << c_dbl << '\n';
    std::cout << '\n';

    // a / b
    std::cout << "double a / b = ";
    std::cout << a_dbl / b_dbl << '\n';
    std::cout << '\n';

    return 0;
}