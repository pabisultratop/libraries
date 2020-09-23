#include "EmailSender.h"

EmailSender::EmailSender()
{
}

void EmailSender::Begin(String smtpServer_, uint16_t smtpServerPort_, String emailSenderAccount_, String emailSenderPassword_)
{
  smtpServer = smtpServer_; 
  smtpServerPort = smtpServerPort_; 
  emailSenderAccount = emailSenderAccount_;
  emailSenderPassword = emailSenderPassword_;
}

// Callback function to get the Email sending status
void sendCallback(SendStatus msg) {
  // Print the current status
  Serial.println(msg.info());

  // Do something when complete
  if (msg.success()) {
    Serial.println("----------------");
  }
}

void EmailSender::Send(String emailSubject, String message, String emailRecipient)
{
  // Set the SMTP Server Email host, port, account and password
  smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);

  // For library version 1.2.0 and later which STARTTLS protocol was supported,the STARTTLS will be
  // enabled automatically when port 587 was used, or enable it manually using setSTARTTLS function.
  //smtpData.setSTARTTLS(true);

  // Set the sender name and Email
  smtpData.setSender("CABINE", emailSenderAccount);

  // Set Email priority or importance High, Normal, Low or 1 to 5 (1 is highest)
  smtpData.setPriority("High");
  
  // Set the subject
  smtpData.setSubject(emailSubject);

  // Set the message with HTML format
  smtpData.setMessage(message, true);
  //"<div style=\"color:#2f4468;\"><h1>Hello World!</h1><p>- Sent from ESP32 board</p></div>"
  // Set the email message in text format (raw)
  //smtpData.setMessage("Hello World! - Sent from ESP32 board", false);

  // Add recipients, you can add more than one recipient
  smtpData.addRecipient(emailRecipient);
  //smtpData.addRecipient("YOUR_OTHER_RECIPIENT_EMAIL_ADDRESS@EXAMPLE.com");

  //smtpData.setSendCallback(sendCallback);

  //Start sending Email, can be set callback function to track the status
  MailClient.sendMail(smtpData);
  //if (!MailClient.sendMail(smtpData))
  //Serial.println("Error sending Email, " + MailClient.smtpErrorReason());

  //Clear all data from Email object to free memory
  smtpData.empty();
}

void EmailSender::SendWithFile(String emailSubject, String message, String emailRecipient, String filePath)
{
  // Set the SMTP Server Email host, port, account and password
  smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);

  // For library version 1.2.0 and later which STARTTLS protocol was supported,the STARTTLS will be
  // enabled automatically when port 587 was used, or enable it manually using setSTARTTLS function.
  //smtpData.setSTARTTLS(true);

  // Set the sender name and Email
  smtpData.setSender("BS 0 TEST", emailSenderAccount);

  // Set Email priority or importance High, Normal, Low or 1 to 5 (1 is highest)
  smtpData.setPriority("High");
  
  // Set the subject
  smtpData.setSubject(emailSubject);

  // Set the message with HTML format
  smtpData.setMessage(message, true);
  //"<div style=\"color:#2f4468;\"><h1>Hello World!</h1><p>- Sent from ESP32 board</p></div>"
  // Set the email message in text format (raw)
  //smtpData.setMessage("Hello World! - Sent from ESP32 board", false);

  // Add recipients, you can add more than one recipient
  smtpData.addRecipient(emailRecipient);
  //smtpData.addRecipient("YOUR_OTHER_RECIPIENT_EMAIL_ADDRESS@EXAMPLE.com");

  // Add attach files from SD card or SPIFFS
  // Comment the next two lines, if no SPIFFS files created or SD card connected
  smtpData.addAttachFile(filePath, "image/jpg");
  //smtpData.addAttachFile("/fever.txt");

  // Set the storage type to attach files in your email (SPIFFS or SD Card)
  smtpData.setFileStorageType(MailClientStorageType::SPIFFS);
  //smtpData.setFileStorageType(MailClientStorageType::SD);

  smtpData.setSendCallback(sendCallback);
  
  //Start sending Email, can be set callback function to track the status
  //MailClient.sendMail(smtpData);
  if (!MailClient.sendMail(smtpData))
      Serial.println("Error sending Email, " + MailClient.smtpErrorReason());

  //Clear all data from Email object to free memory
  smtpData.empty();
}
