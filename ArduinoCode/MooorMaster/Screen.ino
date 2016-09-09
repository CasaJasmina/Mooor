/*************************************************
  DISPLAY HOME
 ************************************************/

void displayHome() {
  tempflag = false;
  String date = String(rtc.getDay()) + "/" + String(rtc.getMonth()) + "/" + String(rtc.getYear()) ;
  String time = String(rtc.getHours()) + ":" + String(rtc.getMinutes());
  tft.setRotation(1);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print(time);
  tft.setCursor(10, 40);
  tft.print("Tmp ");
  tft.print(temp);
  tft.print(" C");
  tft.setTextSize(1.5);
  tft.setCursor(110, 110);
  tft.println(date);

  if ( tempSetted == true) {
    tft.setCursor(10, 80);
    tft.print("Desired temperature:");
    tft.print(desiredTemp);
    tft.print(" C");
  }
}

/*************************************************
  DISPLAY NAV-MENU
 ************************************************/
void Display_NavMenu() {


  switch (encoderValue) {
    case 1:
      tft.fillScreen(ST7735_BLACK);
      tft.fillRect(10, 10, 140, 35, ST7735_WHITE);
      tft.setCursor(20, 20);
      tft.setTextSize(2);
      tft.setTextColor(ST7735_BLACK);
      tft.println("THERMOSTAT");

      tft.drawRect(10, 50, 140, 35, ST7735_WHITE);
      tft.setCursor(30, 60);
      tft.setTextColor(ST7735_WHITE);
      tft.println("MESSAGES");

      tft.drawRect(10, 90, 140, 35, ST7735_WHITE);
      tft.setCursor(17, 100);
      tft.println("DOOR OPENER");

      break;

    case 0:

      tft.fillScreen(ST7735_BLACK);
      tft.setTextSize(2);
      tft.drawRect(10, 10, 140, 35, ST7735_WHITE);
      tft.setCursor(20, 20);
      tft.setTextColor(ST7735_WHITE);
      tft.println("THERMOSTAT");

      tft.fillRect(10, 50, 140, 35, ST7735_WHITE);
      tft.setCursor(30, 60);
      tft.setTextColor(ST7735_BLACK);
      tft.println("MESSAGES");

      tft.drawRect(10, 90, 140, 35, ST7735_WHITE);
      tft.setCursor(17, 100);
      tft.setTextColor(ST7735_WHITE);
      tft.println("DOOR OPENER");
      break;

    case -1:
      tft.fillScreen(ST7735_BLACK);
      tft.setTextSize(2);
      tft.drawRect(10, 10, 140, 35, ST7735_WHITE);
      tft.setCursor(20, 20);
      tft.setTextColor(ST7735_WHITE);
      tft.println("THERMOSTAT");

      tft.drawRect(10, 50, 140, 35, ST7735_WHITE);
      tft.setCursor(30, 60);
      tft.setTextColor(ST7735_WHITE);
      tft.println("MESSAGES");

      tft.fillRect(10, 90, 140, 35, ST7735_WHITE);
      tft.setCursor(17, 100);
      tft.setTextColor(ST7735_BLACK);
      tft.println("DOOR OPENER");
      break;

  }
}


/*************************************************
  DISPLAY NAV-MENU TWO
 ************************************************/
void Display_NavMenuTwo() {


  switch (encoderValue) {
    case 1:
      tft.fillScreen(ST7735_BLACK);
      tft.fillRect(10, 10, 140, 35, ST7735_WHITE);
      tft.setCursor(30, 20);
      tft.setTextSize(2);
      tft.setTextColor(ST7735_BLACK);
      tft.println("SET TEMP");

      tft.drawRect(10, 50, 140, 35, ST7735_WHITE);
      tft.setCursor(20, 60);
      tft.setTextColor(ST7735_WHITE);
      tft.println("TURN IT ON");

      tft.drawRect(10, 90, 140, 35, ST7735_WHITE);
      tft.setCursor(17, 100);
      tft.println("TURN IT OFF");

      break;

    case 0:

      tft.fillScreen(ST7735_BLACK);
      tft.setTextSize(2);
      tft.drawRect(10, 10, 140, 35, ST7735_WHITE);
      tft.setCursor(30, 20);
      tft.setTextColor(ST7735_WHITE);
      tft.println("SET TEMP");

      tft.fillRect(10, 50, 140, 35, ST7735_WHITE);
      tft.setCursor(20, 60);
      tft.setTextColor(ST7735_BLACK);
      tft.println("TURN IT ON");

      tft.drawRect(10, 90, 140, 35, ST7735_WHITE);
      tft.setCursor(17, 100);
      tft.setTextColor(ST7735_WHITE);
      tft.println("TURN IT OFF");
      break;

    case -1:
      tft.fillScreen(ST7735_BLACK);
      tft.setTextSize(2);
      tft.drawRect(10, 10, 140, 35, ST7735_WHITE);
      tft.setCursor(30, 20);
      tft.setTextColor(ST7735_WHITE);
      tft.println("SET TEMP");

      tft.drawRect(10, 50, 140, 35, ST7735_WHITE);
      tft.setCursor(20, 60);
      tft.setTextColor(ST7735_WHITE);
      tft.println("TURN IT ON");

      tft.fillRect(10, 90, 140, 35, ST7735_WHITE);
      tft.setCursor(17, 100);
      tft.setTextColor(ST7735_BLACK);
      tft.println("TURN IT OFF");
      break;

  }
}

/*************************************************
  DISPLAY SET TEMP
 ************************************************/

void Display_SetTemp(int temp) {
  tft.setRotation(1);
  tft.setCursor(10, 20);
  tft.setTextSize(2);
  tft.println("Setting Temp");
  tft.setCursor(40, 60);
  tft.print(" C");

  tft.fillRect(10, 60, 39, 80, ST7735_BLACK);
  tft.setCursor(10, 60);
  tft.setTextColor(ST7735_WHITE);
  tft.print(temp);

}

/*************************************************
  DISPLAY CONFIRM
 ************************************************/

void Display_Confirm() {
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  tft.setCursor(10, 20);
  tft.setTextSize(2);
  tft.println("Done!");
  tft.println("You just set");
  tft.println("the temperature to");
  tft.setCursor(10, 100);
  tft.print(desiredTemp);
  tft.println(" C");

  delay(2000);
  STATE = 0;
  displayHome();
}


/*************************************************
  DISPLAY NOT IMPLEMENTED
 ************************************************/
void Display_NotImplemented() {
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  tft.setCursor(10, 20);
  tft.setTextSize(2);
  tft.println("Not yet");
  tft.setCursor(10, 40);
  tft.println("implemented");
  tft.setCursor(10, 60);
  tft.println(":(");

  delay(2000);
  STATE = 0;
  displayHome();
}


/*************************************************
  DISPLAY DOORBELL
 ************************************************/

void Display_Doorbell() {
  tft.setRotation(0);
  bmpDraw("test.bmp", 0, 0);
}

/*************************************************
  DISPLAY PHONE
 ************************************************/

void Display_Phone() {
  tft.setRotation(0);
  bmpDraw("phone.bmp", 0, 0);
}

/*************************************************
  DISPLAY GATE
 ************************************************/

void Display_Gate() {
  tft.setRotation(0);
  bmpDraw("gate.bmp", 0, 0);
  delay(2000);
  STATE = 0;
  displayHome();
}
