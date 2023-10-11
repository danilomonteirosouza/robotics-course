import 'package:flutter/material.dart';
import 'package:submarino/app/features/submarino/presentation/pages/splashscreen.dart';
import 'package:submarino/app/features/submarino/submarino_route.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  runApp(
    const MaterialApp(
      title: "Submarino",
      home: SplashScreen(),
      debugShowCheckedModeBanner: false,
      initialRoute: "/",
      onGenerateRoute: RouteGenerator.generateRoute,
    ),
  );
}
