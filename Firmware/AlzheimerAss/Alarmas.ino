//Funcion para encender el led y el buzzer de forma ritmica
void alarma(int periodo, int accion) {
  for (int i = 0; i < accion; i++) {
    digitalWrite(BUZZ, HIGH);
    digitalWrite(LED, HIGH);
    delay(periodo / 2);
    digitalWrite(BUZZ, LOW);
    digitalWrite(LED, LOW);
    delay(periodo / 2);
    tiempoContador++;
  }
}
//------------------------------------------------------------
