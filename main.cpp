#include <LiquidCrystal.h>

unsigned long tiempoInicio;
unsigned long tiempoTranscurrido;
int funGenerador = 0;
float maxVal = -1023;
float minVal = 1023;
float amplitud;
float periodo;
float frecuencia;
int pul_1 = 13;
int pul_2 = 7;
int ledPul = 8;
int val = 0;
int estPul_1 = LOW;
int estPul_2 = LOW;
int estLed = LOW;


LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup()
{
    pinMode(pul_1, INPUT);
    pinMode(pul_2, INPUT);
    pinMode(ledPul, OUTPUT);
    Serial.begin(9600);
    lcd_1.begin(16, 2);
    tiempoInicio = millis();
}

void loop()
{
    val = analogRead(funGenerador);
    if(val > maxVal){
        maxVal = val;
    }
    if (val < minVal){
        minVal = val;
    }
    amplitud = (maxVal - minVal) * (5.0/1023.0);

    if (val > 0) {
        tiempoTranscurrido = millis();
        periodo = tiempoTranscurrido - tiempoInicio;
        frecuencia = 1000.0 / periodo;
    }

    Serial.print(val);
    Serial.print(", A:");
    Serial.print(amplitud);
    Serial.print(", F :");
    Serial.println(frecuencia);
    estPul_1 = digitalRead(pul_1);
    estPul_2 = digitalRead(pul_2);
    lcd_1.blink();

    if(digitalRead(pul_1) == HIGH){
        digitalWrite(ledPul, HIGH);
        if(digitalRead(ledPul) == HIGH){
            lcd_1.clear();
            lcd_1.setCursor(0, 0);
            lcd_1.print("Capturando...");
            lcd_1.setCursor(0, 1);
            //Comenzar a capturar datos
        }
    }
    if(digitalRead(pul_2) == HIGH){
        digitalWrite(ledPul, LOW);
        if(digitalRead(ledPul) == LOW){
            lcd_1.clear();
            lcd_1.setCursor(0, 0);
            lcd_1.print("Tiempo: ");
            lcd_1.print(" ms");
            //Procesar los datos
        }
    }
}
