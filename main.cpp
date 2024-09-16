#include <LiquidCrystal.h>
int funGenerador = 0;
int pul_1 = 13;
int pul_2 = 7;
int ledPul = 8;
int val = 0;
int estPul_1 = LOW;
int estPul_2 = LOW;
int estLed = LOW;
unsigned long tiempoInicio = 0;
unsigned long tiempoFin = 0;
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
    val = analogRead(funGenerador);
    Serial.println(val);
    estPul_1 = digitalRead(pul_1);
    estPul_2 = digitalRead(pul_2);

    lcd_1.setCursor(0, 0);
    lcd_1.print("Tiempo: ");

    if(digitalRead(pul_1) == HIGH){
        digitalWrite(ledPul, HIGH);
        if(digitalRead(ledPul) == HIGH){
            lcd_1.print(Tiempo());
            lcd_1.print(" ms");
                //Comenzar a capturar datos
        }
    }
    if(digitalRead(pul_2) == HIGH){
        digitalWrite(ledPul, LOW);
        if(digitalRead(ledPul) == LOW){
            //Procesar los datos
        }
    }
}

unsigned long Tiempo(){
    delay(1000);
    estPul_1 = digitalRead(pul_1);
    if (estPul_1 == HIGH) {
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
