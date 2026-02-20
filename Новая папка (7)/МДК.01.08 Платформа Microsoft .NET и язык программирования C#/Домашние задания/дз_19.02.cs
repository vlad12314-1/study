using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static Dictionary<string, int> shopItems = new Dictionary<string, int>()
    {
        {"Health Potion", 50},
        {"Mana Potion", 75},
        {"Sword", 200},
        {"Shield", 150}
    };

    static void Main()
    {
        while (true)
        {
            Console.WriteLine("\n=== ИГРОВОЙ МАГАЗИН ===");
            Console.WriteLine("1. Показать все товары");
            Console.WriteLine("2. Добавить товар");
            Console.WriteLine("3. Удалить товар");
            Console.WriteLine("4. Заменить товар");
            Console.WriteLine("5. Посчитать стоимость покупки");
            Console.WriteLine("6. Выход");
            Console.Write("Выберите действие: ");

            string choice = Console.ReadLine();

            switch (choice)
            {
                case "1":
                    ShowItems();
                    break;
                case "2":
                    AddItem();
                    break;
                case "3":
                    RemoveItem();
                    break;
                case "4":
                    ReplaceItem();
                    break;
                case "5":
                    CalculatePrice();
                    break;
                case "6":
                    Console.WriteLine("До свидания!");
                    return;
                default:
                    Console.WriteLine("Неверный выбор!");
                    break;
            }
        }
    }

    static void ShowItems()
    {
        Console.WriteLine("\n--- Товары в магазине ---");
        if (shopItems.Count == 0)
        {
            Console.WriteLine("Магазин пуст!");
            return;
        }

        int index = 1;
        foreach (var item in shopItems)
        {
            Console.WriteLine($"{index}. {item.Key} - {item.Value} монет");
            index++;
        }
    }

    static void AddItem()
    {
        Console.Write("\nВведите название товара: ");
        string name = Console.ReadLine();

        if (shopItems.ContainsKey(name))
        {
            Console.WriteLine("Такой товар уже есть!");
            return;
        }

        Console.Write("Введите цену товара: ");
        if (int.TryParse(Console.ReadLine(), out int price) && price > 0)
        {
            shopItems.Add(name, price);
            Console.WriteLine($"Товар '{name}' добавлен!");
        }
        else
        {
            Console.WriteLine("Некорректная цена!");
        }
    }

    static void RemoveItem()
    {
        if (shopItems.Count == 0)
        {
            Console.WriteLine("Магазин пуст!");
            return;
        }

        ShowItems();
        Console.Write("\nВведите название товара для удаления: ");
        string name = Console.ReadLine();

        if (shopItems.Remove(name))
        {
            Console.WriteLine($"Товар '{name}' удален!");
        }
        else
        {
            Console.WriteLine("Товар не найден!");
        }
    }

    static void ReplaceItem()
    {
        if (shopItems.Count == 0)
        {
            Console.WriteLine("Магазин пуст!");
            return;
        }

        ShowItems();
        Console.Write("\nВведите название товара для замены: ");
        string oldName = Console.ReadLine();

        if (!shopItems.ContainsKey(oldName))
        {
            Console.WriteLine("Товар не найден!");
            return;
        }

        Console.Write("Введите новое название: ");
        string newName = Console.ReadLine();

        Console.Write("Введите новую цену: ");
        if (int.TryParse(Console.ReadLine(), out int newPrice) && newPrice > 0)
        {
            // Удаляем старый товар и добавляем новый
            shopItems.Remove(oldName);
            shopItems.Add(newName, newPrice);
            Console.WriteLine($"Товар заменен на '{newName}' - {newPrice} монет!");
        }
        else
        {
            Console.WriteLine("Некорректная цена!");
        }
    }

    static void CalculatePrice()
    {
        if (shopItems.Count == 0)
        {
            Console.WriteLine("Магазин пуст!");
            return;
        }

        ShowItems();
        Console.Write("\nВведите название товара: ");
        string name = Console.ReadLine();

        if (!shopItems.ContainsKey(name))
        {
            Console.WriteLine("Товар не найден!");
            return;
        }

        Console.Write("Введите количество: ");
        if (int.TryParse(Console.ReadLine(), out int quantity) && quantity > 0)
        {
            int total = shopItems[name] * quantity;
            Console.WriteLine($"Стоимость {quantity} x {name} = {total} монет");
        }
        else
        {
            Console.WriteLine("Некорректное количество!");
        }
    }
}