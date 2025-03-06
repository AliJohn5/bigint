#ifndef BIGDATA_ALI
#define BIGDATA_ALI
#define TESTS_BIGINT
#define TESTS_BIGDBL
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cstdint>
#include <cassert>
#include <complex>
#include <cmath>

#define alid(a) std::cout << a << '\n'

/*

4564564
454654
456545645

*/
class BigInt
{

    void remove_first_chars(std::string &s, char c)
    {

        int i = 0;
        if (s.empty())
        {
            s = "0";
            return;
        }

        if (s[i] != c)
            return;

        while (i < s.length())
        {
            if (s[i] != c)
                break;
            ++i;
        }
        s.erase(s.begin(), s.begin() + i);
        if (s.empty())
        {
            s = "0";
        }
    }

    std::string __product(const std::string &a, const std::string &b)
    {
        // return fastAdd(a, b);

        std::string res(a.size() + b.size(), '0');

        int carry = 0;

        int ires = res.size() - 1, ia = a.size() - 1, ib = b.size() - 1;
        int resInt;

        while (
            ib >= 0)
        {
            ires = res.size() - (b.size() - ib);
            // res.size()-1
            ia = a.size() - 1;
            carry = 0;

            while (ia >= 0)
            {
                resInt =
                    (a[ia] - '0') *
                        (b[ib] - '0') +
                    carry +
                    (res[ires] - '0');
                // cout << b.inversed_number[ib] << endl;

                carry = resInt / 10;
                res[ires] = resInt % 10 + '0';
                --ia;
                --ires;
            }
            res[ires] = carry + '0';

            --ib;
        }

        remove_first_chars(res, '0');

        return res;
    }

    std::string __fast_product(const std::string &a, const std::string &b)
    {
        std::vector<std::string> dp(10);
        std::string tempString;
        dp[0] = "0";
        dp[1] = b;

        for (int i = 2; i <= 9; ++i)
        {
            tempString = std::to_string(i);
            dp[i] = __product(tempString, b);
        }

        std::string res(a.size() + b.size() + 1, '0');
        std::string carry = "0";
        long long ires = res.size() - 1;

        for (long long i = a.size() - 1; i >= 0; --i)
        {

            carry = __sum(dp[a[i] - '0'], carry);
            res[ires] = carry[carry.size() - 1];
            if (carry != "0")
            {
                carry.erase(carry.end() - 1);
            }
            --ires;
        }
        for (long long i = carry.size() - 1; i >= 0; --i)
        {
            res[ires] = carry[i];
            --ires;
        }

        remove_first_chars(res, '0');

        return res;
    }

    std::string __sum(const std::string &a, const std::string &b)
    {
        std::string res(std::max(a.length(), b.length()) + 1, '0');
        int carry = 0, ia = a.length() - 1, ib = b.length() - 1, sum = 0, ires = res.length() - 1;

        while (ires >= 0)
        {
            if (ia < 0 && ib >= 0)
            {
                sum = b[ib] + carry - '0';
                res[ires] = (sum % 10) + '0';
                carry = sum / 10;
                --ib;
                --ires;
            }
            else if (ib < 0 && ia >= 0)
            {
                sum = a[ia] + carry - '0';
                res[ires] = (sum % 10) + '0';
                carry = sum / 10;
                --ia;
                --ires;
            }
            else if (ib >= 0 && ia >= 0)
            {
                sum = carry + b[ib] - '0' + a[ia] - '0';
                carry = sum / 10;
                res[ires] = (sum % 10) + '0';
                --ires;
                --ia;
                --ib;
            }
            else
            {
                res[ires] = (carry % 10) + '0';
                carry /= 10;
                --ires;
            }
        }

        remove_first_chars(res, '0');

        return res;
    }

    std::string __minus(const std::string &a, const std::string &b)
    {
        std::string res(std::max(a.length(), b.length()) + 1, '0');
        int carry = 0, ia = a.length() - 1, ib = b.length() - 1, sum = 0, ires = res.length() - 1;
        std::string aa = a;

        while (ires >= 0)
        {
            if (ib < 0 && ia >= 0)
            {
                res[ires] = aa[ia];
                --ia;
                --ires;
            }

            else if (ib >= 0 && ia >= 0)
            {
                if (aa[ia] < b[ib])
                {
                    int ic = ia - 1;

                    // find first num > 0
                    while (ic >= 0)
                    {
                        if (aa[ic] > '0')
                        {
                            --aa[ic];
                            break;
                        }
                        else
                        {
                            aa[ic] = '9';
                        }
                        --ic;
                    }

                    res[ires] = aa[ia] + 10 - b[ib] + '0';
                }

                else
                {
                    res[ires] = aa[ia] - b[ib] + '0';
                }

                --ires;
                --ia;
                --ib;
            }

            else
            {
                res[ires] = '0';
                --ires;
            }
        }

        remove_first_chars(res, '0');

        return res;
    }

    std::string __divide_string_by_2(const std::string &s)
    {
        if (s.empty())
            return "0";

        if (s == "0")
            return "0";

        int ians = 0, is = 0, sum = 0;
        bool carry = 0;
        std::string ans(s.length(), '*');

        while (is < s.length())
        {
            sum = carry * 10 + (s[is] - '0');
            if (sum & 1)
            {
                carry = 1;
            }
            else
            {
                carry = 0;
            }

            ans[ians] = (sum / 2) + '0';
            ians++;
            ++is;
        }

        ians = ans.length() - 1;
        if (ans[ians] != '*')
            return ans;

        while (ians >= 0)
        {
            if (ians != '*')
                break;
            --ians;
        }

        if (ians < 0)
            return "0";

        ans.erase(
            ans.begin() + ians + 1,
            ans.end());

        remove_first_chars(ans, '0');

        return ans;
    }

    bool __isStringLessThanEqualString(const std::string &a, const std::string &b)
    {
        if (a.length() == b.length())
        {
            for (size_t i = 0; i < a.length(); i++)
            {
                if (a[i] > b[i])
                {
                    return false;
                }
                else if (a[i] < b[i])
                {
                    return true;
                }
            }
            return true;
        }

        return a.length() < b.length();
    }

