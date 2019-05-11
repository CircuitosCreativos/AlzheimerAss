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
  Blynk.virtualWrite(vALTURA_PIN, altura);
}
//------------------------------------------------------------
