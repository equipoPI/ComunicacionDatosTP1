int LEDP[] = {2, 3, 4, 5, 6, 7, 8, 9}; //array donde definimos los pines por donde enviaremos el valor generado

#define CLK 10                        //pin del clok

volatile int flag = 0;                //variables de control de estado; vinculado con el encio y la parada
volatile int flag1 = 1;

volatile int cont = 1;                //variable saosida el estado de cambio de color

int color = 0;                        //variable para guardar el valor de color generado automaticamente

const int BotonEncenderApagar = 18;   //pines donde iran conectados los pulsadores de envio/parada y cambio de color
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
  for (int i = 0; i < 8; i++) {  //Se declaran los pines como salidas utilizando un ciclo for
    pinMode(LEDP[i], OUTPUT);
  }

  pinMode(CLK, OUTPUT); //se define el pin clock como salida

  attachInterrupt (digitalPinToInterrupt (BotonEncenderApagar), interrupcion1, FALLING); //Se decalara la interrupción de Encender/Apagar
  attachInterrupt (digitalPinToInterrupt (BotonCambiarColor), interrupcion2, FALLING);   //Se decalara la interrupción de Cambio de color

}

void loop() {

  if (flag == 0) {// Si la comunicación esta apagado, envia el 0 a todas las salidas
    if (flag1 == 1) {
      for (int c = 0; c < 3; c++) {           //con el primer for nos aseguramos de hacer que se imprima tres veces el valor 0 a las salida, cada vez es un color que se pondra en 0
        for (int i = 0; i < 8; i++) {         //con el segundo for imprimimo el valor 0 en todas las salidas para que se apage el led
          digitalWrite(LEDP[i], LOW);
        }
        delay(50);                            //generamos un pulso en el pin clock que activara en el receptor una funcion para sincronizar los dispositivos
        digitalWrite(CLK, HIGH);
        delay(50);
        digitalWrite(CLK, LOW);
        delay(50);
      }
      flag1 = 0;
    }
    cont = 1;
  }

  else {                                          //si en estado de flag pasa a 1 se establece una comunicacion
    if (cont >= 1) {                              //si el valor del cont es mayor a uno se genera un color aleatorio; por defecto cont empieza en 1 y vuelve a este estado cada ves que se pulsa el boton cambio de color
      for (int u = 0; u < 3; u++) {               //con este for nos aseguramos de hacer que se imprima tres veces el valor del color a las salida, cada vez es un valor asociado al pin de cada color del rgb
        color = random (255);                     //genera el codigo de color de forma aleatoria y lo almacena en la variable
        for (int x = 0; x < 8; x++) {                    // con este for imprimimos la variable color en las salidas, se ejecuta una ves ppor cada salida utilizada o
          digitalWrite(LEDP[x], bitRead(color, x));      //utilizando bitread podemos convertir el valor de decimal generado aleatoriamente a binario para poder astablecer lo estados de las salidas
        }
        delay(50);                                //generamos un pulso en el pin clock que activara en el receptor una funcion para sincronizar los dispositivos
        digitalWrite(CLK, HIGH);
        delay(50);
        digitalWrite(CLK, LOW);
        delay(50);
      }
      cont = 0;
    }
  }
}
