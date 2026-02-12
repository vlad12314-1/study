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
      title: 'Profile Card',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const ProfileScreen(),
    );
  }
}

class ProfileScreen extends StatelessWidget {
  const ProfileScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: GFAppBar(
        title: const Text('Профиль пользователя'),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: GFCard(
            elevation: 8,
            shape: GFCardShape.rounded,
            color: Colors.white,
            child: Padding(
              padding: const EdgeInsets.all(20.0),
              child: Column(
                mainAxisSize: MainAxisSize.min,
                children: [
                  // Аватар пользователя
                  const GFAvatar(
                    backgroundImage: AssetImage('assets/avatar.png'),
                    // или используйте NetworkImage('https://example.com/avatar.jpg')
                    size: 80,
                  ),
                  const SizedBox(height: 16),
                  
                  // Имя пользователя
                  const Text(
                    'Иван Иванов',
                    style: TextStyle(
                      fontSize: 24,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                  const SizedBox(height: 4),
                  
                  // Должность
                  Text(
                    'Flutter Developer',
                    style: TextStyle(
                      fontSize: 16,
                      color: Colors.grey[600],
                    ),
                  ),
                  const SizedBox(height: 20),
                  
                  // Email
                  GFListTile(
                    avatar: const GFAvatar(
                      backgroundColor: Colors.blue,
                      child: Icon(
                        Icons.email,
                        color: Colors.white,
                        size: 20,
                      ),
                    ),
                    title: const Text(
                      'Email',
                      style: TextStyle(
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                    description: const Text(
                      'ivan.ivanov@example.com',
                      style: TextStyle(
                        color: Colors.grey,
                      ),
                    ),
                  ),
                  
                  // Телефон (дополнительное задание)
                  GFListTile(
                    avatar: const GFAvatar(
                      backgroundColor: Colors.green,
                      child: Icon(
                        Icons.phone,
                        color: Colors.white,
                        size: 20,
                      ),
                    ),
                    title: const Text(
                      'Телефон',
                      style: TextStyle(
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                    description: const Text(
                      '+7 (999) 123-45-67',
                      style: TextStyle(
                        color: Colors.grey,
                      ),
                    ),
                  ),
                  
                  const SizedBox(height: 10),
                  
                  // Кнопка "Редактировать"
                  GFButton(
                    onPressed: () {
                      // Действие при нажатии
                    },
                    text: 'Редактировать профиль',
                    color: Colors.blue,
                    fullWidthButton: true,
                    shape: GFButtonShape.pills,
                  ),
                ],
              ),
            ),
          ),
        ),
      ),
    );
  }
}