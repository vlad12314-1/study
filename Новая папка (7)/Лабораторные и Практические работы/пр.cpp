#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Структура для хранения финансовой операции
struct Transaction {
    int id;
    string type;        // "income" или "expense"
    string category;
    double amount;
    string date;
    string description;
};

// Глобальные переменные
vector<Transaction> transactions;
int nextId = 1;

// Прототипы функций
void loadFromFile();
void saveToFile();
void addTransaction();
void viewAllTransactions();
void viewByType();
void viewByDate();
void deleteTransaction();
void showStatistics();
void showMainMenu();
bool isValidDate(const string& date);
bool isValidAmount(double amount);
void clearScreen();

// Функция для загрузки данных из файла
void loadFromFile() {
    ifstream file("finance.txt");
    if (!file.is_open()) {
        cout << "Файл не найден. Будет создан новый файл при сохранении." << endl;
        return;
    }
    
    transactions.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Transaction t;
        string type;
        
        ss >> t.id >> type >> t.category >> t.amount >> t.date;
        getline(ss, t.description);
        
        // Удаляем пробелы в начале описания
        if (!t.description.empty() && t.description[0] == ' ') {
            t.description = t.description.substr(1);
        }
        
        t.type = type;
        transactions.push_back(t);
        
        if (t.id >= nextId) {
            nextId = t.id + 1;
        }
    }
    file.close();
    cout << "Данные загружены из файла. Всего записей: " << transactions.size() << endl;
}

// Функция для сохранения данных в файл
void saveToFile() {
    ofstream file("finance.txt");
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл для сохранения!" << endl;
        return;
    }
    
    for (const auto& t : transactions) {
        file << t.id << " " << t.type << " " << t.category << " " 
             << t.amount << " " << t.date << " " << t.description << endl;
    }
    file.close();
    cout << "Данные сохранены в файл finance.txt" << endl;
}

// Проверка корректности даты
bool isValidDate(const string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    
    int year, month, day;
    char dash1, dash2;
    stringstream ss(date);
    ss >> year >> dash1 >> month >> dash2 >> day;
    
    if (year < 2000 || year > 2030) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    return true;
}

// Проверка корректности суммы
bool isValidAmount(double amount) {
    return amount > 0;
}

