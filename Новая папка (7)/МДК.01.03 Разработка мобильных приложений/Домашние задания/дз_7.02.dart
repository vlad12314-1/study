import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        body: Center(
          child: Stack(
            alignment: Alignment.center, // выравнивание дочерних элементов по центру
            children: [
              // Картинка трека (вместо неё можно использовать Image.network или Image.asset)
              Container(
                width: 300,
                height: 300,
                color: Colors.blueGrey, // заглушка, имитирующая обложку
                child: const Center(
                  child: Text(
                    'Обложка трека',
                    style: TextStyle(color: Colors.white),
                  ),
                ),
              ),
              // Ряд иконок по центру поверх картинки
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: const [
                  Icon(Icons.skip_previous, size: 40, color: Colors.white),
                  Icon(Icons.play_arrow, size: 40, color: Colors.white),
                  Icon(Icons.skip_next, size: 40, color: Colors.white),
                ],
              ),
            ],
          ),
        ),
      ),
    );
  }
}