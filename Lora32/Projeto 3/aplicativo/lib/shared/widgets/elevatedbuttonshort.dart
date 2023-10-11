import 'package:flutter/material.dart';

class BotaoCustomizadoShort extends StatelessWidget {

  final VoidCallback onPressed;

  const BotaoCustomizadoShort({Key? key,
    required this.onPressed,
    }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return ElevatedButton(
      onPressed: onPressed,
      style: ElevatedButton.styleFrom(
        backgroundColor: const Color(0xffE2306C),
        minimumSize: const Size(100, 100),
        shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(20)
        ),
      ),
      child: Image.asset('assets/images/seta.png'),
    );
  }
}
