#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    // Задание 1
    std::cout << "=== Задание 1 ===" << std::endl;
    std::vector<int> vec1 = {3, 7, 2, 9, 5, 1, 8, 4, 6, 10};
    
    int sum = std::accumulate(vec1.begin(), vec1.end(), 0);
    std::cout << "Сумма: " << sum << std::endl;
    
    int product = std::accumulate(vec1.begin(), vec1.end(), 1, 
                                  [](int a, int b) { return a * b; });
    std::cout << "Произведение: " << product << std::endl;
    
    // Задание 2
    std::cout << "\n=== Задание 2 ===" << std::endl;
    std::vector<int> vec2(15);
    std::iota(vec2.begin(), vec2.end(), 5);
    
    std::cout << "Вектор: ";
    for (int num : vec2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Задание 3
    std::cout << "\n=== Задание 3 ===" << std::endl;
    std::vector<int> prefix_sums(vec2.size());
    std::partial_sum(vec2.begin(), vec2.end(), prefix_sums.begin());
    
    std::cout << "Префиксные суммы: ";
    for (int num : prefix_sums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}