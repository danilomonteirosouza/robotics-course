import 'package:flutter/material.dart';
import 'package:mqtt_connection_hivemq/homepage.dart';

void main(){
  runApp(
    const MaterialApp(
      home: HomePage(),
      debugShowCheckedModeBanner: false,
    ),
  );
}