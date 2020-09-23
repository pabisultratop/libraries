#ifndef _MP3Player_
#define _MP3Player_

#include "DFRobotDFPlayerMini.h" // lib player

#define MP3_RX_PIN 4
#define MP3_TX_PIN 2

//DEFINIÇÕES DA MENSAGENS DE AÚDIO
enum MESSAGES
{
  MSG_0001,
  MSG_0002,
  MSG_0003,
  MSG_0004,
  MSG_0005,
  MSG_0006,
  MSG_0007,
  MSG_0008,
  MSG_0009,
  MSG_0010
};

class MP3Player {
  public:
    MP3Player(int RX_PIN = MP3_RX_PIN, int TX_PIN = MP3_TX_PIN);
    int Begin();
    void PlayMessage(int msg);
    void PauseMessage();
    void SetVolume(int volume);

  private:
    int RX_PIN, TX_PIN;
    DFRobotDFPlayerMini myDFPlayer;
};

#endif /*_MP3Player_*/
