int LEDP[] = {2,3,4,5,6,7,8,9};
int x = 0;
int cont = 0;
int color = 0;
const int BotonEncenderApagar = 18;
const int BotonCambiarColor = 19;

void interrupcion1() { //función para encender o apagar la comunicación
  if (x < 1){
    x = +1;
  } 
  else{
      x = 0; }
}

void interrupcion2() { //función para cambiar el color del led
  cont = +1 ; 
}

void setup() {
  for (int i = 0; i < 8; i++) {  //Se declaran los pines de salida
    pinMode(LEDP[i], OUTPUT);}
  attachInterrupt (digitalPinToInterrupt (BotonEncenderApagar), interrupcion1, CHANGE); //Se decalara la interrupción de Encender/Apagar
  attachInterrupt (digitalPinToInterrupt (BotonCambiarColor), interrupcion2, CHANGE);   //Se decalara la interrupción de Cambio de color
  Serial.begin(9600);
}

void loop() {
  if (x = 0) {                                         // Si la comunicación esta apagado, envia el 0 a todas las salidas
    for (int i = 0; i < 8; i++) {
      digitalWrite(LEDP[i], bitRead(0, i));}
  }
  else{
    if (cont == CHANGE){                               // Sino, si cambia el valor del contador cuando se presiona el botón, genera un color aleatorio
      color = random (256);
      for (int i = 0; i < 8; i++) {                    // Con bitRead, se convierte el valor de decimal a binario de 8 bits en un ciclo for para que salga el valor a través de las 8 salidas
        digitalWrite(LEDP[i], bitRead(color, i)); }
      }
    }
}
