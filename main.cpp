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
bool capturando = false; // Variable para saber si estamos capturando datos

// Punteros

float *pun_maxVal = &maxVal;
float *pun_minVal = &minVal;

// memoria

int Tam = 10; // numero de espacios para los datos de la señal.
int *pun_men = new int [Tam];
int pos_arre = 0;  // registro de la posición actual en el arreglo donde se debe almacenar el próximo valor. en este caso la primera posición del arreglo comienza en 0.

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

    if(estPul_1 == HIGH && !capturando){
        capturando = true;
        digitalWrite(ledPul, HIGH);
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Capturando...");
    }

    if(estPul_2 == HIGH && capturando){
        capturando = false;
        digitalWrite(ledPul, LOW);
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Tiempo: ");
        lcd_1.print(tiempoTranscurrido);
        lcd_1.print(" ms");
    }

    if(capturando){
        val = analogRead(funGenerador);
        pun_men[pos_arre] = val;
        pos_arre = (pos_arre + 1) % Tam;

        if(val > *pun_maxVal){
            *pun_maxVal = val;
        }
        if (val < *pun_minVal){
            *pun_minVal = val;
        }
        amplitud= (maxVal - minVal) * (5.0/1023.0);

        if (val > 0) {
            tiempoTranscurrido = millis();
            periodo = tiempoTranscurrido - tiempoInicio;
            frecuencia = 1000.0 / periodo;
            tiempoInicio = tiempoTranscurrido;
        }

        Serial.print(val);
        Serial.print(", A:");
        Serial.print(amplitud);
        Serial.print(", F :");
        Serial.println(frecuencia);
    }
}