    std::string __divide(const std::string &a, std::string &b)
    {
        remove_first_chars(b, '0');
        if (b == "0")
            throw std::invalid_argument("can't divide by zero");
        if (b == "1")
            return a;
        if (b.size() > a.size())
        {
            return "0";
        }
        if (b.size() == a.size())
        {
            bool equal = 1;
            for (int i = 0; i < a.size(); ++i)
            {

                if (b[i] > a[i])
                    return "0";
                if (b[i] < a[i])
                {
                    equal = 0;
                    break;
                }
            }

            if (equal)
                return "1";
        }

        std::string mx(a.length() - b.length() + 2, '0'),
            mn(std::max<long long>(a.length() - b.length(), 1), '0');

        mx[0] = '1';
        mn[0] = '1';

        std::string mid, mid1, prod, prod1;
        bool lessmid, lessmid1;

        while (__isStringLessThanEqualString(mn, mx))
        {

            mid = __divide_string_by_2(__sum(mx, mn));

            mid1 = __sum(mid, "1");

            prod = __product(mid, b);

            prod1 = __product(mid1, b);

            lessmid = __isStringLessThanEqualString(prod, a);

            lessmid1 = __isStringLessThanEqualString(prod1, a);

            if (lessmid && !lessmid1)
            {

                remove_first_chars(mid, '0');
                return mid;
            }

            if (lessmid && lessmid1)
            {
                mn = mid1;
            }
            else
            {
                mx = __minus(mid, "1");
            }
        }

        remove_first_chars(mid, '0');

        return mid;
    }

    std::string __mod(const std::string &a, std::string &b)
    {
        return __minus(a, __product(__divide(a, b), b));
    }

public:
    std::string num;
    bool isPositive = true;

    void to_int_and_ignore_point(std::string &s)
    {
        if (s.empty())
        {
            s = "0";
        }
        long long i = -1;
        for (long long c = 0; c < s.length(); ++c)
        {
            if (c == 0)
            {
                if (s[c] == '-')
                    continue;
                if (s[c] == '+')
                    continue;
            }
            if (s[c] == '.' && i == -1)
            {
                i = c;
                continue;
            }
            else if (s[c] < '0' || s[c] > '9')
            {
                throw std::invalid_argument("invalid digit in int");
            }
        }

        if (i != -1)
            s = s.substr(0, i);
    }

    BigInt abss()
    {
        return BigInt(num);
    }

    void append(std::string s)
    {
        num += s;
    }

    void appendR(std::string s)
    {
        num = s + num;
    }

    std::string to_string()
    {
        if (isPositive)
            return num;
        else
            return "-" + num;
    }
    BigInt(std::string s)
    {
        to_int_and_ignore_point(s);
        if (!s.empty())
        {
            if (s[0] == '-')
            {
                isPositive = 0;
                s.erase(0, 1);
                num = s;
            }
            else
                num = s;
        }

        else
        {

            isPositive = 1;
            num = "0";
        }

        if (num == "0")
            isPositive = true;
    }

    BigInt(const char *c)
    {
        std::string s = c;
        to_int_and_ignore_point(s);

        if (!s.empty())
        {
            if (s[0] == '-')
            {
                isPositive = 0;
                s.erase(0, 1);
                num = s;
            }
            else
                num = s;
        }

        else
        {
            isPositive = 1;
            num = "0";
        }

        if (num == "0")
            isPositive = true;
    }

    BigInt(long long int _n)
    {
        if (_n < 0)
        {
            isPositive = 0;
            num = std::to_string(-_n);
        }

        else
        {
            isPositive = 1;
            num = std::to_string(_n);
        }

        if (num == "0")
            isPositive = true;
    }

    BigInt(int _n)
    {
        if (_n < 0)
        {
            isPositive = 0;
            num = std::to_string(-_n);
        }

        else
        {
            isPositive = 1;
            num = std::to_string(_n);
        }
        if (num == "0")
            isPositive = true;
    }

    BigInt()
    {
    }
    std::string getNum()
    {
        return (isPositive ? num : "-" + num);
    }
    void setNum(std::string s)
    {
        to_int_and_ignore_point(s);

        if (!s.empty())
        {
            if (s[0] == '-')
            {
                isPositive = 0;
                s.erase(0, 1);
                num = s;
            }
            else
                num = s;
        }

        else
            num = s;

        if (num == "0")
            isPositive = true;
    }

    BigInt operator*(const BigInt a)
    {
        if (a.isPositive && this->isPositive)
        {
            BigInt ans(__product(this->num, a.num));
            return ans;
        }

        if (!a.isPositive && !this->isPositive)
        {
            BigInt ans(__product(this->num, a.num));

            return ans;
        }

        BigInt ans(__product(this->num, a.num));
        ans.isPositive = 0;
        return ans;
    }

    BigInt operator^(BigInt e)
    {
        if (e == 0)
        {
            return BigInt("1");
        }

        if (*this == "1")
        {
            return *this;
        }

        BigInt res = "1";
        BigInt a = *this;

        while (e > "0")
        {
            if (e.isOdd())
            {
                res = res * a;
            }
            a = a * a;
            e = e / BigInt("2");
        }

        return res;
    }

    BigInt operator^(unsigned int e)
    {
        if (e == 0)
        {
            return BigInt("1");
        }

        if (*this == "1")
        {
            return *this;
        }

        BigInt res = "1";
        BigInt a = *this;

        while (e)
        {
            // alid(e);
            if (e & 1)
            {
                res = res * a;
            }
            a = a * a;
            e >>= 1;
        }

        return res;
    }

    std::string fastAdd(std::string a, std::string b)
    {
        if (b == "0" || a == "0")
        {
            return "0";
        }
        if (a == "1")
        {
            return b;
        }
        if (b == "1")
        {
            return a;
        }

        std::string res = "0";

        while (b != "0")
        {
            if (isOddString(b))
            {
                res = __sum(res, a);
            }

            a = __sum(a, a);

            b = __divide_string_by_2(b);
            remove_first_chars(b, '0');
        }

        return res;
    }

    BigInt operator/(BigInt a)
    {

        if (a.isPositive && this->isPositive)
        {
            BigInt ans(__divide(this->num, a.num));

            return ans;
        }

        if (!a.isPositive && !this->isPositive)
        {

            BigInt ans(__divide(this->num, a.num));

            return ans;
        }

        BigInt ans(__divide(this->num, a.num));
        ans.isPositive = 0;

        return ans;
    }

