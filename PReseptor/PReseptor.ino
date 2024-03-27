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

byte acuR = 0; // variables acumuladoras para el valor de salida del PWM
byte acuG = 0;
byte acuB = 0;

void parada(){
  
  }

void setup() {
  attachInterrupt (digitalPinToInterrupt (CLK),parada, RISING); //acctiva una iterrupcion cuando el pin del clock pasa de bajo a alto
  
  pinMode(EMS,INPUT);
  pinMode(E7,INPUT);
  pinMode(E6,INPUT);
  pinMode(E5,INPUT);
  pinMode(E4,INPUT);
  pinMode(E3,INPUT);
  pinMode(E2,INPUT);
  pinMode(E1,INPUT);

  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
