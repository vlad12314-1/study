#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    // Задание 1
    vector<int> v1 = {3, -1, 4, -5, 2, -8};
    int neg_count = 0;
    for (int x : v1) {
        if (x < 0) neg_count++;
    }
    cout << "1. Отрицательных: " << neg_count << endl;
    
    // Задание 2
    vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < v2.size(); i++) {
        if (v2[i] % 2 == 0) {
            v2.erase(v2.begin() + i);
            i--;  // возвращаемся назад, так как вектор изменился
        }
    }
    cout << "2. Без четных: ";
    for (int x : v2) cout << x << " ";
    cout << endl;
    
    // Задание 3
    vector<int> v3 = {1, 2, 3, 4, 5};
    bool positive = true;
    for (int x : v3) {
        if (x <= 0) positive = false;
    }
    cout << "3. Все положительные? " << (positive ? "Да" : "Нет") << endl;
    
    // Задание 4
    vector<int> v4 = {5, 2, 8, 1, 9};
    int min_pos = 0;
    for (int i = 1; i < v4.size(); i++) {
        if (v4[i] < v4[min_pos]) min_pos = i;
    }
    v4[min_pos] = 0;
    cout << "4. С заменой минимума: ";
    for (int x : v4) cout << x << " ";
    cout << endl;
    
    // Задание 5
    string s = "programming";
    sort(s.begin(), s.end());
    reverse(s.begin(), s.end());
    cout << "5. Обратная сортировка: " << s << endl;
    
    return 0;
}