//这是别人写的，仅作参考

double Fahrenheit(double celsius) 
{
        return 1.8 * celsius + 32;
}    //摄氏温度度转化为华氏温度
 
double Kelvin(double celsius)
{
        return celsius + 273.15;
}     //摄氏温度转化为开氏温度
 
// 露点（点在此温度时，空气饱和并产生露珠）
// 参考: [url=http://wahiduddin.net/calc/density_algorithms.htm]http://wahiduddin.net/calc/density_algorithms.htm[/url] 
double dewPoint(double celsius, double humidity)
{
        double A0= 373.15/(273.15 + celsius);
        double SUM = -7.90298 * (A0-1);
        SUM += 5.02808 * log10(A0);
        SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
        SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
        SUM += log10(1013.246);
        double VP = pow(10, SUM-3) * humidity;
        double T = log(VP/0.61078);   // temp var
        return (241.88 * T) / (17.558-T);
}
 
// 快速计算露点，速度是5倍dewPoint()
// 参考: [url=http://en.wikipedia.org/wiki/Dew_point]http://en.wikipedia.org/wiki/Dew_point[/url]
double dewPointFast(double celsius, double humidity)
{
        double a = 17.271;
        double b = 237.7;
        double temp = (a * celsius) / (b + celsius) + log(humidity/100);
        double Td = (b * temp) / (a - temp);
        return Td;
}
 
#include <dht11.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
 
dht11 DHT11;
 
#define DHT11PIN 8
 
void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.print("Waiting...");
  Serial.begin(9600); 
}
void loop()
{
  int chk = DHT11.read(DHT11PIN);
 
  switch (chk)
  {
    case DHTLIB_OK: 
                lcd.setCursor(0, 0);
                lcd.print("Temp:");
                lcd.print((float)DHT11.temperature,2);
                lcd.write(0xDF);
                lcd.print("C");
 
                lcd.setCursor(0, 1);
                lcd.print("Humidity:");
                lcd.print((float)DHT11.humidity,2);
                lcd.print("%");
 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                lcd.clear();
                lcd.print("Checksum error"); 
                delay(1000);  
                lcd.clear();
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                lcd.clear();
                lcd.print("Time out error"); 
                delay(1000);             
                lcd.clear();
                break;
    default: 
                lcd.clear();
                lcd.print("Unknown error"); 
                delay(1000);                
                lcd.clear();
                break;
  }
  delay(1000);
}


