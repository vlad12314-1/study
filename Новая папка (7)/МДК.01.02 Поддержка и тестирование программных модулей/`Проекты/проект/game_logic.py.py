import random

class GuessGame:
    def __init__(self, min_num=1, max_num=100):
        self.min_num = min_num
        self.max_num = max_num
        self.secret_number = None
        self.attempts = 0
        self.game_over = False
        self.generate_new_number()

    def generate_new_number(self):
        """Генерирует новое случайное число"""
        self.secret_number = random.randint(self.min_num, self.max_num)
        self.attempts = 0
        self.game_over = False
        return self.secret_number

    def check_guess(self, user_guess):
        """Проверяет предположение пользователя"""
        if self.game_over:
            return "Игра окончена. Начните новую игру!"

        try:
            guess = int(user_guess)
        except ValueError:
            return "Пожалуйста, введите целое число!"

        self.attempts += 1

        if guess < self.min_num or guess > self.max_num:
            return f"Число должно быть от {self.min_num} до {self.max_num}!"
        elif guess < self.secret_number:
            return "Загаданное число БОЛЬШЕ!"
        elif guess > self.secret_number:
            return "Загаданное число МЕНЬШЕ!"
        else:
            self.game_over = True
            return (f"Поздравляем! Вы угадали число {self.secret_number} "
                    f"за {self.attempts} попыток!")