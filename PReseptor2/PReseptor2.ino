#define BotonConectar 2 // Pin del botón de conexión
const int rgbLedPin = 9; // Pin del LED RGB

volatile bool Connect = false;

void interrupcion1() {
  if (Connect == false) {
    Connect = true;
  }
  if (Connect == true) {
    Connect = false;
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
    Serial.println("Solicitud de Conexión"); // Solicita conexión al dispositivo 1
    delay(500); // Debounce
  }

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command.startsWith("Alternar LED RGB")) {
      // Cambiar estado del LED RGB
      digitalWrite(rgbLedPin, !digitalRead(rgbLedPin));
      Serial.println("Recibido Acuse de Alternar");
    } else if (command.startsWith("Cambiar Color RGB:")) {
      // Obtener el color del comando
      command.remove(0, 18);
      int commaIndex1 = command.indexOf(",");
      int commaIndex2 = command.indexOf(",", commaIndex1 + 1);
      int r = command.substring(0, commaIndex1).toInt();
      int g = command.substring(commaIndex1 + 1, commaIndex2).toInt();
      int b = command.substring(commaIndex2 + 1).toInt();

      // Cambiar el color del LED RGB
      analogWrite(rgbLedPin, r);
      analogWrite(rgbLedPin + 1, g);
      analogWrite(rgbLedPin + 2, b);
      Serial.println("Recibido Acuse de Cambio de Color");
    }
  }

  // Enviar acuse de recibido al dispositivo 1
  Serial.println("Acuse de Recibo");
  delay(100); // Esperar un momento antes de enviar el siguiente acuse
}
