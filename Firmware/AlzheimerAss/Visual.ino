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
