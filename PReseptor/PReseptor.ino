#define CLK 2 //pin de reloj

#define EMS 3 //entrada bit mas significativo a menos significativo
#define E7 4
#define E6 5
#define E5 6
#define E4 7
#define E3 8
#define E2 12
#define E1 13

#define R 9   //pines pwm asosiado a cada color
#define G 10
#define B 11

byte flag = 0;

int patron [] = {0, 0, 0};      //array donde guardamos el valor del PWM reconstruido para cada color
int ER [] = {0, 0, 0, 0, 0, 0, 0, 0}; //array donde guardamos los estados de las 8 entrasdas de la señal para el color rojo
int EG [] = {0, 0, 0, 0, 0, 0, 0, 0}; //array donde guardamos los estados de las 8 entrasdas de la señal para el color verde
int EB [] = {0, 0, 0, 0, 0, 0, 0, 0}; //array donde guardamos los estados de las 8 entrasdas de la señal para el color azul

void read() {   //funcion que activa la señal del clock que viene desde el emisor
  flag = +1;
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
}

void loop() {
  if (flag == 1) {            //con flag = 1 guardamos los estados de las entradas para el estado del color rojo
    ER [0] = digitalRead(EMS);
    ER [1] = digitalRead(E7);
    ER [2] = digitalRead(E6);
    ER [3] = digitalRead(E5);
    ER [4] = digitalRead(E4);
    ER [5] = digitalRead(E3);
    ER [6] = digitalRead(E2);
    ER [7] = digitalRead(E1);
  }

  if (flag == 2) {            //con flag = 2 guardamos los estados de las entradas para el estado del color verde
    EG [0] = digitalRead(EMS);
    EG [1] = digitalRead(E7);
    EG [2] = digitalRead(E6);
    EG [3] = digitalRead(E5);
    EG [4] = digitalRead(E4);
    EG [5] = digitalRead(E3);
    EG [6] = digitalRead(E2);
    EG [7] = digitalRead(E1);
  }

  if (flag == 3) {             //con flag = 3 guardamos los estados de las entradas para el estado del color azul
    EB [0] = digitalRead(EMS);
    EB [1] = digitalRead(E7);
    EB [2] = digitalRead(E6);
    EB [3] = digitalRead(E5);
    EB [4] = digitalRead(E4);
    EB [5] = digitalRead(E3);
    EB [6] = digitalRead(E2);
    EB [7] = digitalRead(E1);

    flag == 4;
  }

  if (flag == 4) {                    //con flag = 4 reconstruimos el valor guardado en binario a decimal y lo guardamos en el array patron para recrear el color con rgb
    if (ER[0] == 1) {
      patron[0] = +128;
    }
    if (ER[1] == 1) {
      patron[0] = +64;
    }
    if (ER[2] == 1) {
      patron[0] = +32;
    }
    if (ER[3] == 1) {
      patron[0] = +16;
    }
    if (ER[4] == 1) {
      patron[0] = +8;
    }
    if (ER[5] == 1) {
      patron[0] = +4;
    }
    if (ER[6] == 1) {
      patron[0] = +2;
    }
    if (ER[7] == 1) {
      patron[0] = +1;
    }

    if (EG[0] == 1) {
      patron[1] = +128;
    }
    if (EG[1] == 1) {
      patron[1] = +64;
    }
    if (EG[2] == 1) {
      patron[1] = +32;
    }
    if (EG[3] == 1) {
      patron[1] = +16;
    }
    if (EG[4] == 1) {
      patron[1] = +8;
    }
    if (EG[5] == 1) {
      patron[1] = +4;
    }
    if (EG[6] == 1) {
      patron[1] = +2;
    }
    if (EG[7] == 1) {
      patron[1] = +1;
    }

    if (EB[0] == 1) {
      patron[2] = +128;
    }
    if (EB[1] == 1) {
      patron[2] = +64;
    }
    if (EB[2] == 1) {
      patron[2] = +32;
    }
    if (EB[3] == 1) {
      patron[2] = +16;
    }
    if (EB[4] == 1) {
      patron[2] = +8;
    }
    if (EB[5] == 1) {
      patron[2] = +4;
    }
    if (EB[6] == 1) {
      patron[2] = +2;
    }
    if (EB[7] == 1) {
      patron[2] = +1;
    }

    analogWrite(R, patron[0]);
    analogWrite(G, patron[1]);
    analogWrite(B, patron[2]);

    flag == 0;
  }
}
