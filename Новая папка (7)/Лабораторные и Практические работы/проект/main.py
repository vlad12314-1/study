from db.task_repository import TaskRepository

# Инициализация репозитория и состояния
repo = TaskRepository()
tasks_df = repo.get_all()


def refresh_tasks():
    """Обновляет состояние данных"""
    global tasks_df
    tasks_df = repo.get_all()


def show_all_tasks():
    """Показывает все задачи"""
    if tasks_df.empty:
        print("Нет задач в базе данных.")
    else:
        print("\nВсе задачи:")
        print(tasks_df.to_string(index=False))
    print()


def add_task():
    """Добавляет новую задачу"""
    print("\nДобавление новой задачи:")
    title = input("Название задачи: ").strip()
    if not title:
        print("Название задачи обязательно!")
        return

    description = input("Описание (можно пропустить): ").strip() or None
    status = input("Статус (todo/in_progress/done): ").strip()
    while status not in ['todo', 'in_progress', 'done']:
        status = input("Введите корректный статус (todo/in_progress/done): ").strip()

    try:
        priority = int(input("Приоритет (целое число): "))
    except ValueError:
        print("Приоритет должен быть числом!")
        return

    if repo.add(title, description, status, priority):
        refresh_tasks()


def update_task_status():
    """Обновляет статус задачи"""
    print("\nОбновление статуса задачи:")
    try:
        task_id = int(input("ID задачи: "))
    except ValueError:
        print("ID должен быть числом!")
        return

    new_status = input("Новый статус (todo/in_progress/done): ").strip()
    while new_status not in ['todo', 'in_progress', 'done']:
        new_status = input("Введите корректный статус (todo/in_progress/done): ").strip()

    if repo.update_status(task_id, new_status):
        refresh_tasks()


def delete_task():
    """Удаляет задачу"""
    print("\nУдаление задачи:")
    try:
        task_id = int(input("ID задачи: "))
    except ValueError:
        print("ID должен быть числом!")
        return

    if repo.delete(task_id):
        refresh_tasks()


def filter_by_status():
    """Фильтрует задачи по статусу"""
    print("\nФильтр по статусу:")
    status = input("Статус (todo/in_progress/done): ").strip()
    while status not in ['todo', 'in_progress', 'done']:
        status = input("Введите корректный статус (todo/in_progress/done): ").strip()

    filtered_df = repo.get_by_status(status)
    if filtered_df.empty:
        print("Нет задач с таким статусом.")
    else:
        print(f"\nЗадачи со статусом '{status}':")
        print(filtered_df.to_string(index=False))
    print()


def main():
    """Основное меню приложения"""
    while True:
        print("=" * 50)
        print("TASK MANAGER")
        print("=" * 50)
        print("1 — Показать все задачи")
        print("2 — Добавить задачу")
        print("3 — Обновить статус")
        print("4 — Удалить задачу")
        print("5 — Фильтр по статусу")
        print("0 — Выход")
        print("-" * 50)

        choice = input("Выберите действие (0-5): ").