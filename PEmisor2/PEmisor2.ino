#define BotonEncenderApagar 2  // Pin del pulsador encender/apagar
#define BotonCambiarColor 3    // Pin del pulsador cambiar

#define LEDREC 4               //Pin del LED1 (acuse de recibido)
#define LEDCON 5               // Pin del LED2 (conexión establecida)

#define tiempoC 2000
#define tiempoR 2000

volatile bool power = true;
volatile int cont = 1;

String state;

int R = 0;
int G = 0;
int B = 0;

void interrupcion1() {
  if (power == true) {
    power = false;
  }
  if (power == false) {
    power = true;
  }
}


void interrupcion2() {
   if (power >= 1) {
    cont = cont + 1 ;
  }
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

if (Serial.available() > 0) {
  state=Serial.read();
  }

if (state=="connect"){
  digitalWrite(LEDCON,HIGH);
  if (power==true){
    if (cont>=1){
      R = random(255);
      G = random(255);
      B = random(255);
      }
      cont=0;
      //añadir envio de colores
    }
  else {
    //añadir envio de colore en 0
    }

//añadir confirmacion de recepcio de envio y llegada
  }

if (state=="disconnect"){
  digitalWrite(LEDCON,LOW);
  }
  
}
