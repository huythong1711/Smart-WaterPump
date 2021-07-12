#include <virtuabotixRTC.h>
#include "DHT.h" 
const int DHTPIN = 3; 
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);
// Khai báo hàm
virtuabotixRTC myRTC(6, 7, 8); // CLK6, DAT7, RST8
int CBAS = A0; // cảm biến ánh sáng
int GTCBAS; // giá trị cảm biến ánh sáng
int GTCBDAD, TBDAD; // giá trị cảm biến độ ẩm đất, trung bình độ ẩm đất
int CBDAD = A1; // cảm biến độ ẩm đất
int RLBD = 12; // relay bóng đèn quang hợp
int RLMB = 11; // relay máy bơm
int MB = 9;
int BD = 10;
int GTMB;
int GTBD;
void setup()
{
  Serial.begin(9600);
  dht.begin(); 
  //myRTC.setDS1302Time(00, 25, 13, 6, 25, 6, 2021); // thay đổi ngày,tháng,năm
  pinMode(CBAS, INPUT); 
  pinMode(CBDAD, INPUT);
  pinMode(RLBD, OUTPUT);
  pinMode(RLMB, OUTPUT);
  pinMode(MB, INPUT);
  pinMode(BD, INPUT);
  digitalWrite(RLBD, LOW); // tắt relay bóng đèn quang hợp
  digitalWrite(RLMB, LOW); // tắt relay máy bơm
}
void loop()
{
  myRTC.updateTime();
  Serial.print("Current Date / Time: ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);
  // Các hàm ngày tháng giờ năm .... hiện trên cổng COM
  float h = dht.readHumidity();
  delay(500);
  GTCBAS = analogRead(CBAS);
  GTMB = digitalRead(MB);
  GTBD = digitalRead(BD);

  for(int i=0;i<=9;i++)   /*Chúng ta sẽ tạo một hàm for để đọc 10 lần giá trị cảm biến, 
                            sau đó lấy giá trị trung bình để được giá trị chính xác nhất.*/
 {
  GTCBDAD += analogRead(CBDAD);     
 }
    TBDAD=GTCBDAD/10;     //Tính giá trị trung bình
    
    
    int phantramao = map(TBDAD, 0, 1023, 0, 100);    //Chuyển giá trị Analog thành giá trị %
    int phantramthuc = 100 - phantramao;              //Tính giá trị phần trăm thực, chuyển điện thế khô thành ẩm
    
    Serial. print("analog: "); Serial. print(TBDAD); Serial.print(" "); Serial. print("~"); Serial.print(" "); 
    Serial.print(phantramthuc); Serial.println('%'); 
    delay (500);
    GTCBDAD=0;
if ( 45 < phantramthuc || h < 70 || GTMB == 1 )
      
{
digitalWrite(RLMB, HIGH);
}   
else if ( phantramthuc > 80 || h > 80 || GTBD == 0 )
{
digitalWrite(RLMB, LOW);
}
if ( GTCBAS < 400 || GTBD == 1 )
{
  digitalWrite(RLBD, HIGH);
}
else if ( GTCBAS > 400 || GTBD == 0)
{
  digitalWrite(RLBD, LOW);
}
if (myRTC.hours == 6 && myRTC.minutes == 00 && myRTC.seconds == 00 || myRTC.hours == 10 && myRTC.minutes == 00 && myRTC.seconds == 00 )
{
 digitalWrite(RLMB, HIGH);
}
else if (myRTC.hours == 06 && myRTC.minutes == 30 && myRTC.seconds == 00 || myRTC.hours == 18&& myRTC.minutes == 30 && myRTC.seconds == 00 )
{
 digitalWrite(RLMB, LOW);
}
if ( myRTC.hours == 19 && myRTC.minutes == 00 && myRTC.seconds == 00)
{
  digitalWrite(RLBD,HIGH);
}
else if ( myRTC.hours == 05 && myRTC.minutes == 30 && myRTC.seconds == 00)
{
  digitalWrite(RLBD, LOW);
}
}
