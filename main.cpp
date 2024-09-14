#include <LiquidCrystal.h>

int seconds = 0;
int analogPin = 0;
int val = 0;
int Pulsador = 7;
int Estado_Pul = 0;
int even_time= 0;
bool Suceso_time = false;

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

unsigned long Tiempo(){
    
    pinMode(Pulsador, INPUT);
    
  Estado_Pul = digitalRead(Pulsador);
    
    if ( Estado_Pul == LOW && !Suceso_time ){
        
       even_time = millis(); // Devuelve el tiempo en milisegundos desde que Arduino comenzó
        Suceso_time = true;
    }
    if ( Suceso_time) {
      
      unsigned long Intervalo_tiempo = millis() - even_time;
      return Intervalo_tiempo; 
        
    }
   return 0; 
}

void setup()
{
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  lcd_1.print("Odio esto");
}

void loop()
{
  val = analogRead(analogPin);
  Serial.println(val);
  lcd_1.setCursor(0, 1);
  lcd_1.print(seconds);
  delay(1000);
  seconds += 1;
  
  unsigned long Tiempo_obtenido = Tiempo();
  if (Tiempo_obtenido != 0) {
        
        Serial.println(Tiempo_obtenido);

    }
}