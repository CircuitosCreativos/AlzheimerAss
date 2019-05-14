//Sincronizamos el RTC si la conexion se pcae
BLYNK_CONNECTED() {
  //Synchronize time on connection, if connection drops
  rtc.begin();
}
//------------------------------------------------------------

//verificamos con el Widget de eventos es hora de hacer ejercicio,
//ir al baño o tomar medicamentos
BLYNK_WRITE(vEVENTOR_PIN) {
  int valor =  param.asInt();

  switch (valor) {
    case 1:
      estadoActual = estado::EJERCICIO;
      tiempoContador = 0;
      break;

    case 2:
      estadoActual = estado::MEDICAMENTO;
      tiempoContador = 0;
      break;

    case 3:
      estadoActual = estado::SANITARIO;
      tiempoContador = 0;
      break;
  }
}
//------------------------------------------------------------

//Envia los datos a la aplicacion
void enviaDatosSensor() {
  //Sending the sensor values to the Blynk server
  Blynk.virtualWrite(vTEMP_PIN, temp);
  Blynk.virtualWrite(vPRES_PIN, pres);
  Blynk.virtualWrite(vALTURA_PIN, altActual);
}
//------------------------------------------------------------

//Configuramos el color de los Widgets en la app
void setBlynkWidgets() {
  //usamos el color blanco para la tamperatura
  Blynk.setProperty(vTEMP_PIN, "color", "#FFFFFF");
  //usamos el color azul para la presion barometrica
  Blynk.setProperty(vPRES_PIN, "color", "#00BBFF");
  //usamos el color amarillo para la altura
  Blynk.setProperty(vALTURA_PIN, "color", "#DDDD00");
}
//------------------------------------------------------------

//Funcion para detectar las caidas
void confirmarCaida() {
  //Algorithm to check if the patient is falling
  unsigned long tiempoActual = millis();
  if ((tiempoActual - tiempoPasado) >= INTERVALO) {
    float alturaComp = (altAnterior - altActual) * 100;
    if ((alturaComp >= (UMBRAL - TOLE)) && (alturaComp <= (UMBRAL + TOLE))) {
      estadoActual = estado::CAIDA;
      tiempoContador = 0;
      Serial.println("El paciente sufrio una caida");
      //Envia a la App un aviso cuando se detecta una caida
      Blynk.virtualWrite(vCAIDA_PIN, CAIDA_SI);
      //Blynk.notify("DPS310 detected a fall!");
    }
    altAnterior = altActual;  //actualiza el valor pasado al actual
    tiempoPasado = tiempoActual;

    //Si no detecta una caida envia un 0 al la App
    Blynk.virtualWrite(vCAIDA_PIN, CAIDA_NO);
  }
}
//------------------------------------------------------------
