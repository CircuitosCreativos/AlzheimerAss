//menu para mostrar los diferentes mensajes de alarmas
void menuAlarmas() {
  switch (estadoActual) {
    case HORA_FECHA:
      verHoraFecha();
      if (tiempoContador > 20) {
        estadoActual = estado::DATOS_SENSOR;
        tiempoContador = 0;
      }
      tiempoContador++;
      break;

    case DATOS_SENSOR:
      mensajeSensorData();
      if (tiempoContador > 15) {
        estadoActual = estado::HORA_FECHA;
        tiempoContador = 0;
      }
      tiempoContador++;
      break;

    case CAIDA:
      if (tiempoContador == 0) {
        mensajeCaida();
        alarma(FREC_CAIDA, 3);
      }
      else if (tiempoContador > 5) {
        estadoActual = estado::HORA_FECHA;
        mensajeCaida();
        alarma(FREC_CAIDA, 3);
        tiempoContador = 0;
      }
      tiempoContador++;
      break;

    case PANIC:
      if (tiempoContador == 0) {
        mensajePanico();
        alarma(FREC_PANIC, 3);
      }
      else if (tiempoContador == 5) {
        mensajePanico();
        alarma(FREC_PANIC, 3);
      }
      else if (tiempoContador > 10) {
        estadoActual = estado::HORA_FECHA;
        mensajePanico();
        alarma(FREC_PANIC, 3);
        tiempoContador = 0;
      }
      tiempoContador++;
      break;

    case TEMP_HIGH:
      verHoraFecha();
      break;
  }
  Serial.println(estadoActual);
}
//-----------------------------------------------------------

//Funcion para encender el led y el buzzer de forma ritmica
void alarma(int periodo, int accion) {
  for (int i = 0; i < accion; i++) {
    digitalWrite(BUZZ, HIGH);
    digitalWrite(LED, HIGH);
    delay(periodo / 2);
    digitalWrite(BUZZ, LOW);
    digitalWrite(LED, LOW);
    delay(periodo / 2);
  }
}
//------------------------------------------------------------

//Funcion para el boton de panico
void botonPanico() {
  bool boton = digitalRead(BOT_PANIC);
  if (boton == HIGH) {
    Blynk.notify("Boton de panico activado!!");
    estadoActual = estado:: PANIC;
    tiempoContador = 0;
  }
}
//------------------------------------------------------------
