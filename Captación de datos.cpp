#include <LiquidCrystal.h>
int funGenerador = 1;
int pul_1 = 13;
int pul_2 = 7;
int ledPul = 8;
int val = 0;
int estPul_1 = LOW;
int estPul_2 = LOW;
int estLed = LOW;
unsigned long tiempoInicio = 0; 
unsigned long tiempoPresionado = 0;


LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup()
{
  pinMode(pul_1, INPUT);
  pinMode(pul_2, INPUT);
  pinMode(ledPul, OUTPUT);
  Serial.begin(9600);
  lcd_1.begin(16, 2);
}

void loop()
{
  Tiempo();  

  lcd_1.setCursor(0, 0);
  lcd_1.print("Tiempo: ");
  lcd_1.print(tiempoPresionado);
  lcd_1.print(" ms");

  lcd_1.setCursor(0, 1);
  lcd_1.print("Val: ");
  lcd_1.print(val);
  
  Serial.print(tiempoPresionado);  
  Serial.print(",");             
  Serial.println(val);  
    }



unsigned long Tiempo(){
  estPul_1 = digitalRead(pul_1);
  estPul_2 = digitalRead(pul_2);

  if (estPul_1 == HIGH && estLed == LOW) { 
    estLed = HIGH;                  // Cambiar estado del LED a encendido
    tiempoInicio = millis();        // Iniciar el conteo de tiempo
    digitalWrite(ledPul, HIGH);     // Encender el LED
  }
  
  if (estPul_2 == HIGH && estLed == HIGH) { 
    estLed = LOW;                   // Cambiar estado del LED a apagado
    digitalWrite(ledPul, LOW);      // Apagar el LED
    lcd_1.clear();                  
  }

  if (estLed == HIGH) {
    val = analogRead(funGenerador); 
    tiempoPresionado = millis() - tiempoInicio;  // Calcular el tiempo transcurrido
  }
}
 
