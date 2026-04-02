#include <iostream>
#include <string>
using namespace std;

// ========== ЗАДАНИЕ 1 ==========
class Student {
private:
    string name;
    int age;
    double grade;
    
public:
    Student(string n, int a, double g) {
        name = n;
        age = a;
        grade = g;
        cout << "Студент " << name << " создан" << endl;
    }
    
    ~Student() {
        cout << "Student destroyed" << endl;
    }
    
    void setData(string n, int a, double g) {
        name = n;
        age = a;
        grade = g;
    }
    
    void printInfo() {
        cout << "Имя: " << name << endl;
        cout << "Возраст: " << age << endl;
        cout << "Средний балл: " << grade << endl;
        cout << "------------------------" << endl;
    }
};

// ========== ЗАДАНИЕ 2 ==========
class Car {
public:
    string brand;
    
private:
    int year;
    
protected:
    int speed;
    
public:
    Car(string b, int y, int s) {
        brand = b;
        year = y;
        speed = s;
    }
    
    void setYear(int y) {
        year = y;
    }
    
    int getYear() {
        return year;
    }
    
    void setSpeed(int s) {
        speed = s;
    }
    
    int getSpeed() {
        return speed;
    }
    
    void printInfo() {
        cout << "Марка: " << brand << endl;
        cout << "Год выпуска: " << year << endl;
        cout << "Скорость: " << speed << " км/ч" << endl;
        cout << "------------------------" << endl;
    }
};

// ========== ЗАДАНИЕ 3 ==========
class Product {
private:
    string name;
    double price;
    int quantity;
    
public:
    Product(string n, double p, int q) {
        name = n;
        price = p;
        quantity = q;
        cout << "Товар " << name << " создан" << endl;
    }
    
    ~Product() {
        cout << "Product destroyed" << endl;
    }
    
    Product* setData(string n, double p, int q) {
        this->name = n;
        this->price = p;
        this->quantity = q;
        return this;
    }
    
    void printInfo() {
        cout << "Название: " << name << endl;
        cout << "Цена: " << price << " руб." << endl;
        cout << "Количество на складе: " << quantity << " шт." << endl;
        cout << "------------------------" << endl;
    }
    
    void buy(int amount) {
        if (amount <= quantity) {
            quantity -= amount;
            cout << "Куплено " << amount << " шт. товара " << name << endl;
        } else {
            cout << "Ошибка: недостаточно товара на складе!" << endl;
            cout << "Доступно только " << quantity << " шт." << endl;
        }
    }
};

// ========== ГЛАВНАЯ ФУНКЦИЯ ==========
int main() {
    // Задание 1
    cout << "=== Задание 1. Класс Student ===" << endl;
    Student s1("Alex", 20, 4.5);
    s1.printInfo();
    Student s2 = s1;
    s2.printInfo();
    cout << endl;
    
    // Задание 2
    cout << "=== Задание 2. Класс Car ===" << endl;
    Car c1("Toyota", 2020, 180);
    c1.printInfo();
    c1.setYear(2021);
    c1.setSpeed(200);
    c1.printInfo();
    cout << endl;
    
    // Задание 3
    cout << "=== Задание 3. Класс Product ===" << endl;
    Product p1("Laptop", 1500.0, 10);
    p1.printInfo();
    p1.buy(3);
    p1.printInfo();
    cout << endl;
    
    return 0;
}