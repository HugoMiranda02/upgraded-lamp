import 'package:flutter/material.dart';
import 'dart:io';
import 'dart:convert';
import 'package:flutter/services.dart';

void main() {
  runApp(MyApp());
}

tcp() async {
  Socket socket = await Socket.connect('192.168.1.111', 8088);
  return socket;
  /* socket.listen((List<int> event) {
    print(utf8.decode(event));
  });

  // send hello
  socket.add(utf8.encode('hello'));

  // wait 5 seconds
  await Future.delayed(Duration(seconds: 5));

  // .. and close the socket
  socket.close(); */
}

class MyApp extends StatefulWidget {
  const MyApp({
    Key? key,
  }) : super(key: key);
  @override
  State<MyApp> createState() => _MyAppState();
}

Future changeColor(int red, int green, int blue) async {
  if (blue < 0 || red < 0 || green < 0) {
    return "O valor deve ser entre 0 e 255!";
  }
  Socket socket = await Socket.connect('192.168.1.111', 8088);
  socket.write('$red,$green,$blue');
  socket.close();
}

class _MyAppState extends State<MyApp> {
  final red = TextEditingController();
  final green = TextEditingController();
  final blue = TextEditingController();
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        title: 'Controle de led',
        theme: ThemeData(
          primaryColor: Colors.red[800],
        ),
        home: Scaffold(
            body: Column(children: [
          Center(
            /* heightFactor: 2,
            widthFactor: 2, */
            child: Column(
              children: <Widget>[
                Text("Vermelho:"),
                SizedBox(height: 20),
                TextField(
                  controller: red,
                  decoration: InputDecoration(
                    focusedBorder: OutlineInputBorder(
                      borderSide: BorderSide(color: Colors.red, width: 5.0),
                    ),
                    enabledBorder: OutlineInputBorder(
                      borderSide: BorderSide(color: Colors.black, width: 5.0),
                    ),
                    hintText: '0 - 255',
                  ),
                  keyboardType: TextInputType.number,
                  inputFormatters: <TextInputFormatter>[
                    FilteringTextInputFormatter.digitsOnly
                  ], // Only numbers can be entered
                ),
                Text("Verde"),
                SizedBox(height: 20),
                TextField(
                  controller: green,
                  decoration: InputDecoration(
                    focusedBorder: OutlineInputBorder(
                      borderSide: BorderSide(color: Colors.green, width: 5.0),
                    ),
                    enabledBorder: OutlineInputBorder(
                      borderSide: BorderSide(color: Colors.black, width: 5.0),
                    ),
                    hintText: '0 - 255',
                  ),
                  keyboardType: TextInputType.number,
                  inputFormatters: <TextInputFormatter>[
                    FilteringTextInputFormatter.digitsOnly
                  ], // Only numbers can be entered
                ),
                Text("Azul"),
                SizedBox(height: 20),
                TextField(
                  controller: blue,
                  decoration: InputDecoration(
                    focusedBorder: OutlineInputBorder(
                      borderSide: BorderSide(color: Colors.blue, width: 5.0),
                    ),
                    enabledBorder: OutlineInputBorder(
                      borderSide: BorderSide(color: Colors.black, width: 5.0),
                    ),
                    hintText: '0 - 255',
                  ),
                  keyboardType: TextInputType.number,
                  inputFormatters: <TextInputFormatter>[
                    FilteringTextInputFormatter.digitsOnly
                  ], // Only numbers can be entered
                ),
                TextButton(
                  child: Text(
                    "Enviar",
                    style: TextStyle(
                        color: Colors.black,
                        fontFamily: "Sans-serif",
                        fontWeight: FontWeight.w500,
                        fontSize: 16),
                  ),
                  style: TextButton.styleFrom(
                      backgroundColor: Colors.red,
                      textStyle: TextStyle(color: Colors.black)),
                  onPressed: () => {
                    changeColor(int.parse(red.text), int.parse(green.text),
                        int.parse(blue.text))
                  },
                ),
              ],
            ),
          )
        ])));
  }
}
