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
      home: const MyHomePage(),
    );
  }
}

class MyHomePage extends StatelessWidget {
  const MyHomePage({super.key});

  // Метод для показа диалогового окна
  Future<void> _showMyDialog(BuildContext context) async {
    // Показываем диалог и ожидаем результат
    bool? result = await showDialog<bool>(
      context: context,
      builder: (BuildContext context) {
        return AlertDialog(
          title: const Text('Подтверждение'),
          content: const Text('Вы уверены, что хотите продолжить?'),
          actions: <Widget>[
            TextButton(
              child: const Text('Нет'),
              onPressed: () => Navigator.pop(context, false), // Возвращаем false
            ),
            TextButton(
              child: const Text('Да'),
              onPressed: () => Navigator.pop(context, true), // Возвращаем true
            ),
          ],
        );
      },
    );

    // Обрабатываем результат
    if (result != null) {
      String message = result ? 'Вы выбрали ДА' : 'Вы выбрали НЕТ';
      Color backgroundColor = result ? Colors.green : Colors.red;

      // Показываем тост с результатом
      Fluttertoast.showToast(
        msg: message,
        toastLength: Toast.LENGTH_SHORT,
        gravity: ToastGravity.BOTTOM,
        backgroundColor: backgroundColor,
        textColor: Colors.white,
        fontSize: 16.0,
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Пример AlertDialog'),
      ),
      body: Center(
        child: ElevatedButton(
          onPressed: () => _showMyDialog(context),
          child: const Text('Показать диалог'),
        ),
      ),
    );
  }
}