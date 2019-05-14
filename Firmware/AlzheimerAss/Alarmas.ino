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
      else if (tiempoContador > 9) {
        estadoActual = estado::HORA_FECHA;
        mensajePanico();
        alarma(FREC_PANIC, 3);
        tiempoContador = 0;
      }
      tiempoContador++;
      break;

    case TEMP_HIGH:
      if (temp >= TEMP_MAX && tiempoContador < 100) {
        mensajeSensorData();
      }
      //envia una notificacion cada 10 segundos hasta que la
      //temperatura disminuya
      else if (temp >= TEMP_MAX && tiempoContador == 100) {
        Blynk.notify("Peligro Temperatura elevada!!");
        mensajeTempAlta();
        alarma(FREC_PANIC, 3);
      }
      else if (temp >= TEMP_MAX && tiempoContador == 105) {
        Blynk.notify("Peligro Temperatura elevada!!");
        mensajeTempAlta();
        alarma(FREC_PANIC, 3);
      }
      else if (tiempoContador > 109) {
        Blynk.setProperty(vTEMP_PIN, "color", "#FFFFFF");
        Blynk.notify("Peligro Temperatura elevada!!");
        estadoActual = estado::HORA_FECHA;
        mensajeTempAlta();
        alarma(FREC_PANIC, 3);
        tiempoContador = 0;
      }
      else if (temp < TEMP_MAX) {
        Blynk.setProperty(vTEMP_PIN, "color", "#FFFFFF");
        estadoActual = estado::HORA_FECHA;
        tiempoContador = 0;
      }
      tiempoContador++;
      break;

    case EJERCICIO:
      mensajeEvento("EJERCICIO!!");
      if (tiempoContador == 0) {
        alarma(FREC_CAIDA, 4);
      }
      else if (tiempoContador > 20) {
        estadoActual = estado::HORA_FECHA;
        tiempoContador = 0;
      }
      tiempoContador++;
      break;

    case MEDICAMENTO:
      mensajeEvento("MEDICAMENTO!!");
      if (tiempoContador == 0) {
        alarma(FREC_CAIDA, 4);
      }
      else if (tiempoContador > 20) {
        estadoActual = estado::HORA_FECHA;
        tiempoContador = 0;
      }
      tiempoContador++;
      break;

    case SANITARIO:
      mensajeEvento("SANITARIO!!");
      if (tiempoContador == 0) {
        alarma(FREC_CAIDA, 4);
      }
      else if (tiempoContador > 20) {
        estadoActual = estado::HORA_FECHA;
        tiempoContador = 0;
      }
      tiempoContador++;
      break;
  }
  //Serial.println(estadoActual);
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

//Funcion paras detectar altas temperaturas
void tempAlta(float tempMax) {
  if (temp >= tempMax && estadoActual != estado::TEMP_HIGH) {
    //colocamos el Widget en rojo para indicar el peligro
    Blynk.setProperty(vTEMP_PIN, "color", "#FF0000");
    estadoActual = estado::TEMP_HIGH;
  }
}
//------------------------------------------------------------
