//pin de reloj
#define CLK 2 

//entrada bit mas significativo a menos significativo
#define EMS 3 
#define E7 4
#define E6 5
#define E5 6
#define E4 7
#define E3 8
#define E2 12
#define E1 13

//pines PWM asosiados a cada color
#define R 9   
#define G 10
#define B 11

volatile byte flag = 0;       //variables de estado para controlar el estado de ejecucion del void loop
volatile byte flag1 = 0;

int acuR = 0;  //variables acumuladoras para los valores PWM de los diferentes colores
int acuG = 0;
int acuB = 0;
int ER [] = {0, 0, 0, 0, 0, 0, 0, 0}; //array donde guardamos los estados de las 8 entrasdas de la señal para el color rojo
int EG [] = {0, 0, 0, 0, 0, 0, 0, 0}; //array donde guardamos los estados de las 8 entrasdas de la señal para el color verde
int EB [] = {0, 0, 0, 0, 0, 0, 0, 0}; //array donde guardamos los estados de las 8 entrasdas de la señal para el color azul

void read() {   //funcion que activa la señal del clock que viene desde el emisor
  flag = flag + 1;
  flag1 = flag1 + 1;
}

void setup() {
  attachInterrupt (digitalPinToInterrupt (CLK), read, RISING); //acctiva una iterrupcion cuando el pin del clock pasa de bajo a alto
  
  pinMode(EMS, INPUT);  //definimos los pines asociados a la comunicacion
  pinMode(E7, INPUT);
  pinMode(E6, INPUT);
  pinMode(E5, INPUT);
  pinMode(E4, INPUT);
  pinMode(E3, INPUT);
  pinMode(E2, INPUT);
  pinMode(E1, INPUT);

  pinMode(R, OUTPUT);   //definimos los pines PWM para controlar el RGB
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

   Serial.begin(9600);  //iniciamos el configuramos el puerto serie para poder ver valores de variables a traves de este 
                        //y así controlar el correcto funcionamiento del programa
}

void loop() {
  Serial.print('F');          //imprimimos valores para control de la correcta ejecucion del programa en el puerto serie
  Serial.println(flag);

  if (flag == 1) {            //con flag = 1 guardamos los estados de las entradas para el estado del color rojo
    if (flag1 == 1) {
      ER [0] = digitalRead(EMS);
      ER [1] = digitalRead(E7);
      ER [2] = digitalRead(E6);
      ER [3] = digitalRead(E5);
      ER [4] = digitalRead(E4);
      ER [5] = digitalRead(E3);
      ER [6] = digitalRead(E2);
      ER [7] = digitalRead(E1);
      flag1 = 0;
    }
  }

  Serial.print('F');          //imprimimos valores para control de la correcta ejecucion del programa en el puerto serie
  Serial.println(flag);

  if (flag == 2) {            //con flag = 2 guardamos los estados de las entradas para el estado del color verde
    if (flag1 == 1) {
      EG [0] = digitalRead(EMS);
      EG [1] = digitalRead(E7);
      EG [2] = digitalRead(E6);
      EG [3] = digitalRead(E5);
      EG [4] = digitalRead(E4);
      EG [5] = digitalRead(E3);
      EG [6] = digitalRead(E2);
      EG [7] = digitalRead(E1);
      flag1 = 0;
    }
  }

  Serial.print('F');
  Serial.println(flag);

  if (flag == 3) {             //con flag = 3 guardamos los estados de las entradas para el estado del color azul
    if (flag1 == 1) {
      EB [0] = digitalRead(EMS);
      EB [1] = digitalRead(E7);
      EB [2] = digitalRead(E6);
      EB [3] = digitalRead(E5);
      EB [4] = digitalRead(E4);
      EB [5] = digitalRead(E3);
      EB [6] = digitalRead(E2);
      EB [7] = digitalRead(E1);
      flag1 = 0;
      flag = 4;
    }

  }

  Serial.print('F');      //imprimimos valores para control de la correcta ejecucion del programa en el puerto serie
  Serial.println(flag);

  if (flag == 4) {        //con flag = 4 reconstruimos el valor guardado en binario a decimal y lo guardamos en el los 
                          //acumuladores de cada color para recrear el color con rgb
    acuR = 0;
    acuG = 0;
    acuB = 0; 
    
    if (ER[0] == 1) {
      acuR = acuR + 128;
    }
    if (ER[1] == 1) {
      acuR = acuR + 64;
    }
    if (ER[2] == 1) {
      acuR = acuR + 32;
    }
    if (ER[3] == 1) {
      acuR = acuR + 16;
    }
    if (ER[4] == 1) {
      acuR = acuR + 8;
    }
    if (ER[5] == 1) {
      acuR = acuR + 4;
    }
    if (ER[6] == 1) {
      acuR = acuR + 2;
    }
    if (ER[7] == 1) {
      acuR = acuR + 1;
    }

    if (EG[0] == 1) {
      acuG =  acuG + 128;
    }
    if (EG[1] == 1) {
      acuG = acuG + 64;
    }
    if (EG[2] == 1) {
      acuG =  acuG + 32;
    }
    if (EG[3] == 1) {
      acuG =  acuG + 16;
    }
    if (EG[4] == 1) {
      acuG =  acuG + 8;
    }
    if (EG[5] == 1) {
      acuG =  acuG + 4;
    }
    if (EG[6] == 1) {
      acuG =  acuG + 2;
    }
    if (EG[7] == 1) {
      acuG =  acuG + 1;
    }

    if (EB[0] == 1) {
      acuB = acuB + 128;
    }
    if (EB[1] == 1) {
      acuB = acuB + 64;
    }
    if (EB[2] == 1) {
      acuB = acuB + 32;
    }
    if (EB[3] == 1) {
      acuB = acuB + 16;
    }
    if (EB[4] == 1) {
      acuB = acuB + 8;
    }
    if (EB[5] == 1) {
      acuB = acuB + 4;
    }
    if (EB[6] == 1) {
      acuB = acuB + 2;
    }
    if (EB[7] == 1) {
      acuB = acuB + 1;

    }
    flag = 0;
  }

  Serial.print('F');       //imprimimos valores para control de la correcta ejecucion del programa en el puerto serie
  Serial.println(flag);
  Serial.print('R');
  Serial.println(acuR);
  Serial.print('G');
  Serial.println(acuG);
  Serial.print('B');
  Serial.println(acuB);

  analogWrite(R, acuR);    //imprimimos el valor de cada acumulador a la salida
  analogWrite(G, acuG);
  analogWrite(B, acuB);

}
