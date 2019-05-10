/*
  Project : Asistente Alzhaimer
  Version : 1.2.0
  Date    : 10/05/2019-17/05/2019
  Author  : Carlos Andres Betancourt
  Company :
  Comments: puede monitorear al paciente desde cualquier lugar con
  conexion a internet

  Chip type               : DOIT ESP32 V1
  Program type            : Application
  AVR Core Clock frequency: 80MHz
  Memory model            : Small
  External RAM size       : 0
  Data Stack size         : 512
  commit:
  ---------------------------------------------------------------
  Conexiones electricas

  ---------------------------------------------------------------*/

//Incluimos las librerias y archivos de cabecera necesarios
#include "AlzheimerAss.h"
#include <U8g2lib.h>
#include <SPI.h>
//------------------------------------------------------------

//instanciamos los objetos de las librerias
//LCD Nokia 5110
U8G2_PCD8544_84X48_F_4W_SW_SPI u8g2(U8G2_R0, CLK, DIN, CE, DC, RST);
//------------------------------------------------------------

//Funcion de configuracion
void setup() {
  pinMode(BL, OUTPUT);

  digitalWrite(BL, LOW);

  u8g2.begin();
}
//------------------------------------------------------------

//Funcion principal
void loop() {
  digitalWrite(BL, HIGH);
  mensajeInicio(13, 15);

}
