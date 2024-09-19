#include <LiquidCrystal.h>

unsigned long tiempoInicio;
unsigned long tiempoTranscurrido;
int funGenerador = 0; // Asegúrate de que este es el pin correcto
float maxVal = 0;
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
bool capturando = false;

// Punteros
float *pun_maxVal = &maxVal;
float *pun_minVal = &minVal;
int *Cuadra;
int *Cuadra_1;

// Memoria
const int Tam = 20; // número de espacios para los datos de la señal
int *pun_men = new int[Tam];
int pos_arre = 0;  // registro de la posición actual en el arreglo donde se debe almacenar el próximo valor

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
    estPul_1 = digitalRead(pul_1);
    estPul_2 = digitalRead(pul_2);
    estLed = digitalRead(ledPul);

    if (estPul_1 == HIGH) {
        capturando = true;
        digitalWrite(ledPul, HIGH);
    }

    if (estPul_2 == HIGH) {
        capturando = false;
        digitalWrite(ledPul, LOW);
    }

    if (capturando) {
        val = analogRead(funGenerador);
        pun_men[pos_arre] = val;  // 8
        pos_arre = (pos_arre + 1) % Tam;

        *Cuadra = pun_men[0];
        *Cuadra_1 = pun_men[0];
        for (int i = 1; i < Tam; ++i) {
            if (pun_men[i] == *Cuadra) {
                *Cuadra = pun_men[i];
                Serial.print(*Cuadra);
                Serial.print("Es cuadrada");
            }
            if (pun_men[i] != *Cuadra) {
                *Cuadra_1 = pun_men[i];
            }
        }

        if(val > *pun_maxVal){
            *pun_maxVal = val;
        }
        if (val < *pun_minVal){
            *pun_minVal = val;
        }
        amplitud= ( *pun_maxVal - *pun_minVal ) * (5.0/1023.0);

        if (val > 512) {
            tiempoTranscurrido = millis();
            periodo =   tiempoTranscurrido - tiempoInicio ;
            frecuencia = 1000.0/ periodo;
            tiempoInicio = tiempoTranscurrido;
        }
    }

    if (estLed == HIGH) {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Onda...");
        lcd_1.setCursor(0, 1);
        lcd_1.print(frecuencia);
        lcd_1.print(" Hz");
        lcd_1.setCursor(10, 1);
        lcd_1.print(amplitud);
        lcd_1.print(" V");
        delay(100);
        Serial.print(val);
        Serial.print(", A:");
        Serial.print(amplitud);
        Serial.print(", F:");
        Serial.print(frecuencia);
        Serial.print(", P:");
        Serial.println(periodo);
    }

    if (estLed == LOW) {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Esperando...");
        // Reiniciar valores
        *pun_maxVal = 0;
        *pun_minVal = 1023;
        amplitud = 0;
        periodo = 0;
        frecuencia = 0;
        delay(100);
    }
}
