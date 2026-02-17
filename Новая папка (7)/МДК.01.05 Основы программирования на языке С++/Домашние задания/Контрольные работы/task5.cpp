#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept> // для std::runtime_error

int main() {
    std::string input;
    int number;

    std::cout << "Введите число: ";
    std::getline(std::cin, input);

    try {
        // 1. Проверка, является ли ввод числом
        std::stringstream ss(input);
        if (!(ss >> number)) {
            throw std::runtime_error("Ошибка: ввод не является числом!");
        }

        // 2. Проверка на отрицательное число
        if (number < 0) {
            throw std::runtime_error("Ошибка: число отрицательное!");
        }

        // Если все хорошо
        std::cout << "Вы ввели число: " << number << std::endl;

    }
    catch (const std::runtime_error& e) {
        // Перехватываем и выводим сообщение об ошибке
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}