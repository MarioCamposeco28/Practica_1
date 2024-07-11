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

#include <Wire.h>    
#include <LiquidCrystal_I2C.h>

#define IN1  9
#define IN2  10
#define IN3  11
#define IN4  12

#define pot A0

#define direccion_lcd 0x27
#define filas 2
#define columnas 16

#define sensor_hall 2

#define sensor_IR 3

LiquidCrystal_I2C lcd(direccion_lcd, columnas, filas);

unsigned int valor_pot;
unsigned int velocidad_motor;

bool state_sensor;

int paso[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

void setup(){
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(pot, INPUT);
  
  lcd.init(); 
  lcd.backlight(); 
  lcd.print("Contador de rev.");
  lcd.setCursor(0, 1);
  lcd.print("No. De Rev.");
  lcd.print(state_sensor);

  pinMode(sensor_hall, INPUT); 
  
  pinMode(sensor_IR, INPUT);
}

void loop(){
  state_sensor = digitalRead(sensor_IR); 
  
  valor_pot = analogRead(pot);
  velocidad_motor = map(valor_pot, 0, 1023, 1, 6);  // Ajusta la velocidad del motor

  if(state_sensor == LOW){
  for (int i = 0; i < 8; i++){
    digitalWrite(IN1, paso[i][0]);
    digitalWrite(IN2, paso[i][1]);
    digitalWrite(IN3, paso[i][2]);
    digitalWrite(IN4, paso[i][3]);
    delay(velocidad_motor);
    
    state_sensor = digitalRead(sensor_hall);                      
    if(state_sensor == LOW){
    delay(10);
    }
  }
  }
}




  
