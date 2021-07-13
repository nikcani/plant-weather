#include <Arduino.h>
#include <WiFi.h>
#include <ESP_Mail_Client.h>
#include <Wire.h>
#include <rgb_lcd.h>
#include <arduino_secrets.h>

#define PIN_NO_LED 14
#define PIN_NO_BUTTON 26
#define PIN_NO_DISPLAY_SDA 17
#define PIN_NO_DISPLAY_SCL 16

volatile bool buttonState = false;
rgb_lcd lcd;
char messageBuffer[50];
int threshold = 10;

void buttonClicked() {
    buttonState = digitalRead(PIN_NO_BUTTON);
}

void listNetworks() {
    // scan for nearby networks:
    Serial.println("** Scan Networks **");
    int numSsid = WiFi.scanNetworks();
    if (numSsid == -1) {
        Serial.println("Couldn't get a wifi connection");
        while (true);
    }

    // print the list of networks seen:
    Serial.print("number of available networks:");
    Serial.println(numSsid);

    // print the network number and name for each network found:
    for (int thisNet = 0; thisNet < numSsid; thisNet++) {
        Serial.print(thisNet);
        Serial.print(") ");
        Serial.print(WiFi.SSID(thisNet));
        Serial.print("\tSignal: ");
        Serial.print(WiFi.RSSI(thisNet));
        Serial.print(" dBm");
        Serial.print("\tEncryption: ");
        Serial.println(WiFi.encryptionType(thisNet));
    }

    Serial.println("---");
    Serial.print("localIP: ");
    Serial.print(WiFi.localIP());
    Serial.println();
    Serial.print("subnetMask: ");
    Serial.print(WiFi.subnetMask());
    Serial.println();
    Serial.print("gatewayIP: ");
    Serial.print(WiFi.gatewayIP());
    Serial.println();
    Serial.print("RSSI: ");
    Serial.print(WiFi.RSSI());
    Serial.println();
}

void printToLCD() {
    lcd.clear();
    lcd.setRGB(150, 0, 0);
    lcd.setCursor(0, 0);
    lcd.print("Plant Weather");
    lcd.setCursor(0, 1);
    lcd.print(messageBuffer);
}

void sendMail() {
    SMTPSession smtp;
    ESP_Mail_Session session;
    SMTP_Message message;
    session.server.host_name = SECRET_MAIL_HOST;
    session.server.port = SECRET_MAIL_PORT;
    session.login.email = SECRET_MAIL_USER;
    session.login.password = SECRET_MAIL_PASS;
    // session.login.user_domain = "client domain or ip e.g. mydomain.com";

    message.sender.name = "Plant Weather";
    message.sender.email = "plant@weather.io";
    message.subject = "Testmeldung";
    message.addRecipient(SECRET_USER_NAME, SECRET_USER_MAIL);
    message.text.content = "Lorem ipsum";

    smtp.connect(&session);

    if (!MailClient.sendMail(&smtp, &message)) {
        Serial.println("Error sending Email, " + smtp.errorReason());
    }
}

void setup() {
    pinMode(PIN_NO_LED, OUTPUT);
    digitalWrite(PIN_NO_LED, LOW);

    pinMode(PIN_NO_BUTTON, INPUT);
    attachInterrupt(PIN_NO_BUTTON, buttonClicked, CHANGE);

    Serial.begin(9600);

    WiFi.begin(SECRET_WIFI_SSID, SECRET_WIFI_PASS);

    Wire.begin(PIN_NO_DISPLAY_SDA, PIN_NO_DISPLAY_SCL);

    lcd.begin(PIN_NO_DISPLAY_SCL, 2);
    sprintf(messageBuffer, "Threshold: %i", threshold);
    printToLCD();
}

void loop() {
    digitalWrite(PIN_NO_LED, buttonState);

    if (buttonState) {
        sprintf(messageBuffer, "button pressed");
        printToLCD();

        listNetworks();

        sendMail();
        sprintf(messageBuffer, "mail sent");
        printToLCD();

        delay(2000);
        sprintf(messageBuffer, "");
        printToLCD();
    }
}
