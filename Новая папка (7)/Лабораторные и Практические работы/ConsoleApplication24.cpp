#include <iostream>
#include <cmath>

using namespace std;

class Fraction {
private:
    int numerator;    // числитель
    int denominator;  // знаменатель

    // Вспомогательный метод для нахождения НОД
    int gcd(int a, int b) {
        a = abs(a);
        b = abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

public:
    // Конструктор по умолчанию
    Fraction() : numerator(0), denominator(1) {}

    // Конструктор с параметрами
    Fraction(int num, int den) {
        if (den == 0) {
            cout << "Ошибка: знаменатель не может быть равен 0!" << endl;
            numerator = 0;
            denominator = 1;
        }
        else {
            numerator = num;
            denominator = den;
            simplify(); // сразу сокращаем дробь
        }
    }

    // Метод вывода
    void print() {
        cout << numerator << "/" << denominator;
    }

    // Сокращение дроби
    void simplify() {
        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        // Если знаменатель отрицательный, переносим минус в числитель
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    // Оператор сложения
    Fraction operator+(const Fraction& other) {
        int new_num = numerator * other.denominator + other.numerator * denominator;
        int new_den = denominator * other.denominator;
        Fraction result(new_num, new_den);
        return result;
    }

    // Оператор вычитания
    Fraction operator-(const Fraction& other) {
        int new_num = numerator * other.denominator - other.numerator * denominator;
        int new_den = denominator * other.denominator;
        Fraction result(new_num, new_den);
        return result;
    }

    // Оператор умножения
    Fraction operator*(const Fraction& other) {
        int new_num = numerator * other.numerator;
        int new_den = denominator * other.denominator;
        Fraction result(new_num, new_den);
        return result;
    }

    // Оператор деления
    Fraction operator/(const Fraction& other) {
        int new_num = numerator * other.denominator;
        int new_den = denominator * other.numerator;
        Fraction result(new_num, new_den);
        return result;
    }

    // Оператор сравнения
    bool operator=(const Fraction& other) {
        // Приводим к общему знаменателю и сравниваем числители
        return numerator * other.denominator == other.numerator * denominator;
    }

    // Дружественная функция для вывода через cout
    friend ostream& operator<<(ostream& os, const Fraction& f) {
        os << f.numerator << "/" << f.denominator;
        return os;
    }
};

// Пример использования
int main() {
    setlocale(LC_ALL, "Russian"); // для русских символов в консоли

    // Создание дробей
    Fraction f1(1, 2);
    Fraction f2(3, 4);
    Fraction f3(2, 4);  // сократится до 1/2

    // Вывод с использованием метода print()
    cout << "Вывод через метод print(): ";
    f1.print();
    cout << endl;

    // Вывод с использованием перегруженного оператора <<
    cout << "Вывод через оператор <<: " << f1 << endl;
    cout << endl;

    cout << "f1 = " << f1 << endl;
    cout << "f2 = " << f2 << endl;
    cout << "f3 = " << f3 << " (сократилась автоматически)" << endl;
    cout << endl;

    // Арифметические операции
    Fraction sum = f1 + f2;
    Fraction diff = f2 - f1;
    Fraction prod = f1 * f2;
    Fraction quot = f1 / f2;

    cout << "f1 + f2 = " << sum << endl;
    cout << "f2 - f1 = " << diff << endl;
    cout << "f1 * f2 = " << prod << endl;
    cout << "f1 / f2 = " << quot << endl;
    cout << endl;

    // Сравнение
    if (f1 = f3) {
        cout << "f1 и f3 равны" << endl;
    }
    else {
        cout << "f1 и f3 не равны" << endl;
    }

    if (f1 =f2) {
        cout << "f1 и f2 равны" << endl;
    }
    else {
        cout << "f1 и f2 не равны" << endl;
    }
    cout << endl;

    // Проверка на ошибку
    cout << "Проверка обработки ошибки:" << endl;
    Fraction f4(1, 0);  // попытка создать дробь с нулевым знаменателем
    cout << "f4 = " << f4 << endl;

    return 0;
}