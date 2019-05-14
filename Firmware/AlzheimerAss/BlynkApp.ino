//Sincronizamos el RTC si la conexion se pcae
BLYNK_CONNECTED() {
  //Synchronize time on connection, if connection drops
  rtc.begin();
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

//Funcion para detectar las caidas
void confirmarCaida() {
  //Algorithm to check if the patient is falling
  unsigned long tiempoActual = millis();
  if ((tiempoActual - tiempoPasado) >= INTERVALO) {
    float alturaComp = (altAnterior - altActual) * 100;
    if ((alturaComp >= (CAIDA - TOLE)) && (alturaComp <= (CAIDA + TOLE))) {
      caidaConfirm = true;
      alarma_ON = true;

      Serial.println("El paciente sufrio una caida");
      //Envia a la App un aviso cuando se detecta una caida
      Blynk.virtualWrite(vCAIDA_PIN, CAIDA_SI);
      //Blynk.notify("DPS310 detected a fall!");
    }
    mensajeCaida();
    altAnterior = altActual;  //actualiza el valor pasado al actual
    tiempoPasado = tiempoActual;
    caidaConfirm = false;

    //Si no detecta una caida envia un 0 al la App
    Blynk.virtualWrite(vCAIDA_PIN, CAIDA_NO);
  }
}
//------------------------------------------------------------
