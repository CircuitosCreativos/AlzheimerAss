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
#include <BlynkSimpleEsp32.h> //comunicacion con la app Blynk
#include <HardwareSerial.h>   //Puerto serial para el HC-05
#include "AlzheimerAss.h"     //Archivo de cabezera del proyecto
#include <U8g2lib.h>          //Controla la pantala LCD
#include <WidgetRTC.h>        //Reloj en tiempo real desde Blynk
//------------------------------------------------------------

//instanciamos los objetos de las librerias
//LCD Nokia 5110
U8G2_PCD8544_84X48_F_4W_SW_SPI u8g2(U8G2_R0, CLK, DIN, CE, DC, RST);
HardwareSerial HC05(2);   //Usaremos la UART2 del ESP32
BlynkTimer timer;
WidgetRTC rtc;
//------------------------------------------------------------

//Declaramos las variables globales necesarias
//Comunicacion con la App de Blynk mediante WiFi
char auth[] = "c73f497faf3c43c7b36d1be975c1ca5b";  //Token
char ssid[] = "Nexxt_505B10";   //Nombre de la red
char pass[] = "Administrador";  //Contraseña (WPA2)

//Banderas de control
bool caidaConfirm = false;//Indica si el paciente sufrio una caida
bool btConectado = false; //Indica si la conexion bluetooth se establecio

//Variables medidas por el sensor Hub
float temp;
float pres;
float altActual;
float altAnterior;
unsigned long tiempoPasado = 0; //ayuda a medir el tiempo transcurrido
//------------------------------------------------------------

//Funcion de configuracion
void setup() {
  //iniciamos las comunicaciones Serial y Bluetooth
  Serial.begin(115200);
  HC05.begin(115200, SERIAL_8N1, RXD2, TXD2);

  //Establecemos los intervalos de tiempos para disparar las funciones
  timer.setInterval(1000L, enviaDatosSensor);
  timer.setInterval(3000L, verHoraFecha);

  u8g2.setBusClock(SPI_CLK);//EL driver del LCD trabaja excelente a 1MHz
  u8g2.begin(); //iniciamos el LCD Nokia 5110

  //configuramos los pines de entrada/salida
  pinMode(STATUS, INPUT);
  pinMode(BL, OUTPUT);

  //Activamos la luz de fondo y mostramos el mensaje de inicio
  luzFondo(true);
  mensajeInicio(13, 15);
  delay(2000);    //Esperamos 2 segundos

  //Revisamos si la conexion con el sensor Hub se establecio
  while (!btConectado) {
    if (digitalRead(STATUS) == HIGH) {
      btConectado = true;
    }
    else {
      esperaConexion(8, 15);
    }
  }
  iniciaSensor();

  Blynk.begin(auth, ssid, pass);//conexion WiFi con la aplicacion Blynk
  rtc.begin();  //Iniciamos el reloj en tiempo realB
  //Tambien se puede especificar el servidor
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  verHoraFecha();
  enviarComando(HIGH_PRESI);  //usamos el sensor en modo Alta presicion
  enviarComando(START);
}
//------------------------------------------------------------

//Funcion principal
void loop() {
  Blynk.run();
  timer.run();
  //Aqui se puede colocar cogido adicional dependiendo del proyecto
  //Recuerde evitar la funcion delay();
  leerDatosSensor();
  confirmarCaida();
}
//------------------------------------------------------------
