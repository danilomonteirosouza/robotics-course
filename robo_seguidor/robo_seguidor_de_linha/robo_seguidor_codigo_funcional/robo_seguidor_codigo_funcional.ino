//Definição dos pinos de controle do motor
#define MOTOR_ESQUERDO 11 // Pino_Velocidade 1º Motor ( 0 a 255)_ Porta IN2 ponte H;
#define MOTOR_DIREITO 9 //Pino_Velocidade 2º Motor ( 0 a 255) _ Porta IN4 ponte H;
#define direcao_motor_esquerdo 8 //Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
#define direcao_motor_direito 10 //Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;

// LINHA PRETA = 0
// LINHA BRANCA = 1

//Definição dos pinos dos sensores
#define pin_sensor_esquerdo 7
#define pin_sensor_direito 6
bool sensor_esquerdo = 0;
bool sensor_direito = 0;

//variável responsável por controlar a velocidade dos motores
int velocidade = 150;

void setup(){
  pinMode(MOTOR_ESQUERDO, OUTPUT);
  pinMode(MOTOR_DIREITO, OUTPUT);
  pinMode(direcao_motor_esquerdo, OUTPUT);
  pinMode(direcao_motor_direito, OUTPUT);
  Serial.begin(9600);
  digitalWrite(direcao_motor_esquerdo, LOW); // HIGH: GIRA SENTIDO HORARIO - LOW: SENTIDO ANTI-HORARIO
  digitalWrite(direcao_motor_direito, LOW); // HIGH: GIRA SENTIDO ANTI-HORARIO - LOW: SENTIDO ANTI-HORARIO
  pinMode(pin_sensor_esquerdo, INPUT);
  pinMode(pin_sensor_direito, INPUT);
}

void loop(){
  //Neste processo armazenamos o valor lido pelo sensor na variável que armazena tais dados.
  sensor_esquerdo = digitalRead(pin_sensor_esquerdo);
  sensor_direito = digitalRead(pin_sensor_direito);
  Serial.print(sensor_direito);
  Serial.print(" || ");
  Serial.println(sensor_esquerdo);


  if(sensor_direito == 0 && sensor_esquerdo == 0){ // Se detectar um lado branco e o outro branco
    analogWrite(MOTOR_ESQUERDO, velocidade); // vai para frente
    analogWrite(MOTOR_DIREITO, velocidade); // vai para frente   
   }
  
  if(sensor_direito == 0 && sensor_esquerdo == 1){ // Se detectar um lado preto e o outro branco
    analogWrite(MOTOR_ESQUERDO, velocidade); //liga
    analogWrite(MOTOR_DIREITO, 0); // desliga    
    }

  if(sensor_direito == 1 && sensor_esquerdo == 0){ // Se detectar um lado branco e o outro preto
    analogWrite(MOTOR_ESQUERDO, 0); //desliga
    analogWrite(MOTOR_DIREITO, velocidade); // liga   
    }
 }