    BigInt operator%(BigInt a)
    {

        if (a.isPositive && this->isPositive)
        {
            BigInt ans(__mod(this->num, a.num));
            return ans;
        }

        if (!a.isPositive && this->isPositive)
        {
            BigInt ans(__mod(this->num, a.num));
            ans.isPositive = 1;
            return ans;
        }

        BigInt ans(__mod(this->num, a.num));
        ans.isPositive = 0;
        return ans;
    }

    BigInt operator+(const BigInt a)
    {
        BigInt &d = *this;

        if (d.isPositive == a.isPositive)
        {
            if (d.isPositive)
                return BigInt(__sum(this->num, a.num));
            else
            {
                BigInt ans(__sum(a.num, this->num));
                ans.isPositive = 0;
                return ans;
            }
        }

        if (d.isPositive && !a.isPositive)
        {
            BigInt c = a;
            c.isPositive = 1;
            return d - c;
        }

        if (!d.isPositive && a.isPositive)
        {

            BigInt c = a;
            d.isPositive = true;
            return c - d;
        }
        return d;
    }

    bool operator>(const BigInt a)
    {
        if (this->isPositive && !a.isPositive)
            return true;
        if (!this->isPositive && a.isPositive)
            return false;

        if (this->isPositive && a.isPositive)
        {
            if (this->num.length() == a.num.length())
            {
                for (size_t i = 0; i < a.num.length(); i++)
                {
                    if (this->num[i] > a.num[i])
                    {
                        return true;
                    }
                    else if (this->num[i] < a.num[i])
                    {
                        return false;
                    }
                }
                return false;
            }

            return this->num.length() > a.num.length();
        }

        if (!this->isPositive && !a.isPositive)
        {
            if (this->num.length() == a.num.length())
            {
                for (size_t i = 0; i < a.num.length(); i++)
                {
                    if (this->num[i] < a.num[i])
                    {
                        return true;
                    }
                    else if (this->num[i] > a.num[i])
                    {
                        return false;
                    }
                }
                return false;
            }

            return this->num.length() < a.num.length();
        }
        return false;
    }

    bool operator<(const BigInt a)
    {
        if (this->isPositive && !a.isPositive)
            return false;
        if (!this->isPositive && a.isPositive)
            return true;

        if (this->isPositive && a.isPositive)
        {
            if (this->num.length() == a.num.length())
            {
                for (size_t i = 0; i < a.num.length(); i++)
                {
                    if (this->num[i] > a.num[i])
                    {
                        return false;
                    }
                    else if (this->num[i] < a.num[i])
                    {
                        return true;
                    }
                }
                return false;
            }

            return this->num.length() < a.num.length();
        }

        if (!this->isPositive && !a.isPositive)
        {
            if (this->num.length() == a.num.length())
            {
                for (size_t i = 0; i < a.num.length(); i++)
                {
                    if (this->num[i] < a.num[i])
                    {
                        return false;
                    }
                    else if (this->num[i] > a.num[i])
                    {
                        return true;
                    }
                }
                return false;
            }

            return this->num.length() > a.num.length();
        }
        return 0;
    }

    bool operator>=(const BigInt a)
    {
        if (this->isPositive && !a.isPositive)
            return true;
        if (!this->isPositive && a.isPositive)
            return false;

        if (this->isPositive && a.isPositive)
        {
            if (this->num.length() == a.num.length())
            {
                for (size_t i = 0; i < a.num.length(); i++)
                {
                    if (this->num[i] > a.num[i])
                    {
                        return true;
                    }
                    else if (this->num[i] < a.num[i])
                    {
                        return false;
                    }
                }
                return true;
            }

            return this->num.length() > a.num.length();
        }

        if (!this->isPositive && !a.isPositive)
        {
            if (this->num.length() == a.num.length())
            {
                for (size_t i = 0; i < a.num.length(); i++)
                {
                    if (this->num[i] < a.num[i])
                    {
                        return true;
                    }
                    else if (this->num[i] > a.num[i])
                    {
                        return false;
                    }
                }
                return true;
            }

            return this->num.length() < a.num.length();
        }
        return 0;
    }

    bool operator<=(const BigInt a)
    {
        if (this->isPositive && !a.isPositive)
            return false;
        if (!this->isPositive && a.isPositive)
            return true;

        if (this->isPositive && a.isPositive)
        {
            if (this->num.length() == a.num.length())
            {
                for (size_t i = 0; i < a.num.length(); i++)
                {
                    if (this->num[i] > a.num[i])
                    {
                        return false;
                    }
                    else if (this->num[i] < a.num[i])
                    {
                        return true;
                    }
                }
                return true;
            }

            return this->num.length() < a.num.length();
        }

        if (!this->isPositive && !a.isPositive)
        {
            if (this->num.length() == a.num.length())
            {
                for (size_t i = 0; i < a.num.length(); i++)
                {
                    if (this->num[i] < a.num[i])
                    {
                        return false;
                    }
                    else if (this->num[i] > a.num[i])
                    {
                        return true;
                    }
                }
                return true;
            }

            return this->num.length() > a.num.length();
        }
        return 0;
    }

    bool operator==(const BigInt a)
    {
        if (this->num.length() == a.num.length() && this->isPositive == a.isPositive)
        {
            for (size_t i = 0; i < a.num.length(); i++)
            {
                if (this->num[i] != a.num[i])
                {
                    return false;
                }
            }
            return true;
        }

        return false;
    }

    bool operator!=(const BigInt a)
    {
        if (this->num.length() == a.num.length() && this->isPositive == a.isPositive)
        {
            for (size_t i = 0; i < a.num.length(); i++)
            {
                if (this->num[i] != a.num[i])
                {
                    return true;
                }
            }
            return false;
        }

        return true;
    }

    friend std::ostream &operator<<(std::ostream &out, const BigInt &n)
    {
        if (n.isPositive)
            out << n.num;
        else
            out << '-' << n.num;

        return out;
    }

    friend std::istream &operator>>(std::istream &in, BigInt &n)
    {
        std::string s;
        in >> s;
        if (s == "")
            s = "0";
        n = s;
        return in;
    }

    bool isOdd()
    {
        return ((num[num.length() - 1] - '0') & 1);
    }

    bool isOddString(std::string &s)
    {
        return ((s[s.length() - 1] - '0') & 1);
    }

