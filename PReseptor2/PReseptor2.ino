#define BotonConectar 2 // Pin del botón de conexión
const int rgbLedPin = 9; // Pin del LED RGB

volatile bool Connect = false;
volatile bool flag = false;

void interrupcion1() {
  if (Connect == false) {
    flag = false;
    Connect = true;
  }
  if (Connect == true) {
    Connect = false;
    flag = false;
  }
}

void setup() {
  attachInterrupt (digitalPinToInterrupt (BotonConectar), interrupcion1, FALLING);

  pinMode(rgbLedPin, OUTPUT);
  digitalWrite(rgbLedPin, LOW); // Inicialmente apagado

  Serial.begin(9600);
}

void loop() {
  if (Connect == true) { // Si se presiona el botón de conexión y no está conectado
    if (flag == false) {
      Serial.println("connect"); // Solicita conexión al dispositivo 1
      delay(500); // Debounce
      flag = true;
    }

    //añadir recepcion colores

    //añadir confirmacion envio y recepcion
  }
  else {
    if (flag == false) {
      Serial.println("disconnect"); // Solicita conexión al dispositivo 1
      delay(500); // Debounce
      flag = true;
    }
  }

}
