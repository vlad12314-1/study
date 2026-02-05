#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Создаем вектор для работы
    std::vector<int> numbers = {5, 15, -3, 20, 8, 12, -1, 7, 25, 0};
    
    std::cout << "Исходный вектор: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Задание 1: Количество чисел больше 10
    int countGreaterThan10 = std::count_if(numbers.begin(), numbers.end(), 
        [](int x) { return x > 10; });
    std::cout << "1. Количество чисел больше 10: " << countGreaterThan10 << std::endl;
    
    // Задание 2: Первое отрицательное число
    auto firstNegative = std::find_if(numbers.begin(), numbers.end(), 
        [](int x) { return x < 0; });
    
    if (firstNegative != numbers.end()) {
        std::cout << "2. Первое отрицательное число: " << *firstNegative 
                  << " (позиция: " << std::distance(numbers.begin(), firstNegative) 
                  << ")" << std::endl;
    } else {
        std::cout << "2. Отрицательных чисел не найдено" << std::endl;
    }
    
    // Задание 3: Сортировка по убыванию
    std::sort(numbers.begin(), numbers.end(), 
        [](int a, int b) { return a > b; });
    
    std::cout << "3. Вектор после сортировки по убыванию: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}