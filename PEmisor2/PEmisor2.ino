#define LEDRECP 4               //Pin del LED1 (acuse de recibido)
#define LEDCON 5               // Pin del LED2 (conexión establecida)

unsigned long antirebote1 = 0;  //variables para hacer el anti rebote de los pulsadores
unsigned long  antirebote2 = 0;
int tiempoR = 2000;

volatile bool power = true;  //variables que utilizaremos para controlar los estados de prendiso/apagado y cambio de color
volatile int cont = 1;

int state;                   //variable donde almacenarame el valor leido en el puerto serie

int on = 0;                  //variables para controlar el flujo de ejecucion del programa
int off = 0;

unsigned long sLEDR = 0;     //variable donde almacenaremos el tiempo de millis para controlar el encendido y apagado del led de recepcion sin la necesidad de parar el programa
int flag = 1;

int R = 0;                   //variables relacionadas con los colores
int G = 0;
int B = 0;

void interrupcion1() {                    //interrupcion donde se controla el estado de prendido y apagado
  if ((millis() - antirebote1) > 500) {
    if (power == true) {
      power = false;
      cont = 1;
      flag = 1;
    }
    else {
      power = true;
      flag = 1;
    }
    antirebote1 = millis();
  }
}


void interrupcion2() {                  //interrupcion donde se controla el estado de cambio de color
  if ((millis() - antirebote2) > 500) {
    if (power == true) {
      cont = 1 ;
    }
    antirebote2 = millis();
  }
}

void setup() {
  attachInterrupt (digitalPinToInterrupt (2), interrupcion1, RISING); //Se decalara la interrupción de Encender/Apagar
  attachInterrupt (digitalPinToInterrupt (3), interrupcion2, RISING);   //Se decalara la interrupción de Cambio de color

  pinMode(LEDRECP, OUTPUT);   //declaramos los pines de los ledes como salidas
  pinMode(LEDCON, OUTPUT);

  Serial.begin(9600); //iniciamos el puerto serie
}

void loop() {
  if (Serial.available() > 0) { //si hay datos en el puerto serie
    state = Serial.read();      //leemos el puerto y guardamos el valor leido en la variable state

    if (state == 'C') {         //si se recibe una C es que se debe establecer una conexion
      on = 1;
      off = 0;
    }

    if (state == 'D') {         //si se recibe una D se debe desconectar
      on = 0;
      off = 1;
    }

    if (state == 'R' ) {       //si se recibe una R se nos confirma de que llegaron detos al receptor
      digitalWrite(LEDRECP, HIGH);
      sLEDR = millis();
    }
  }

  if (on == 1) {               //prendemos el led de conexion establecida
    digitalWrite(LEDCON, HIGH); 
  }

  if (power == true and on == 1) { //generamos colores randoms y los enviamos por el puerto serie
    if (cont >= 1 ) {
      R = random(255);
      G = random(255);
      B = random(255);

      Serial.print("R");      //envio de colores
      Serial.print(R);
      Serial.flush();         //Serial.flush() lo usamos para tener prioridad de envio de datos y esperar a que se termine el envio de los datos anteriores
      Serial.print("G");
      Serial.print(G);
      Serial.flush();
      Serial.print("B");
      Serial.print(B);
      Serial.flush();
      Serial.print("P");

    }
    cont = 0;
  }

  if (power == false and flag == 1 and on == 1)  {
    R = 0;
    G = 0;                  //enviamos 0 en todos los colores para apagar el led rgb
    B = 0;

    Serial.print("R");      //envio de colores
    Serial.print(R);
    Serial.flush();
    Serial.print("G");
    Serial.print(G);
    Serial.flush();
    Serial.print("B");
    Serial.print(B);
    Serial.flush();
    Serial.print("P");

    flag = 0;
  }

  if ((millis() - sLEDR) > tiempoR) { //si el tiempo desde que se prendio el LEDRECP es mayor a 2 segundos se apaga el led
    digitalWrite(LEDRECP, LOW);
  }

  if (off == 1) {                   //si se habia recibido un D la variable off se pone en 1 y se apaga el led que indica la conexion
    digitalWrite(LEDCON, LOW);   
  }
}
