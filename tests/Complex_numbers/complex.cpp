#include "complex.hpp"

Complex::Complex()
{
    r = 0;
    i = 0;
}

Complex::Complex(double real, double imag)
{
    r = real;
    i = imag;
}

void Complex::print()
{
    std::cout << r << " + " << i << "i" << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Complex &z)
{
    if (z.imag() > 0)
    {
        out << z.real() << " + " << z.imag() << "i";
    }
    else
    {
        out << z.real() << " - " << -z.imag() << "i";
    }
    return out;
}

Complex Complex::operator+(Complex const &obj)
{
    Complex res;
    res.r = r + obj.r;
    res.i = i + obj.i;
    return res;
}

Complex Complex::operator-(Complex const &obj)
{
    Complex res;
    res.r = r - obj.r;
    res.i = i - obj.i;
    return res;
}

Complex Complex::operator*(Complex const &obj)
{
    Complex res;
    res.r = r * obj.r - i * obj.i;
    res.i = r * obj.i + i * obj.r;
    return res;
}

Complex Complex::operator/(Complex const &obj)
{
    Complex res;
    double den = obj.r * obj.r + obj.i * obj.i;
    res.r = (r * obj.r + i * obj.i) / den;
    res.i = (i * obj.r - r * obj.i) / den;
    return res;
}

Complex Complex::operator=(Complex const &obj)
{
    Complex res;
    res.r = obj.r;
    res.i = obj.i;
    return res;
}

bool Complex::operator==(Complex const &obj)
{
    if ((r == obj.r) && (i == obj.i))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Complex::operator!=(Complex const &obj)
{
    if ((r != obj.r) || (i != obj.i))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Complex Complex::conj()
{
    Complex res;
    res.r = r;
    res.i = -i;
    return res;
}

double Complex::real() const
{
    return r;
}

double Complex::imag() const
{
    return i;
}

Complex::~Complex()
{
}