    BigInt operator-(const BigInt a)
    {
        BigInt &d = *this;

        if (d.isPositive && a.isPositive)
        {
            if (d >= a)
            {

                return BigInt(__minus(this->num, a.num));
            }
            else
            {

                BigInt ans(__minus(a.num, this->num));
                ans.isPositive = 0;
                return ans;
            }
        }

        if (!d.isPositive && !a.isPositive)
        {
            if (d >= a)
            {

                return BigInt(__minus(a.num, this->num));
            }
            else
            {

                BigInt ans(__minus(this->num, a.num));
                ans.isPositive = 0;
                return ans;
            }
        }

        if (d.isPositive && !a.isPositive)
        {

            return BigInt(__sum(this->num, a.num));
        }

        if (!d.isPositive && a.isPositive)
        {

            BigInt ans(__sum(a.num, this->num));
            ans.isPositive = 0;
            return ans;
        }
        return d;
    }
};
#ifdef TESTS_BIGINT
#include <chrono>
#include <time.h>
class BigIntTester
{

public:
    int test_counter = 1;

    void run_all_tests(int n)
    {
        auto start = std::chrono::high_resolution_clock::now();

        test_multiplication();

        test_division();

        test_modulo();

        test_comparisons();

        test_conversions();

        loop_test_operater(n, '+');
        loop_test_operater(n, '-');
        loop_test_operater(n, '/');
        loop_test_operater(n, '*');
        loop_test_operater(n, '%');

        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout
            << "All tests passed in " << microsec << " micro second\n";
    }

private:
    void loop_test_operater(
        int n,
        char operator__)
    {
        test_operator_with_range(
            n,
            operator__,
            0, 10000000,
            0, 10000000);
        test_operator_with_range(
            n,
            operator__,
            -10000000, 0,
            -10000000, 0);

        test_operator_with_range(
            n,
            operator__,
            -10000000, 10000000,
            -10000000, 10000000);

        test_operator_with_range(
            n,
            operator__,
            0, 10000000,
            -10000000, 0);
        test_operator_with_range(
            n,
            operator__,
            -10000000, 0,
            0, 10000000);

        test_operator_with_range_same(
            n,
            operator__,
            0, 10000000);

        test_operator_with_range_same(
            n,
            operator__,
            -10000000, 0);

        test_operator_with_range_same(
            n,
            operator__,
            -10000000, 10000000);
    }

    void test_multiplication()
    {

        assert(BigInt(123) * BigInt(2) == BigInt(246));

        assert(BigInt(-12) * BigInt(3) == BigInt(-36));

        assert(BigInt(0) * BigInt(0) == BigInt(0));

        assert(BigInt(1) * BigInt(2) == BigInt(2));

        BigInt a("123456789");
        BigInt b("987654321");
        alid((a * b));
        assert(a * b == BigInt("121932631112635269"));

        std::cout << "test [ " << test_counter << " ] ok.\n";

        ++test_counter;
    }

    void test_division()
    {

        assert(BigInt(100) / BigInt(5) == BigInt(20));
        assert(BigInt(-81) / BigInt(9) == BigInt(-9));
        assert(BigInt(0) / BigInt(1) == BigInt(0));

        bool caught = false;

        try
        {
            BigInt(5) / BigInt(0);
        }
        catch (const std::invalid_argument &)
        {
            caught = true;
        }
        assert(caught);

        std::cout << "test [ " << test_counter << " ] ok.\n";

        ++test_counter;
    }

    void test_modulo()
    {
        assert(BigInt(17) % BigInt(5) == BigInt(2));
        assert(BigInt(-17) % BigInt(5) == BigInt(-2));
        assert(BigInt(25) % BigInt(7) == BigInt(4));
        alid(BigInt(0) % BigInt(1));
        assert(BigInt(0) % BigInt(1) == BigInt(0));

        bool caught = false;
        try
        {
            BigInt(5) % BigInt(0);
        }
        catch (const std::invalid_argument &)
        {
            caught = true;
        }
        assert(caught);
        std::cout << "test [ " << test_counter << " ] ok.\n";

        ++test_counter;
    }

    void test_comparisons()
    {
        assert(BigInt(5) > BigInt(3));
        assert(BigInt(-2) <= BigInt(0));
        assert(BigInt("1000000") >= BigInt(999999));
        assert(!(BigInt(-0) < BigInt(0)));

        std::cout << "test [ " << test_counter << " ] ok.\n";
        ++test_counter;
    }

    void test_conversions()
    {
        assert(BigInt("12345") == 12345);
        assert(BigInt("-42") == -42);
        bool caught = true;
        try
        {
            BigInt("9999999999999999999");
        }
        catch (const std::overflow_error &)
        {
            caught = false;
        }
        assert(caught);

        std::cout << "test [ " << test_counter << " ] ok.\n";
        ++test_counter;
    }

    void test_operator_with_range(
        int number_of_tests,
        char operator__,
        int min_range_a,
        int max_range_a,

        int min_range_b,
        int max_range_b

    )
    {
        long long ia, ib, ic;
        BigInt bia, bib, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < number_of_tests; i++)
        {
            ia = (long long)rand() % (max_range_a - min_range_a);
            ib = (long long)rand() % (max_range_b - min_range_b);

            if (max_range_a >= 0 || min_range_a >= 0)
            {
                ia += min_range_a;
            }
            else
            {
                ia += max_range_a;
            }

            if (max_range_b >= 0 || min_range_b >= 0)
            {
                ib += min_range_b;
            }
            else
            {
                ib += max_range_b;
            }

            if (ia > max_range_a || ia < min_range_a)
            {
                throw std::invalid_argument("out of range");
            }
            if (ib > max_range_b || ib < min_range_b)
            {
                throw std::invalid_argument("out of range");
            }

            switch (operator__)
            {
            case '/':
                ib += (ib == 0);
                ic = ia / ib;
                break;
            case '*':
                ic = ia * ib;
                break;
            case '+':
                ic = ia + ib;
                break;
            case '-':
                ic = ia - ib;
                break;
            case '%':
                ib += (ib == 0);
                ic = ia % ib;
                break;

            default:
                throw std::invalid_argument("unknown operator");
                break;
            }

            bia = std::to_string(ia);
            bib = std::to_string(ib);

            switch (operator__)
            {
            case '/':

                bic = bia / bib;

                break;
            case '*':
                bic = bia * bib;
                break;
            case '+':
                bic = bia + bib;
                break;
            case '-':
                bic = bia - bib;
                break;
            case '%':
                bic = bia % bib;
                break;

            default:
                throw std::invalid_argument("unknown operator");
                break;
            }

            if (atoll(bic.to_string().c_str()) != ic)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia << ' ' << operator__ << ' ' << ib << " = " << ic << std::endl;
                std::cerr << "you get " << bia << ' ' << operator__ << ' ' << bib << " = " << bic << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "test [ " << test_counter << " ]:" << " OK passed all " << operator__ << " tests(" << number_of_tests << ") in " << microsec << " micro second.\n";

        ++test_counter;
    }

