#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>

int main() {
    std::string input = "apple,banana,orange,apple,kiwi";
    std::vector<std::string> words;
    std::stringstream ss(input);
    std::string item;

    // 1. Разбиваем строку по запятой
    while (std::getline(ss, item, ',')) {
        words.push_back(item);
    }

    // 2. Удаляем повторяющиеся слова (используем множество для фильтрации)
    std::set<std::string> uniqueSet(words.begin(), words.end());
    words.assign(uniqueSet.begin(), uniqueSet.end());

    // 3. Сортируем в алфавитном порядке (set уже хранит отсортированными, но на всякий случай)
    // std::sort(words.begin(), words.end()); // Раскомментировать, если бы мы не использовали set

    // 4. Выводим результат
    std::cout << "Результат: ";
    for (size_t i = 0; i < words.size(); ++i) {
        std::cout << words[i];
        if (i != words.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}