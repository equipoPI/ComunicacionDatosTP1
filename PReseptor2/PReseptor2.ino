#define BotonConectar 2 // Pin del botón de conexión

volatile bool Connect = false; //variables de la interrupcion que controla la conexion y desconexion
volatile bool flag = true;

int antirebote1 = 0;           //variable para controlar el antirebote del pulsador

#define RPIN 9                 //pines del led rgb segun los colores
#define GPIN 10
#define BPIN 11

int Rr = 0;                    //variables donde almacenaremos los valores recibidos para cada color
int Gr = 0;
int Br = 0;

int change = 0;                //variable donde almacenaremos el estado de imprimir el color en el led

void interrupcion1() {         //interrupcion donde cambiaremos los estados de unas variables para enviar la solicitud de conexion o desconexion
  if ((millis() - antirebote1) > 500) {
    if (Connect == false) {
      Connect = true;
      flag = true;
    }
    else {
      Connect = false;
      flag = true;
    }
    antirebote1 = millis();
  }
}

void setup() {
  attachInterrupt (digitalPinToInterrupt (BotonConectar), interrupcion1, FALLING);  //definimos la funcion de interrupcion externa de conexion o desxonexion

  pinMode(RPIN, OUTPUT);   //definimos los pines conectados al led rgb como salidas
  pinMode(GPIN, OUTPUT);
  pinMode(BPIN, OUTPUT);

  Serial.begin(9600);     //inicializamos el puerto serie
}

void loop() {

  if (Connect == true and flag == true ) { // enviamos un C por el puerto
    Serial.print('C');
    flag = false;
  }

  if (Connect == false and flag == true) { // enviamos un D por el puerto
    Serial.print('D');
    flag = false;
  }

  if (Serial.available() > 0) { //si hay datos en el puerto se ejecutan las instrucciones
    if (Serial.find('R')) {     //Serial.find()se usa para buscar un caracter, palabra definida o palabra de cierto ancho
      Rr = Serial.parseInt();   //Serial.parseInt() se usa para que cualquier valor numerico que hay este en el puerto se gurade, tiene que se un numero entero
    }
    if (Serial.find('G')) {
      Gr = Serial.parseInt();
    }
    if (Serial.find('B')) {
      Br = Serial.parseInt();
    }

    if (Serial.find('P')) {
      change = 1;
    }
  }
if (change == 1) {            //se usa el PWM para poner los valores en el pin del led reb y formar los colores
      analogWrite(RPIN, Rr);
      analogWrite(GPIN, Gr);
      analogWrite(BPIN, Br);
      change = 0;
      Serial.print('R');      //envia por el puerto una R para confirmar la recepcion de los datos
    }
 }
