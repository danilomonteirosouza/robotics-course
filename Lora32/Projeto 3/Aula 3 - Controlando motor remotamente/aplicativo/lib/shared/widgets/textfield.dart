import 'package:flutter/material.dart';

class InputCustomizado extends StatelessWidget {
  final TextEditingController? controller;
  final String? hint;
  final bool? obscure;

  const InputCustomizado({
    Key? key,
    this.controller,
    this.hint,
    this.obscure,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return TextField(
      controller: controller,
      style: const TextStyle(
        fontSize: 20,
        color: Colors.white,
      ),
      decoration: InputDecoration(
        contentPadding: const EdgeInsets.all(20),
        //labelText: "User",
        hintText: hint,
        hintStyle: const TextStyle(
            // Altera a cor do texto dentro
            color: Color(0xffA5A5A5)),
        filled: true,
        fillColor: const Color(0xff320995),
        border: OutlineInputBorder(
          borderRadius: BorderRadius.circular(32),
        ),
        enabledBorder: OutlineInputBorder(
            borderSide: const BorderSide(
              color: Color(0xffA5A5A5),
            ),
            borderRadius: BorderRadius.circular(20)),
        focusedBorder: OutlineInputBorder(
            borderSide: const BorderSide(
              color: Color(0xffA5A5A5),
            ),
            borderRadius: BorderRadius.circular(20)),
      ),
      obscureText: obscure as bool,
    );
  }
}
