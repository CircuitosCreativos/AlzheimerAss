void luzFondo(bool bl) {
  if (bl == true) {
    digitalWrite(BL, HIGH);
  }
  else {
    digitalWrite(BL, LOW);
  }
}
//------------------------------------------------------------

//Mensaje de inicio del sistema
void mensajeInicio(uint8_t xPos, uint8_t yPos) {
  //Definimos los parametros para el marco
  uint8_t x = 4;
  uint8_t y = 0;
  uint8_t ancho = 75;
  uint8_t alto = 48;
  uint8_t r = 8;

  //Mostramos el mensaje de inicio
  u8g2.clearBuffer();
  u8g2.drawRFrame(x, y, ancho, alto, r);
  u8g2.setFont(u8g2_font_prospero_bold_nbp_tf);
  u8g2.drawStr(xPos, yPos, "Asistente");
  u8g2.drawStr(xPos + 15, yPos + 13, "para");
  u8g2.drawStr(xPos, yPos + 28, "Alzheimer");
  u8g2.sendBuffer();
}
//------------------------------------------------------------

void esperaConexion(uint8_t xPos, uint8_t yPos) {
  //Muestra un mensaje de espera de conexion con el sensor Hub nano
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_prospero_bold_nbp_tf);
  u8g2.drawStr(xPos, yPos, "Conectando");
  u8g2.drawStr(xPos + 1, yPos + 13, "con sensor");
  u8g2.drawStr(xPos + 2, yPos + 26, "Hub Nano!!!");
  u8g2.sendBuffer();
}
//------------------------------------------------------------

void sensorConectado(uint8_t xPos, uint8_t yPos) {
  //Muestra un mensaje cuando el sensor esta conectado
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x13B_tf);
  u8g2.drawStr(xPos, yPos, "Conectado a");
  u8g2.drawStr(xPos + 6, yPos + 12, "Infineon's");
  u8g2.drawStr(xPos + 6, yPos + 24, "Sensor Hub");
  u8g2.drawStr(xPos + 28, yPos + 36, "Nano");
  u8g2.sendBuffer();
}
//------------------------------------------------------------

void mensajeError() {
  //Muestra el mensaje de error
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_fub14_tf);
  u8g2.drawStr(9, 30, "ERROR");
  u8g2.sendBuffer();
}
//------------------------------------------------------------
//Muestra la hora y la fecha en el LCD
void verHoraFecha() {
  //Displays the time and date from the RTC widget in Blynk in 24 hours format
  if (year() == 1970 && Serial.available()) {
    Serial.println("El reloj no esta sincronizado!!");
  }
  else if (year() != 1970) {
    char bufHours[3];
    char bufColon[2];
    char bufMinutes[3];
    char bufDate[11];

    String currentHours = String(hour());
    String colon = ":";
    String currentMinutes = String(minute());
    String currentDate = String(day()) + "/" + month() + "/" + year();

    String(currentHours).toCharArray(bufHours, 3);
    String(colon).toCharArray(bufColon, 2);
    String(currentMinutes).toCharArray(bufMinutes, 3);
    String(currentDate).toCharArray(bufDate, 11);

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_inr33_mf);
    u8g2.drawStr(30, 30, bufColon);
    u8g2.setFont(u8g2_font_logisoso32_tn);
    u8g2.drawStr(0, 32, bufHours);
    u8g2.drawStr(45, 32, bufMinutes);
    u8g2.setFont(u8g2_font_saikyosansbold8_8n);
    u8g2.drawHLine(0, 35, 85);
    u8g2.drawStr(0, 46, bufDate);
    u8g2.sendBuffer();
  }
}
//------------------------------------------------------------

//muestra los datos obtenidos del sensor Hub
void mensajeSensorData() {
  char bufT[10];  //Array para convertir el float en char
  char bufP[10];  //Array para convertir el float en char
  char bufA[10];  //Array para convertir el float en char

  //Convertimos en char las variables float que entrega el sensor
  String(temp).toCharArray(bufT, 10);
  String(pres).toCharArray(bufP, 10);
  String(altActual).toCharArray(bufA, 10);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf );

  //mostramos la temperatura en grados Celsius
  u8g2.drawStr(0, 10, "T:");
  u8g2.drawStr(12, 10, bufT);
  u8g2.drawStr(73, 10, "C");
  u8g2.drawCircle(70, 4, 1, U8G2_DRAW_ALL);
  u8g2.drawHLine(0, 12, 85);

  //mostramos la presion barometrica en milibares
  u8g2.drawStr(0, 26, "P:");
  u8g2.drawStr(12, 26, bufP);
  u8g2.drawStr(60, 26, "mBar");
  u8g2.drawHLine(0, 28, 85);

  //mostramos la altura con respecto al mar en metros
  u8g2.drawStr(0, 42, "A:");
  u8g2.drawStr(12, 42, bufA);
  u8g2.drawStr(72, 42, "m");
  u8g2.drawHLine(0, 44, 85);

  u8g2.sendBuffer();  //Enviamos los valores al LCD
}
//------------------------------------------------------------

//muestra un mensaje cuando el paciente sufre una caida
void mensajeCaida() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x13B_tf);
  u8g2.drawStr(10, 10, "Paciente");
  u8g2.drawStr(15, 22, "Sufrio");
  u8g2.drawStr(13, 34, "CAIDA!!");
  u8g2.sendBuffer();
}
//------------------------------------------------------------

//muestra un aviso cuando se presiona el boton de panico
void mensajePanico() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x13B_tf);
  u8g2.drawStr(10, 10, "Boton de");
  u8g2.drawStr(17, 22, "panico");
  u8g2.drawStr(6, 34, "ACTIVADO!!");
  u8g2.sendBuffer();
}
//------------------------------------------------------------

//muestra un aviso cuando la temperatura esta muy elevada
void mensajeTempAlta() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x13B_tf);
  u8g2.drawStr(14, 10, "Peligro");
  u8g2.drawStr(6, 22, "temperatura");
  u8g2.drawStr(8, 34, "ELEVADA!!");
  u8g2.sendBuffer();
}
//------------------------------------------------------------

//muestra un aviso cuando se dispara algun evento programado
void mensajeEvento(char nombre[]) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x13B_tf);
  u8g2.drawStr(24, 10, "Hora");
  u8g2.drawStr(30, 22, "de");
  u8g2.drawStr(7, 34, nombre);
  u8g2.sendBuffer();
}
//------------------------------------------------------------
