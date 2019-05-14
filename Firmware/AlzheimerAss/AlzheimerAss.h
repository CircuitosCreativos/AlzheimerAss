#ifndef __AlzheimerAss_H__
#define __AlzheimerAss_H__

//Definimos los pines necesarios para controlar el hardware
//LCD Nokia 5110
#define CLK       19
#define DIN       18
#define RST       2
#define CE        4
#define DC        5
#define BL        21

//Bluetooth HC_05
#define STATUS    15
#define RXD2      16
#define TXD2      17

//parametros constantes
//Comandos sensor Hub nano
//Defining Sensor Hub Nano board commands
#define HELLO         "$hello id="
#define INFO          "$info id="
#define SENSOR_INFO   "$sinfo id=1"
#define LOW_ENERGY    "$set_mode sid=1;md=mode;val=bg"
#define STANDARD_MODE "$set_mode sid=1;md=prs_osr;val=16"
#define HIGH_PRESI    "$set_mode sid=1;md=prs_mr;val=32"
#define START         "$start_sensor id=1"
#define STOP          "$stop id="

//Aplicacion Blynk Alzheimer_Ass
#define vTEMP_PIN     V0    //pin virtual temperatura en la App
#define vPRES_PIN     V1    //pin virtual presion barometrica en la App
#define vALTURA_PIN   V2    //pin virtual altura en la App
#define vEVENTOR_PIN  V3    //pin virtual en la App
#define vCAIDA_PIN    V4    //pin virtual en la App

//Deteccion de caidas
#define INTERVALO     1000  //intervalo de tiempo revisar caidas (1seg)
#define CAIDA         70    //Umbral de 0.7m para detectar una caida
#define TOLE          20    //Margen de tolerancia para detectar caidas
#define CAIDA_SI      255
#define CAIDA_NO      0

//Pantalla Nokia 5110
#define SPI_CLK   1000000 //Velocidad bus SPI (1MHz)    

#endif
