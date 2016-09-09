/*************************************************
  NAVMENU
 ************************************************/

void NavMenu() {

  long newPosition = myEnc->read();
  Serial.println(newPosition);

  if (newPosition != oldPosition) {
    homeTimer = millis();
    oldPosition = newPosition;
    if (Counter + 4 <= newPosition) {
      Counter = newPosition;
      encoderValue++;
      if (encoderValue > 1) {
        encoderValue = -1;
      }
      Display_NavMenu();
    }
    else if (Counter - 4 >= newPosition) {
      Counter = newPosition;
      encoderValue--;
      if (encoderValue < -1) {
        encoderValue = 1;
      }
      Display_NavMenu();
    }

  }


}

/*************************************************
  NAVMENU2
 ************************************************/

void NavMenuTwo() {

  long newPosition = myEnc->read();

  if (newPosition != oldPosition) {
    homeTimer = millis();
    oldPosition = newPosition;
    if (Counter + 4 <= newPosition) {
      Counter = newPosition;
      encoderValue++;
      if (encoderValue > 1) {
        encoderValue = -1;
      }
      Display_NavMenuTwo();
    }
    else if (Counter - 4 >= newPosition) {
      Counter = newPosition;
      encoderValue--;
      if (encoderValue < -1) {
        encoderValue = 1;
      }
      Display_NavMenuTwo();
    }

  }


}

/*************************************************
  SET TEMP
 ************************************************/
void SetTemp() {

  long newPosition = myEnc->read();

  if (newPosition != oldPosition) {
    oldPosition = newPosition;

    if (Counter + 4 <= newPosition) {
      encoderValue--;
      Counter = newPosition;
      Display_SetTemp(encoderValue);
    }
    else if (Counter - 4 >= newPosition) {
      encoderValue++;
      Counter = newPosition;
      Display_SetTemp(encoderValue);
    }
  }
}


/*************************************************
  BUTTON PRESSED
 ************************************************/

void ButtonPressed() {
  if(millis()-lastPressed<100){
    return;
  }
  lastPressed=millis();
  Serial.println("Pressed");

  if (STATE == 0) {
    STATE = 1;
    encoderValue = 0;
    Display_NavMenu();
  }

  else if (STATE == 1) {
    if (encoderValue == 1) {
      STATE = 2;
      encoderValue = 0;
      Display_NavMenuTwo();
    }
    else if (encoderValue != 1) {
      Serial.println(encoderValue);
      STATE = 5;
    }
  }

  else if (STATE == 2) {
    if (encoderValue == 1) {
      STATE = 3;
      encoderValue = 20 ;
      tft.fillScreen(ST7735_BLACK);
      Display_SetTemp(encoderValue);
    }
    else if (encoderValue == -1) {
      STATE = 0;
      Serial.println(encoderValue);
      encoderValue = 0 ;
      tempSetted = false;
      displayHome();
    }
    else if (encoderValue == 0) {
      STATE = 0;
      encoderValue = 0 ;
      tempSetted = true;
      displayHome();
    }
  }

  else if (STATE == 3) {
    desiredTemp = encoderValue;
    tempSetted = true;
    STATE = 4;
    encoderValue = 0 ;
  }

  else if (STATE == 7) {
    STATE = 8;    
  }
}

/*************************************************
  GET TEMP
 ************************************************/

int GetTemp() {
  int  t = dht.readTemperature(); // Read temperature as Celsius (the default)
  return t;
}