    void test_operator_with_range_same(
        int number_of_tests,
        char operator__,
        int min_range_a,
        int max_range_a

    )
    {
        long long ia, ic;
        BigInt bia, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < number_of_tests; i++)
        {
            ia = (long long)rand() % (max_range_a - min_range_a);

            if (max_range_a >= 0 || min_range_a >= 0)
            {
                ia += min_range_a;
            }
            else
            {
                ia += max_range_a;
            }

            if (ia > max_range_a || ia < min_range_a)
            {
                throw std::invalid_argument("out of range");
            }

            switch (operator__)
            {
            case '/':
                ia += (ia == 0);
                ic = ia / ia;
                break;
            case '*':
                ic = ia * ia;
                break;
            case '+':
                ic = ia + ia;
                break;
            case '-':
                ic = ia - ia;
                break;
            case '%':
                ia += (ia == 0);
                ic = ia % ia;
                break;

            default:
                throw std::invalid_argument("unknown operator");
                break;
            }

            bia = std::to_string(ia);

            switch (operator__)
            {
            case '/':

                bic = bia / bia;

                break;
            case '*':
                bic = bia * bia;
                break;
            case '+':
                bic = bia + bia;
                break;
            case '-':
                bic = bia - bia;
                break;
            case '%':
                bic = bia % bia;
                break;

            default:
                throw std::invalid_argument("unknown operator");
                break;
            }

            if (atoll(bic.to_string().c_str()) != ic)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia << ' ' << operator__ << ' ' << ia << " = " << ic << std::endl;
                std::cerr << "you get " << bia << ' ' << operator__ << ' ' << bia << " = " << bic << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "test [ " << test_counter << " ]:" << " OK passed all " << operator__ << " tests(" << number_of_tests << ") in " << microsec << " micro second.\n";
        ++test_counter;
    }
};
#endif
class BigDbl
{
public:
    long long _e = 0;
    BigInt _n;
    BigDbl abss()
    {

        std::string s = _n.num;
        if (_e > s.length())
        {
            s = std::string(_e - s.length() + 1, '0') + s;
        }

        if (_e > 0)
            s.insert(s.begin() + s.length() - _e, '.');

        return BigDbl(s);
    }
    void remove_first_chars(std::string &s, char c)
    {

        int i = 0;
        if (s.empty())
        {
            s = "0";
            return;
        }

        if (s[i] != c)
            return;

        while (i < s.length())
        {
            if (s[i] != c)
                break;
            ++i;
        }
        s.erase(s.begin(), s.begin() + i);
    }

    long long findPointOrMius1(std::string &s)
    {
        for (long long i = 0; i < s.length(); ++i)
        {
            if (s[i] == '.')
            {
                return i;
            }
        }
        return -1;
    }
    void setNumFromString(std::string &s, long long &e)
    {
        remove_first_chars(s, '0');
        long long pointIndex = findPointOrMius1(s);

        if (pointIndex != -1)
        {
            long long newE = s.length() - pointIndex - 1;
            if (e > newE)
            {
                s += std::string(e - newE, '0');
                _e = newE;
            }
            else
            {
                _e = newE;
            }

            s.erase(pointIndex, 1);
        }
        else
        {
            s += std::string(_e, '0');
        }
        _n = s;
    }

public:
    void makeTwoBigDblSameLength(BigDbl &b)
    {
        remove_first_chars(_n.num, '0');
        remove_first_chars(b._n.num, '0');

        if (_n.num.length() < b._n.num.length())
        {
            increaseE(b._e);
        }
        else if (_n.num.length() > b._n.num.length())
        {
            b.increaseE(_e);
        }
    }

    long long getE()
    {
        return _e;
    }
    long long getER()
    {
        return _n.num.size() - _e;
    }

    std::string to_string()
    {

        std::string s = _n.to_string();

        if (_e > _n.num.length())
        {
            _n.appendR(std::string(_e - _n.num.length() + 1, '0'));
        }

        if (_e > 0)
            s.insert(s.begin() + s.length() - _e, '.');
        else if (_e < 0)
        {
            _n.appendR(std::string(1 - _e, '0'));
            _e = _n.num.length() - 1;
        }
        if (!s.empty())
        {
            if (s[0] == '.')
                s = "0" + s;
        }
        else
        {
            s = "0";
        }

        return s;
    }

    void increaseE(long long e)
    {

        long long dif = abs(e - _e);
        if (_e < e)
        {
            _e = e;
            _n.append(std::string(dif, '0'));
        }
    }

    void increaseER(long long e)
    {

        long long dif = e - (_n.num.size() - _e);
        if (dif > 0)
        {
            _n.appendR(std::string(dif, '0'));
        }
    }

    BigDbl() {}
    BigDbl(BigInt n) : _n(n)
    {
    }
    BigDbl(BigInt n, long long e) : _n(n), _e(e)
    {
    }

    BigDbl(const char *s)
    {
        std::string str = s;
        setNumFromString(str, _e);
    }

    BigDbl(std::string s)
    {
        setNumFromString(s, _e);
    }

    BigDbl(long double n)
    {
        std::string str = std::to_string(n);
        setNumFromString(str, _e);
    }

    BigDbl(const char *s, long long e)
    {
        std::string str = s;
        setNumFromString(str, _e);
    }

    BigDbl(std::string s, long long e)
    {
        setNumFromString(s, _e);
    }

    BigDbl(long double n, long long e)
    {
        std::string str = std::to_string(n);
        setNumFromString(str, _e);
    }

    bool operator==(BigDbl a)
    {

        makeTwoBigDblSameLength(a);
        if (a._n.num.length() == a._e)
        {
            a._n.appendR("0");
        }

        if (_n.num.length() == _e)
        {
            _n.appendR("0");
        }

        if (a._e == _e)
            return _n == a._n;
        else
            return 0;
    }
    bool operator!=(BigDbl a)
    {

        makeTwoBigDblSameLength(a);

        if (a._e == _e)
            return _n != a._n;
        else
            return 1;
    }

