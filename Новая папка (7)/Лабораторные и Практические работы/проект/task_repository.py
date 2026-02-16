from db.connection import get_connection
import pandas as pd
from sqlalchemy.exc import SQLAlchemyError


class TaskRepository:
    def __init__(self):
        self.engine = get_connection()

    def get_all(self):
        """
        Возвращает все задачи в виде DataFrame
        """
        try:
            query = "SELECT * FROM app.tasks ORDER BY id"
            return pd.read_sql(query, self.engine)
        except Exception as e:
            print(f"Ошибка при получении данных: {e}")
            return pd.DataFrame()

    def get_by_status(self, status):
        """
        Фильтрует задачи по статусу
        """
        try:
            query = "SELECT * FROM app.tasks WHERE status = %s ORDER BY id"
            return pd.read_sql(query, self.engine, params=[status])
        except Exception as e:
            print(f"Ошибка при фильтрации по статусу: {e}")
            return pd.DataFrame()

    def add(self, title, description, status, priority):
        """
        Добавляет новую задачу
        """
        try:
            with self.engine.connect() as conn:
                query = """
                INSERT INTO app.tasks (title, description, status, priority) 
                VALUES (%s, %s, %s, %s)
                """
                conn.execute(query, [title, description, status, priority])
                conn.commit()
                print("Задача успешно добавлена!")
                return True
        except SQLAlchemyError as e:
            print(f"Ошибка при добавлении задачи: {e}")
            return False

    def update_status(self, task_id, new_status):
        """
        Обновляет статус задачи
        """
        try:
            with self.engine.connect() as conn:
                query = "UPDATE app.tasks SET status = %s WHERE id = %s"
                result = conn.execute(query, [new_status, task_id])
                conn.commit()

                if result.rowcount == 0:
                    print("Задача не найдена!")
                    return False
                else:
                    print("Статус задачи обновлен!")
                    return True
        except SQLAlchemyError as e:
            print(f"Ошибка при обновлении статуса: {e}")
            return False

    def delete(self, task_id):
        """
        Удаляет задачу по ID
        """
        try:
            with self.engine.connect() as conn:
                query = "DELETE FROM app.tasks WHERE id = %s"
                result = conn.execute(query, [task_id])
                conn.commit()

                if result.rowcount == 0:
                    print("Задача не найдена!")
                    return False
                else:
                    print("Задача удалена!")
                    return True
        except SQLAlchemyError as e:
            print(f"Ошибка при удалении задачи: {e}")
            return False
