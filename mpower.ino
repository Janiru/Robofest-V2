void mpower(int lm, int rm) {

  if (lm > 255) {
    lm = 255;
  }
  if (lm == 0) {
    digitalWrite(LmS, LOW);
  }

  if (lm > 0 && lm <= 255) {
    digitalWrite(LmF, HIGH);
    digitalWrite(LmB, LOW);
    analogWrite(LmS, lm);
  }

  else if (lm < 0) {
    digitalWrite(LmB, HIGH);
    digitalWrite(LmF, LOW);
    analogWrite(LmS, lm * -1);
  }

  if (rm > 255) {
    rm = 255;
  }

  if (rm == 0) {
    digitalWrite(RmS, LOW);
  }

  if (rm > 0 && rm <= 255) {
    digitalWrite(RmF, HIGH);
    digitalWrite(RmB, LOW);
    analogWrite(RmS, rm);
  }
  else if (rm < 0) {
    digitalWrite(RmB, HIGH);
    digitalWrite(RmF, LOW);
    analogWrite(RmS, rm * -1);
  }

}
