import 'package:flutter/material.dart';

import 'mqtt_connection.dart';

class HomePage extends StatefulWidget {
  const HomePage({Key? key}) : super(key: key);

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {

  MQTTClientWrapper client = MQTTClientWrapper("BasicSensors", "");

  @override
  void initState() {
    super.initState();
    client.prepareMqttClient();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Controlando LED'),
        centerTitle: true,
      ),
      body: SafeArea(
        child: Center(
          child: Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              ElevatedButton(
                  onPressed: (){
                    client.publishMessage("ledOn");
                  },
                  child: const Text("Turn On Led")
              ),
              Padding(
                  padding: const EdgeInsets.fromLTRB(10, 0, 0, 0),
                child: ElevatedButton(
                    onPressed: (){
                      client.publishMessage("ledOff");
                    },
                    child: const Text("Turn Off Led")
                ),
              ),
              Padding(
                padding: const EdgeInsets.fromLTRB(10, 0, 0, 0),
                child: ElevatedButton(
                    onPressed: (){
                      client.publishMessage("tempRead");
                    },
                    child: const Text("Temperature")
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
