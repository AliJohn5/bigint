#ifndef BIGINT_ALI
#define BIGINT_ALI

#define TESTS_BIGINT

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cstdint>
#include <cassert>
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
    }

    std::string __product(const std::string &a, const std::string &b)
    {
        std::string res(a.size() + b.size(), '0');

        int carry = 0;

        int ires = res.size() - 1, ia = a.size() - 1, ib = b.size() - 1;
        int resInt;

        while (
            ib >= 0)
        {
            ires = res.size() - (b.size() - ib);
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

    std::string __divide(const std::string &a, const std::string &b)
    {

        if (b == "1")
            return a;

        if (b == "0")
            throw std::invalid_argument("can't divide by zero");

        std::string mx(a.length() - b.length() + 1, '0'),
            mn(std::max<long long>(a.length() - b.length(), 1), '0');

        mx[0] = '1';
        mn[0] = '1';

        if (b.size() > a.size())
        {
            return "0";
        }

        if (b.size() == a.size())
        {
            for (int i = 0; i < a.size(); ++i)
            {

                if (b[i] > a[i])
                    return "0";
                if (b[i] < a[i])
                    break;
            }
        }

        std::string mid, mid1, prod, prod1;
        bool lessmid, lessmid1;

        while (__isStringLessThanEqualString(mn, mx))
        {
            mid = __divide_string_by_2(__sum(mx, mn));
            mid1 = __sum(mid1, "1");

            prod = __product(mid, b);
            prod1 = __product(mid1, b);

            lessmid = __isStringLessThanEqualString(prod, a);
            lessmid1 = __isStringLessThanEqualString(prod1, a);

            if (lessmid && !lessmid1)
            {
                // std::cout << mid << '\n';
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

    std::string __mod(const std::string &a, const std::string &b)
    {
        return __minus(a, __product(__divide(a, b), b));
    }

public:
    std::string num;
    bool isPositive = true;
    std::string to_string()
    {
        if (isPositive)
            return num;
        else
            return "-" + num;
    }
    BigInt(std::string s)
    {
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
            num = s;
        }
    }

    BigInt(const char *c)
    {
        std::string s = c;
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
            num = s;
        }
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

    BigInt operator/(const BigInt a)
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

    BigInt operator%(const BigInt a)
    {
        if (a.isPositive && this->isPositive)
        {
            BigInt ans(__mod(this->num, a.num));
            return ans;
        }

        BigInt ans(__mod(this->num, a.num));
        ans.isPositive = 0;
        return ans;
    }

    BigInt operator*=(const BigInt a)
    {
        if (a.isPositive && this->isPositive)
            return BigInt(__product(this->num, a.num));

        if (!a.isPositive && !this->isPositive)
            return BigInt(__product(this->num, a.num));

        BigInt ans(__product(this->num, a.num));
        ans.isPositive = 0;
        return ans;
    }

    BigInt operator/=(const BigInt a)
    {
        if (a.isPositive && this->isPositive)
            return BigInt(__divide(this->num, a.num));

        if (!a.isPositive && !this->isPositive)
            return BigInt(__divide(this->num, a.num));

        BigInt ans(__divide(this->num, a.num));
        ans.isPositive = 0;
        return ans;
    }

    BigInt operator%=(const BigInt a)
    {
        if (a.isPositive && this->isPositive)
            return BigInt(__mod(this->num, a.num));

        BigInt ans(__mod(this->num, a.num));
        ans.isPositive = 0;
        return ans;
    }

    BigInt operator*=(const std::string a)
    {
        BigInt c(a);
        if (c.isPositive && this->isPositive)
            return BigInt(__product(this->num, c.num));

        if (!c.isPositive && !this->isPositive)
            return BigInt(__product(this->num, c.num));

        BigInt ans(__product(this->num, c.num));
        ans.isPositive = 0;
        return ans;
    }

    BigInt operator/=(const std::string a)
    {
        BigInt c(a);
        if (c.isPositive && this->isPositive)
            return BigInt(__divide(this->num, c.num));

        if (!c.isPositive && !this->isPositive)
            return BigInt(__divide(this->num, c.num));

        BigInt ans(__divide(this->num, c.num));
        ans.isPositive = 0;
        return ans;
    }

    BigInt operator%=(const std::string a)
    {
        BigInt c(a);
        if (c.isPositive && this->isPositive)
            return BigInt(__mod(this->num, c.num));

        BigInt ans(__mod(this->num, c.num));
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
            c.isPositive = true;
            return d - c;
        }

        if (!d.isPositive && a.isPositive)
        {
            BigInt c = d;
            c.isPositive = true;
            return c - a;
        }
        return d;
    }

    BigInt operator+=(const BigInt a)
    {
        BigInt v = *this + a;
        return v;
    }
    BigInt operator+=(const std::string a)
    {
        BigInt v = *this + BigInt(a);
        return v;
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
        if (!s.empty())
        {
            if (s[0] == '-')
            {
                n.isPositive = 0;
                s.erase(0, 1);
                n.num = s;
            }
            else
                n.num = s;
        }

        else
            n.num = s;

        return in;
    }

    void operator=(std::string s)
    {
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
    }

    void operator=(long long s)
    {
        if (s < 0)
        {
            isPositive = 0;
            num = std::to_string(-s);
        }

        else
        {
            isPositive = 1;
            num = std::to_string(s);
        }
    }

    void operator=(int s)
    {
        if (s < 0)
        {
            isPositive = 0;
            num = std::to_string(-s);
        }

        else
        {
            isPositive = 1;
            num = std::to_string(s);
        }
    }

    void operator=(const char *c)
    {
        std::string s = c;
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
            num = s;
        }
    }

    bool isOdd()
    {
        return ((num[num.length() - 1] - '0') & 1);
    }

    BigInt operator-(const BigInt a)
    {
        BigInt &d = *this;

        if (d.isPositive && a.isPositive)
        {
            if (d > a)
                return BigInt(__minus(this->num, a.num));
            else
            {
                BigInt ans(__minus(a.num, this->num));
                ans.isPositive = 0;
                return ans;
            }
        }

        if (!d.isPositive && !a.isPositive)
        {
            if (d > a)
                return BigInt(__minus(a.num, this->num));
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

    BigInt operator-=(const BigInt a)
    {
        BigInt v = *this - a;
        return v;
    }
    BigInt operator-=(const std::string a)
    {
        BigInt v = *this - BigInt(a);
        return v;
    }
};

#ifdef TESTS_BIGINT
#include <chrono>
class BigIntTester
{
public:
    static void run_all_tests()
    {
        test_multiplication();

        test_division();

        test_modulo();

        test_comparisons();

        test_conversions();

        testSum(100000);

        testMinus(100000);

        testProduct(100000);

        testDivide(100000);

        testMod(100000);

        std::cout << "All tests passed!\n";
    }

private:
    static void test_multiplication()
    {

        assert(BigInt(123) * BigInt(2) == BigInt(246));

        assert(BigInt(-12) * BigInt(3) == BigInt(-36));


        BigInt a("123456789");
        BigInt b("987654321");

        assert(a * b == BigInt("121932631112635269"));
    }

    static void test_division()
    {
        assert(BigInt(100) / BigInt(5) == BigInt(20));
        assert(BigInt(-81) / BigInt(9) == BigInt(-9));
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
    }

    static void test_modulo()
    {
        assert(BigInt(17) % BigInt(5) == BigInt(2));
        assert(BigInt(-17) % BigInt(5) == BigInt(-2));
        assert(BigInt(25) % BigInt(7) == BigInt(4));
    }

    static void test_comparisons()
    {
        assert(BigInt(5) > BigInt(3));
        assert(BigInt(-2) <= BigInt(0));
        assert(BigInt("1000000") >= BigInt(999999));
    }

    static void test_conversions()
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
    }

    static void testProduct(int n)
    {
        srand(time(0));
        long long ia, ib, ic;
        BigInt bia, bib, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; i++)
        {
            ia = (long long)(rand() % 1000000) - 500000;
            ib = (long long)(rand() % 1000000) - 500000;
            ic = ia * ib;

            bia = std::to_string(ia);
            bib = std::to_string(ib);

            bic = bia * bib;

            if (atoll(bic.to_string().c_str()) != ic)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia << " * " << ib << " = " << ic << std::endl;
                std::cerr << "you get " << bia << " * " << bib << " = " << bic << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "OK passed all product tests (" << n << ") in " << microsec << " micro second.\n";
    }

    static void testSum(int n)
    {
        long long ia, ib, ic;
        BigInt bia, bib, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; i++)
        {
            ia = (long long)(rand() % 1000000) - 500000;
            ib = (long long)(rand() % 1000000) - 500000;
            ic = ia + ib;

            bia = std::to_string(ia);
            bib = std::to_string(ib);

            bic = bia + bib;

            if (atoll(bic.to_string().c_str()) != ic)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia << " + " << ib << " = " << ic << std::endl;
                std::cerr << "you get " << bia << " + " << bib << " = " << bic << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "OK passed all sum tests (" << n << ") in " << microsec << " micro second.\n";
    }

    static void testMinus(int n)
    {
        long long ia, ib, ic;
        BigInt bia, bib, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; i++)
        {
            ia = (long long)(rand() % 1000000) - 500000;
            ib = (long long)(rand() % 1000000) - 500000;
            ic = ia - ib;

            bia = std::to_string(ia);
            bib = std::to_string(ib);

            bic = bia - bib;

            if (atoll(bic.to_string().c_str()) != ic)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia << " - " << ib << " = " << ic << std::endl;
                std::cerr << "you get " << bia << " * " << bib << " = " << bic << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "OK passed all sum tests (" << n << ") in " << microsec << " micro second.\n";
    }

    static void testDivide(int n)
    {
        long long ia, ib, ic;
        BigInt bia, bib, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; i++)
        {
            ia = (long long)(rand() % 1000000) - 500000;
            ib = (long long)(rand() % 1000000) - 500000;
            ic = ia / ib;

            bia = std::to_string(ia);
            bib = std::to_string(ib);

            bic = bia / bib;

            if (atoll(bic.to_string().c_str()) != ic)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia << " / " << ib << " = " << ic << std::endl;
                std::cerr << "you get " << bia << " / " << bib << " = " << bic << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "OK passed all sum tests (" << n << ") in " << microsec << " micro second.\n";
    }

    static void testMod(int n)
    {
        long long ia, ib, ic;
        BigInt bia, bib, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; i++)
        {
            ia = (long long)(rand() % 1000000) - 500000;
            ib = (long long)(rand() % 1000000) - 500000;
            ic = ia % ib;

            bia = std::to_string(ia);
            bib = std::to_string(ib);

            bic = bia % bib;

            if (atoll(bic.to_string().c_str()) != ic)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia << " * " << ib << " = " << ic << std::endl;
                std::cerr << "you get " << bia << " * " << bib << " = " << bic << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "OK passed all sum tests (" << n << ") in " << microsec << " micro second.\n";
    }
};
#endif

#endif