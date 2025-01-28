#ifndef BIGINT_ALI
#define BIGINT_ALI

/*
    (negative and positive):
    supported operaters:
        *
        +
        *=
        +=
        =
        cout <<
        cin >>
        >
        >=
        <
        <=
        ==
        !=
        -
        -=
        /
        /=
        %
        %=

*/

#include <iostream>
#include <string>
#include <vector>

#define TESTS_BIGINT

#ifdef TESTS_BIGINT

#include <chrono>
#include <time.h>

#endif


class BigInt
{

    inline std::string __product(const std::string &a, const std::string &b)
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

        int i = 0;

        while (i < res.size())
        {
            if (res[i] != '0')
                break;
            ++i;
        }

        if (i >= 0)
        {
            res.erase(
                res.begin(),
                res.begin() + i);
        }

        if (res == "")
            return "0";
        return res;
    }

    inline std::string __sum(const std::string &a, const std::string &b)
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

        int i = 0;

        while (i < res.size())
        {
            if (res[i] != '0')
                break;
            ++i;
        }

        if (i >= 0)
        {
            res.erase(
                res.begin(),
                res.begin() + i);
        }

        return res;
    }

    inline std::string __minus(const std::string &a, const std::string &b)
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

        int i = 0;

        while (i < res.size())
        {
            if (res[i] != '0')
                break;
            ++i;
        }

        if (i >= 0)
        {
            res.erase(
                res.begin(),
                res.begin() + i);
        }

        return res;
    }

    inline std::string __divide_string_by_2(const std::string &s)
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

    inline bool __isStringLessThanEqualString(const std::string &a, const std::string &b)
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

    inline std::string __divide(const std::string &a, const std::string &b)
    {

        if (b == "1")
            return a;

        if (b == "0")
            return "0";

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

        return mid;
    }

    inline std::string __mod(const std::string &a, const std::string &b)
    {
        return __minus(a, __product(__divide(a, b), b));
    }

public:
    std::string num;
    bool isPositive = true;
    inline BigInt(std::string s)
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

    inline BigInt(const char *c)
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

    inline BigInt(long long int _n)
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

    inline BigInt(int _n)
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

    inline BigInt()
    {
    }
    inline std::string getNum()
    {
        return (isPositive ? num : "-" + num);
    }
    inline void setNum(std::string s)
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

    inline BigInt operator*(const BigInt a)
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

    inline BigInt operator/(const BigInt a)
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

    inline BigInt operator%(const BigInt a)
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

    inline BigInt operator*=(const BigInt a)
    {
        if (a.isPositive && this->isPositive)
            return BigInt(__product(this->num, a.num));

        if (!a.isPositive && !this->isPositive)
            return BigInt(__product(this->num, a.num));

        BigInt ans(__product(this->num, a.num));
        ans.isPositive = 0;
        return ans;
    }

    inline BigInt operator/=(const BigInt a)
    {
        if (a.isPositive && this->isPositive)
            return BigInt(__divide(this->num, a.num));

        if (!a.isPositive && !this->isPositive)
            return BigInt(__divide(this->num, a.num));

        BigInt ans(__divide(this->num, a.num));
        ans.isPositive = 0;
        return ans;
    }

    inline BigInt operator%=(const BigInt a)
    {
        if (a.isPositive && this->isPositive)
            return BigInt(__mod(this->num, a.num));

        BigInt ans(__mod(this->num, a.num));
        ans.isPositive = 0;
        return ans;
    }

    inline BigInt operator*=(const std::string a)
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

    inline BigInt operator/=(const std::string a)
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

    inline BigInt operator%=(const std::string a)
    {
        BigInt c(a);
        if (c.isPositive && this->isPositive)
            return BigInt(__mod(this->num, c.num));

        BigInt ans(__mod(this->num, c.num));
        ans.isPositive = 0;
        return ans;
    }

    inline BigInt operator+(const BigInt a)
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

    inline BigInt operator+=(const BigInt a)
    {
        BigInt v = *this + a;
        return v;
    }
    inline BigInt operator+=(const std::string a)
    {
        BigInt v = *this + BigInt(a);
        return v;
    }
    inline bool operator>(const BigInt a)
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

    inline bool operator<(const BigInt a)
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

    inline bool operator>=(const BigInt a)
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
    }

    inline bool operator<=(const BigInt a)
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
    }

    inline bool operator==(const BigInt a)
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

    inline bool operator!=(const BigInt a)
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

    inline friend std::ostream &operator<<(std::ostream &out, const BigInt &n)
    {
        if (n.isPositive)
            out << n.num;
        else
            out << '-' << n.num;

        return out;
    }

    inline friend std::istream &operator>>(std::istream &in, BigInt &n)
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

    inline void operator=(std::string s)
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

    inline void operator=(long long s)
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

    inline void operator=(int s)
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

    inline void operator=(const char *c)
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

    inline bool isOdd()
    {
        return ((num[num.length() - 1] - '0') & 1);
    }

    inline BigInt operator-(const BigInt a)
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

    inline BigInt operator-=(const BigInt a)
    {
        BigInt v = *this - a;
        return v;
    }
    inline BigInt operator-=(const std::string a)
    {
        BigInt v = *this - BigInt(a);
        return v;
    }

