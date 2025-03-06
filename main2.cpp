#include <vector>
#include <complex>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

const double PI = acos(-1);

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

void fft(vector<complex<double>> &a, bool invert)
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
        double ang = 2 * PI / s * (invert ? 1 : -1);
        complex<double> wm(cos(ang), sin(ang));
        for (int k = 0; k < n; k += s)
        {
            complex<double> w(1);
            for (int j = 0; j < s / 2; ++j)
            {
                complex<double> u = a[k + j];
                complex<double> t = w * a[k + j + s / 2];
                a[k + j] = u + t;
                a[k + j + s / 2] = u - t;
                w *= wm;
            }
        }
    }
    if (invert)
    {
        for (complex<double> &x : a)
        {
            x /= n;
        }
    }
}

long long find_first_not_of(std::vector<bool> &v, bool a)
{
    for (long long i = 0; i < v.size(); ++i)
    {
        if (v[i] != a)
        {
            return i;
        }
    }
    return -1;
}

std::vector<bool>
multiply_binary(const std::vector<bool> &a_str, const std::vector<bool> &b_str)
{
    if (a_str.empty() || b_str.empty())
    {
        return {0};
    }
    if (a_str[0] == 0 || b_str[0] == 0)
    {
        return {0};
    }

    vector<complex<double>> a, b;

    for (int i = a_str.size() - 1; i >= 0; --i)
    {
        a.push_back(a_str[i] ? 1.0 : 0.0);
    }
    for (int i = b_str.size() - 1; i >= 0; --i)
    {
        b.push_back(b_str[i] ? 1.0 : 0.0);
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

    vector<complex<double>> c(n);
    for (int i = 0; i < n; ++i)
    {
        c[i] = a[i] * b[i];
    }

    fft(c, true);

    vector<int> coeffs(n);
    for (int i = 0; i < n; ++i)
    {
        coeffs[i] = llround(c[i].real());
    }

    vector<bool> result_digits;
    int carry = 0;
    int total;

    for (int i = 0; i < n; ++i)
    {
        total = coeffs[i] + carry;
        carry = total / 2;
        result_digits.push_back(total % 2);
    }
    while (carry > 0)
    {
        result_digits.push_back(carry % 2);
        carry /= 2;
    }

    reverse(result_digits.begin(), result_digits.end());
    std::vector<bool> &result = result_digits;

    long long first_non_zero = find_first_not_of(result, false);

    if (first_non_zero != -1)
    {
        result.erase(result.begin(), result.begin() + first_non_zero);
    }
    else
    {
        return {0};
    }

    return result;
}

int main()
{
    std::vector<bool> a(10, true), b(10, true);
    std::vector<bool> c = multiply_binary(a, b);

    cout << "Product: ";
    for (const auto &x : c)
    {
        cout << x;
    }
    cout << endl;
    return 0;
}