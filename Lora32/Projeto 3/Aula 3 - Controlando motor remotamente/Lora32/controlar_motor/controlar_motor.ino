#include <WiFi.h> 
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

// Lora radio Port Configuration
#define LORA_SCK    5   
#define LORA_MISO   19 
#define LORA_CS     18
#define LORA_MOSI   27 
#define LORA_RST    14  
#define LORA_IRQ    26
//Lora OLED Port Configuration
#define OLED_SCL    15
#define OLED_SDA    4
#define OLED_RST    16
//ONBOARD LED
#define LED_ONBOARD 25
//MOTOR
#define MOTOR         17

// Wi-fi credentials
const char* ssid = "FamilyLDD";
const char* password = "JOAO0316@@!";

//MQTT Broker credentials
const char* mqtt_server = "231ccd91865148f78345c07e2d7e799e.s2.eu.hivemq.cloud";
int mqtt_server_port = 8883;
const char* hiveIOTUser = "submarino";
const char* hiveIOTPassword = "Espaco40ETE@@!";

WiFiClientSecure espClient;   // for no secure connection use WiFiClient instead of WiFiClientSecure 
PubSubClient client(espClient);

//Publish Message parameters
#define MSG_BUFFER_SIZE (500)
char bufferMessage[MSG_BUFFER_SIZE];
int value = 0; // Message counter

//Basic Sensors configuration
const char* topicBasicSensors = "submarino";

//Topic to publish first communication
const char* topicNameStablishConnection = "firstAttemptConnection";
const char* messageOnceStablishConnection = "Communication working properly";

static const char *root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection…");
    String clientId = "ESPClient - MyClient";
    if (client.connect(clientId.c_str(), hiveIOTUser, hiveIOTPassword )) {
      Serial.println("connected");
      client.publish(topicNameStablishConnection, messageOnceStablishConnection);
      publishers();
    } else {
      Serial.print("Failed, rc = ");
      Serial.print(client.state());
      Serial.println("Try again in 5 seconds");
      delay(5000);
    }
  }
}

void mqtt_callbak(char* topic, byte* payload, unsigned int length) {
  String commandArrived;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
      commandArrived = commandArrived + (char) payload[i];  // convert *byte to string
    }
      Serial.print(commandArrived);
      //------LED CONTROL-------------
      if (commandArrived == "ligarMotor") {digitalWrite(MOTOR, HIGH);}
      if (commandArrived == "desligarMotor") {digitalWrite(MOTOR, LOW);}
      Serial.println();
}

void serial_setup() {
  delay(500);
  Serial.begin(9600);
  delay(500);
}

void output_data() {
  pinMode(MOTOR, OUTPUT);
}

void mqtt_broker_communication() {
  client.setServer(mqtt_server, mqtt_server_port);
  client.setCallback(mqtt_callbak);
}

void establish_ssl_connection() {
  espClient.setCACert(root_ca);
}

void publishers() {
  client.subscribe(topicBasicSensors);
}

void setup() {
  serial_setup();
  setup_wifi();
  output_data();
  establish_ssl_connection();
  mqtt_broker_communication();
}

void loop() { 
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
