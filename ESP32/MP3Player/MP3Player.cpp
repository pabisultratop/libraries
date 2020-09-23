#include "MP3Player.h"

MP3Player::MP3Player(int RX_PIN, int TX_PIN)
{
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
}

int MP3Player::Begin()
{
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(Serial2)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    return 0;
  }
  Serial.println(F("DFPlayer Mini online."));

  //----Set different EQ----
  //  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.EQ(DFPLAYER_EQ_POP);
  //  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
  //  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
  //  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
  //  myDFPlayer.EQ(DFPLAYER_EQ_BASS);
  return 1;
}

void MP3Player::PlayMessage(int msg)
{
  myDFPlayer.playMp3Folder(msg + 1); //play specific mp3 in SD:/MP3/0001.mp3; File Name(0~65535)
}

void MP3Player::PauseMessage()
{
  myDFPlayer.pause();
}

void MP3Player::SetVolume(int volume)
{
  myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
}
