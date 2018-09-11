//Elaborado por: Yocoyani Pérez

const int buzzerAlarma = 4, ledAlarma = 5, motorAspersor = 11, bomba = 10; //Dispositivos de salida
const int sensorFlama = A0, sensorGas = A5, sensorAgua = A1; //Sensores a utilizar
const int limiteFlama = 40, limiteAgua = 100, limiteGas = 500, calibracionGas = 350; //Limites para detectar datos en la lectura

int lecturaFlama = 0, lecturaAgua = 0, lecturaGas = 0; //Variables para guardar lecturas

void setup() {

  Serial.begin(9600);
  
  //Declaración de PINES de SALIDA y ENTRADA
  pinMode(buzzerAlarma, OUTPUT);
  pinMode(ledAlarma, OUTPUT);
  pinMode(motorAspersor, OUTPUT);
  pinMode(bomba, OUTPUT);
  pinMode(sensorFlama, INPUT);
  pinMode(sensorGas, INPUT);
  pinMode(sensorAgua, INPUT);

  //Dispositivos apagados por seguridad al inicio del programa
  digitalWrite(buzzerAlarma, LOW);
  digitalWrite(ledAlarma, LOW);
  digitalWrite(motorAspersor, LOW);
  digitalWrite(bomba, LOW);

  //Calibración sensor de gas
  lecturaGas = analogRead(sensorGas);
  delay(50);
  lecturaGas = analogRead(sensorGas);
  while(lecturaGas < calibracionGas){
    
    digitalWrite(buzzerAlarma, HIGH);
    digitalWrite(ledAlarma, HIGH);
    delay(100);
    digitalWrite(buzzerAlarma, LOW);
    digitalWrite(ledAlarma, LOW);
    delay(100);
    lecturaGas = analogRead(sensorGas);
    
  }
    //Indicador de que empieza a funcionar la alerta
    delay(1000);
    digitalWrite(buzzerAlarma, HIGH);
    digitalWrite(ledAlarma, HIGH);
    delay(50);
    digitalWrite(buzzerAlarma, LOW);
    digitalWrite(ledAlarma, LOW);
    delay(50);

}

void loop() {

  //Lectura de  la alarma
  lecturaGas = analogRead(sensorGas);
  lecturaFlama = analogRead(sensorFlama);
  lecturaAgua = analogRead(sensorAgua);

  //Condición que implica que haya humo, flama y agua en el tinaco
  if(lecturaGas > limiteGas && lecturaFlama < limiteFlama && lecturaAgua < limiteAgua){

    Serial.println("Hay un incendio, se esta apagando inmediatamente");
    digitalWrite(motorAspersor, HIGH);
    delay(3000);
    
  }
  //Caso en el que se tiene un incendio pero no agua
  else if(lecturaGas > limiteGas && lecturaFlama < limiteFlama){

    Serial.println("Hay un incendio, PELIGRO, AUSCENCIA DE AGUA!!!");
    digitalWrite(bomba, HIGH);
    //Instruccion para alertar con LED y buzzer por 3s en lo que se llena la bomba
    for(int x; x < 2; x++){

      digitalWrite(buzzerAlarma, HIGH);
      digitalWrite(ledAlarma, HIGH);
      delay(1000);
      digitalWrite(buzzerAlarma, LOW);
      digitalWrite(ledAlarma, LOW);
      delay(1000);
       
    }
    digitalWrite(bomba, LOW);
    Serial.println("Se procedera a apagar el incendio");
    digitalWrite(motorAspersor, HIGH);
    delay(3000);
  }

  else{
    //Caso en el que no haya agua
    if(lecturaAgua > 100){

      digitalWrite(bomba, HIGH);
      delay(3000);
      digitalWrite(bomba, LOW);
      
    }
    //Caso en el que solo haya humo, pero por fumadores
    if(lecturaGas < limiteGas){

      Serial.println("Alguien esta fumando");
      
    }
    
  }
  
}
