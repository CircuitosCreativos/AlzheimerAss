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
#define HIGH_PRECI    "$set_mode sid=1;md=prs_mr;val=32"
#define START         "$start_sensor id=1"
#define STOP          "$stop id="

//Pantalla Nokia 5110
#define SPI_CLK   1000000 //Velocidad bus SPI (1MHz)    

#endif
