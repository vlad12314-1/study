import 'package:flutter/material.dart';
import 'package:getwidget/getwidget.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Регистрация',
      theme: ThemeData(
        primarySwatch: Colors.blue,
        useMaterial3: true,
      ),
      home: const RegistrationScreen(),
      debugShowCheckedModeBanner: false,
    );
  }
}

class RegistrationScreen extends StatefulWidget {
  const RegistrationScreen({super.key});

  @override
  State<RegistrationScreen> createState() => _RegistrationScreenState();
}

class _RegistrationScreenState extends State<RegistrationScreen> {
  // Контроллеры для полей ввода
  final TextEditingController _loginController = TextEditingController();
  final TextEditingController _passwordController = TextEditingController();
  final TextEditingController _confirmPasswordController = TextEditingController();

  // Переменные для хранения ошибок валидации
  String? _loginError;
  String? _passwordError;
  String? _confirmPasswordError;

  // Флаг для скрытия/показа пароля
  bool _isPasswordVisible = false;
  bool _isConfirmPasswordVisible = false;

  @override
  void dispose() {
    _loginController.dispose();
    _passwordController.dispose();
    _confirmPasswordController.dispose();
    super.dispose();
  }

  /// Валидация логина
  void _validateLogin(String value) {
    setState(() {
      if (value.isEmpty) {
        _loginError = 'Логин не может быть пустым';
      } else if (value.length < 4) {
        _loginError = 'Логин должен содержать минимум 4 символа';
      } else if (value.length > 20) {
        _loginError = 'Логин не может быть длиннее 20 символов';
      } else if (!RegExp(r'^[a-zA-Z0-9_]+$').hasMatch(value)) {
        _loginError = 'Логин может содержать только буквы, цифры и знак подчеркивания';
      } else {
        _loginError = null;
      }
    });
  }

  /// Валидация пароля
  void _validatePassword(String value) {
    setState(() {
      if (value.isEmpty) {
        _passwordError = 'Пароль не может быть пустым';
      } else if (value.length < 8) {
        _passwordError = 'Пароль должен содержать минимум 8 символов';
      } else if (!RegExp(r'[A-Z]').hasMatch(value)) {
        _passwordError = 'Пароль должен содержать хотя бы одну заглавную букву';
      } else if (!RegExp(r'[0-9]').hasMatch(value)) {
        _passwordError = 'Пароль должен содержать хотя бы одну цифру';
      } else if (!RegExp(r'[!@#$%^&*(),.?":{}|<>]').hasMatch(value)) {
        _passwordError = 'Пароль должен содержать хотя бы один специальный символ (!@#$%^&* и т.д.)';
      } else {
        _passwordError = null;
      }
    });
    
    // Если пароль изменился, проверяем и подтверждение пароля
    _validateConfirmPassword(_confirmPasswordController.text);
  }

  /// Валидация подтверждения пароля
  void _validateConfirmPassword(String value) {
    setState(() {
      if (_passwordController.text != value) {
        _confirmPasswordError = 'Пароли не совпадают';
      } else if (value.isEmpty) {
        _confirmPasswordError = 'Подтвердите пароль';
      } else {
        _confirmPasswordError = null;
      }
    });
  }

