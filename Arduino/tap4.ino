// BUZZER THINGS
void SoundProcess(int _melody[], int _tempo[], int _size)
{
  for (int thisNote = 0; thisNote < _size; thisNote++)
  {
    int noteDuration = 1000 / _tempo[thisNote];
    tone(BUZZER_PIN, _melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
}
void wakeUpSound()
{
  //  int melody[] = {1319, 1568, 2637, 2093, 2349, 3136};
  //  int tempo[] = {25, 25, 25, 25, 25, 25};
  int melody[] = {1319, 1568, 2637, 2093, 2349, 3136};
  int tempo[] = {25, 25, 25, 25, 25, 25};
  SoundProcess(melody, tempo, 6);

}
void chargingSound()
{
  int melody[] = {1500, 1500, 1500, 3000, 2000, 2500, 2500};
  int tempo[] = {25, 25, 25, 25, 25, 25, 25};
  SoundProcess(melody, tempo, 7);
}

void Sound_Beep1()
{
  int melody[] = {2637, 1568, 1216};
  int tempo[] = {16, 16, 12};
  SoundProcess(melody, tempo, 3);
}
//----------------------------------------------------------------------------------//
void Sound_Beep2()
{
  int melody[] = {167, 593};
  int tempo[] = {64, 8};

  SoundProcess(melody, tempo, 2);
}
void Sound_Beep3()
{
  int melody[] = {167, 314};
  int tempo[] = {64, 8};

  SoundProcess(melody, tempo, 2);
}
void batteryPowerBeep()
{
  int melody[] = {2437, 1968, 1216, 900};
  int tempo[] = {25, 25, 25, 25};
  SoundProcess(melody, tempo, 3);
}

//----------------------------------------------------------------------------------//

void Sound_Coin()
{
  int melody[] = {988, 1319};
  int tempo[] = {16, 2};
  SoundProcess(melody, tempo, 2);
}
//----------------------------------------------------------------------------------//

void Sound_FireBall()
{
  int melody[] = {392, 784, 1568};
  int tempo[] = {36, 36, 36};
  SoundProcess(melody, tempo, 3);
}
