import 'package:flutter/material.dart';
import 'package:lottie/lottie.dart';
import 'package:submarino/app/features/submarino/presentation/pages/initial.dart';
import 'package:submarino/app/features/submarino/presentation/pages/splashscreen.dart';

class RouteGenerator {
  static const String root = "/";
  static const String initial = "/initial_screen";

  static Route<dynamic>? generateRoute(RouteSettings settings) {
    switch (settings.name) {
      case root:
        return MaterialPageRoute(builder: (_) => const SplashScreen());
      case initial:
        return MaterialPageRoute(builder: (_) => const InitialScreen());
      default:
        _erroRota();
    }
    return null;
  }

  static Route<dynamic> _erroRota() {
    return MaterialPageRoute(builder: (_) {
      return Scaffold(
        body: Container(
            color: const Color(0xff00ceff),
            child: Column(
              children: <Widget>[
                Expanded(
                    flex: 3,
                    child: Align(
                      alignment: Alignment.bottomCenter,
                      child: Lottie.asset('assets/page_not_found.json'),
                    )),
                const Expanded(
                  flex: 1,
                  child: Align(
                      alignment: Alignment.center,
                      child: SafeArea(
                        child: Text(
                          '\u00a9Smart Student',
                          style: TextStyle(fontSize: 20, color: Colors.grey),
                        ),
                      )),
                ),
              ],
            )),
      );
    });
  }
}
