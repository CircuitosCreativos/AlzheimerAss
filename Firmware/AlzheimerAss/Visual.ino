//Mensaje de inicio del sistema
void mensajeInicio(uint8_t fila, uint8_t columna) {
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
  u8g2.drawStr(fila, columna, "Asistente");
  u8g2.drawStr(fila + 15, columna + 13, "para");
  u8g2.drawStr(fila, columna + 28, "Alzheimer");
  u8g2.sendBuffer();
}
//------------------------------------------------------------
