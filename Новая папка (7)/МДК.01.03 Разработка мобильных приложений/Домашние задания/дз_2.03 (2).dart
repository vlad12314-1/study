import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Навигация наложением',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const LoginScreen(),
    );
  }
}

// Первый экран - экран входа
class LoginScreen extends StatefulWidget {
  const LoginScreen({super.key});

  @override
  State<LoginScreen> createState() => _LoginScreenState();
}

class _LoginScreenState extends State<LoginScreen> {
  // Контроллеры для полей ввода
  final TextEditingController _loginController = TextEditingController();
  final TextEditingController _passwordController = TextEditingController();
  
  // Правильные логин и пароль
  final String _correctLogin = 'user';
  final String _correctPassword = 'user123';

  // Функция проверки логина и пароля
  void _login() {
    String login = _loginController.text;
    String password = _passwordController.text;
    
    if (login == _correctLogin && password == _correctPassword) {
      // Если данные верны - переходим на второй экран
      Navigator.push(
        context,
        MaterialPageRoute(builder: (context) => const ImageScreen()),
      );
    } else {
      // Если данные неверны - показываем тост
      Fluttertoast.showToast(
        msg: "Неверные логин или пароль",
        toastLength: Toast.LENGTH_SHORT,
        gravity: ToastGravity.BOTTOM,
        backgroundColor: Colors.red,
        textColor: Colors.white,
        fontSize: 16.0,
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Вход в приложение'),
        centerTitle: true,
      ),
      body: Padding(
        padding: const EdgeInsets.all(20.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // Поле ввода логина
            TextField(
              controller: _loginController,
              decoration: InputDecoration(
                labelText: 'Логин',
                border: OutlineInputBorder(
                  borderRadius: BorderRadius.circular(10),
                ),
                prefixIcon: const Icon(Icons.person),
              ),
              onChanged: (value) {
                // Реагируем на изменения в реальном времени
                print('Логин изменен: $value');
              },
              onSubmitted: (value) {
                // При нажатии "Готово" на клавиатуре
                print('Ввод логина завершен: $value');
              },
            ),
            
            const SizedBox(height: 20),
            
            // Поле ввода пароля
            TextField(
              controller: _passwordController,
              obscureText: true,
              decoration: InputDecoration(
                labelText: 'Пароль',
                border: OutlineInputBorder(
                  borderRadius: BorderRadius.circular(10),
                ),
                prefixIcon: const Icon(Icons.lock),
              ),
              onChanged: (value) {
                print('Пароль изменен');
              },
              onSubmitted: (value) {
                _login(); // Можно выполнять вход при нажатии "Готово"
              },
            ),
            
            const SizedBox(height: 30),
            
            // Кнопка входа
            ElevatedButton(
              onPressed: _login,
              style: ElevatedButton.styleFrom(
                minimumSize: const Size(double.infinity, 50),
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(10),
                ),
              ),
              child: const Text(
                'Войти',
                style: TextStyle(fontSize: 18),
              ),
            ),
          ],
        ),
      ),
    );
  }

  @override
  void dispose() {
    // Освобождаем ресурсы контроллеров
    _loginController.dispose();
    _passwordController.dispose();
    super.dispose();
  }
}

// Второй экран - экран с картинкой
class ImageScreen extends StatelessWidget {
  const ImageScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Изображение'),
        centerTitle: true,
        // Кнопка возврата на предыдущий экран
        leading: IconButton(
          icon: const Icon(Icons.arrow_back),
          onPressed: () {
            Navigator.pop(context); // Возвращаемся на первый экран
          },
        ),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // Картинка из интернета (можно заменить на любую другую)
            Image.network(
              'https://flutter.github.io/assets-for-api-docs/assets/widgets/owl.jpg',
              width: 300,
              height: 300,
              fit: BoxFit.cover,
            ),
            const SizedBox(height: 20),
            const Text(
              'Добро пожаловать!',
              style: TextStyle(
                fontSize: 24,
                fontWeight: FontWeight.bold,
              ),
            ),
          ],
        ),
      ),
    );
  }
}