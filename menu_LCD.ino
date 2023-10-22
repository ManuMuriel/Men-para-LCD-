#include <Wire.h>
#include <LiquidCrystal_I2C.h>

byte customChar[8] = {
  0b00000,
  0b00010,
  0b00110,
  0b01110,
  0b11110,
  0b01110,
  0b00110,
  0b00010
};


LiquidCrystal_I2C lcd(0x27, 16, 2);  

const int menuButtonPin = 4;
const int selectButtonPin = 5;
int menuOption = 0;
bool inMenu = true;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(menuButtonPin, INPUT_PULLUP);
  pinMode(selectButtonPin, INPUT_PULLUP);
  displayMenu();
}

void loop() {
  if (inMenu) {
    if (digitalRead(menuButtonPin) == LOW) {
      menuOption = (menuOption + 1) % 3;  
      displayMenu();
      delay(200);  // Debounce
    }
    if (digitalRead(selectButtonPin) == LOW) {
      displaySubMenu();
    }
  } else {
    if (digitalRead(selectButtonPin) == LOW) {
      inMenu = true;
      lcd.clear();
      displayMenu();
    }
  }
}

void displayMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Seleccione:");
  lcd.setCursor(0, 1);
  
  switch (menuOption) {
    case 0:
      lcd.print("> VOLTAJE");
      break;
    case 1:
      lcd.print("> CORRIENTE");
      break;
    case 2:
      lcd.print("> POTENCIA");
      break;
  }
}

void displaySubMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  
  switch (menuOption) {
    case 0:
      lcd.print("  Voltaje pico");
      delay(2000);  
      lcd.clear();
      lcd.print("  Voltaje RMS");
      delay(2000);  
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("para volver");
      lcd.createChar(0, customChar);  
      lcd.setCursor(0, 0);  
      lcd.write(0);  
      lcd.print("Pulsa");
      break;
    case 1:
      lcd.print(" Corriente max");
      delay(2000);  
      lcd.clear();
      lcd.print(" Corriente RMS");
      delay(2000);  
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("para volver");
      lcd.createChar(0, customChar);  
      lcd.setCursor(0, 0);  
      lcd.write(0);  
      lcd.print("Pulsa");
      break;
    case 2:
      lcd.print(" Pot Aparente");
      delay(2000);  
      lcd.clear();
      lcd.print("  Pot Activa");
      delay(2000);  
      lcd.clear();
      lcd.print("  Pot Reactiva");
      delay(2000);  
      lcd.clear();
      lcd.print(" Factor de Pot");
      delay(2000);  
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("para volver");
      lcd.createChar(0, customChar);  
      lcd.setCursor(0, 0);  
      lcd.write(0);  
      lcd.print("Pulsa");
      break;
  }
}






