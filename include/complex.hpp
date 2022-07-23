#include <iostream>

class Complex
{
private:
    double r;
    double i;

public:
    Complex();
    Complex(double real, double imag);
    ~Complex();

    void print();
    Complex operator+(Complex const &obj);
    Complex operator-(Complex const &obj);
    Complex operator*(Complex const &obj);
    Complex operator/(Complex const &obj);
    Complex operator=(Complex const &obj);
    bool operator==(Complex const &obj);
    bool operator!=(Complex const &obj);
    Complex conj();
    double real() const;
    double imag() const;
    double abs();
    // Complex sqrt();
    // Complex ln();
    friend std::ostream &operator<<(std::ostream &out, const Complex &z);
};