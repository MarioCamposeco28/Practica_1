/* 
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AV 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Uso del sensor Ultrasónico
   Dev: Profe. Alejandro Lopez Navas
   Fecha: 20 de junio.
*/

#include <Adafruit_NeoPixel.h>

#define pinTrig A5
#define pinEcho A4
#define A 4
#define B 5
#define C 6
#define D 7
#define E 8
#define F 9
#define G 10

#define leds 7  // Cambiado a 7 LEDs
#define pinLed A3

const int N = 7;
const int segmentos[N] = {A, B, C, D, E, F, G};

const int digitos[11][N] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2 
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}, // 9
  {0, 0, 0, 0, 0, 0, 1}  // G
};

const int maxPersonas = 9; 
int contador = 0; 

Adafruit_NeoPixel neopixel(leds, pinLed, NEO_GRB + NEO_KHZ800);

float leerDistancia(void);
void mostrarContador(int valor);

void setup(){
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  digitalWrite(pinTrig, LOW);
  Serial.begin(9600);
  Serial.println("Contador de aforo");

  neopixel.begin();
  
  // Apagar todos los LEDs al inicio
  for(int i = 0; i < leds; i++) {
    neopixel.setPixelColor(i, 0, 0, 0); 
    neopixel.show();
  }
  for(int i = 0; i < leds; i++) {
        neopixel.setPixelColor(i, 0, 255, 0); // Cambia el color a verde para todas las LEDs
        neopixel.show();
      }

  for(int i = 0; i < N; i++){
    pinMode(segmentos[i], OUTPUT);
    digitalWrite(segmentos[i], LOW);
  }

  mostrarContador(0);
}

void loop() {
  float distancia = leerDistancia();
  
  if(distancia >= 6 && distancia <= 10) {
    Serial.print("Distancia medida por el sensor: ");
    Serial.print(distancia); 
    Serial.println(" cm");

    if(contador < maxPersonas){
      contador++; 
      mostrarContador(contador);
    }
    if(contador == 9){
      mostrarContador(maxPersonas);
      contador++; 
      delay(700);
      for(int i = 0; i < leds; i++) {
        
        neopixel.setPixelColor(i, 255, 0, 0); // Cambia el color a rojo para todas las LEDs
        neopixel.show();
      }
       mostrarContador(10);
    } 
    }
    delay(1000); 
  }

float leerDistancia(void){
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  
  long echoSensor = pulseIn(pinEcho, HIGH);
  long distancia = echoSensor / 59;
  
  return distancia;
}

void mostrarContador(int valor){
  for(int i = 0; i < N; i++){
    digitalWrite(segmentos[i], digitos[valor][i]);
  }
}
