import 'dart:io';
import 'package:flutter/material.dart';
import 'package:mqtt_client/mqtt_client.dart';
import 'package:mqtt_client/mqtt_server_client.dart';
import 'package:typed_data/typed_data.dart';

// connection states for easy identification
enum MqttCurrentConnectionState {
  idle,
  connecting,
  connected,
  disconnected,
  errorWhenConnecting
}

//Topic configuration
const String messageSend = 'Mensagem Inicial';
const String topicName = 'submarino';

enum MqttSubscriptionState { idle, subscribed }

class MQTTClientWrapper {
  late MqttServerClient client;

  //MQTT Connection
  String mqttUrl = '231ccd91865148f78345c07e2d7e799e.s2.eu.hivemq.cloud';
  String user = 'submarino';
  String password = 'Espaco40ETE@@!';
  int port = 8883;

  MQTTClientWrapper(topicName, messageSend);

  MqttCurrentConnectionState connectionState = MqttCurrentConnectionState.idle;
  MqttSubscriptionState subscriptionState = MqttSubscriptionState.idle;

  // using async tasks, so the connection won't hinder the code flow
  void prepareMqttClient() async {
    _setupMqttClient();
    await _connectClient();
    _subscribeToTopic(topicName);
    publishMessage(messageSend);
  }

  // waiting for the connection, if an error occurs, print it and disconnect
  Future<void> _connectClient() async {
    try {
      debugPrint('client connecting....');
      connectionState = MqttCurrentConnectionState.connecting;
      await client.connect(user, password);
    } on Exception catch (e) {
      debugPrint('client exception - $e');
      connectionState = MqttCurrentConnectionState.errorWhenConnecting;
      client.disconnect();
    }

    // when connected, print a confirmation, else print an error
    if (client.connectionStatus?.state == MqttConnectionState.connected) {
      connectionState = MqttCurrentConnectionState.connected;
      debugPrint('client connected');
    } else {
      debugPrint(
          'ERROR client connection failed - disconnecting, status is ${client.connectionStatus}');
      connectionState = MqttCurrentConnectionState.errorWhenConnecting;
      client.disconnect();
    }
  }

  void _setupMqttClient() {
    client = MqttServerClient.withPort(mqttUrl, user, port);
    // the next 2 lines are necessary to connect with tls, which is used by HiveMQ Cloud
    client.secure = true;
    client.securityContext = SecurityContext.defaultContext;
    client.keepAlivePeriod = 20;
    client.onDisconnected = _onDisconnected;
    client.onConnected = _onConnected;
    client.onSubscribed = _onSubscribed;
  }

  void _subscribeToTopic(String topicName) {
    debugPrint('Subscribing to the $topicName topic');
    client.subscribe(topicName, MqttQos.atMostOnce);

    // print the message when it is received
    client.updates?.listen((List<MqttReceivedMessage<MqttMessage>> c) {
      final MqttPublishMessage recMess = c[0].payload as MqttPublishMessage;
      var message =
          MqttPublishPayload.bytesToStringAsString(recMess.payload.message);
      debugPrint('YOU GOT A NEW MESSAGE:');
      debugPrint(message);
    });
  }

  void publishMessage(String message) {
    final MqttClientPayloadBuilder builder = MqttClientPayloadBuilder();
    builder.addString(message);

    debugPrint('Publishing message "$message" to topic $topicName');
    client.publishMessage(
        topicName, MqttQos.atMostOnce, builder.payload as Uint8Buffer);
  }

  // callbacks for different events
  void _onSubscribed(String topic) {
    debugPrint('Subscription confirmed for topic $topic');
    subscriptionState = MqttSubscriptionState.subscribed;
  }

  void _onDisconnected() {
    debugPrint('OnDisconnected client callback - Client disconnection');
    connectionState = MqttCurrentConnectionState.disconnected;
  }

  void _onConnected() {
    connectionState = MqttCurrentConnectionState.connected;
    debugPrint('OnConnected client callback - Client connection was sucessful');
  }
}
