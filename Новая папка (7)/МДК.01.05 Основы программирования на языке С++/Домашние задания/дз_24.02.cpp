// Инвентарь

/*
Данное приложение предназначено для простого взаимодействия с RPG-инвентарем:
1. Просмотр инвентаря;
2. Фильтрация данных внутри инвентаря.
*/

/*
Из чего состоит инвентарь:
- Предметы со следующими характеристиками:
        - Редкость предмета;
        - Стоимость предмета;
        - Тип предмета;
        - Вес предмета.
*/

#include <iostream>
#include <vector>

using namespace std;

enum ItemType {
    armor,
    weapon,
    potion,
    other
};

enum Rarity {
    usually,
    rare,
    epic,
    legendary
};

/// Распаковка типа предмета
string typeToString(ItemType type) {
    switch (type) {
    case armor: return "Броня";
    case weapon: return "Оружие";
    case potion: return "Зелье";
    case other: return "Другое";
    }
    return "Такого типа не существует";
};

// Распаковка редкости предмета
string rarityToString(Rarity rarity) {
    switch (rarity) {
    case usually: return "Обычный";
    case rare: return "Редкий";
    case epic: return "Эпический";
    case legendary: return "Легендарный";
    }
    return "Такой редкости не существует";
};


struct Item {
    int id;
    string name;
    ItemType type;
    Rarity rarity;
    int value;
    double weight;
};

// Получение текущей вместимости инвенторя
double getTotalWeight(const vector<Item>& inventory) {
    double total = 0;
    for (const auto& item : inventory) {
        total += item.weight;
    }
    return total;
};

void listItems(const vector<Item>& inventory, double maxWeigth) {
    cout << "\n=== ИНВЕНТАРЬ ===" << endl;
    cout << "ID | Название | Тип | Редкость | Цена | Вес" << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& item : inventory) {
        cout << item.id << " | " << item.name << " | "
            << typeToString(item.type) << " | " << rarityToString(item.rarity) << " | " << item.value << " | " << item.weight << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "Общий вес: " << getTotalWeight(inventory) << "/" << maxWeigth << endl;
    cout << "========================================\n" << endl;
}

// Добавление предмета в инвентарь
bool addItem(vector<Item>& inventory, const Item& item, const double& maxWeight) {
    if (getTotalWeight(inventory) + item.weight > maxWeight) {
        cout << "Инвентарь переполнен!!!" << endl;
        return false;
    }
    inventory.push_back(item);
    cout << "Предмет успешно добавлен" << endl;
    return true;
};

// Удаление предмета из инвентаря по ID
bool removeItem(vector<Item>& inventory, int itemId) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->id == itemId) {
            cout << "Предмет \"" << it->name << "\" удален из инвентаря" << endl;
            inventory.erase(it);
            return true;
        }
    }
    cout << "Предмет с ID " << itemId << " не найден в инвентаре" << endl;
    return false;
}

int main() {

    cout << endl;
    vector<Item> inventory;
    double maxWeight = 100.0;

    // Создаем предметы
    Item sword = { 1, "Стальной меч", weapon, usually, 50, 5.0 };
    Item dragonArmor = { 2, "Драконья броня", armor, epic, 2500, 52.0 };
    Item healthPotion = { 3, "Лечебное зелье", potion, rare, 200, 1.0 };

    addItem(inventory, sword, maxWeight);
    addItem(inventory, dragonArmor, maxWeight);
    addItem(inventory, healthPotion, maxWeight);

    listItems(inventory, maxWeight);

    // Пример использования функции удаления
    cout << "Пытаемся удалить предмет с ID 2:" << endl;
    removeItem(inventory, 2);

    listItems(inventory, maxWeight);

    cout << "Пытаемся удалить несуществующий предмет с ID 5:" << endl;
    removeItem(inventory, 5);

    listItems(inventory, maxWeight);
}

// 2. Удаление предмета. сделай