    bool operator<(BigDbl a)
    {
        makeTwoBigDblSameLength(a);

        if (_n.isPositive && a._n.isPositive)
        {
            int ithis = _n.num.size() - _e;
            int ia = a._n.num.size() - a.getE();

            if (ithis == ia)
            {

                for (long long i = 0; i < _n.num.size(); ++i)
                {

                    if (_n.num[i] < a._n.num[i])
                    {
                        return true;
                    }
                    if (_n.num[i] > a._n.num[i])
                    {
                        return false;
                    }
                }
                return false;
            }

            return ithis < ia;
        }

        if (!_n.isPositive && !a._n.isPositive)
        {
            int ithis = _n.num.size() - _e;
            int ia = a._n.num.size() - a.getE();

            if (ithis == ia)
            {

                for (long long i = 0; i < _n.num.size(); ++i)
                {

                    if (_n.num[i] > a._n.num[i])
                    {
                        return true;
                    }
                    if (_n.num[i] < a._n.num[i])
                    {
                        return false;
                    }
                }
                return false;
            }

            return ithis > ia;
        }

        return !_n.isPositive;
    }

    bool operator<=(BigDbl a)
    {

        makeTwoBigDblSameLength(a);
        if (_n.isPositive && a._n.isPositive)
        {
            int ithis = _n.num.size() - _e;
            int ia = a._n.num.size() - a.getE();

            if (ithis == ia)
            {

                for (long long i = 0; i < _n.num.size(); ++i)
                {

                    if (_n.num[i] < a._n.num[i])
                    {
                        return true;
                    }
                    if (_n.num[i] > a._n.num[i])
                    {
                        return false;
                    }
                }
                return true;
            }

            return ithis < ia;
        }

        if (!_n.isPositive && !a._n.isPositive)
        {
            int ithis = _n.num.size() - _e;
            int ia = a._n.num.size() - a.getE();

            if (ithis == ia)
            {

                for (long long i = 0; i < _n.num.size(); ++i)
                {

                    if (_n.num[i] > a._n.num[i])
                    {
                        return true;
                    }
                    if (_n.num[i] < a._n.num[i])
                    {
                        return false;
                    }
                }
                return true;
            }

            return ithis > ia;
        }

        return !_n.isPositive;
    }

    bool operator>(BigDbl a)
    {

        makeTwoBigDblSameLength(a);
        if (_n.isPositive && a._n.isPositive)
        {

            int ithis = _n.num.size() - _e;
            int ia = a._n.num.size() - a.getE();

            if (ithis == ia)
            {

                for (long long i = 0; i < _n.num.size(); ++i)
                {

                    if (_n.num[i] > a._n.num[i])
                    {
                        return true;
                    }
                    if (_n.num[i] < a._n.num[i])
                    {
                        return false;
                    }
                }
                return false;
            }

            return ithis > ia;
        }

        if (!_n.isPositive && !a._n.isPositive)
        {
            int ithis = _n.num.size() - _e;
            int ia = a._n.num.size() - a.getE();

            if (ithis == ia)
            {

                for (long long i = 0; i < _n.num.size(); ++i)
                {

                    if (_n.num[i] < a._n.num[i])
                    {
                        return true;
                    }
                    if (_n.num[i] > a._n.num[i])
                    {
                        return false;
                    }
                }
                return false;
            }

            return ithis < ia;
        }

        return _n.isPositive;
    }

    bool operator>=(BigDbl a)
    {
        makeTwoBigDblSameLength(a);

        if (_n.isPositive && a._n.isPositive)
        {
            int ithis = _n.num.size() - _e;
            int ia = a._n.num.size() - a.getE();

            if (ithis == ia)
            {

                for (long long i = 0; i < _n.num.size(); ++i)
                {

                    if (_n.num[i] > a._n.num[i])
                    {
                        return true;
                    }
                    if (_n.num[i] < a._n.num[i])
                    {
                        return false;
                    }
                }
                return true;
            }

            return ithis > ia;
        }

        if (!_n.isPositive && !a._n.isPositive)
        {
            int ithis = _n.num.size() - _e;
            int ia = a._n.num.size() - a.getE();

            if (ithis == ia)
            {

                for (long long i = 0; i < _n.num.size(); ++i)
                {

                    if (_n.num[i] < a._n.num[i])
                    {
                        return true;
                    }
                    if (_n.num[i] > a._n.num[i])
                    {
                        return false;
                    }
                }
                return true;
            }

            return ithis < ia;
        }

        return _n.isPositive;
    }

    BigDbl operator+(BigDbl a)
    {
        makeTwoBigDblSameLength(a);
        BigDbl ans;
        ans._n = this->_n + a._n;
        ans._e = _e;
        return ans;
    }
    BigDbl operator-(BigDbl a)
    {
        makeTwoBigDblSameLength(a);
        BigDbl ans;
        ans._n = this->_n - a._n;
        ans._e = _e;
        if (ans._e == ans._n.num.length())
        {
            ans._n.appendR("0");
        }
        return ans;
    }
    BigDbl operator*(BigDbl a)
    {
        makeTwoBigDblSameLength(a);
        BigDbl ans;
        ans._n = this->_n * a._n;
        ans._e = _e * 2;
        return ans;
    }
    BigDbl operator/(BigDbl a)
    {
        if (_e == 0)
        {
            increaseE(1);
        }
        if (a._e == 0)
        {
            a.increaseE(1);
        }
        makeTwoBigDblSameLength(a);
        BigDbl ans;
        increaseE(2 * _e);

        ans._n = this->_n / a._n;
        ans._e = _e - a._e;

        if (ans._e < 0)
        {
            ans._n.appendR(std::string(1 - ans._e, '0'));
            ans._e = ans._n.num.length() - 1;
        }

        return ans;
    }

    friend std::ostream &operator<<(std::ostream &out, BigDbl n)
    {

        out << n.to_string();
        return out;
    }

