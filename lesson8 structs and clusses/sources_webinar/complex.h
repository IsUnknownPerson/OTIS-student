#ifndef COMPLEX_H
#define COMPLEX_H

class Complex {
public:
    Complex();
    Complex(double real, double im);
    ~Complex();

    double abs() const;
    double angle() const;

    void set_real(double real);
    void set_img(double img);

private:
    double m_real;
    double m_img;
};

#endif // COMPLEX_H
