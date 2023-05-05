#include <Ultrasonic.h> //Inclui a biblioteca do ultrassônico
Ultrasonic ultrassom(5, 4); //Cria o objeto ultrassom, do tipo Ultrassonic, e define os pinos onde está ligado o TRIG(pino 5) e o ECHO(pino 4) respectivamente

long distancia; //cria a variável distancia do tipo long

void setup() {
  Serial.begin(9600); //Inicializa a comunicação serial, com velocidade de comunicação de 9600
}

void loop(){
  distancia = ultrassom.Ranging(CM);//ultrassom.Ranging(CM) retorna a distancia em centímetros(CM)
  Serial.print("Distância medida = ");//Imprime na serial o texto "Distância = "
  Serial.print(distancia); //Imprime na serial o valor da variável distancia
  Serial.println("cm"); //Imprime na serial o texto "cm"
  delay(1000); //Intervalo de 1 segundo
}
