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
    byte error;
    error = Wire.endTransmission();
    if(error != 0) {                               // If your device is 0x3F
      lcd = LiquidCrystal_I2C(0x3F,20,4);
    }
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

int i = 0;
char buf[20];
char buf2[20];

void loop()
{
  char key = keypad.getKey();

  if (key)
  {
    buf[i] = key;
    buf[i+1] = '\0';
    if (i == 1)
    {
      char * pEnd;
      int tmpNum = strtol(buf, &pEnd, 10);
      if (pEnd != buf)
      {
        int celsius = 5.0/9.0 * static_cast<double>(tmpNum-32) + 0.5;
        itoa(celsius, buf2, 10);
        strcat(buf, "F = ");
        strcat(buf, buf2);
        strcat(buf, "C.");
        printer.print(buf);
        buf[0] = '\0';
        buf2[0] = '\0';
      }
    } else
    {
      printer.print(buf);
    }
    i = (i + 1) % 2;
  }
}