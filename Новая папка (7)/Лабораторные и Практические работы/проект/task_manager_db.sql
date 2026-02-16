-- Создание базы данных
CREATE DATABASE task_manager_db;



-- Создание схемы
CREATE SCHEMA app;

-- Создание таблицы задач
CREATE TABLE app.tasks (
    id SERIAL PRIMARY KEY,
    title VARCHAR(150) NOT NULL,
    description TEXT,
    status VARCHAR(30) NOT NULL,
    priority INTEGER NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Добавление тестовых данных
INSERT INTO app.tasks (title, description, status, priority)
VALUES
('Изучить Repository', 'Разобраться с DAL', 'in_progress', 2),
('Сделать практику', 'Написать код', 'todo', 1),
('Повторить SQL', 'Закрепить SELECT и JOIN', 'done', 3);

-- Проверка данных
SELECT * FROM app.tasks;