    friend std::istream &operator>>(std::istream &in, BigDbl &n)
    {
        std::string s;
        in >> s;
        if (s == "")
            s = "0";
        n = s;
        return in;
    }
};
#ifdef TESTS_BIGDBL
#include <chrono>
#include <time.h>
class BigDblTester
{
private:
    int test_counter = 1;

public:
    void run_all_tests(int n)
    {
        test_define();
        loop_test_operater(1000, '<');
        loop_test_operater(1000, '>');
        loop_test_not_boolean_operater(1000, '+');
        loop_test_not_boolean_operater(1000, '-');
        loop_test_not_boolean_operater(1000, '*');
        loop_test_not_boolean_operater(1000, '/');
    }

    void test_define()
    {
        BigDbl
            n2(-100.10),
            n1,
            n3(1000),
            n4(1000.23),
            n5(100.10, 5),
            n6(1000, 5),
            n7(1000.23, 5),
            n8("100.10"),
            n9("1000"),
            n10("1000.23"),
            n11("100.10", 5),
            n12("1000", 5),
            n13("1000.23", 5),

            n14("100.10000"),
            n15("00000100.10"),

            n16("1100.10"),
            n17("100.10");

        assert(n2.to_string() == "-100.100000");
        assert(n3.to_string() == "1000.000000");
        assert(n4.to_string() == "1000.230000");

        assert(n5.to_string() == "100.100000");
        assert(n6.to_string() == "1000.000000");
        assert(n7.to_string() == "1000.230000");

        assert(n8.to_string() == "100.10");
        assert(n9.to_string() == "1000");
        assert(n10.to_string() == "1000.23");

        assert(n11.to_string() == "100.10");
        assert(n12.to_string() == "1000");
        assert(n13.to_string() == "1000.23");

        assert(n14 == n15);
        assert(!(n16 == n17));

        // std::cout << n13 << '\n';
        // std::cin >> n13;
        // std::cout << n13 << '\n';

        std::cout << "test [ " << test_counter << " ] ok.\n";

        ++test_counter;
    }
    BigDblTester() {};
    ~BigDblTester() {};

