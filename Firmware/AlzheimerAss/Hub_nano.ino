//Inicio comunicacion son el sensor Hub nano
void iniciaSensor() {
  //Inicia el Sensor Hub nano y give an error if there is any problem
  String datos; //Almacena los datos entregados por el sensor
  enviarComando(INFO);
  while (HC05.find("IFX_NanoHub") == false) {
    enviarComando(INFO);
    Serial.println("ERROR");
    mensajeError();
  }
  datos = HC05.readStringUntil('\n');
  Serial.println(datos);
  datos = "";
  sensorConectado(0, 10);
  delay(1500);
}
//------------------------------------------------------------

//Enviar comandos al sensor Hub nano
void enviarComando (String comando) {
  HC05.println(comando);
  HC05.flush();
}
//------------------------------------------------------------
