#define BotonConectar 2 // Pin del botón de conexión
const int rgbLedPin = 9; // Pin del LED RGB
volatile byte colorsReceived[3] = {0}; // Array para almacenar los tres colores recibidos
volatile bool Connect = false;
volatile bool flag = true;
volatile byte colorReceived = 0;
bool confirmationSent = false;
#define R 9
#define G 10
#define B 11

void interrupcion1() {

  if (Connect == false) {
    Connect = true;
    flag = true;
  }
  else {
    Connect = false;
    flag = true;
  }
  //hacer anti rebote con millis()
}

void setup() {
  attachInterrupt (digitalPinToInterrupt (2), interrupcion1, FALLING);

  pinMode(rgbLedPin, OUTPUT);
  digitalWrite(rgbLedPin, LOW); // Inicialmente apagado

  Serial.begin(9600);
}

void loop() {

  if (Connect == true and flag == true ) {
    Serial.write('C');
    flag = false;
  }

  if (Connect == false and flag == true) {
    Serial.write('D');
    flag = false;
  }

  // Si hay un color recibido, mostrarlo en el LED RGB
  if (colorReceived != 0) {
    analogWrite(rgbLedPin, colorReceived); // Mostrar el color recibido en el LED RGB
    colorReceived = 0; // Reiniciar el valor de color recibido

  }
  //añadir confirmacion envio y recepcion
  // Confirmar el envío y recepción de datos al dispositivo remoto
  if (!confirmationSent) {
    Serial.println("confirmation"); // Enviar confirmación al dispositivo remoto
    confirmationSent = true;
  }

  // Si hay tres colores recibidos, mostrarlos en el LED RGB
  if (colorsReceived[0] != 0 && colorsReceived[1] != 0 && colorsReceived[2] != 0) {
    analogWrite(R, colorsReceived[0]); // Mostrar el primer color recibido en el LED RGB
    delay(500); // Esperar
    analogWrite(G, colorsReceived[1]); // Mostrar el segundo color recibido en el LED RGB
    delay(500); // Esperar
    analogWrite(B, colorsReceived[2]); // Mostrar el tercer color recibido en el LED RGB
    delay(500); // Esperar

  }
}