    void test_operator_with_range(
        int number_of_tests,
        char operator__,
        int min_range_a,
        int max_range_a,

        int min_range_b,
        int max_range_b,
        double e

    )
    {
        long double ia, ib;
        BigDbl bia, bib;
        bool ic, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < number_of_tests; i++)
        {
            ia = (long double)(rand() % (max_range_a - min_range_a));
            ib = (long double)(rand() % (max_range_b - min_range_b));

            if (max_range_a >= 0 || min_range_a >= 0)
            {
                ia += min_range_a;
            }
            else
            {
                ia += max_range_a;
            }

            if (max_range_b >= 0 || min_range_b >= 0)
            {
                ib += min_range_b;
            }
            else
            {
                ib += max_range_b;
            }

            ia /= e;
            ib /= e;

            switch (operator__)
            {
            case '<':
                if (i & 1)
                    ic = ia < ib;
                else
                    ic = ia <= ib;
                break;
            case '>':
                if (i & 1)
                    ic = ia > ib;
                else
                    ic = ia >= ib;
                break;

            default:
                throw std::invalid_argument("unknown operator");
                break;
            }

            bia = std::to_string(ia);
            bib = std::to_string(ib);

            switch (operator__)
            {
            case '>':

                if (i & 1)
                    bic = bia > bib;
                else
                    bic = bia >= bib;

                break;

            case '<':

                if (i & 1)
                    bic = bia < bib;
                else
                    bic = bia <= bib;

                break;

            default:
                throw std::invalid_argument("unknown operator");
                break;
            }

            if (bic != ic)
            {
                if (i & 1)
                {
                    std::cerr << "ERROR in test: " << i << std::endl;
                    std::cerr << ia << ' ' << operator__ << ib << " = " << ic << std::endl;
                    std::cerr << "you get " << bia << ' ' << operator__ << ' ' << bib << " = " << bic << std::endl;
                }
                else
                {
                    std::cerr << "ERROR in test: " << i << std::endl;
                    std::cerr << ia << ' ' << operator__ << '=' << ib << " = " << ic << std::endl;
                    std::cerr << "you get " << bia << ' ' << operator__ << '=' << ' ' << bib << " = " << bic << std::endl;
                }

                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "test [ " << test_counter << " ]:" << " OK passed all " << operator__ << " and " << operator__ << '=' << " tests(" << number_of_tests << ") in " << microsec << " micro second.\n";

        ++test_counter;
    }

    void test_not_boolean_operator_with_range(
        int number_of_tests,
        char operator__,
        int min_range_a,
        int max_range_a,

        int min_range_b,
        int max_range_b,
        double e

    )
    {
        long double ia, ib, ic;
        BigDbl bia, bib, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < number_of_tests; i++)
        {
            ia = (long double)(rand() % (max_range_a - min_range_a));
            ib = (long double)(rand() % (max_range_b - min_range_b));

            if (max_range_a >= 0 || min_range_a >= 0)
            {
                ia += min_range_a;
            }
            else
            {
                ia += max_range_a;
            }

            if (max_range_b >= 0 || min_range_b >= 0)
            {
                ib += min_range_b;
            }
            else
            {
                ib += max_range_b;
            }

            ia /= e;
            ib /= e;

            switch (operator__)
            {
            case '+':
                ic = ia + ib;
                break;

            case '-':
                ic = ia - ib;
                break;
            case '*':
                ic = ia * ib;
                break;
            case '/':
                ib += (ib == 0);
                ic = ia / ib;
                break;

            default:

                throw std::invalid_argument("unknown operator");
                break;
            }

            bia = std::to_string(ia);
            bib = std::to_string(ib);

            switch (operator__)
            {
            case '+':
                bic = bia + bib;
                break;
            case '-':
                bic = bia - bib;
                break;
            case '*':

                bic = bia * bib;
                break;
            case '/':

                bic = bia / bib;

                break;

            default:
                throw std::invalid_argument("unknown operator");
                break;
            }

            if ((bic - BigDbl(ic)).abss() > BigDbl("0.000001"))
            {
                std::cerr
                    << "ERROR in test: " << i << std::endl;
                std::cerr << ia << ' ' << operator__ << ' ' << ib << " = " << ic << std::endl;
                std::cerr << "you get " << bia << ' ' << operator__ << ' ' << bib << " = " << bic << std::endl;

                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "test [ " << test_counter << " ]:" << " OK passed all " << operator__ << " tests(" << number_of_tests << ") in " << microsec << " micro second.\n";

        ++test_counter;
    }

    void loop_test_operater(
        int n,
        char operator__)
    {
        test_operator_with_range(
            n,
            operator__,
            0, 10000000,
            0, 10000000, 1000.0);
        test_operator_with_range(
            n,
            operator__,
            -10000000, 0,
            -10000000, 0, 1000.0);

        test_operator_with_range(
            n,
            operator__,
            -10000000, 10000000,
            -10000000, 10000000, 1000.0);

        test_operator_with_range(
            n,
            operator__,
            0, 10000000,
            -10000000, 0, 1000.0);
        test_operator_with_range(
            n,
            operator__,
            -10000000, 0,
            0, 10000000, 1000.0);
    }

    void loop_test_not_boolean_operater(
        int n,
        char operator__)
    {
        test_not_boolean_operator_with_range(
            n,
            operator__,
            0, 10000000,
            0, 10000000, 1000.0);
        test_not_boolean_operator_with_range(
            n,
            operator__,
            -10000000, 0,
            -10000000, 0, 1000.0);

        test_not_boolean_operator_with_range(
            n,
            operator__,
            -10000000, 10000000,
            -10000000, 10000000, 1000.0);

        test_not_boolean_operator_with_range(
            n,
            operator__,
            0, 10000000,
            -10000000, 0, 1000.0);
        test_not_boolean_operator_with_range(
            n,
            operator__,
            -10000000, 0,
            0, 10000000, 1000.0);
    }
};
#endif

typedef std::vector<bool> vb;

class BigInt2
{

private:
    void
    _mul(const vb &a_str, const vb &b_str, vb &result)
    {

        if (a_str.empty() || b_str.empty())
        {
            result = {0};
            return;
        }
        if ((a_str[0] == 0 && a_str.size() == 1) ||
            (b_str[0] == 0 && b_str.size() == 1))
        {
            result = {0};
            return;
        }

        std::vector<std::complex<double>> a(a_str.size()), b(b_str.size());

        for (long long i = 0; i < a.size(); ++i)
        {

            a[i] = (a_str[i] ? 1.0 : 0.0);
        }

        for (long long i = 0; i < b.size(); ++i)
        {
            b[i] = (b_str[i] ? 1.0 : 0.0);
        }

        int result_size = a.size() + b.size() - 1;
        int n = 1;
        while (n < result_size)
        {
            n <<= 1;
        }

        a.resize(n, 0.0);
        b.resize(n, 0.0);

        fft(a, false);
        fft(b, false);

        std::vector<std::complex<double>> c(n);
        for (int i = 0; i < n; ++i)
        {
            c[i] = a[i] * b[i];
        }

        fft(c, true);

        std::vector<int> coeffs(n);
        for (int i = 0; i < n; ++i)
        {
            coeffs[i] = llround(c[i].real());
        }

        int carry = 0;
        int total;
        result.resize(n, false);

        for (int i = 0; i < n; ++i)
        {
            total = coeffs[i] + carry;
            carry = total / 2;
            result[i] = total % 2;
        }
        while (carry > 0)
        {
            result.push_back(carry % 2);
            carry /= 2;
        }

        long long first_non_zero = find_last_not_of(result, false);

        if (first_non_zero != -1)
        {
            result.erase(result.begin() + first_non_zero + 1, result.end());
        }
        else
        {
            result = {0};
            return;
        }
    }

public:
    vb numVector;
    bool isPositive;

    int reverse_bits(int x, int log2n)
    {
        int res = 0;
        for (int i = 0; i < log2n; ++i)
        {
            res = (res << 1) | (x & 1);
            x >>= 1;
        }
        return res;
    }

    void fft(std::vector<std::complex<double>> &a, bool invert)
    {
        int n = a.size();
        int log2n = 0;
        while ((1 << log2n) < n)
        {
            log2n++;
        }
        for (int i = 0; i < n; ++i)
        {
            int rev = reverse_bits(i, log2n);
            if (i < rev)
            {
                swap(a[i], a[rev]);
            }
        }
        for (int s = 2; s <= n; s <<= 1)
        {
            double ang = (2 * M_PI) / s * (invert ? 1 : -1);
            std::complex<double> wm(cos(ang), sin(ang));
            for (int k = 0; k < n; k += s)
            {
                std::complex<double> w(1);
                for (int j = 0; j < s / 2; ++j)
                {
                    std::complex<double> u = a[k + j];
                    std::complex<double> t = w * a[k + j + s / 2];
                    a[k + j] = u + t;
                    a[k + j + s / 2] = u - t;
                    w *= wm;
                }
            }
        }
        if (invert)
        {
            for (std::complex<double> &x : a)
            {
                x /= n;
            }
        }
    }

    long long find_last_not_of(std::vector<bool> &v, bool a)
    {
        for (long long i = v.size() - 1; i >= 0; --i)
        {
            if (v[i] != a)
            {
                return i;
            }
        }
        return -1;
    }

    BigInt2(const char *s)
    {
        BigInt n = s;

        numVector.clear();
        isPositive = true;

        if (!n.isPositive)
        {
            isPositive = false;
            n.isPositive = true;
        }

        while (n > 0)
        {
            numVector.push_back(n.isOdd());
            n = n / 2;
        }
    }

    std::string to_string()
    {
        BigInt b = "2";
        int e = 0;
        BigInt n = "0";

        for (const auto &x : numVector)
        {
            if (x)
                n = n + (b ^ e);
            ++e;
        }
        n.isPositive = isPositive;

        return n.to_string();
    }

    BigInt2()
    {
        isPositive = true;
        numVector = {0};
    }

    BigInt2
    operator*(const BigInt2 a)
    {
        BigInt2 ans;
        _mul(this->numVector, a.numVector, ans.numVector);

        if (a.isPositive ^ this->isPositive)
        {
            ans.isPositive = 0;
        }

        return ans;
    }

    friend std::ostream &operator<<(std::ostream &out, BigInt2 &n)
    {
        out << n.to_string();
        return out;
    }

    BigInt2 operator^(unsigned int e)
    {
        if (e == 0)
        {
            return BigInt2("1");
        }

        if (this->to_string() == "1")
        {
            return *this;
        }

        BigInt2 res = "1";
        BigInt2 a = *this;

        while (e)
        {
            alid(e);
            if (e & 1)
            {
                res = res * a;
            }
            a = a * a;
            e >>= 1;
        }

        return res;
    }

    ~BigInt2()
    {
    }
};

#endif
