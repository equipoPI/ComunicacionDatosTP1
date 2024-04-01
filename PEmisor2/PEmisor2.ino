#define BotonEncenderApagar 2  // Pin del pulsador encender/apagar
#define BotonCambiarColor 3    // Pin del pulsador cambiar

#define LEDREC 4               //Pin del LED1 (acuse de recibido)
#define LEDCON 5               // Pin del LED2 (conexión establecida)

bool isConnected = false;
volatile bool power = true;

void interrupcion1() {
  if (power == true) {
    power = false;
  }
  if (power == false) {
    power = true;
  }
}


void interrupcion2() {

}

void setup() {
  attachInterrupt (digitalPinToInterrupt (BotonEncenderApagar), interrupcion1, FALLING); //Se decalara la interrupción de Encender/Apagar
  attachInterrupt (digitalPinToInterrupt (BotonCambiarColor), interrupcion2, FALLING);   //Se decalara la interrupción de Cambio de color

  pinMode(LEDREC, OUTPUT);
  pinMode(LEDCON, OUTPUT);

  digitalWrite(LEDCON, LOW); // Inicialmente apagado

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(BotonEncenderApagar) == LOW) { // Si se presiona el botón encender/apagar
    digitalWrite(LEDREC, HIGH); // Enciende el LED2 (conexión establecida)
    if (isConnected) {
      Serial.println("Alternar LED RGB"); // Envia comando al dispositivo 2 para cambiar estado del LED RGB
    }
    delay(500); // Debounce
  }

  if (digitalRead(BotonCambiarColor) == LOW) { // Si se presiona el botón cambiar
    int r = random(255);
    int g = random(255);
    int b = random(255);
    Serial.print("Cambiar Color RGB: ");
    Serial.print(r);
    Serial.print(",");
    Serial.print(g);
    Serial.print(",");
    Serial.println(b);
    digitalWrite(LEDREC, HIGH); // Enciende el LED1 (acuse de recibido)
    delay(2000); // Espera 2 segundos
    digitalWrite(LEDREC, LOW); // Apaga el LED1
    delay(500); // Debounce
  }
}