  /// Функция регистрации
  void _register() {
    // Проверяем все поля перед регистрацией
    _validateLogin(_loginController.text);
    _validatePassword(_passwordController.text);
    _validateConfirmPassword(_confirmPasswordController.text);

    // Если ошибок нет, регистрируем пользователя
    if (_loginError == null && _passwordError == null && _confirmPasswordError == null) {
      GFToast.show(
        'Регистрация успешно выполнена!\nДобро пожаловать, ${_loginController.text}!',
        context,
        toastPosition: GFToastPosition.BOTTOM,
        backgroundColor: Colors.green,
        textColor: Colors.white,
        duration: const Duration(seconds: 3),
      );
    } else {
      GFToast.show(
        'Пожалуйста, исправьте ошибки в форме',
        context,
        toastPosition: GFToastPosition.BOTTOM,
        backgroundColor: Colors.red,
        textColor: Colors.white,
        duration: const Duration(seconds: 3),
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        decoration: const BoxDecoration(
          gradient: LinearGradient(
            begin: Alignment.topLeft,
            end: Alignment.bottomRight,
            colors: [
              Color(0xFF667eea),
              Color(0xFF764ba2),
            ],
          ),
        ),
        child: SafeArea(
          child: Center(
            child: SingleChildScrollView(
              padding: const EdgeInsets.all(24.0),
              child: Card(
                elevation: 8,
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(20),
                ),
                child: Padding(
                  padding: const EdgeInsets.all(32.0),
                  child: Column(
                    mainAxisSize: MainAxisSize.min,
                    children: [
                      // Заголовок
                      const Icon(
                        Icons.person_add_alt_1,
                        size: 80,
                        color: Color(0xFF667eea),
                      ),
                      const SizedBox(height: 16),
                      const Text(
                        'Создать аккаунт',
                        style: TextStyle(
                          fontSize: 28,
                          fontWeight: FontWeight.bold,
                          color: Color(0xFF333333),
                        ),
                      ),
                      const SizedBox(height: 8),
                      const Text(
                        'Заполните форму для регистрации',
                        style: TextStyle(
                          fontSize: 14,
                          color: Colors.grey,
                        ),
                      ),
                      const SizedBox(height: 32),

                      // Поле для логина
                      TextField(
                        controller: _loginController,
                        decoration: InputDecoration(
                          labelText: 'Логин',
                          hintText: 'Введите ваш логин',
                          prefixIcon: const Icon(Icons.person),
                          border: OutlineInputBorder(
                            borderRadius: BorderRadius.circular(12),
                          ),
                          errorText: _loginError,
                          errorStyle: const TextStyle(fontSize: 12),
                        ),
                        onChanged: _validateLogin,
                      ),
                      const SizedBox(height: 20),

                      // Поле для пароля
                      TextField(
                        controller: _passwordController,
                        obscureText: !_isPasswordVisible,
                        decoration: InputDecoration(
                          labelText: 'Пароль',
                          hintText: 'Введите пароль',
                          prefixIcon: const Icon(Icons.lock),
                          suffixIcon: IconButton(
                            icon: Icon(
                              _isPasswordVisible
                                  ? Icons.visibility_off
                                  : Icons.visibility,
                            ),
                            onPressed: () {
                              setState(() {
                                _isPasswordVisible = !_isPasswordVisible;
                              });
                            },
                          ),
                          border: OutlineInputBorder(
                            borderRadius: BorderRadius.circular(12),
                          ),
                          errorText: _passwordError,
                          errorStyle: const TextStyle(fontSize: 12),
                        ),
                        onChanged: _validatePassword,
                      ),
                      const SizedBox(height: 20),

                      // Поле для подтверждения пароля
                      TextField(
                        controller: _confirmPasswordController,
                        obscureText: !_isConfirmPasswordVisible,
                        decoration: InputDecoration(
                          labelText: 'Подтверждение пароля',
                          hintText: 'Повторите пароль',
                          prefixIcon: const Icon(Icons.lock_outline),
                          suffixIcon: IconButton(
                            icon: Icon(
                              _isConfirmPasswordVisible
                                  ? Icons.visibility_off
                                  : Icons.visibility,
                            ),
                            onPressed: () {
                              setState(() {
                                _isConfirmPasswordVisible =
                                    !_isConfirmPasswordVisible;
                              });
                            },
                          ),
                          border: OutlineInputBorder(
                            borderRadius: BorderRadius.circular(12),
                          ),
                          errorText: _confirmPasswordError,
                          errorStyle: const TextStyle(fontSize: 12),
                        ),
                        onChanged: _validateConfirmPassword,
                        onSubmitted: (_) => _register(),
                      ),
                      const SizedBox(height: 32),

                      // Кнопка регистрации
                      SizedBox(
                        width: double.infinity,
                        height: 50,
                        child: ElevatedButton(
                          onPressed: _register,
                          style: ElevatedButton.styleFrom(
                            backgroundColor: const Color(0xFF667eea),
                            foregroundColor: Colors.white,
                            shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(12),
                            ),
                            elevation: 2,
                          ),
                          child: const Text(
                            'Зарегистрироваться',
                            style: TextStyle(
                              fontSize: 16,
                              fontWeight: FontWeight.bold,
                            ),
                          ),
                        ),
                      ),

                      const SizedBox(height: 16),

                      // Информация о требованиях
                      Container(
                        padding: const EdgeInsets.all(12),
                        decoration: BoxDecoration(
                          color: Colors.grey.shade50,
                          borderRadius: BorderRadius.circular(12),
                        ),
                        child: Column(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: [
                            const Text(
                              'Требования к паролю:',
                              style: TextStyle(
                                fontSize: 12,
                                fontWeight: FontWeight.bold,
                                color: Colors.grey,
                              ),
                            ),
                            const SizedBox(height: 4),
                            Text(
                              '• Минимум 8 символов\n• Хотя бы одна заглавная буква\n• Хотя бы одна цифра\n• Хотя бы один специальный символ (!@#\$%^&*)',
                              style: TextStyle(
                                fontSize: 11,
                                color: Colors.grey.shade600,
                              ),
                            ),
                            const SizedBox(height: 8),
                            const Text(
                              'Требования к логину:',
                              style: TextStyle(
                                fontSize: 12,
                                fontWeight: FontWeight.bold,
                                color: Colors.grey,
                              ),
                            ),
                            const SizedBox(height: 4),
                            Text(
                              '• От 4 до 20 символов\n• Только буквы, цифры и знак подчеркивания',
                              style: TextStyle(
                                fontSize: 11,
                                color: Colors.grey.shade600,
                              ),
                            ),
                          ],
                        ),
                      ),
                    ],
                  ),
                ),
              ),
            ),
          ),
        ),
      ),
    );
  }
}