// Добавление новой записи
void addTransaction() {
    Transaction t;
    t.id = nextId++;
    
    cout << "\n=== ДОБАВЛЕНИЕ НОВОЙ ЗАПИСИ ===\n";
    
    // Выбор типа операции
    int typeChoice;
    do {
        cout << "Тип операции (1 - Доход, 2 - Расход): ";
        cin >> typeChoice;
        if (typeChoice == 1) {
            t.type = "income";
            break;
        } else if (typeChoice == 2) {
            t.type = "expense";
            break;
        } else {
            cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (true);
    
    // Ввод категории
    cout << "Категория (например: еда, транспорт, зарплата): ";
    cin.ignore();
    getline(cin, t.category);
    
    // Ввод суммы
    do {
        cout << "Сумма: ";
        cin >> t.amount;
        if (!isValidAmount(t.amount)) {
            cout << "Сумма должна быть положительной!\n";
        }
    } while (!isValidAmount(t.amount));
    
    // Ввод даты
    do {
        cout << "Дата (ГГГГ-ММ-ДД): ";
        cin >> t.date;
        if (!isValidDate(t.date)) {
            cout << "Неверный формат даты! Используйте ГГГГ-ММ-ДД\n";
        }
    } while (!isValidDate(t.date));
    
    // Ввод описания
    cout << "Описание (необязательно): ";
    cin.ignore();
    getline(cin, t.description);
    
    transactions.push_back(t);
    cout << "\n✓ Запись успешно добавлена! ID: " << t.id << endl;
    saveToFile();
}

// Просмотр всех операций
void viewAllTransactions() {
    if (transactions.empty()) {
        cout << "\nНет ни одной операции.\n";
        return;
    }
    
    cout << "\n=== ВСЕ ОПЕРАЦИИ ===\n";
    cout << left << setw(5) << "ID" 
         << setw(10) << "Тип" 
         << setw(15) << "Категория"
         << setw(10) << "Сумма" 
         << setw(12) << "Дата" 
         << "Описание\n";
    cout << string(70, '-') << endl;
    
    for (const auto& t : transactions) {
        string typeRu = (t.type == "income") ? "Доход" : "Расход";
        cout << left << setw(5) << t.id
             << setw(10) << typeRu
             << setw(15) << t.category
             << setw(10) << t.amount
             << setw(12) << t.date
             << t.description << endl;
    }
}

// Просмотр по типу
void viewByType() {
    if (transactions.empty()) {
        cout << "\nНет ни одной операции.\n";
        return;
    }
    
    int typeChoice;
    cout << "\n=== ПРОСМОТР ПО ТИПУ ===\n";
    cout << "1 - Только доходы\n";
    cout << "2 - Только расходы\n";
    cout << "Выберите тип: ";
    cin >> typeChoice;
    
    string typeFilter = (typeChoice == 1) ? "income" : "expense";
    string typeRu = (typeChoice == 1) ? "Доходы" : "Расходы";
    
    cout << "\n=== " << typeRu << " ===\n";
    cout << left << setw(5) << "ID" 
         << setw(15) << "Категория"
         << setw(10) << "Сумма" 
         << setw(12) << "Дата" 
         << "Описание\n";
    cout << string(60, '-') << endl;
    
    bool found = false;
    for (const auto& t : transactions) {
        if (t.type == typeFilter) {
            cout << left << setw(5) << t.id
                 << setw(15) << t.category
                 << setw(10) << t.amount
                 << setw(12) << t.date
                 << t.description << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "Нет операций этого типа.\n";
    }
}

// Просмотр за период
void viewByDate() {
    if (transactions.empty()) {
        cout << "\nНет ни одной операции.\n";
        return;
    }
    
    string startDate, endDate;
    cout << "\n=== ПРОСМОТР ЗА ПЕРИОД ===\n";
    cout << "Введите начальную дату (ГГГГ-ММ-ДД): ";
    cin >> startDate;
    cout << "Введите конечную дату (ГГГГ-ММ-ДД): ";
    cin >> endDate;
    
    cout << "\n=== ОПЕРАЦИИ ЗА ПЕРИОД " << startDate << " - " << endDate << " ===\n";
    cout << left << setw(5) << "ID" 
         << setw(10) << "Тип" 
         << setw(15) << "Категория"
         << setw(10) << "Сумма" 
         << "Описание\n";
    cout << string(60, '-') << endl;
    
    bool found = false;
    for (const auto& t : transactions) {
        if (t.date >= startDate && t.date <= endDate) {
            string typeRu = (t.type == "income") ? "Доход" : "Расход";
            cout << left << setw(5) << t.id
                 << setw(10) << typeRu
                 << setw(15) << t.category
                 << setw(10) << t.amount
                 << t.description << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "Нет операций за указанный период.\n";
    }
}

// Удаление записи
void deleteTransaction() {
    if (transactions.empty()) {
        cout << "\nНет ни одной операции для удаления.\n";
        return;
    }
    
    int id;
    cout << "\n=== УДАЛЕНИЕ ЗАПИСИ ===\n";
    viewAllTransactions();
    cout << "Введите ID записи для удаления: ";
    cin >> id;
    
    auto it = find_if(transactions.begin(), transactions.end(), 
                      [id](const Transaction& t) { return t.id == id; });
    
    if (it != transactions.end()) {
        cout << "Удалить запись \"" << it->category << " - " << it->amount << " руб.\"? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            transactions.erase(it);
            cout << "✓ Запись успешно удалена!\n";
            saveToFile();
        } else {
            cout << "Удаление отменено.\n";
        }
    } else {
        cout << "Запись с ID " << id << " не найдена!\n";
    }
}

// Статистика
void showStatistics() {
    if (transactions.empty()) {
        cout << "\nНет данных для статистики.\n";
        return;
    }
    
    double totalIncome = 0;
    double totalExpense = 0;
    vector<pair<string, double>> incomeByCategory;
    vector<pair<string, double>> expenseByCategory;
    
    for (const auto& t : transactions) {
        if (t.type == "income") {
            totalIncome += t.amount;
            
            // Поиск категории для доходов
            auto it = find_if(incomeByCategory.begin(), incomeByCategory.end(),
                              [&](const pair<string, double>& p) { return p.first == t.category; });
            if (it != incomeByCategory.end()) {
                it->second += t.amount;
            } else {
                incomeByCategory.push_back({t.category, t.amount});
            }
        } else {
            totalExpense += t.amount;
            
            // Поиск категории для расходов
            auto it = find_if(expenseByCategory.begin(), expenseByCategory.end(),
                              [&](const pair<string, double>& p) { return p.first == t.category; });
            if (it != expenseByCategory.end()) {
                it->second += t.amount;
            } else {
                expenseByCategory.push_back({t.category, t.amount});
            }
        }
    }
    
    double balance = totalIncome - totalExpense;
    
    cout << "\n=== ФИНАНСОВАЯ СТАТИСТИКА ===\n";
    cout << fixed << setprecision(2);
    cout << "Общая сумма доходов: " << totalIncome << " руб.\n";
    cout << "Общая сумма расходов: " << totalExpense << " руб.\n";
    cout << "Текущий баланс: " << balance << " руб.\n";
    
    // Статистика по категориям доходов
    if (!incomeByCategory.empty()) {
        cout << "\n--- Доходы по категориям ---\n";
        for (const auto& cat : incomeByCategory) {
            cout << "  " << cat.first << ": " << cat.second << " руб.\n";
        }
    }
    
    // Статистика по категориям расходов
    if (!expenseByCategory.empty()) {
        cout << "\n--- Расходы по категориям ---\n";
        for (const auto& cat : expenseByCategory) {
            cout << "  " << cat.first << ": " << cat.second << " руб.\n";
        }
    }
}

// Очистка экрана
void clearScreen() {
    system("clear");  // Для Linux/Mac
    // system("cls"); // Для Windows
}

// Главное меню
void showMainMenu() {
    cout << "\n╔══════════════════════════════════╗\n";
    cout << "║     УЧЕТ ЛИЧНЫХ ФИНАНСОВ        ║\n";
    cout << "╠══════════════════════════════════╣\n";
    cout << "║ 1. Добавить операцию            ║\n";
    cout << "║ 2. Просмотреть все операции     ║\n";
    cout << "║ 3. Просмотреть по типу          ║\n";
    cout << "║ 4. Просмотреть за период        ║\n";
    cout << "║ 5. Удалить операцию             ║\n";
    cout << "║ 6. Показать статистику          ║\n";
    cout << "║ 7. Сохранить и выйти            ║\n";
    cout << "╚══════════════════════════════════╝\n";
    cout << "Выберите действие: ";
}

// Главная функция
int main() {
    cout << "Добро пожаловать в программу учета финансов!\n";
    loadFromFile();
    
    int choice;
    do {
        showMainMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                addTransaction();
                break;
            case 2:
                viewAllTransactions();
                break;
            case 3:
                viewByType();
                break;
            case 4:
                viewByDate();
                break;
            case 5:
                deleteTransaction();
                break;
            case 6:
                showStatistics();
                break;
            case 7:
                saveToFile();
                cout << "До свидания!\n";
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
        }
        
        if (choice != 7) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 7);
    
    return 0;
}