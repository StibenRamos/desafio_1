#include <LiquidCrystal.h>

int analogPin = 0;
int val = 0;
int Estado_Pul = 0; 
unsigned long tiempoInicio = 0; 
unsigned long tiempoFin = 0; 
unsigned long tiempoPresionado = 0;


LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup()
{
  pinMode(7, INPUT);
  Serial.begin(9600);
  lcd_1.begin(16, 2);
}

void loop()
{
  val = analogRead(analogPin);
  Serial.println(val);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Tiempo: ");
  lcd_1.print(Tiempo());
  lcd_1.print(" ms");
}

unsigned long Tiempo(){
  	delay(1000);
	Estado_Pul = digitalRead(7);
    if (Estado_Pul == HIGH) { 
    if (tiempoInicio == 0) { // Si es la primera vez que se presiona   
      tiempoInicio = millis(); 
    }
    } else { 
    if (tiempoInicio != 0) { // Si se había presionado antes
      tiempoFin = millis(); // Guarda el tiempo de fin
      tiempoPresionado = tiempoFin - tiempoInicio;
      tiempoInicio = 0; // Resetea el tiempo de inicio para la próxima vez
    }
  }
  return tiempoPresionado;
}