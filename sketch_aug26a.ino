#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte pin_rows[ROW_NUM] = {3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {0, 1, 2}; //connect to the column pinouts of the keypad


Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void printToLcd(const char *str)
{
  byte error;
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  if(error == 0) {                      // If your device is 0x27
    LiquidCrystal_I2C lcd(0x27,20,4);
    lcd.init(); 
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print(str);
  } else {                               // If your device is 0x3F
    LiquidCrystal_I2C lcd(0x3F,20,4);
    lcd.init(); 
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print(str);
  }
}

class WirePrinter
{
  public:
  WirePrinter() : lcd(0x27,20,4)
  {

  }
  void init()
  {
    Wire.begin();
    Wire.beginTransmission(0x27);
    lcd.init(); 
    lcd.backlight();
    lcd.setCursor(0,0);
  }
  void print(const char str[])
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(str);
  }
  private:
  LiquidCrystal_I2C lcd;
};


WirePrinter printer;

void setup()
{
  printer.init();
  printer.print("Enter a key");
}

char buf[10];
void loop()
{
  char key = keypad.getKey();

  if (key)
  {
    buf[0] = key;
    buf[1] = '\0';
    printer.print(buf);
  }
}