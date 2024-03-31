int LEDP[] = {2, 3, 4, 5, 6, 7, 8, 9};

#define CLK 10

volatile int flag = 0;
volatile int flag1 = 1;

volatile int cont = 0;
int color = 0;

const int BotonEncenderApagar = 18;
const int BotonCambiarColor = 19;

void interrupcion1() { //función para encender o apagar la comunicación
  if (flag < 1) {
    flag = flag + 1 ;
    flag1 = 0;
  }
  else {
    flag = 0;
    flag1 = 1;
  }
}

void interrupcion2() { //función para cambiar el color del led
  if (flag >= 1) {
    cont = cont + 1 ;
  }
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {  //Se declaran los pines de salida
    pinMode(LEDP[i], OUTPUT);
  }

  pinMode(CLK, OUTPUT);

  attachInterrupt (digitalPinToInterrupt (BotonEncenderApagar), interrupcion1, FALLING); //Se decalara la interrupción de Encender/Apagar
  attachInterrupt (digitalPinToInterrupt (BotonCambiarColor), interrupcion2, FALLING);   //Se decalara la interrupción de Cambio de color

}

void loop() {
  Serial.println(cont);
  Serial.println(flag);
  if (flag == 0) {// Si la comunicación esta apagado, envia el 0 a todas las salidas
    if (flag1 == 1) {
      for (int c = 0; c < 3; c++) {               // genera el codigo de color y lo almacena en tres variables, una por cada color del RGB
        for (int i = 0; i < 8; i++) {
          digitalWrite(LEDP[i], LOW);
        }                 //cambie bitread por LOW porque lo unico que tiene que hacer es poner las entradas a 0
        delay(50);
        digitalWrite(CLK, HIGH);
        delay(50);
        digitalWrite(CLK, LOW);
        delay(50);
      }
      flag1 = 0;
    }
  }

  //si usas el bitread estas haciendo que se hagan operaciones de mas al transformar 0 a binario

  else {
    if (cont >= 1) {                              // Sino, si cambia el valor del contador cuando se presiona el botón, genera un color aleatorio
      for (int u = 0; u < 3; u++) {               // genera el codigo de color y lo almacena en tres variables, una por cada color del RGB
        color = random (255);
        for (int x = 0; x < 8; x++) {                    // Con bitRead, se convierte el valor de decimal a binario de 8 bits en un ciclo for para que salga el valor a través de las 8 salidas
          digitalWrite(LEDP[x], bitRead(color, x));      //falta la utilizacion del bit de clock; lo defini arriba como CLK
        }
        delay(50);
        digitalWrite(CLK, HIGH);
        delay(50);
        digitalWrite(CLK, LOW);
        delay(50);
      }
      cont = 0;
    }
  }
}