#ifdef TESTS_BIGINT
    inline void testProduct(int n)
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

            bia.setNum(std::to_string(ia));
            bib.setNum(std::to_string(ib));

            bic = bia * bib;

            if (atoll(bic.getNum().c_str()) != ic)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia << " * " << ib << " = " << ic << std::endl;
                std::cerr << "you get " << bia.getNum() << " * " << bib.getNum() << " = " << bic.getNum() << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "OK passed all product tests (" << n << ") in " << microsec << " micro second.\n";
    }

    inline void testSum(int n)
    {
        long long ia, ib, ic;
        BigInt bia, bib, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; i++)
        {
            ia = (rand() % 1000000) - 500000;
            ib = (rand() % 1000000) - 500000;
            ic = ia + ib;

            bia.setNum(std::to_string(ia));
            bib.setNum(std::to_string(ib));
            bic = bia + bib;

            if (atoll(bic.getNum().c_str()) != ic)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia << " + " << ib << " = " << ic << std::endl;
                std::cerr << "you get " << bia.getNum() << " + " << bib.getNum() << " = " << bic.getNum() << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "OK passed all sum tests (" << n << ") in " << microsec << " micro second.\n";
    }

    inline void testSum2(int n)
    {
        long long ia, ib;
        BigInt bia, bib;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; i++)
        {
            ia = (rand() % 1000000) - 500000;
            ib = (rand() % 1000000) - 500000;
            ia += ib;

            bia.setNum(std::to_string(ia));
            bib.setNum(std::to_string(ib));
            bia += bib;

            if (atoll(bia.getNum().c_str()) != ia)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia - ib << " += " << ib << " = " << ia << std::endl;
                std::cerr << "you get " << bia.getNum() << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "OK passed all sum tests (" << n << ") in " << microsec << " micro second.\n";
    }

    inline void testMinus(int n)
    {
        long long ia, ib, ic;
        BigInt bia, bib, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; i++)
        {
            ia = (rand() % 1000000) - 500000;
            ib = (rand() % 1000000) - 500000;
            ic = ia - ib;

            bia.setNum(std::to_string(ia));
            bib.setNum(std::to_string(ib));
            bic = bia - bib;

            if (atoll(bic.getNum().c_str()) != ic)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia << " - " << ib << " = " << ic << std::endl;
                std::cerr << "you get " << bia.getNum() << " - " << bib.getNum() << " = " << bic.getNum() << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "OK passed all sum tests (" << n << ") in " << microsec << " micro second.\n";
    }

    inline void testDivide(int n)
    {
        long long ia, ib, ic;
        BigInt bia, bib, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; i++)
        {
            ia = (rand() % 1000000) - 500000;
            ib = (rand() % 1000000) - 500000;
            ic = ia / ib;

            bia.setNum(std::to_string(ia));
            bib.setNum(std::to_string(ib));
            bic = bia / bib;

            if (atoll(bic.getNum().c_str()) != ic)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia << " / " << ib << " = " << ic << std::endl;
                std::cerr << "you get " << bia.getNum() << " / " << bib.getNum() << " = " << bic.getNum() << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "OK passed all sum tests (" << n << ") in " << microsec << " micro second.\n";
    }

    inline void testMod(int n)
    {
        long long ia, ib, ic;
        BigInt bia, bib, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; i++)
        {
            ia = (rand() % 1000000) - 500000;
            ib = (rand() % 1000000) - 500000;
            ic = ia % ib;

            bia.setNum(std::to_string(ia));
            bib.setNum(std::to_string(ib));
            bic = bia % bib;

            if (atoll(bic.getNum().c_str()) != ic)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia << " % " << ib << " = " << ic << std::endl;
                std::cerr << "you get " << bia.getNum() << " % " << bib.getNum() << " = " << bic.getNum() << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "OK passed all sum tests (" << n << ") in " << microsec << " micro second.\n";
    }

    inline void testDivideBy2(int n)
    {
        long long ia, ic;
        std::string bia, bic;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; i++)
        {
            ia = (rand() % 1000000);
            bia = std::to_string(ia);

            ic = ia / 2;
            bic = __divide_string_by_2(bia);

            if (atoll(bic.c_str()) != ic)
            {
                std::cerr << "ERROR in test: " << i << std::endl;
                std::cerr << ia << " 2 / " << " = " << ic << std::endl;
                std::cerr << "you get " << bia << " / 2 " << " = " << bic << std::endl;
                exit(-1);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();

        int64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        std::cout << "OK passed all sum tests (" << n << ") in " << microsec << " micro second.\n";
    }

#endif
};

#endif