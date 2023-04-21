// Definir el pin del buzzer
#define BUZZER_PIN 2

// Definir la frecuencia del ladrido de perro
#define LADRIDO_PERROFREQ 2000

// Definir la duración del ladrido de perro en milisegundos
#define LADRIDO_PERRODURATION 100

const int motorA1 = 7;
const int motorA2 = 6;
const int motorAspeed = 9;

const int motorB1 = 5;
const int motorB2 = 4;
const int motorBspeed = 3;

int num_direccion, num_rotacion;
int pulso, cm;

const int pin_Servo = 8;
const int pin_Echo = 11;
const int pin_Trig = 12;
String direccion;

void setup() {
  Serial.begin(9600);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  pinMode(motorBspeed, OUTPUT);
  pinMode(motorAspeed, OUTPUT);

  pinMode(pin_Trig, OUTPUT);
  pinMode(pin_Echo, INPUT);
  pinMode(pin_Servo, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  analogWrite(motorA1, 0);
  analogWrite(motorA2, 0);
  analogWrite(motorB1, 0);
  analogWrite(motorB2, 0);
}

void loop() {


  //digitalWrite(pin_Trig, LOW);
  //delayMicroseconds(2);
  digitalWrite(pin_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_Trig, LOW);
  delayMicroseconds(2);

  pulso = pulseIn(pin_Echo, HIGH);
  //cm = pulso / 29 / 2;
  cm = pulso/59;
  Serial.println(cm);
  delay(200);

    if (cm <= 25) {


      rotar();

    
  }else{

    enfrente();

  }
    
  }


void rotar() {
  atras();
  delay(700);//tIEMPO QUE DARA HACIA ATRAS
  direccion = prob_direccion();
  if (direccion == "izquierda") {
    izquierda();
    delay(1000);//Tiempo que dara hacia la izquierda
  } else if (direccion == "derecha") {
    derecha();
    delay(1000);//Tiempo que dara hacia la derecha
  }
}

  void atras() {
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorA1, LOW);

  digitalWrite(motorB2, HIGH);
  digitalWrite(motorB1, LOW);

  analogWrite(motorAspeed, 95);
  analogWrite(motorBspeed, 95);
  delay(200);
    String rnd = prob();
  if (rnd == "mover colita") {
    mover();
  } else {
    ladrar();
  }
}

String prob_direccion() {
  num_direccion = random(0, 67);
  if (num_direccion <= 33) {
    return "izquierda";
  } else {
    return "derecha";
  }
}


void izquierda() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);

  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);

  analogWrite(motorAspeed, 95);
  analogWrite(motorBspeed, 95);
}

  void derecha() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);

  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);

  analogWrite(motorAspeed, 95);
  analogWrite(motorBspeed, 95);
}

void enfrente() {
  
  digitalWrite(motorA2, LOW);
  digitalWrite(motorA1, HIGH);

  digitalWrite(motorB2, LOW);
  digitalWrite(motorB1, HIGH);

  analogWrite(motorAspeed, 95);
  analogWrite(motorBspeed, 95);
}

String prob() {
  num_direccion = random(0, 101);
  if (num_direccion <= 70) {
    return "mover colita";
  } else {
    return "ladrar";
  }
}


void ladrar() {
  // Generar un ladrido de perro
  tone(BUZZER_PIN, LADRIDO_PERROFREQ);
  delay(LADRIDO_PERRODURATION);
  noTone(BUZZER_PIN);
}

void mover() {
  for (int i = 0; i <= 90; i++) {
    int angle = map(i, 0, 90, 0, 178);  // Mapear el ángulo a los valores de PWM (0 a 180)
    analogWrite(pin_Servo, angle);      // Generar el pulso PWM para el ángulo actual
    delay(10);                          // Esperar un breve tiempo para que el servomotor se mueva
  }

}