import 'package:flutter/material.dart';

class BotaoCustomizadoLong extends StatelessWidget {

  final String texto;
  final Color corTexto;
  final VoidCallback onPressed;

  const BotaoCustomizadoLong({Key? key,
    required this.texto,
    required this.onPressed,
    this.corTexto = Colors.white,
  }) : super(key: key);


  @override
  Widget build(BuildContext context) {
    return ElevatedButton(
      onPressed: onPressed,
      style: ElevatedButton.styleFrom(
        backgroundColor: const Color(0xff1220c1),
        minimumSize: const Size(350, 70),
        shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(20)
        ),
      ),
      child: Text( texto ),
    );
  }
}
