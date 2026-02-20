import 'package:flutter/material.dart';

void main() => runApp(const MyApp());

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Like Button Demo',
      theme: ThemeData(primarySwatch: Colors.blue),
      home: const MyHomePage(),
    );
  }
}

class MyHomePage extends StatelessWidget {
  const MyHomePage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Лайк')),
      body: const Center(
        child: MyLikeWidget(),
      ),
    );
  }
}

// Первый класс — неизменяемая часть (StatefulWidget)
class MyLikeWidget extends StatefulWidget {
  const MyLikeWidget({super.key});

  @override
  State<MyLikeWidget> createState() => _MyLikeWidgetState();
}

// Второй класс — изменяемая часть (State)
class _MyLikeWidgetState extends State<MyLikeWidget> {
  int _counter = 0; // текущее состояние: 0 или 1

  void _toggleLike() {
    setState(() {
      // если был 0 → станет 1, если 1 → станет 0
      _counter = _counter == 0 ? 1 : 0;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Column(
      mainAxisAlignment: MainAxisAlignment.center,
      children: [
        GestureDetector(
          onTap: _toggleLike,
          child: Icon(
            Icons.favorite,
            size: 80,
            color: _counter == 1 ? Colors.red : Colors.grey,
          ),
        ),
        const SizedBox(height: 16),
        Text(
          '$_counter',
          style: const TextStyle(fontSize: 24),
        ),
      ],
    );
  }
}