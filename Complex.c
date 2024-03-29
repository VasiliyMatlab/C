#include <math.h>

// Определение структуры комплексных чисел
typedef struct complex{
    double Re;
    double Im;
} complex;

// Операция взятия модуля числа
double mod(complex number) {
    return sqrt(pow(number.Re,2) + pow(number.Im,2));
}

// Нахождение аргумента числа
double arg(complex number) {
    double phi;
    phi = atan(number.Im / number.Re);
    if (number.Re < 0) {
        if (number.Im >= 0)
            phi += M_PI;
        else
            phi -= M_PI;
    }
    return phi;
}

// Возвращение действительной части числа
double real(complex number) {
    return number.Re;
}
// Возвращение мнимой части числа
double imag(complex number) {
    return number.Im;
}

// Перевод из радиан в градусы
double rad2grad(double phi) {
    return phi * 180/M_PI;
}

// Перевод из градусов в радианы
double grad2rad(double phi) {
    return phi * M_PI/180;
}

// Сложение двух комплексных чисел
complex add(complex num1, complex num2) {
    complex num3;
    num3.Re = num1.Re + num2.Re;
    num3.Im = num1.Im + num2.Im;
    return num3;
}

// Разность двух комплексных чисел
complex sub(complex num1, complex num2) {
    complex num3;
    num3.Re = num1.Re - num2.Re;
    num3.Im = num1.Im - num2.Im;
    return num3;
}

// Произведение двух комплексных чисел
complex mul(complex num1, complex num2) {
    complex num3;
    num3.Re = num1.Re*num2.Re - num1.Im*num2.Im;
    num3.Im = num1.Re*num2.Im + num1.Im*num2.Re;
    return num3;
}

// Деление двух комплексных чисел
complex div(complex num1, complex num2) {
    complex num3;
    double tmp = pow(num2.Re,2) + pow(num2.Im,2);
    num3.Re = (num1.Re*num2.Re + num1.Im*num2.Im) / tmp;
    num3.Im = (num1.Im*num2.Re - num1.Re*num2.Im) / tmp;
    return num3;
}

// Сложение комплексного и действительного числа
complex add_real(complex number, double n) {
    complex num;
    num.Re = number.Re + n;
    num.Im = number.Im;
    return num;
}

// Разность комплексного и действительного числа
complex sub_real(complex number, double n) {
    complex num;
    num.Re = number.Re - n;
    num.Im = number.Im;
    return num;
}

// Сложение комплексного и мнимого числа
complex add_imag(complex number, double n) {
    complex num;
    num.Re = number.Re;
    num.Im = number.Im + n;
    return num;
}

// Разность комплексного и мнимого числа
complex sub_imag(complex number, double n) {
    complex num;
    num.Re = number.Re;
    num.Im = number.Im + n;
    return num;
}

// Произведение комплексного и действительного числа
complex mul_real(complex number, double n) {
    complex num;
    num.Re = number.Re * n;
    num.Im = number.Im * n;
    return num;
}

// Деление комплексного и действительного числа
complex div_real(complex number, double n) {
    complex num;
    num.Re = number.Re / n;
    num.Im = number.Im / n;
    return num;
}

// Произведение комплексного и мнимого числа
complex mul_imag(complex number, double n) {
    complex num;
    num.Re = - number.Im * n;
    num.Im = number.Re * n;
    return num;
}

// Деление комплексного и мнимого числа
complex div_imag(complex number, double n) {
    complex num;
    num.Re = number.Im / n;
    num.Im = - number.Re / n;
    return num;
}

// Возвращает комплексно-сопряженное число
void conj(complex *number) {
    number->Im = - number->Im;
}

// Установка действительной и мнимой частей комплексного числа
complex set(double real, double imag) {
    complex number;
    number.Re = real;
    number.Im = imag;
    return number;
}