import sys
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication, QMainWindow, QMessageBox
from PyQt5.QtCore import Qt
from game_logic import GuessGame

# Импорт сгенерированного интерфейса (альтернатива: прямой загрузке .ui)
# from ui_mainwindow import Ui_MainWindow

class GuessNumberGame(QMainWindow):
    def __init__(self):
        super().__init__()
        # Загрузка интерфейса из файла .ui
        uic.loadUi('mainwindow.ui', self)
        
        # Инициализация игровой логики
        self.game = GuessGame()
        
        # Находим виджеты (имена должны совпадать с Qt Designer)
        self.input_number = self.findChild(QLineEdit, 'inputNumber')
        self.btn_check = self.findChild(QPushButton, 'btnCheck')
        self.btn_new_game = self.findChild(QPushButton, 'btnNewGame')
        self.label_hint = self.findChild(QLabel, 'labelHint')
        self.label_attempts = self.findChild(QLabel, 'labelAttempts')
        self.label_range = self.findChild(QLabel, 'labelRange')
        
        # Обновляем отображение диапазона
        self.label_range.setText(f"Я загадал число от {self.game.min_num} до {self.game.max_num}.")
        
        # Подключаем сигналы к слотам
        self.btn_check.clicked.connect(self.check_number)
        self.btn_new_game.clicked.connect(self.new_game)
        self.input_number.returnPressed.connect(self.check_number)  # Enter для проверки
        
        # Инициализируем интерфейс
        self.update_attempts_label()
        self.label_hint.setText("Введите число и нажмите 'Проверить'.")
        
    def check_number(self):
        """Обработка нажатия кнопки 'Проверить'"""
        user_input = self.input_number.text()
        if not user_input:
            return
            
        result = self.game.check_guess(user_input)
        self.label_hint.setText(result)
        self.update_attempts_label()
        
        # Очищаем поле ввода, если игра не окончена
        if not self.game.game_over:
            self.input_number.clear()
            self.input_number.setFocus()
        else:
            self.btn_check.setEnabled(False)
            
    def new_game(self):
        """Начало новой игры"""
        self.game.generate_new_number()
        self.input_number.clear()
        self.input_number.setFocus()
        self.label_hint.setText("Введите число и нажмите 'Проверить'.")
        self.update_attempts_label()
        self.btn_check.setEnabled(True)
        
    def update_attempts_label(self):
        """Обновление счетчика попыток"""
        self.label_attempts.setText(f"Попыток: {self.game.attempts}")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = GuessNumberGame()
    window.setWindowTitle("Угадай число!")
    window.show()
    sys.exit(app.exec_())