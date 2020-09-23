#ifndef _EmailSender_
#define _EmailSender_

#include <String>
#include "ESP32_MailClient.h"
#include "SPIFFS.h"

class EmailSender {
  public:
    EmailSender();
    void Begin(String smtpServer_, uint16_t smtpServerPort_, String emailSenderAccount_, String emailSenderPassword_);
    void Send(String emailSubject, String message, String emailRecipient);
    void SendWithFile(String emailSubject, String message, String emailRecipient, String filePath);

  private:
    SMTPData smtpData;
    String smtpServer;
    uint16_t smtpServerPort;
    String emailSenderAccount;
    String emailSenderPassword;

};

#endif /*_EmailSender_*/
