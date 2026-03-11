using System;
using System.Collections.Generic;

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
            Console.WriteLine("1 - Показать все товары");
            Console.WriteLine("2 - Добавить товар");
            Console.WriteLine("3 - Удалить товар");
            Console.WriteLine("4 - Заменить товар");
            Console.WriteLine("5 - Посчитать стоимость");
            Console.WriteLine("6 - Выйти");
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
                    return;
                default:
                    Console.WriteLine("Неверный выбор!");
                    break;
            }
        }
    }

    static void ShowItems()
    {
        Console.WriteLine("\n--- ТОВАРЫ ---");
        if (shopItems.Count == 0)
        {
            Console.WriteLine("Магазин пуст");
            return;
        }

        int number = 1;
        foreach (var item in shopItems)
        {
            Console.WriteLine($"{number}. {item.Key} - {item.Value} монет");
            number++;
        }
    }

    static void AddItem()
    {
        Console.Write("Введите название товара: ");
        string name = Console.ReadLine();
        
        if (shopItems.ContainsKey(name))
        {
            Console.WriteLine("Такой товар уже есть!");
            return;
        }

        Console.Write("Введите цену: ");
        if (int.TryParse(Console.ReadLine(), out int price))
        {
            shopItems.Add(name, price);
            Console.WriteLine("Товар добавлен!");
        }
        else
        {
            Console.WriteLine("Неверная цена!");
        }
    }

    static void RemoveItem()
    {
        ShowItems();
        if (shopItems.Count == 0) return;

        Console.Write("Введите название товара для удаления: ");
        string name = Console.ReadLine();

        if (shopItems.Remove(name))
        {
            Console.WriteLine("Товар удален!");
        }
        else
        {
            Console.WriteLine("Товар не найден!");
        }
    }

    static void ReplaceItem()
    {
        ShowItems();
        if (shopItems.Count == 0) return;

        Console.Write("Введите название товара для замены: ");
        string oldName = Console.ReadLine();

        if (!shopItems.ContainsKey(oldName))
        {
            Console.WriteLine("Товар не найден!");
            return;
        }

        Console.Write("Введите новое название: ");
        string newName = Console.ReadLine();
        
        Console.Write("Введите новую цену: ");
        if (int.TryParse(Console.ReadLine(), out int newPrice))
        {
            shopItems.Remove(oldName);
            shopItems.Add(newName, newPrice);
            Console.WriteLine("Товар заменен!");
        }
        else
        {
            Console.WriteLine("Неверная цена!");
        }
    }

    static void CalculatePrice()
    {
        ShowItems();
        if (shopItems.Count == 0) return;

        Console.Write("Введите название товара: ");
        string name = Console.ReadLine();

        if (!shopItems.ContainsKey(name))
        {
            Console.WriteLine("Товар не найден!");
            return;
        }

        Console.Write("Введите количество: ");
        if (int.TryParse(Console.ReadLine(), out int count) && count > 0)
        {
            int total = shopItems[name] * count;
            Console.WriteLine($"Общая стоимость: {total} монет");
        }
        else
        {
            Console.WriteLine("Неверное количество!");
        }
    }
}